/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

//#define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS

//#define SSD1306OLED

//#define USE_SERIAL_PD2

//#define TAPPING_FORCE_HOLD  
//#define TAPPING_TERM 150

#ifdef RGBLIGHT_ENABLE
    #undef RGBLED_NUM
    #define RGBLIGHT_ANIMATIONS
    #define RGBLED_NUM 27
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif

//#define FORCE_NKRO
//#define ONESHOT_TIMEOUT 8000
#define TAPPING_TERM 170 //used to be 170
// #define HOLD_ON_OTHER_KEY_PRESS 
// This isn't necessary, but because permissive holds are broken with layer taps, I recommend building this keymap with sigprof's fork,
// which has a feature (Hold on other key press) that fixes it. https://github.com/sigprof/qmk_firmware
// #define PERMISSIVE_HOLD
//#define RETRO_TAPPING
#define COMBO_COUNT 6
#define COMBO_TERM 60
 #define IGNORE_MOD_TAP_INTERRUPT // this makes it possible to do rolling combos (zx) with keys that convert to other keys on hold (z becomes ctrl when you hold it, and when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x. That's bad.) 


 #define MOUSEKEY_INTERVAL 7
 
 #define MOUSEKEY_DELAY 0
  
 #define MOUSEKEY_TIME_TO_MAX 60
 
 #define MOUSEKEY_MAX_SPEED 6
 
 #define MOUSEKEY_WHEEL_DELAY 0
