
#include "globals.h"
#include "config.h"
#include "settings.h"
#include "management.h"

#include <SPI.h>

//
// Global State
//

Settings settings;
U8G2_SSD1322_NHD_256X64_1_4W_HW_SPI display(U8G2_R0, Pins::Display::Cs, Pins::Display::Dc, Pins::Display::Reset);
Led led;
Input input;
Laser laser;
Tec tec;

//
// Inputs are handled by a pin change interrupt.
//
ISR(PORTD_PORT_vect)
{
  input.processInterrupt();
}

void setup()
{
  Serial.begin(9600);
  while (!Serial);

  Serial.println(F("\nController starting up..."));

  //
  // Configure LEDs. LEDs are currently configured all on port C
  // but PWM off timer A does not route there. Change the routing to
  // enable PWM on port C before starting LEDs.
  //

  PORTMUX_TCAROUTEA = PORTMUX_TCA0_PORTC_gc;
  led.begin();

  //
  // Configure SPI port
  //

  pinMode(Pins::Spi::Ss, OUTPUT);
  pinMode(Pins::Spi::Miso, INPUT_PULLUP);
  pinMode(Pins::Spi::Mosi, OUTPUT);
  pinMode(Pins::Spi::Sck, OUTPUT);
  digitalWrite(Pins::Spi::Ss, HIGH);

  //
  // Configure display
  //

  pinMode(Pins::Display::Cs, OUTPUT);
  pinMode(Pins::Display::Reset, OUTPUT);
  pinMode(Pins::Display::Dc, OUTPUT);
  display.setBusClock(10000000);
  display.begin();
  display.clear();

  //
  // Read settings from EEPROM and configure
  // power and TEC boards.
  //

  settings.load();

  laser.reset();
  input.reset();

  Serial.println(F("Ready."));
}

void loop()
{
  Management::tick();
}