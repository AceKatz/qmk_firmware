/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

#include "thumbstick.h"
enum custom_keycodes
{
  MS_BTN1 = SAFE_RANGE,
  MS_BTN2,
  MS_BTN3
};
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
      MS_BTN1
    )
};
report_mouse_t currentReport = {};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  debug_mouse=true;
}
// clang-format on

// void matrix_init_user(void) {
// #ifdef ENCODER_ENABLE
//     encoder_utils_init();
// #endif
// }

// layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); }

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case TMB_MODE:
//             if (record->event.pressed) {
//                 thumbstick_mode_cycle(false);
//             }
//     }
//     return true;
// }
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	//uint8_t layer;
	//layer = biton32(layer_state);  // get the current layer  //Or don't, I didn't use it.
	bool returnVal = true; //this is to determine if more key processing is needed.

	 //custom layer handling for tri_layer,
	switch (keycode) {
    //mouse buttons, for 1-3, to update the mouse report:
    case MS_BTN1:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        // if (shift_held && shift_suspended){
        //   register_code(KC_LSFT);
        //   shift_suspended = false;
        // }
        //update mouse report here
        currentReport.buttons |= MOUSE_BTN1; //MOUSE_BTN1 is a const defined in report.h
      } else {
        //update mouse report here
        currentReport.buttons &= ~MOUSE_BTN1;
      }
      pointing_device_set_report(currentReport);
      returnVal = false;
      pointing_device_send();
      break;
    case MS_BTN2:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        // if (shift_held && shift_suspended){
        //   register_code(KC_LSFT);
        //   shift_suspended = false;
        // }
        //update mouse report here
        currentReport.buttons |= MOUSE_BTN2; //MOUSE_BTN2 is a const defined in report.h
      } else {
        //update mouse report here
        currentReport.buttons &= ~MOUSE_BTN2;
      }
      pointing_device_set_report(currentReport);
      returnVal = false;
      pointing_device_send();
      break;
    case MS_BTN3:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        // if (shift_held && shift_suspended){
        //   register_code(KC_LSFT);
        //   shift_suspended = false;
        // }
        //update mouse report here
        currentReport.buttons |= MOUSE_BTN3; //MOUSE_BTN3 is a const defined in report.h
      } else {
        //update mouse report here
        currentReport.buttons &= ~MOUSE_BTN3;
      }
      pointing_device_set_report(currentReport);
      pointing_device_send();
      returnVal = false;
      break;
    //Additionally, if NS_ keys are in use, then shift may be held (but is
    //disabled for the unshifted keycodes to be send.  Check the bool and
    //register shift as necessary.
    default:
      // if (shift_held){
      //   register_code(KC_LSFT);
      // }
    break;
  }
	return returnVal;

}
