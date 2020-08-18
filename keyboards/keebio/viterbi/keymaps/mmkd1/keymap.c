#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif

// extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _FN 1

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  // STK_SHIFT,
  // STK_CTRL,
  // STK_ALT,
  // STK_GUI,
  // STK_META,
  // STK_CLEAR,
  // RGB_LEVEL_UP,
  // RGB_LEVEL_DOWN,
};

enum {
  TD_SPC_ENT = 0,
  TD_KC_LSFT_CAPS,
  TD_KC_RSFT_CAPS,
  TD_BRC_L_R
};
#define KC_ KC_TRNS

#define KC_SWIN LGUI(KC_TILD)   // Switch between windows
#define KC_SAPP LGUI(KC_TAB)    // Switch between applications
#define KC_FN1 MO(_FN)
#define KC_LCAG LCAG(KC_NO)
// #define KC_RTOG RGB_TOG
// #define KC_RGUP RGB_LEVEL_UP
// #define KC_RGDN RGB_LEVEL_DOWN
#define KC_RST RESET
// #define KC_SSFT STK_SHIFT
// #define KC_SCTL STK_CTRL
// #define KC_SALT STK_ALT
// #define KC_SGUI STK_GUI
// #define KC_SMTA STK_META
// #define KC_SCLR STK_CLEAR

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,--------+---------+---------+---------+---------+---------+---------.    ,---------+---------+---------+---------+---------+---------+---------.
     GRV  , 1    , 2    , 3    , 4    , 6    ,      7    , 8    , 9    , 0    , MINS , EQL  , BSPC,
  //|--------+---------+---------+---------+---- -----+---------+---------|    |---------+---------+---------+---------+---------+---------+---------|
     TAB  , Q    , W    , E    , R    , RBRC ,      Y    , U    , I    , O    , P    , TD(TD_BRC_L_R) , BSLS,
  //|--------+---------+---------+---------+---------+---------+---------|    |---------+---------+---------+---------+---------+---------+---------|
     ESC  , A    , S    , D    , F    , SAPP ,      H    , J    , K    , L    , SCLN , QUOT , ENT ,
  //|--------+---------+---------+---------+---------+---------+---------|    |---------+---------+---------+---------+---------+---------+---------|
     LSFT , Z    , X    , C    , V    , SWIN ,      N    , M    , COMM , DOT  , SLSH , UP   , RSFT,
  //|--------+---------+---------+---------+---------+---------+---------|    |---------+---------+---------+---------+---------+---------+---------|
     CTL  , LGUI , LALT , MENU , FN1     , SPC  ,      SPC  , RALT , RGUI , RCTL , LEFT , DOWN , RIGHT
  //`--------+---------+---------+---------+---------+---------+---------'    `---------+---------+---------+---------+---------+---------+---------'
  ),

  [_FN] = LAYOUT_kc(
  //,----+----+----+----+-----+-----+-----.    ,----+----+------+-------+--------+--------+-------.
         , F1 , F2 , F3 , F4  , F5  , F6  ,         ,    ,      ,KC_PPSLS,KC_PPAST ,KC_PPMNS ,KC_DEL ,
  //|----+----+----+----+-----+-----+-----|    |----+----+------+-------+--------+--------+-------|
         , F7 , F8 , F9 , F10 , F11 ,F12  ,         ,    ,KC_P7 ,KC_P8  ,KC_P9   ,KC_PPLS ,PSCR,
  //|----+----+----+----+-----+-----+-----|    |----+----+------+-------+--------+--------+-------|
         ,    ,    ,    ,RST  ,     ,     ,         ,    ,KC_P4 ,KC_P5  ,KC_P6   ,KC_PPLS ,       ,
  //|----+----+----+----+-----+-----+-----|    |----+----+------+-------+--------+--------+-------|
         ,    ,    ,    ,RTOG ,RGDN ,RGUP ,         ,    ,KC_P1 ,KC_P2  ,KC_P3   ,KC_PENT ,       ,
  //|----+----+----+----+-----+-----+-----|    |----+----+------+-------+--------+--------+-------|
         ,    ,    ,    ,     ,     ,     ,         ,    ,KC_P1 ,KC_P1  ,KC_PDOT ,KC_PENT ,
  //`----+----+----+----+-----+-----+-----'    `----+----+------+-------+--------+--------+-------'
  )

};


