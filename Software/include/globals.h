#pragma once

#include <Arduino.h>
#include <U8g2lib.h>

// Uncomment this define to enable support for "simulating" missing
// boards for testing.
//#define ENABLE_SIMULATION

#include "input.h"
#include "laser.h"
#include "led.h"
#include "management.h"
#include "settings.h"
#include "tec.h"

#ifdef LOW_MEM
#define DISPLAY_TARGET U8G2_SSD1322_NHD_256X64_1_4W_HW_SPI
#else
#define DISPLAY_TARGET U8G2_SSD1322_NHD_256X64_F_4W_HW_SPI
#endif

extern Settings settings;
extern DISPLAY_TARGET display;
extern Input input;
extern Laser laser;
extern Tec tec;
extern Led led;
