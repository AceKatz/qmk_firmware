#pragma once
#include "quantum.h"



// extern rgblight_config_t rgblight_config;
// static uint32_t rgb_preview_timer;
// layer_state_t layer_state_set_user(layer_state_t state);
// // void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
void keyboard_post_init_user(void);
// // void keyboard_post_init_keymap(void);
// // void keyboard_post_init_rgb_light(void);
// // void matrix_scan_user(void);
// void eeconfig_init_user(void);
// bool led_update_user(led_t led_state);
// void keyboard_post_init_keymap(void);
bool          process_record_user_rgb_light(uint16_t keycode, keyrecord_t *record);

layer_state_t layer_state_set_rgb_light(layer_state_t state);
layer_state_t default_layer_state_set_rgb_light(layer_state_t state);
void          rgblight_sethsv_default_helper(uint8_t index);