//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {

  //Tap once for space, tap twice for enter
  // [TD_SPC_ENT]  = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT),
  //Tap once for Left Shift, twice for Caps Lock
  [TD_KC_LSFT_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
  //Tap once for Right Shift, twice for Caps Lock
  [TD_KC_RSFT_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS),
  // Tap once for left bracket, twice for right bracket
  [TD_BRC_L_R]  = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),


// Other declarations would go here, separated by commas, if you have them

};


// bool modifier_already_applied = false;
// uint8_t physically_held_modifiers = 0;
// uint8_t last_mods = 0xFF;
// uint8_t rgb_dimming = 0;
// #define SET_LED_RGB(val, led_num) setrgb(((val >> 16) & 0xFF) >> rgb_dimming, ((val >> 8) & 0xFF) >> rgb_dimming, (val & 0xFF) >> rgb_dimming, (LED_TYPE *)&led[led_num])
//
// void update_underglow_level(void) {
//   if (get_mods() == last_mods)
//     return;
//
//   last_mods = get_mods();
//
//   if (get_mods() == 0) {
//     uint8_t level = 0x10 >> rgb_dimming;
//     rgblight_setrgb(level, level, level);
//     return;
//   }
//
//   uint32_t mod_colors[4] = {0};
//   uint8_t mod_count = 0;
//   rgblight_setrgb(0x00, 0x00, 0x00);
//
//   if (get_mods() & MOD_BIT(KC_LSFT))
//     mod_colors[mod_count++] = 0xFF0000;
//   if (get_mods() & MOD_BIT(KC_LCTL))
//     mod_colors[mod_count++] = 0x00FF00;
//   if (get_mods() & MOD_BIT(KC_LALT))
//     mod_colors[mod_count++] = 0x0000FF;
//   if (get_mods() & MOD_BIT(KC_LGUI))
//     mod_colors[mod_count++] = 0xFFFF00;
//
//   uint8_t led_num = 0;
//   for (int m = 0; m < mod_count; m++) {
//     for (; led_num < RGBLED_NUM*(m+1)/mod_count; led_num++) {
//       SET_LED_RGB(mod_colors[m], led_num);
//     }
//   }
//   rgblight_set();
// }

//
// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//     // Taken from ../dwallace/keymap.c
//     // case QWERTY:
//     //   if (record->event.pressed) {
//     //     #ifdef AUDIO_ENABLE
//     //       PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
//     //     #endif
//     //     persistent_default_layer_set(1UL<<_QWERTY);
//     //   }
//     //   return false;
//     //   break;
//     case RGB_LEVEL_DOWN:
//       if (record->event.pressed && rgb_dimming < 8) {
//         rgb_dimming++;
//       }
//       return false;
//       break;
//     case RGB_LEVEL_UP:
//       if (record->event.pressed && rgb_dimming > 0) {
//         rgb_dimming--;
//       }
//       return false;
//       break;
//   }
//   if (!record->event.pressed && IS_KEY(keycode)) {
//     modifier_already_applied = true;
//     if (physically_held_modifiers == 0)
//       clear_sticky_modifiers();
//   }
//   return true;
// }


// void matrix_init_user(void) {
//   #ifdef RGBLIGHT_ENABLE
//   rgblight_enable();
//   #endif //RGBLIGHT_ENABLE
// }
//
// void matrix_scan_user(void) {
//   #ifdef RGBLIGHT_ENABLE
//   update_underglow_level();
//   #endif //RGBLIGHT_ENABLE
// }
