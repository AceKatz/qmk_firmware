// #pragma once
#include "mmkd.h"

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     return true;
// }

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
        add_keylog(keycode);
#endif
    }
    return true;
}

// void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
// //     // Allow for a preview of changes when modifying RGB
// // # if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
// //   switch (keycode) {
// //     case RGB_TOG ... VLK_TOG:
// //       for (uint8_t i = 0; i < RGBLIGHT_MAX_LAYERS; i++) {
// //         rgblight_set_layer_state(i, false);
// //       }
// //       rgb_preview_timer = timer_read32();
// //       break;
// //   }
// // # endif
//   return;
// }
// void keyboard_post_init_keymap(void){ }
