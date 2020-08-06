#include QMK_KEYBOARD_H
#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "rgblight.h"
;

enum custom_keycodes{
	TD_BRAK = 0,
	TD_G_E,
	TD_BSLSH,
	TD_SWAP_HANDS,
	TD_LINE
};
typedef struct {
  bool is_press_action;
  int state;
} tap;
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
	DOUBLE_SINGLE_TAP = 5,
};
int cur_dance (qk_tap_dance_state_t *state);
void spc_finished(qk_tap_dance_state_t *state, void *user_data);
void spc_reset(qk_tap_dance_state_t *state, void *user_data);

#define TD_BRK TD(TD_BRAK)
#define TD_SWAP TD(TD_SWAP_HANDS)
#define TD_HOME TD(TD_LINE)
#define TD_SLSH TD(TD_BSLSH)
#define KC_G_E TD(TD_G_E)
#define PRV_TB LCTL(KC_PGUP)
#define NXT_TB LCTL(KC_PGDN)
#define LS(l) LT(l, KC_SPC)

enum layer_names {
	_MAIN,
	_FN,
	_NUM,
	_SWAP,
	_LF
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_MAIN] = LAYOUT_ortho_5x14(
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|-----------|
		 	KC_G_E	,	KC_1			,	KC_2		,	KC_3		,	KC_4		,	KC_5		,	KC_6					,		KC_7					,	KC_8		,	KC_9		,	KC_0		,	KC_MINS	,	KC_EQL	,	KC_BSPC		,
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|-----------|
		 	KC_TAB	,	KC_Q			,	KC_W		,	KC_E		,	KC_R		,	KC_T		,	MO(_NUM)			,		KC_Y					,	KC_U		,	KC_I		,	KC_O		,	KC_P		,	TD_BRK	,	TD_SLSH		,
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|-----------|
		 	KC_ESC	,	KC_A			,	KC_S		,	KC_D		,	KC_F		,	KC_G		,	LALT(KC_GRV)	,		KC_H					,	KC_J		,	KC_K		,	KC_L		,	KC_SCLN	,	KC_QUOT	,	KC_ENT		,
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|-----------|
		 	KC_LSFT	,	KC_Z			,	KC_X		,	KC_C		,	KC_V		,	KC_B		,	TD_HOME				,		KC_N					,	KC_M		,	KC_COMM	,	KC_DOT	,	KC_SLSH	,	KC_UP		,	MO(_NUM)	,
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|-----------|
		 	KC_LCTL	,	KC_LGUI		,	KC_LALT	,	KC_LALT	,	TD_SWAP	,	KC_SPC	,	KC_SPC				,		KC_SPC				,	TD_SWAP	,	KC_RALT	,	KC_APP	,	KC_LEFT	,	KC_DOWN	,	KC_RGHT
		 	// KC_LCTL	,	KC_LALT		,	KC_LGUI	,	KC_LGUI	,	MO(_FN)	,	KC_SPC	,	KC_SPC				,		KC_SPC				,	KC_SPC	,	KC_RALT	,	KC_APP	,	KC_LEFT	,	KC_DOWN	,	KC_RGHT
	// 		KC_LCTL	,	KC_LALT		,	KC_LGUI	,	KC_LGUI	,	MO(_FN)	,	KC_SPC	,	SH_T(KC_SPC)	,		SH_T(KC_SPC)	,	LS(_FN)	,	KC_RALT	,	KC_APP	,	KC_LEFT	,	KC_DOWN	,	KC_RGHT
 	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|-----------|
	),
	[_FN] = LAYOUT_ortho_5x14(
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|---------|
			KC_TRNS	,	KC_F1			,	KC_F2		,	KC_F3		,	KC_F4		,	KC_F5		,	KC_F6					,		KC_F7					,	KC_F8		,	KC_F9		,	KC_F10	,	KC_F11	,	KC_F12	,	KC_DEL	,
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|---------|
			KC_PGUP	,	KC_PAUSE	,	KC_F12	,	KC_END	,	KC_TRNS	,	KC_TRNS	,	DF(_SWAP)			,		KC_TRNS				,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_LCBR	,	KC_RCBR	,
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|---------|
			KC_PGDN	,	KC_HOME		,	KC_END	,	KC_TRNS	,	KC_PSCR	,	KC_TRNS	,	LALT(KC_TAB)	,		KC_TRNS				,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|---------|
			KC_TRNS	,	KC_INS		,	KC_TRNS	,	PRV_TB	, NXT_TB	,	KC_F12	,	KC_PAUSE			,		KC_TRNS				,	KC_TRNS	,	KC_MPRV	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|---------|
			KC_TRNS	,	KC_TRNS		,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS				,		KC_TRNS				,	KC_TRNS	,	KC_MNXT	,	KC_VOLD	,	KC_VOLU	,	KC_MPLY	,	KC_MUTE
			// KC_TRNS	,	KC_TRNS		,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	TG(_LF)	,	TG(_LF)				,		KC_TRNS				,	KC_TRNS	,	KC_MNXT	,	KC_VOLD	,	KC_VOLU	,	KC_MPLY	,	KC_MUTE
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|---------|
	),
	[_NUM] = LAYOUT_ortho_5x14(
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|---------|
			KC_TRNS	,	KC_F1			,	KC_F2		,	KC_F3		,	KC_F4		,	KC_F5		,	KC_F6					,		KC_F7					,	KC_F8		,	KC_F9		,	KC_NLCK	,	KC_PSLS	,	KC_PAST	,	KC_PMNS	,
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|---------|
			KC_TRNS	,	KC_TRNS		,	RESET	 	,	RGB_TOG	,	RGB_MOD	,	RGB_HUD	,	KC_TRNS				,		RGB_SAD				,	RGB_SAI	,	KC_TRNS	,	KC_P7		,	KC_P8		,	KC_P9		,	KC_PPLS	,
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|---------|
			KC_TRNS	,	KC_TRNS		,	KC_TRNS	,	KC_TRNS	,	AU_ON		,	AU_OFF	,	AG_NORM				,		RGB_VAI				,	RGB_VAD	,	KC_TRNS	,	KC_P4		,	KC_P5		,	KC_P6		,	KC_PENT	,
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|---------|
			KC_TRNS	,	KC_TRNS		,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS				,		BL_INC				,	BL_DEC	,	KC_P0		,	KC_P1		,	KC_P2		,	KC_P3		,	KC_TRNS	,
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|---------|
			KC_TRNS	,	KC_TRNS		,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS				,		BL_TOGG				,	BL_TOGG	,	KC_TRNS	,	KC_P0		,	KC_P0		,	KC_PDOT	,	KC_TRNS
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|---------|
	),
	[_SWAP] = LAYOUT_ortho_5x14( // This is used b/c my pc's sometimes swap GUI and ALT, this toggles them
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|-----------|
		 	KC_TRNS	,	KC_TRNS		,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS				,		KC_TRNS				,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS		,
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|-----------|
		 	KC_TRNS	,	KC_TRNS		,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS				,		KC_TRNS				,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS		,
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|-----------|
		 	KC_TRNS	,	KC_TRNS		,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS				,		KC_TRNS				,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS		,
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|-----------|
		 	KC_TRNS	,	KC_TRNS		,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS				,		KC_TRNS				,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS		,
	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|-----------|
		 	KC_TRNS	,	KC_LALT	  ,	KC_LGUI ,	KC_LGUI	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS       ,		KC_TRNS				,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_RGHT
 	//|---------|-----------|---------|---------|---------|---------|---------------|	|---------------|---------|---------|---------|---------|---------|-----------|
	),
	[_LF] = LAYOUT_ortho_5x14(
	//|---------|-----------|---------|---------|---------|---------|---------------|	|-------------|---------|---------|---------|---------|---------|---------|
			KC_BSPC	,	KC_EQL		,	KC_MINS	,	KC_0		,	KC_9		,	KC_8		,	KC_7					,		KC_6				,	KC_5		,	KC_4		,	KC_3		,	KC_2		,	KC_1		,	KC_GRV	,
	//|---------|-----------|---------|---------|---------|---------|---------------|	|-------------|---------|---------|---------|---------|---------|---------|
			TD_SLSH	,	TD_BRK		,	KC_P		,	KC_O		,	KC_I		,	KC_U		,	KC_Y					,		MO(_NUM)		,	KC_T		,	KC_R		,	KC_E		,	KC_W		,	KC_Q		,	KC_TAB	,
	//|---------|-----------|---------|---------|---------|---------|---------------|	|-------------|---------|---------|---------|---------|---------|---------|
			KC_ENT	,	KC_QUOT		,	KC_SCLN	,	KC_L		,	KC_K		,	KC_J		,	KC_H					,		LALT(KC_GRV),	KC_G		,	KC_F		,	KC_D		,	KC_S		,	KC_A		,	KC_ESC	,
	//|---------|-----------|---------|---------|---------|---------|---------------|	|-------------|---------|---------|---------|---------|---------|---------|
			KC_TRNS	,	KC_UP			,	KC_SLSH	,	KC_DOT	,	KC_COMM	,	KC_M		,	KC_N					,		MO(_LF)			,	KC_B		,	KC_V		,	KC_C		,	KC_X		,	KC_Z		,	KC_LSFT	,
	//|---------|-----------|---------|---------|---------|---------|---------------|	|-------------|---------|---------|---------|---------|---------|---------|
			KC_TRNS	,	KC_TRNS		,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS				,		KC_TRNS			,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS	,	KC_TRNS
	//|---------|-----------|---------|---------|---------|---------|---------------|	|-------------|---------|---------|---------|---------|---------|---------|
	),
};
static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};


