#pragma once
#include QMK_KEYBOARD_H
#include "quantum.h"

// clang-format off
typedef union {
    uint32_t raw;
    struct {
        bool    rgb_layer_change     :1;
        bool    is_overwatch         :1;
        bool    nuke_switch          :1;
        bool    swapped_numbers      :1;
        bool    rgb_matrix_idle_anim :1;
    };
} userspace_config_t;
extern userspace_config_t userspace_config;

// #include "version.h"


#ifdef RGBLIGHT_ENABLE
    #include "rgblight.h"
    #include "rgb_underglow.h"
#endif

#ifdef OLED_DRIVER_ENABLE
    #include "oled_stuff.h"
    #include "animations.h"
#endif

enum tap_dance {
	TD_BRAK = 0,
	TD_G_E,
	TD_BSLSH,
	TD_SWAP_HANDS,
	TD_LINE
};

enum layer_names {
  _QWERTY = 0,  //Qwerty with custom shortcuts and functions
  _NUM,  //numpad or numbers
  _FN,
  _SWAP, // This is used b/c my pc's sometimes swap GUI and ALT, this toggles them
  _MOVE  // Swap left and right hands
  // _DEFAULT     //Default ANSI for gaming, enable with FN2+RCtl
  // _NAVKEY,      //Macropad nav keys
  // _MEDIA,       //Macropad media controls
  // _RGB,         //Macropad RGB controls
  // _FN1PAD,      //Macropad reset and make commands
  // _FN1_60,      //Function keys, arrows, custom shortcuts, volume control
  // _FN2_60       //RGB Underglow controls and RESET
};

#define TD_BRK TD(TD_BRAK)
#define TD_SWAP TD(TD_SWAP_HANDS)
#define TD_HOME TD(TD_LINE)
#define TD_SLSH TD(TD_BSLSH)
#define KC_G_E TD(TD_G_E)
#define PRV_TB LCTL(KC_PGUP)
#define NXT_TB LCTL(KC_PGDN)
#define LS(l) LT(l, KC_SPC)

#define FN(x) LT(_FN, x)
#define LW(x) LT(_MOVE, x)
#define RS(x) LT(_NUM, x)
#define SHF(x) MT(MOD_LSFT, x) // tap x, hold shift
#define ALT(x) MT(MOD_LALT, x) // tap x, hold alt
#define CTL(x) MT(MOD_LCTL, x) // tap x, hold ctrl
#define GUI(x) MT(MOD_LGUI, x) // tap x, hold gui
#define COM KC_COMMA
#define G_SW LM(_SWAP, MOD_LGUI)
#define A_SW LM(_SWAP, MOD_LALT)
#define DEL KC_DELETE
#define ENT KC_ENT
#define SPC KC_SPACE
#define BSC KC_BSPACE
#define TAB KC_TAB
#define CAP_PURPLE  250, 25, 68
// static uint32_t rgb_preview_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record);
// void post_process_record_user(uint16_t keycode, keyrecord_t *record);
// void keyboard_post_init_keymap(void);
