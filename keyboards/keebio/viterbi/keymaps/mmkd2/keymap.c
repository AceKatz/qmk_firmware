// #include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"
#include QMK_KEYBOARD_H
;

enum {
	// TD_SPC_ENT = 0,
	TD_BRC_L_R = 0,
	TD_BRC_R_L,
	TD_G_E,
	TD_KC_LSFT_CAPS,
	TD_KC_RSFT_CAPS
};
#define TD_L_BRK TD(TD_BRC_L_R)
#define TD_R_BRK TD(TD_BRC_R_L)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ortho_5x14(
	//-----------|---------|-----------|-----------|---------|----------|--------------|	|---------|----------|----------|---------|---------|---------|---------|
	    KC_GESC  , KC_1    , KC_2      , KC_3      , KC_4    , KC_5     , KC_6         ,	  KC_7    , KC_8     , KC_9     , KC_0    , KC_MINS , KC_EQL  , KC_BSPC ,
	//-----------|---------|-----------|-----------|---------|----------|--------------|	|---------|----------|----------|---------|---------|---------|---------|
	    KC_TAB   , KC_Q    , KC_W      , KC_E      , KC_R    , KC_T     , MO(3)        ,	  KC_Y    , KC_U     , KC_I     , KC_O    , KC_P    , TD_L_BRK, KC_BSLS ,
	//-----------|---------|-----------|-----------|---------|----------|--------------|	|---------|----------|----------|---------|---------|---------|---------|
	    TD_G_E   , KC_A    , KC_S      , KC_D      , KC_F    , KC_G     , LALT(KC_GRV) ,	  KC_H    , KC_J     , KC_K     , KC_L    , KC_SCLN , KC_QUOT , KC_ENT  ,
	//-----------|---------|-----------|-----------|---------|----------|--------------|	|---------|----------|----------|---------|---------|---------|---------|
	    KC_LSFT  , KC_Z    , KC_X      , KC_C      , KC_V    , KC_B     , LGUI(KC_TAB) ,	  KC_N    , KC_M     , KC_COMM  , KC_DOT  , KC_SLSH , KC_UP   , KC_RSFT ,
	//-----------|---------|-----------|-----------|---------|----------|--------------|	|---------|----------|----------|---------|---------|---------|---------|
	    KC_LCTL  , KC_LGUI , KC_LALT	 , MO(1)   	 , MO(2)	 , KC_SPC		, KC_SPC       ,	  KC_SPC  , KC_SPC  , KC_RALT	  , KC_APP	, KC_LEFT , KC_DOWN ,	KC_RGHT
 	//-----------|---------|-----------|-----------|---------|----------|--------------|	|---------|----------|----------|---------|---------|---------|---------|
),
	[1] = LAYOUT_ortho_5x14(
	//-----------|---------|-----------|-----------|---------|----------|--------------|	|---------|----------|----------|---------|---------|---------|---------|
			KC_TRNS  , KC_F1   , KC_F2     , KC_F3     , KC_F4   , KC_F5    , KC_F6        ,    KC_F7	  , KC_F8    , KC_F9    , KC_F10  , KC_F11  , KC_F12  , KC_DEL  ,
	//-----------|---------|-----------|-----------|---------|----------|--------------|	|---------|----------|----------|---------|---------|---------|---------|
			KC_UNDS  , KC_TILD , KC_EXLM   , KC_AT     , KC_HASH , KC_DLR   , KC_PERC      ,    KC_CIRC , KC_AMPR  , KC_ASTR  , KC_LPRN , KC_RPRN , KC_LCBR , KC_RCBR ,
	//-----------|---------|-----------|-----------|---------|----------|--------------|  |---------|----------|----------|---------|---------|---------|---------|
			KC_PLUS  , KC_TRNS , KC_F1     , KC_F2     , KC_F3   , KC_F4    , KC_F5        ,    KC_F6	  , KC_UNDS  , KC_PLUS  , KC_LCBR , KC_RCBR , KC_TRNS , KC_TRNS ,
	//-----------|---------|-----------|-----------|---------|----------|--------------|	|---------|----------|----------|---------|---------|---------|---------|
			KC_TRNS  , KC_TRNS , KC_F7     , KC_F8     , KC_F9   , KC_F10   , KC_F11       ,    KC_F12  , KC_TRNS  , KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
	//-----------|---------|-----------|-----------|---------|----------|--------------|  |---------|----------|----------|---------|---------|---------|---------|
			KC_TRNS  , KC_TRNS , KC_TRNS   , KC_TRNS   , KC_TRNS , KC_TRNS  , KC_TRNS      ,    KC_TRNS , MO(3)    , KC_MNXT  , KC_VOLD , KC_VOLU , KC_MPLY , KC_MUTE
	//-----------|---------|-----------|-----------|---------|----------|--------------|	|---------|----------|----------|---------|---------|---------|---------|``
),