// determine the tapdance state to return
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  // if (state->count == 3) {
  //   if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
  //   else return TRIPLE_HOLD;
  // }
  else return 8; //magic number. At some point this method will expand to work for more presses
}
void spc_finished(qk_tap_dance_state_t *state, void *user_data)
{
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_HOLD: layer_on(_FN); break;
		case DOUBLE_HOLD: layer_on(_LF); break;
    // case DOUBLE_SINGLE_TAP: register_code(KC_SPC); unregister_code(KC_SPC); register_code(KC_SPC); break;
		// default: register_code(KC_SPC); break;
  }

}


void spc_reset(qk_tap_dance_state_t *state, void *user_data)
{
  switch (xtap_state.state) {
	  case SINGLE_HOLD: layer_off(_FN); break;
		case DOUBLE_HOLD: layer_off(_LF); break;
	  // case DOUBLE_SINGLE_TAP: unregister_code(KC_SPC); break;
		// default: unregister_code(KC_SPC); break;
  }
  xtap_state.state = 0;
}
/*
// void spc_finished(qk_tap_dance_state_t *state, void *user_data)
// {
//   xtap_state.state = cur_dance(state);
//   switch (xtap_state.state) {
//     case SINGLE_TAP: register_code(KC_SPC); break;
//     case SINGLE_HOLD: break;
//     case DOUBLE_TAP: break;
// 		case DOUBLE_HOLD: layer_on(_LF); break;
//     case DOUBLE_SINGLE_TAP: register_code(KC_SPC); unregister_code(KC_SPC); register_code(KC_SPC); break;
// 		default: register_code(KC_SPC); break;
//   }
//
// }
//
//
// void spc_reset(qk_tap_dance_state_t *state, void *user_data)
// {
//   switch (xtap_state.state) {
// 	  case SINGLE_TAP: unregister_code(KC_SPC); break;
// 	  case SINGLE_HOLD: break;
// 	  case DOUBLE_TAP: break;
// 		case DOUBLE_HOLD: layer_off(_LF); break;
// 	  case DOUBLE_SINGLE_TAP: unregister_code(KC_SPC); break;
// 		default: unregister_code(KC_SPC); break;
//   }
//   xtap_state.state = 0;
// }
*/
//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_BRAK]		= ACTION_TAP_DANCE_DOUBLE(KC_LBRC,	KC_RBRC),
	[TD_G_E]		= ACTION_TAP_DANCE_DOUBLE(KC_GRV,	KC_ESC),
	[TD_BSLSH]	= ACTION_TAP_DANCE_DOUBLE(KC_BSLS,	KC_SLSH),
	[TD_LINE]		= ACTION_TAP_DANCE_DOUBLE(KC_HOME,	KC_END),
	[TD_SWAP_HANDS]		= ACTION_TAP_DANCE_FN_ADVANCED(NULL, spc_finished, spc_reset)
};
