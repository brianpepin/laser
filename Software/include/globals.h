#pragma once

#include <Arduino.h>
#include <U8g2lib.h>

#include "input.h"
#include "laser.h"
#include "led.h"
#include "management.h"
#include "settings.h"
#include "tec.h"

extern Settings settings;
extern U8G2_SSD1322_NHD_256X64_1_4W_HW_SPI display;
extern Input input;
extern Laser laser;
extern Tec tec;
extern Led led;
