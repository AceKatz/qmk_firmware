
#ifndef CONFIG_USER_H
#define CONFIG_USER_H
#endif

#include "../../config.h"

/* Use I2C or Serial, not both */

// #define USE_SERIAL
#define USE_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS
#define BACKLIGHT_BREATHING
// #define TAPPING_TERM 200
#define TAPPING_TERM 150

#ifdef RGBLIGHT_ENABLE

// #define RGBLIGHT_ANIMATIONS
  #undef RGBLED_NUM
  #undef RGBLED_SPLIT
  #define RGBLIGHT_SLEEP
  #define RGBLIGHT_LAYERS
  #define RGBLED_NUM 12
  #define RGBLIGHT_SPLIT
  #define RGBLED_SPLIT { 6, 6 }
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8

#endif
