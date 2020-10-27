#include "mmkd.h"
#include "rgb_underglow.h"

const rgblight_segment_t PROGMEM qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,RGBLED_NUM, HSV_PURPLE}
);
const rgblight_segment_t PROGMEM move_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,RGBLED_NUM, HSV_GREEN}
);
const rgblight_segment_t PROGMEM fn_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,RGBLED_NUM, HSV_RED}
);
const rgblight_segment_t PROGMEM swap_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,RGBLED_NUM, HSV_BLUE}
);
const rgblight_segment_t PROGMEM num_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,RGBLED_NUM, HSV_PINK}
);
// const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
// 		{0,20,HSV_WHITE}
// 	);
// const rgblight_segment_t PROGMEM my_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
// 		{0,20,HSV_TEAL}
// 	);
const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    qwerty_layer,
    move_layer,
    fn_layer,
    swap_layer,
    num_layer
);

//Set the appropriate layer color
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_QWERTY, layer_state_cmp(state, _QWERTY));
    rgblight_set_layer_state(_MOVE, layer_state_cmp(state, _MOVE));
    rgblight_set_layer_state(_SWAP, layer_state_cmp(state, _SWAP));
    rgblight_set_layer_state(_NUM, layer_state_cmp(state, _NUM));
    rgblight_set_layer_state(_FN, layer_state_cmp(state, _FN));
    // rgblight_set_layer_state(_SWAP, layer_state_cmp(state, _SWAP));
    // return update_tri_layer_state(state, _MOVE, _NUM, _FN);
    return state;
}

// void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
//     // Allow for a preview of changes when modifying RGB
// # if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
//   switch (keycode) {
//     case RGB_TOG ... VLK_TOG:
//       for (uint8_t i = 0; i < RGBLIGHT_MAX_LAYERS; i++) {
//         rgblight_set_layer_state(i, false);
//       }
//       rgb_preview_timer = timer_read32();
//       break;
//   }
// # endif
//   return;
// }

void keyboard_post_init_user(void) {
	//Enable the LED layers
	rgblight_layers = _rgb_layers;
	// layer_state_set_user(layer_state);
	//
    keyboard_post_init_keymap();
}
void keyboard_post_init_keymap(void){ }

bool led_update_user(led_t led_state) {
		rgblight_set_layer_state(0, led_state.caps_lock);
		return true;
}
//EEPROM Reset Function
void eeconfig_init_user(void) {
  rgblight_enable(); // Enable RGB by default
  rgblight_sethsv_purple();  // Set it to orange by default
}
