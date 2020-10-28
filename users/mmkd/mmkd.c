// #pragma once
#include "mmkd.h"

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     return true;
// }
userspace_config_t userspace_config;

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
        add_keylog(keycode);
#endif
    }
    return true;
}
__attribute__((weak)) void keyboard_pre_init_keymap(void) {}

void keyboard_pre_init_user(void) {
    userspace_config.raw = eeconfig_read_user();
    keyboard_pre_init_keymap();
}

__attribute__((weak)) void eeconfig_init_keymap(void) {}

void eeconfig_init_user(void) {
    userspace_config.raw              = 0;
    userspace_config.rgb_layer_change = true;
    eeconfig_update_user(userspace_config.raw);
    eeconfig_init_keymap();
    keyboard_init();
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
