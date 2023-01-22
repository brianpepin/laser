#include <Arduino.h>
#include <SPI.h>
#include "MAX20096.h"

//=------------------------------------------------------
// MAX20096 Protocol Definitions
//=------------------------------------------------------

// Registers / commands
#define CMD_NO_OP       0x00
#define CMD_CNFG_SPI    0x01
#define CMD_CNFG_GEN    0x02
#define CMD_CNFG_CRNT1  0x03
#define CMD_CNFG_CRNT2  0x04
#define CMD_CNFG_TMNG   0x05
#define CMD_CNFG_PWM1   0x06
#define CMD_CNFG_PWM2   0x07
#define CMD_MON_VBUCK1  0x0A
#define CMD_MON_VBUCK2  0x0B
#define CMD_MON_LED1    0x0C
#define CMD_MON_LED2    0x0D
#define CMD_MON_TEMP    0x0E
#define CMD_GEN_STAT    0x0F

// Read / write command structure

union COMMAND
{
    struct
    {
        uint16_t Data       : 10;
        uint16_t Parity     : 1;
        uint16_t Address    : 4;
        uint16_t Read       : 1;
    } s;
    uint16_t v;    
};

// All data payloads have this as a
// header.

union COMMAND_STAT
{
    struct
    {
        uint16_t Unused_0   : 10;
        uint16_t PARITY     : 1;
        uint16_t STAT       : 4;
        uint16_t SPI_ERR    : 1;
    } s;
    uint16_t v;    
};

// Bitfields for status registers

union REG_NO_OP
{
    struct
    {
        uint16_t SDO_TEST   : 4;
        uint16_t REV_ID     : 6;
        uint16_t Unused_0   : 6;
    } s;
    uint16_t v;
};

union REG_CNFG_SPI
{
    struct
    {
        uint16_t SFT_SDI    : 1;
        uint16_t SFT_CLK    : 1;
        uint16_t SFT_CSB    : 1;
        uint16_t SFT_RB     : 1;
        uint16_t ST_AB      : 1;
        uint16_t DCHN       : 1;
        uint16_t HW_RST     : 1;
        uint16_t RW_ERR     : 1;
        uint16_t PAR_ERR    : 1;
        uint16_t CLK_ERR    : 1;
        uint16_t Unused_0   : 6;
    } s;
    uint16_t v;
};

union REG_CNFG_GEN
{
    struct
    {
        uint16_t PWM_FREQ   : 3;
        uint16_t Unused_1   : 1;
        uint16_t BUCK2_EN   : 1;
        uint16_t BUCK1_EN   : 1;
        uint16_t PWM2_SEL   : 1;
        uint16_t PWM1_SEL   : 1;
        uint16_t CNFG_SEL   : 1;
        uint16_t Unused_0   : 7;
    } s;
    uint16_t v;
};

union REG_CNFG_CRNT
{
    struct
    {
        uint16_t ILED       : 7;
        uint16_t Unused_1   : 1;
        uint16_t VSHORT     : 2;
        uint16_t Unused_0   : 6;
    } s;
    uint16_t v;
};

union REG_CNFG_TMNG
{
    struct
    {
        uint16_t DLY2       : 4;
        uint16_t DLY1       : 4;
        uint16_t TM_OUT     : 2;
        uint16_t Unused_0   : 6;
    } s;
    uint16_t v;    
};

union REG_CNFG_PWM
{
    struct
    {
        uint16_t PWM_DUTY   : 10;
        uint16_t Unused_0   : 6;
    } s;
    uint16_t v;
};

union REG_MON_VBUCK
{
    struct
    {
        uint16_t VBUCK      : 8;
        uint16_t EXCEPT     : 1;
        uint16_t Unused_0   : 7;
    } s;
    uint16_t v;    
};

union REG_MON_LED
{
    struct
    {
        uint16_t IMON       : 8;
        uint16_t Unused_0   : 8;
    } s;
    uint16_t v;    
};

union REG_MON_TEMP
{
    struct
    {
        uint16_t TEMP       : 8;
        uint16_t Unused_0   : 8;
    } s;
    uint16_t v;    
};

union REG_GEN_STAT
{
    struct
    {
        uint16_t OPEN2      : 1;
        uint16_t SHORT2     : 1;
        uint16_t OVERC2     : 1;
        uint16_t OVP2       : 1;
        uint16_t OPEN1      : 1;
        uint16_t SHORT1     : 1;
        uint16_t OVERC1     : 1;
        uint16_t OVP1       : 1;
        uint16_t TH_WARN    : 1;
        uint16_t TH_SHDN    : 1;
        uint16_t Unused_0   : 6;
    } s;
    uint16_t v;
};

static bool calcParity(uint16_t value)
{
    uint16_t v = value;
    bool parity = 0;

    for (int bit = 0; bit < 16; bit++)
    {
        parity = parity ^ (v & 1);
        v = v >> 1;
    }

    return !parity;
}

static float calcTemp(uint8_t reading)
{
    //  TJ = ((TEMP[7:0] x 523)/255) - 272°C
    return (float)reading * 523.0 / 255.0 - 272;        
}