[2] = LAYOUT_ortho_5x14(
	//-----------|---------|-----------|-----------|---------|----------|-------------|		|---------|----------|----------|-----------|----------|----------|---------|
			KC_TRNS  , KC_TILD , KC_F1     , KC_F2     , KC_F3   , KC_F4    , KC_F5       ,     KC_F6	 	, KC_F7  	 , KC_F8  	, KC_PSLS		, KC_PAST  , KC_PMNS  , KC_DEL  ,
	//-----------|---------|-----------|-----------|---------|----------|-------------|		|---------|----------|----------|-----------|----------|----------|---------|
			KC_UNDS  , KC_TRNS , KC_1      , KC_2      , KC_3    , KC_4     , KC_5        ,     KC_6 	 	, KC_7   	 , KC_P7  	, KC_P8   	, KC_P9    , KC_PPLS  , KC_RCBR ,
	//-----------|---------|-----------|-----------|---------|----------|-------------|		|---------|----------|----------|-----------|----------|----------|---------|
			KC_PLUS  , KC_TRNS , KC_F1     , KC_F2     , KC_F3   , KC_F4    , KC_F5       ,     KC_F6		, KC_MINS	 , KC_P4  	, KC_P5   	, KC_P6    , KC_PPLS  , KC_TRNS ,
	//-----------|---------|-----------|-----------|---------|----------|-------------|		|---------|----------|----------|-----------|----------|----------|---------|
			KC_TRNS  , KC_TRNS , KC_F7     , KC_F8     , KC_F9   , KC_F10   , KC_F11      ,     KC_F12	, KC_NUHS	 , KC_P1  	, KC_P2   	, KC_P3    , KC_PENT  , KC_TRNS ,
	//-----------|---------|-----------|-----------|---------|----------|-------------|		|---------|----------|----------|-----------|----------|----------|---------|
			KC_TRNS  , KC_TRNS , KC_TRNS   , KC_TRNS   , KC_TRNS , KC_TRNS  , KC_TRNS     ,     KC_TRNS , MO(3)  	 , KC_P0  	, KC_P0   	, KC_PDOT  , KC_PENT  , KC_TRNS
	//-----------|---------|-----------|-----------|---------|----------|-------------|		|---------|----------|----------|-----------|----------|----------|---------|
	),

	[3] = LAYOUT_ortho_5x14(
	//-------|--------|--------|--------|--------|--------|--------|							   -------|--------|--------|--------|--------|--------|--------|
		KC_TRNS, KC_F1	, KC_F2	 , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,					 		   KC_F7	 , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_DEL,
	//-------|--------|--------|--------|--------|--------|--------|							   -------|--------|--------|--------|--------|--------|--------|
		KC_TRNS, KC_TRNS, RESET	 , RGB_TOG, RGB_MOD, RGB_HUD, KC_TRNS,							   RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, KC_TRNS, KC_DEL , KC_TRNS,
	//-------|--------|--------|--------|--------|--------|--------|							   -------|--------|--------|--------|--------|--------|--------|
		KC_TRNS, KC_TRNS, KC_TRNS, RGB_HUI, AU_ON  , AU_OFF , AG_NORM,							   AG_SWAP, TO(0)  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//-------|--------|--------|--------|--------|--------|--------|							   -------|--------|--------|--------|--------|--------|--------|
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,							   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//-------|--------|--------|--------|--------|--------|--------|							   -------|--------|--------|--------|--------|--------|--------|
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 							   KC_TRNS, BL_TOGG, BL_INC , BL_DEC , BL_BRTG, KC_TRNS, KC_TRNS
	//-------|--------|--------|--------|--------|--------|--------|							   -------|--------|--------|--------|--------|--------|--------|
	)
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {

  // //Tap once for space, tap twice for enter
  // [TD_SPC_ENT]  = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT),
  //Tap once for Left Shift, twice for Caps Lock
  // [TD_KC_LSFT_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
  //Tap once for Right Shift, twice for Caps Lock
  // [TD_KC_RSFT_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS)
  // Tap once for left bracket, twice for right bracket
  [TD_BRC_L_R]  = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
  [TD_BRC_R_L]  = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_LBRC),
  [TD_G_E]  		= ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_ESC)


// Other declarations would go here, separated by commas, if you have them

};
