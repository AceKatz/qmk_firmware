#include "mmkd.h"
#include "rgb_underglow.h"
#include "eeprom.h"


//
// const rgblight_segment_t PROGMEM qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
// 		{0,RGBLED_NUM, HSV_PURPLE}
// );
// const rgblight_segment_t PROGMEM move_layer[] = RGBLIGHT_LAYER_SEGMENTS(
// 		{0,RGBLED_NUM, HSV_GREEN}
// );
// const rgblight_segment_t PROGMEM fn_layer[] = RGBLIGHT_LAYER_SEGMENTS(
// 		{0,RGBLED_NUM, HSV_RED}
// );
// const rgblight_segment_t PROGMEM swap_layer[] = RGBLIGHT_LAYER_SEGMENTS(
// 		{0,RGBLED_NUM, HSV_BLUE}
// );
// const rgblight_segment_t PROGMEM num_layer[] = RGBLIGHT_LAYER_SEGMENTS(
// 		{0,RGBLED_NUM, HSV_PINK}
// );
// // const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
// // 		{0,20,HSV_WHITE}
// // 	);
// // const rgblight_segment_t PROGMEM my_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
// // 		{0,20,HSV_TEAL}
// // 	);
// const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST(
//     qwerty_layer,
//     move_layer,
//     fn_layer,
//     swap_layer,
//     num_layer
// );

//Set the appropriate layer color
// layer_state_t layer_state_set_user(layer_state_t state) {
//     rgblight_set_layer_state(_QWERTY, layer_state_cmp(state, _QWERTY));
//     rgblight_set_layer_state(_MOVE, layer_state_cmp(state, _MOVE));
//     rgblight_set_layer_state(_SWAP, layer_state_cmp(state, _SWAP));
//     rgblight_set_layer_state(_NUM, layer_state_cmp(state, _NUM));
//     rgblight_set_layer_state(_FN, layer_state_cmp(state, _FN));
//     // rgblight_set_layer_state(_SWAP, layer_state_cmp(state, _SWAP));
//     // return update_tri_layer_state(state, _MOVE, _NUM, _FN);
//     return state;
// }
// //EEPROM Reset Function
// void eeconfig_init_user(void) {
  // rgblight_enable(); // Enable RGB by default
  // rgblight_sethsv_purple();  // Set it to orange by default
// }
void keyboard_post_init_rgb_light(void) {
#if defined(RGBLIGHT_STARTUP_ANIMATION)
    is_enabled = rgblight_is_enabled();
    // if (1){//userspace_config.rgb_layer_change) {
        rgblight_enable_noeeprom();
    // }
    if (rgblight_is_enabled()) {
        layer_state_set_rgb_light(layer_state);
        old_hue = rgblight_get_hue();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        is_rgblight_startup = true;
    }
#endif
    layer_state_set_rgb_light(layer_state);
}

bool process_record_user_rgb_light(uint16_t keycode, keyrecord_t *record) {
    uint16_t temp_keycode = keycode;
    // Filter out the actual keycode from MT and LT keys.
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        temp_keycode &= 0xFF;
    }

    switch (temp_keycode) {
#ifdef RGBLIGHT_TWINKLE
        case KC_A ... KC_SLASH:
        case KC_F1 ... KC_F12:
        case KC_INSERT ... KC_UP:
        case KC_KP_SLASH ... KC_KP_DOT:
        case KC_F13 ... KC_F24:
        case KC_AUDIO_MUTE ... KC_MEDIA_REWIND:
            if (record->event.pressed) {
                start_rgb_light();
            }
            break;
#endif  // RGBLIGHT_TWINKLE
    }
    return true;
}

void rgblight_sethsv_default_helper(uint8_t index) { rgblight_sethsv_at(rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val(), index); }


void rgblight_set_hsv_and_mode(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode) {
    rgblight_sethsv_noeeprom(hue, sat, val);
    wait_us(175);  // Add a slight delay between color and mode to ensure it's processed correctly
    rgblight_mode_noeeprom(mode);
}

layer_state_t layer_state_set_rgb_light(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    // if (1){//userspace_config.rgb_layer_change) {
			// uint8_t mode = get_highest_layer(state) == _MODS ? RGBLIGHT_MODE_BREATHING : RGBLIGHT_MODE_STATIC_LIGHT;
			uint8_t mode =  RGBLIGHT_MODE_STATIC_LIGHT;
        switch (get_highest_layer(state)) {
            case _MOVE:
                rgblight_set_hsv_and_mode(HSV_ORANGE, mode); //userspace_config.is_overwatch ? RGBLIGHT_MODE_SNAKE + 2 : RGBLIGHT_MODE_SNAKE + 3);
                break;
            case _SWAP:
                rgblight_set_hsv_and_mode(HSV_CHARTREUSE, mode); //RGBLIGHT_MODE_KNIGHT + 1);
                break;
            case _NUM:
                rgblight_set_hsv_and_mode(HSV_GREEN, mode); //RGBLIGHT_MODE_SNAKE + 2);
                break;
            case _FN:
                rgblight_set_hsv_and_mode(HSV_RED, mode); //RGBLIGHT_MODE_BREATHING + 3);
                break;
            default:  //  for any other layers, or the default layer
            {
                switch (get_highest_layer(default_layer_state)) {
                    // case _COLEMAK:
                    //     rgblight_set_hsv_and_mode(HSV_MAGENTA, mode);
                    //     break;
                    // case _DVORAK:
                    //     rgblight_set_hsv_and_mode(HSV_SPRINGGREEN, mode);
                    //     break;
                    // case _WORKMAN:
                    //     rgblight_set_hsv_and_mode(HSV_GOLDENROD, mode);
                    //     break;
                    // case _NORMAN:
                    //     rgblight_set_hsv_and_mode(HSV_CORAL, mode);
                    //     break;
                    // case _MALTRON:
                    //     rgblight_set_hsv_and_mode(HSV_YELLOW, mode);
                    //     break;
                    // case _EUCALYN:
                    //     rgblight_set_hsv_and_mode(HSV_PINK, mode);
                    //     break;
                    // case _CARPLAX:
                    //     rgblight_set_hsv_and_mode(HSV_BLUE, mode);
                    //     break;
                    default:
                        rgblight_set_hsv_and_mode(CAP_PURPLE, mode);
                        break;
                }
                break;
            }
        }
    // }
#endif  // RGBLIGHT_ENABLE

    return state;
}
