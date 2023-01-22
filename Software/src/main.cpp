
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
ISR(PCINT2_vect)
{
  input.processInterrupt();
}

void setup()
{
  Serial.begin(9600);
  while (!Serial);

  Serial.println(F("\nController starting up..."));

  //
  // Configure SPI port
  //

  pinMode(Pins::Spi::Ss, OUTPUT);
  pinMode(Pins::Spi::Miso, INPUT_PULLUP);
  pinMode(Pins::Spi::Mosi, OUTPUT);
  pinMode(Pins::Spi::Sck, OUTPUT);
  digitalWrite(Pins::Spi::Ss, HIGH);
  SPI.usingInterrupt(255);

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
  // Configure a pin change interrupt for 
  // our buttons
  //

  PCICR |= (1 << PCIE2); // Enable pin change interrupt 2 (D pins)
  PCMSK2 |= (1 << Pins::Gpio::Irq);

  //
  // Read settings from EEPROM and configure
  // power and TEC boards.
  //

  settings.load();

  laser.reset();
  input.reset();

  //
  // Now enable interrupts to start processing input.
  //

  sei();

  Serial.println(F("Ready."));
}

void loop()
{
  Management::tick();
}