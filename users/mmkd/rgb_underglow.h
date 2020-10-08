#pragma once
#include "quantum.h"



extern rgblight_config_t rgblight_config;

bool process_record_user(uint16_t keycode, keyrecord_t *record);
void post_process_record_user(uint16_t keycode, keyrecord_t *record);
layer_state_t layer_state_set_user(layer_state_t state);
void keyboard_post_init_user(void);
void matrix_scan_user(void);
void eeconfig_init_user(void);