MAX20096::MAX20096(uint8_t csPin, uint8_t resetPin, float rcs, uint32_t rvd1, uint32_t rvd2) :
    _cs(csPin),
    _reset(resetPin),
    _rcs(rcs),
    _rvd1(rvd1),
    _rvd2(rvd2)
{
    pinMode(_reset, OUTPUT);
    pinMode(_cs, OUTPUT);
    digitalWrite(_cs, HIGH);
    digitalWrite(_reset, HIGH);
}

bool MAX20096::reset()
{
    // Assert RESETB and setup SPI.

    digitalWrite(_reset, LOW);
    delayMicroseconds(1);
    digitalWrite(_reset, HIGH);
    delayMicroseconds(1);

    // Execute a no op to ensure comms are working.
    // SDO_TEST comes back as 9 if everything is
    // OK.

    REG_NO_OP noOp;
    read(CMD_NO_OP, noOp.v);

    if (noOp.s.SDO_TEST != 0b1001)
    {
        return false;
    }

    // Configure part to be controlled
    // via software

    REG_CNFG_GEN cfg = {};
    cfg.s.CNFG_SEL = 1;
    cfg.s.PWM1_SEL = 1;
    cfg.s.PWM2_SEL = 1;
    cfg.s.PWM_FREQ = 0b110; // 2Khz
    cfg.s.BUCK1_EN = 0;
    cfg.s.BUCK2_EN = 0;

    write(CMD_CNFG_GEN, cfg.v);

    // Default PWM to be a full duty cycle.

    REG_CNFG_PWM pwm = {};
    pwm.s.PWM_DUTY = 1000;

    write(CMD_CNFG_PWM1, pwm.v);
    write(CMD_CNFG_PWM2, pwm.v);

    return true;
}

MAX20096::Status MAX20096::getStatus()
{
    Status status = {};

    REG_MON_VBUCK vbuck;
    read(CMD_MON_VBUCK1, vbuck.v);
    status.led1.exception = vbuck.s.EXCEPT;
    status.led1.voltage = calcVoltage(vbuck.s.VBUCK);

    read(CMD_MON_VBUCK2, vbuck.v);
    status.led2.exception = vbuck.s.EXCEPT;
    status.led2.voltage = calcVoltage(vbuck.s.VBUCK);

    REG_CNFG_CRNT cnt;
    read(CMD_CNFG_CRNT1, cnt.v);
    status.led1.setCurrent = calcSetCurrent(cnt.s.ILED);

    read(CMD_CNFG_CRNT2, cnt.v);
    status.led2.setCurrent = calcSetCurrent(cnt.s.ILED);

    REG_MON_LED led;
    read(CMD_MON_LED1, led.v);

    status.led1.current = calcMonCurrent(led.s.IMON);

    read(CMD_MON_LED2, led.v);
    status.led2.current = calcMonCurrent(led.s.IMON);

    REG_CNFG_PWM pwm;
    read(CMD_CNFG_PWM1, pwm.v);
    status.led1.setPwm = (float)pwm.s.PWM_DUTY / 1000.0;

    read(CMD_CNFG_PWM2, pwm.v);
    status.led2.setPwm = (float)pwm.s.PWM_DUTY / 1000.0;

    REG_MON_TEMP temp;
    read(CMD_MON_TEMP, temp.v);
    status.dieTemp = calcTemp(temp.s.TEMP);

    REG_CNFG_GEN cnfgGen;
    read(CMD_CNFG_GEN, cnfgGen.v);

    REG_GEN_STAT genStat;
    read(CMD_GEN_STAT, genStat.v);
    status.thermalShutdown = genStat.s.TH_SHDN;
    status.thermalWarning = genStat.s.TH_WARN;
    status.led1.enabled = cnfgGen.s.BUCK1_EN;
    status.led1.overVoltage = genStat.s.OVP1;
    status.led1.overCurrent = genStat.s.OVERC1;
    status.led1.shortDetected = genStat.s.SHORT1;
    status.led1.openDetected = genStat.s.OPEN1;
    status.led2.enabled = cnfgGen.s.BUCK2_EN;
    status.led2.overVoltage = genStat.s.OVP2;
    status.led2.overCurrent = genStat.s.OVERC2;
    status.led2.shortDetected = genStat.s.SHORT2;
    status.led2.openDetected = genStat.s.OPEN2;

    // If the PS switcher is off the current reading will hold the
    // last read value.

    if (status.led1.setCurrent == 0.0 || !status.led1.enabled) status.led1.current = 0.0;
    if (status.led2.setCurrent == 0.0 || !status.led2.enabled) status.led2.current = 0.0;

    REG_CNFG_SPI spi;
    read(CMD_CNFG_SPI, spi.v);

    status.errors.unused = 0;
    status.errors.clock = !!spi.s.CLK_ERR;
    status.errors.hardwareReset = !!spi.s.HW_RST;
    status.errors.parity = !!spi.s.PAR_ERR;
    status.errors.readWrite = !!spi.s.RW_ERR;

    return status;
}

