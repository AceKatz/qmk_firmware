/* Copyright 2019 Danny Nguyen <danny@keeb.io>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "config.h"
;
void eeconfig_init_user(void) {
    set_unicode_input_mode(UC_LNX);
};

// enum custom_keycodes {
//   UC_PLY
// };

#define WIN_MOD(l) LM(l, MOD_LGUI)
// #define CTL_MOD(l) LM(l, MOD_LCTL)
enum unicode_names {
  CCCP,
  CIRCA,
  // SNEK,
  BANG
};
enum custom_keycodes{
	// TD_SPC_ENT = 0,
	TD_HE = 0,
  TD_COM
};

const uint32_t PROGMEM unicode_map[] = {
    [CCCP]  = 0x262D,  // ☭
    [CIRCA] = 0x24B6,  // Ⓐ
    // [SNEK]  = 0x1F40D, // 🐍
    [BANG]  = 0x203D,  // ‽
};
// #define KC_COM TD(TD_COM)
// #define KC_HE TD(TD_HE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Knob 1: Vol Dn/Up |              | Knob 2: Page Dn/Up  |
        | Press: Mute       | Unicode      | Press: Play/Pause   |
        | Hold: Layer 2     | Media Next   | ☭                  |
        | Delete            | PauseBreak   | F12                 |
    */
    [0] = LAYOUT(
        WIN_MOD(2)     , LT(1, KC_MPLY) , WIN_MOD(2),
        LT(3, KC_PSCR) , KC_MNXT        , TD(TD_COM),
        TD(TD_HE)      , KC_PAUSE       , KC_F12
    ),
    /*
        | RESET          | Unicode Mod | Media Stop |
        | Held: Layer 2  | Media Prev  | Ⓐ          |
        | Backlight | Home        | End |
     */
    [1] = LAYOUT(
        _______ , _______ , KC_LCTL,
        UC_MOD  , KC_MPRV , X(CIRCA),
        BL_STEP , BL_STEP , X(BANG)
    ),
    // [2] = LAYOUT(
    //     _______ , _______ , _______,
    //     _______ , _______ , _______,
    //     _______ , _______ , _______
    // ),
    [3] = LAYOUT(
        _______ , KC_LSFT  , _______,
        _______ , RGB_MOD  , RGB_TOG,
        RGB_HUI , RGB_SAI  , RGB_VAI
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
      if(IS_LAYER_ON(2)) {
        if (clockwise) {
          tap_code(KC_GRV);
        } else {
          tap_code16(LSFT(KC_GRV));
        }
      } else if(IS_LAYER_ON(1)) {
        if (clockwise) {
          backlight_increase();
        } else {
          backlight_decrease();
        }
      } else {
        if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
      }
    }
    else if (index == 1) {
      if(IS_LAYER_ON(2)) {
        if (clockwise) {
          tap_code(KC_TAB);
        } else {
          // https://www.reddit.com/r/olkb/comments/byyfra/noobencoder_questions/
          // https://www.reddit.com/r/olkb/comments/byj2kd/is_it_possible_to_assign_lguikc_tab_to_a_rotary/
          // register_code(KC_LSHIFT);
          // tap_code(KC_TAB);
          // unregister_code(KC_LSHIFT);
          tap_code16(LSFT(KC_TAB));
        }
      } else {
        if(IS_LAYER_ON(1)) {
          register_code(KC_LCTL);
        }
        if (clockwise) {
          tap_code(KC_PGDN);
        } else {
          tap_code(KC_PGUP);
        }
        unregister_code(KC_LCTL);
      }
    }
}

//Tap Dance Definitions

void leftist (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {☭Ⓐ
    // send_unicode_string("Ⓐ");
    unicode_input_start();
    register_hex(0x24B6);
    // send_unicode_hex_string(0x24B6);
    // send_unicode_hex_string(CIRCA);
  } else {
    // send_unicode_string("☭");
    unicode_input_start();
    register_hex(0x262D);
    // send_unicode_hex_string(0x262D);
    // send_unicode_hex_string(CCCP);
  }
  unicode_input_finish();
  reset_tap_dance (state);
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_HE]  		= ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_END),
  [TD_COM]  	= ACTION_TAP_DANCE_FN(leftist)
};
