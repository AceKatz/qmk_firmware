#pragma once
#include "quantum.h"



extern rgblight_config_t rgblight_config;
// static uint32_t rgb_preview_timer;
layer_state_t layer_state_set_user(layer_state_t state);
// void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
void keyboard_post_init_user(void);
// void keyboard_post_init_keymap(void);
// void keyboard_post_init_rgb_light(void);
// void matrix_scan_user(void);
void eeconfig_init_user(void);
bool led_update_user(led_t led_state);
void keyboard_post_init_keymap(void);