float MAX20096::getMaxCurrent()
{
    return calcSetCurrent(127);
}

bool MAX20096::getEnabled(uint8_t channel)
{
    REG_CNFG_GEN cnfgGen;
    read(CMD_CNFG_GEN, cnfgGen.v);

    switch (channel)
    {
        case 0:
            return !!cnfgGen.s.BUCK1_EN;
        case 1:
            return !!cnfgGen.s.BUCK2_EN;
        default:
            return false;

    }
}

float MAX20096::getCurrent(uint8_t channel)
{
    int command;

    switch (channel)
    {
        case 0:
            command = CMD_CNFG_CRNT1;
            break;

        case 1:
            command = CMD_CNFG_CRNT2;
            break;

        default:
            return 0.0;
    }

    REG_CNFG_CRNT cnt;
    read(command, cnt.v);
    return calcSetCurrent(cnt.s.ILED);
}

float MAX20096::getPWM(uint8_t channel)
{
    int command;
    switch (channel)
    {
        case 0:
            command = CMD_CNFG_PWM1;
            break;

        case 1:
            command = CMD_CNFG_PWM2;
            break;

        default:
            return 0.0;
    }

    REG_CNFG_PWM pwm;
    read(command, pwm.v);
    return (float)pwm.s.PWM_DUTY / 1000.0;
}

bool MAX20096::setEnabled(uint8_t channel, bool enabled)
{
    REG_CNFG_GEN gen;
    read(CMD_CNFG_GEN, gen.v);

    switch (channel)
    {
        case 0:
            gen.s.BUCK1_EN = enabled;
            break;

        case 1:
            gen.s.BUCK2_EN = enabled;
            break;

        default:
            return false;
    }

    return write(CMD_CNFG_GEN, gen.v);
}

bool MAX20096::setCurrent(uint8_t channel, float amps)
{
    if (amps < 0) amps = 0;

    //  ILED2 = ((1.25V x ILED2[6:0]/127) - 0.2V)/(5 x RCS2)

    float maxCurrent = getMaxCurrent();
    float setCurrent = min(amps, maxCurrent);
    float dac = (127.0 * (5 * _rcs  *  setCurrent + .2)) / 1.25;

    int command;
    switch (channel)
    {
        case 0:
            command = CMD_CNFG_CRNT1;
            break;

        case 1:
            command = CMD_CNFG_CRNT2;
            break;

        default:
            return false;
    }

    REG_CNFG_CRNT crnt = {};
    crnt.s.ILED = (uint8_t)min(dac, 127);

    return write(command, crnt.v);
}

bool MAX20096::setPWM(uint8_t channel, float percent)
{
    int command;
    switch (channel)
    {
        case 0:
            command = CMD_CNFG_PWM1;
            break;

        case 1:
            command = CMD_CNFG_PWM2;
            break;

        default:
            return false;
    }

    REG_CNFG_PWM pwm;
    pwm.s.PWM_DUTY = (int)(percent * 1000);

    return write(command, pwm.v);
}

uint16_t MAX20096::spiTransfer(uint16_t value)
{
    SPISettings spi(1000000, MSBFIRST, SPI_MODE0);
    SPI.beginTransaction(spi);
    digitalWrite(_cs, LOW);
    value = SPI.transfer16(value);
    digitalWrite(_cs, HIGH);
    SPI.endTransaction();
    return value;
}

void MAX20096::read(int cmd, uint16_t& result)
{
    COMMAND c = {};
    c.s.Read = 1;
    c.s.Address = cmd;
    c.s.Parity = calcParity(c.v);
    result = spiTransfer(c.v);
}

bool MAX20096::write(int cmd, uint16_t data)
{
    COMMAND c = {};
    c.s.Address = cmd;
    c.s.Data = data;
    c.s.Parity = calcParity(c.v);

    COMMAND_STAT stat;
    stat.v = spiTransfer(c.v);

    // Note this is from the last transaction, not this
    // write, so is more a general "device needs to be reset"
    // flag.

    return !stat.s.SPI_ERR;
}

float MAX20096::calcSetCurrent(uint8_t reading)
{
    //  ILED2 = ((1.25V x ILED2[6:0]/127) - 0.2V)/(5 x RCS2)
    // RCS == 4mOhm
    float current = ((1.25 * (float)reading / 127) - .2) / (5 * _rcs);
    if (current < 0) current = 0;
    return current;
}

float MAX20096::calcMonCurrent(uint8_t reading)
{
    // ILED1 = ((2.5V x IMON1[7:0]/255) - 0.2V)/(5 x RCS1)
    // RCS == 4mOhm
    float current = ((2.5 * (float)reading / 255) - .2) / (5 * _rcs);
    if (current < 0) current = 0;
    return current;
}

float MAX20096::calcVoltage(uint8_t reading)
{
    // VBUCK1 = MON_VBUCK1[7:0](dec) x 2.5 x (R2 + R3)/(255 x R3) in volts
    return (float)reading * 2.5 * (_rvd1 + _rvd2) / (255.0 * _rvd2);
}
