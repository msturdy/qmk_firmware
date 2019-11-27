#include QMK_KEYBOARD_H
// #include "version.h"

#define HOME 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // mouse and media keys
#define GAME 3 // "game" keys, not really used
#define SUBL 4 // shortcuts and things for sublime text editor
#define RGHT 5 // mirror right hand to left
#define ESKY 6 // Endless Sky keyboard

enum custom_keycodes {
  EPRM = SAFE_RANGE,
  VRSN,
  RGB_SLD,
  DYNAMIC_MACRO_RANGE // must be last in the list
};
// must be included after the DYNAMIC_MACRO_RANGE is defined.
#include "dynamic_macro.h"

//Tap Dance Declarations
enum {
  TD_SHFT_CAPS = 0,
  TD_MINUS_ACT,
  TD_QUOTE_TLD,
  TD_COLON_CDL,
  TD_LAYER_CHG
 };

// TAP DANCE - Layer switch
// turn off all layers then activate one (or not)
void dance_layer_shift_finished (qk_tap_dance_state_t *state, void *user_data) {
  layer_off(SYMB);
  layer_off(MDIA);
  layer_off(GAME);
  // 2 for layer 2
  if (state->count == 2) { 
    layer_on(SYMB);
  }
  // 3 for layer 3
  else if (state->count == 3) {
    layer_on(MDIA);
  } 
  // 4 for Endless Sky
  else if (state->count == 4) {
    layer_on(ESKY);
  } 
}

// turn off all layers then activate one (or not)
void dance_layer_shift_reset (qk_tap_dance_state_t *state, void *user_data) {
  layer_off(SYMB);
  layer_off(MDIA);
  layer_off(GAME);
  // 2 for layer 2
  if (state->count == 2) { 
    layer_on(SYMB);
  }
  // 3 for layer 3
  else if (state->count == 3) {
    layer_on(MDIA);
  }
  // 4 for Endless Sky
  else if (state->count == 4) {
    layer_on(ESKY);
  } 
}

// TAP DANCE - caps lock
// caps lock on 3 presses
void dance_caps_lock_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count < 3) {
    register_code(KC_LSFT);
  } 
  if (state->count == 3) {
    register_code(KC_CAPS);
  } 
}
void dance_caps_lock_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count < 3) {
    unregister_code(KC_LSFT);
  } 
  if (state->count == 3) {
    unregister_code(KC_CAPS);
  } 
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // once for -  twice for ´`
  [TD_MINUS_ACT]  = ACTION_TAP_DANCE_DOUBLE(KC_MINUS, BR_ACUT),
  // once for '  twice for ~^
  [TD_QUOTE_TLD]  = ACTION_TAP_DANCE_DOUBLE(BR_QUOT, BR_TILD),
  // once for :  twice for çÇ
  [TD_COLON_CDL]  = ACTION_TAP_DANCE_DOUBLE(BR_SCLN, BR_CCDL),
  //Tap once for Shift, twice for Caps Lock
  [TD_SHFT_CAPS]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_caps_lock_finished, dance_caps_lock_reset),
  // tap dance layer shift
  [TD_LAYER_CHG]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_layer_shift_finished, dance_layer_shift_reset),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC   |   1  |   2  |   3  |   4  |   5  | term |           |  L1  |   6  |   7  |   8  |   9  |   0  | backsp |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   Q  |   W  |   E  |   R  |   T  |  Del |           |  = + |   Y  |   U  |   I  |   O  |   P  |  - ´   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  | J/Hyp| K/ctl|   L  | ; ç  |  ' ~   |
 * |--------+------+------+------+------+------| Enter|           | \ |  |------+------+------+------+------+--------|
 * | Cntl   |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |  /?  | Enter  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |TT(5) |TDSWCH| Super|  UP  | Down |                                       | Left | Right| ~L4  | menu | ~L2  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | light| anim |       | vol- | vol+ |
 *                                 ,------|------|------|       |------+------+------.
 *                                 | space|      | Meh  |       |      |      | space|
 *                                 | ~L1  |  ~L4 |------|       |------| RAlt | LAlt |
 *                                 |      |      | Hyper|       |      |      |      |
 *                                 `--------------------'       `--------------------'
 *
 *    tap dance on shift -> caps locks
 *    tap dance on minus -> acute/grave accents
 *    tap dance on quote -> circumflex/tilde accents
 *    tap dance on colon -> cedilha char
 */
[HOME] = LAYOUT_ergodox(
  // left hand
  KC_ESCAPE,        KC_1,              KC_2,      KC_3,     KC_4,      KC_5,    LCTL(LSFT(KC_Z)),
  KC_TAB,           KC_Q,              KC_W,      KC_E,     KC_R,      KC_T,    KC_DELETE,
  TD(TD_SHFT_CAPS), KC_A,              KC_S,      KC_D,     KC_F,      KC_G,
  KC_LCTRL,         KC_Z,              KC_X,      KC_C,     KC_V,      KC_B,    KC_ENT,
  TT(RGHT),         TD(TD_LAYER_CHG),  KC_LGUI,   KC_UP,    KC_DOWN,
                                                                   RGB_TOG,   RGB_MOD,
                                                                              KC_MEH,
                                                 LT(SYMB, KC_SPC), MO(SUBL),  KC_HYPR,
  // right hand
  TO(SYMB),     KC_6,    KC_7,         KC_8,         KC_9,      KC_0,              KC_BSPACE,
  KC_EQUAL,     KC_Y,    KC_U,         KC_I,         KC_O,      KC_P,              TD(TD_MINUS_ACT),
                KC_H,    HYPR_T(KC_J), LCTL_T(KC_K), KC_L,      TD(TD_COLON_CDL),  TD(TD_QUOTE_TLD),
  BR_BSLS,      KC_N,    KC_M,         KC_COMM,      KC_DOT,    BR_SLSH,           KC_ENT,
                         KC_LEFT,      KC_RIGHT,     MO(SUBL),  KC_APPLICATION,    MO(MDIA),
  KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, 
  KC_NO,
  KC_NO,   KC_RALT,  LALT_T(KC_SPC)
),
/* Keymap 1: Symbol Layer  
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * | ESC     |  F1  |  F2  |  F3  |  F4  |  F5  |  L0  |           |  L2  |  F6  |  F7  |  F8  |  F9  |  F10 | backsp |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |  ª   |  Del |           |      |  €   |   7  |   8  |   9  |   *  |   F11  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |  º   |------|           |------|  £   |   4  |   5  |   6  |   +  |   F12  |
 * |---------+------+------+------+------+------| enter|           |      |------+------+------+------+------+--------|
 * | Control |   %  |      |   [  |   ]  |  °   |      |           |      |      |   1  |   2  |   3  |   \  |  enter |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |TDSWCH|      | home |  end |                                       |   0  |   .  |   -  |   =  | ~L2  |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,--------------.         ,-------------.
 *                                        |autosft|toggle|         |Toggle|Solid |
 *                                 ,------|-------|------|         |------+------+------.
 *                                 |      | super |ctlprt|         |brght+| Hue- | Hue+ |
 *                                 | ~L1  |   +   |------|         |------|      |      |
 *                                 |      |   L   |print |         |brght-|      |      |
 *                                 `---------------------'         `--------------------'
 *
 *        left cluster toggle is to turn lights on/off
 *        right cluster toggle is to switch through animations 
 *        right cluster solid turns the aniumation to solid light 
 *        left cluster then second big key locks screen.  
 *        ctlprt is ctrl + printscr to take screenshot (selecting area).
 */
[SYMB] = LAYOUT_ergodox(
  // left hand
  KC_ESCAPE,  KC_F1,    KC_F2,     KC_F3,     KC_F4,     KC_F5,           TO(HOME),
  KC_NO,      KC_EXLM,  KC_AT,     BR_LCBR,   BR_RCBR,   RALT(BR_LBRC),   KC_DELETE,
  KC_NO,      KC_HASH,  KC_DLR,    KC_LPRN,   KC_RPRN,   RALT(BR_RBRC),
  KC_LCTRL,   KC_PERC,  KC_NO,     BR_LBRC,   BR_RBRC,   RALT(BR_SLSH),   KC_ENT,
  KC_NO,      KC_TRNS,  KC_NO,     KC_HOME,   KC_END,
                                               KC_ASTG,    RGB_TOG,
                                                           LCTL(KC_PSCR),
                                     KC_TRNS, LGUI(KC_L),  KC_PSCR,
  // right hand
  TO(MDIA),  KC_F6,      KC_F7,   KC_F8,   KC_F9,     KC_F10,    KC_BSPACE,
  KC_NO,     RALT(KC_E), KC_7,    KC_8,    KC_9,      KC_ASTR,   KC_F11,
             RALT(KC_4), KC_4,    KC_5,    KC_6,      KC_PLUS,   KC_F12,
  KC_NO,     KC_NO,      KC_1,    KC_2,    KC_3,      BR_BSLS,   KC_ENT,
                          KC_0,    KC_DOT,  KC_MINUS,  KC_EQL,    KC_TRNS,
  RGB_MODE_FORWARD,       RGBLIGHT_MODE_STATIC_LIGHT,
  RGB_VAI,
  RGB_VAD,    RGB_HUD,  RGB_HUI
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  Esc   | Prev | Play | Stop | Next |      |  L1  |           |  L3  |      |      |      |      |      | backsp |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Tab   |      |wh dwn| MsUp |wh up |      | Del  |           |      |      |   UP |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Shift  |      |MsLeft|MsDown|MsRght|      |------|           |------| LEFT | DOWN | RIGHT|      |      |  PgUp  |
 * |--------+------+------+------+------+------|enter |           |      |------+------+------+------+------+--------|
 * |Control |      |      |      |      |      |      |           |      |      |      |      |      |      |  PgDn  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |TDSWCH|Super |      |      |                                       |      |accel0|accel1|accel2| ~L2  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |reset |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 | Lclk | Mclk |------|       |------|      |Back  |
 *                                 |      |      | Rclk |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 *  reset - flashes the firmware.
 */
[MDIA] = LAYOUT_ergodox(
  // left hand
  KC_ESCAPE, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_STOP, KC_MEDIA_NEXT_TRACK, KC_NO,  TO(SYMB),  
  KC_TAB,    KC_NO,               KC_MS_WH_UP,         KC_MS_U,       KC_MS_WH_DOWN,       KC_NO,  KC_DELETE,  
  KC_LSFT,   KC_NO,               KC_MS_L,             KC_MS_D,       KC_MS_R,             KC_NO,
  KC_LCTRL,  KC_NO,               KC_NO,               KC_NO,         KC_NO,               KC_NO,  KC_ENT,  
  KC_NO,     KC_TRNS,             KC_LGUI,             KC_NO,         KC_NO,
                                               KC_NO,  RESET,  
                                                       KC_NO,  
                              KC_MS_BTN1, KC_MS_BTN3,  KC_MS_BTN2,   
  // right hand
  TO(GAME), KC_NO,   KC_NO,   KC_NO,        KC_NO,        KC_NO,        KC_BSPACE,  
  KC_NO,    KC_NO,   KC_UP,   KC_NO,        KC_NO,        KC_NO,        KC_NO,  
            KC_LEFT, KC_DOWN, KC_RIGHT,     KC_NO,        KC_NO,        KC_PGUP,
  KC_NO,    KC_NO,   KC_NO,   KC_MPRV,      KC_MNXT,      KC_NO,        KC_PGDN,  
                     KC_NO,   KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, KC_TRNS,  
  KC_NO,   KC_NO,  
  KC_NO,  
  KC_NO,   KC_NO,   KC_WBAK
),
/* Keymap 3: Gaming keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC   |   1  |  2   |  3   |  4   |   5  |  L2  |           |  L0  |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Tab   |   Q  |  Up  |  E   |      |      | Del  |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Shift | left | down | right|      |  L   |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|enter |           |      |------+------+------+------+------+--------|
 * |  LCTL  |   Z  |  X   |  C   | .    |  B   |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |TDSWCH|      | LAlt |      |                                       |      |      |      |      | ~L2  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |space |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[GAME] = LAYOUT_ergodox(
  // left hand
  KC_ESCAPE,  KC_1,     KC_2,     KC_3,      KC_4,     KC_5,    TO(MDIA),  
  KC_TAB,     KC_Q,     KC_UP,    KC_E,      KC_NO,    KC_NO,   KC_DELETE,  
  KC_LSFT,    KC_LEFT,  KC_DOWN,  KC_RIGHT,  KC_NO,    KC_L,  
  KC_LCTRL,   KC_Z,     KC_X,     KC_C,      KC_DOT,   KC_B,    KC_ENT,  
              KC_NO,    KC_TRNS,  KC_NO,     KC_LALT,  KC_NO,
                                             KC_NO,    KC_NO,  
                                                       KC_NO,  
                                     KC_SPC, KC_NO,    KC_NO,  
  // right hand
  TO(HOME),  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
  KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
                      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,  
  KC_NO,   KC_NO,  
  KC_NO,  
  KC_NO,   KC_NO,   KC_NO
),
/* Keymap 4: shortcuts and keys for sublime text editor
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | GRID |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | 1col | 2col | 3col |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      | 2row | 3row |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |slctup|slctdn|                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |  ~L4 |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 * 1col, 2col - switch sublime text layout to 1 column, 2 column etc.
 * slctup/slctdn - select up.
 */
[SUBL] = LAYOUT_ergodox(
  // left hand
  KC_NO,  KC_NO,  KC_NO,             KC_NO,             KC_NO,  KC_NO,     KC_NO,  
  KC_NO,  KC_NO,  LSFT(LALT(KC_1)),  LSFT(LALT(KC_5)),  KC_NO,  KC_NO,     KC_NO,  
  KC_NO,  KC_NO,  LSFT(LALT(KC_1)),  LSFT(LALT(KC_2)),  LSFT(LALT(KC_3)),  KC_NO,  
  KC_NO,  KC_NO,  LSFT(LALT(KC_1)),  LSFT(LALT(KC_8)),  LSFT(LALT(KC_9)),  KC_NO,     KC_NO,  
          KC_NO,  KC_NO,             KC_NO,             LSFT(LALT(KC_UP)),  LSFT(LALT(KC_DOWN)),
                                          KC_NO,  KC_NO,  
                                                  KC_NO,  
                                KC_NO,  KC_TRNS,  KC_NO,  
  // right hand
  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
                   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
  KC_NO,  KC_NO,  
  KC_NO,  
  KC_NO,  KC_NO,   KC_NO
),
/* Keymap 5: map right hand to left for one handed typing
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  6   |  7   |  8   |  9   |  0   | BKSP |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  Y   |  U   |  I   |  O   |  P   | - ´  |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   = +  |  H   |  J   |  K   |  L   | ; ç  |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------| ' ~  |           |      |------+------+------+------+------+--------|
 * |   \ |  |  N   |  M   |  ,   |  .   |  /   |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |TT(5) |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 * 1col, 2col - switch sublime text layout to 1 column, 2 column etc.
 * slctup/slctdn - select up.
 */
[RGHT] = LAYOUT_ergodox(
  // left hand
  KC_NO,    KC_6,     KC_7,    KC_8,     KC_9,               KC_0,               KC_BSPACE,  
  KC_NO,    KC_Y,     KC_U,    KC_I,     KC_O,               KC_P,               TD(TD_MINUS_ACT),  
  KC_EQUAL, KC_H,     KC_J,    KC_K,     KC_L,               TD(TD_COLON_CDL),  
  BR_BSLS,  KC_N,     KC_M,    KC_COMM,  KC_DOT,             BR_SLSH,            TD(TD_QUOTE_TLD),  
            KC_TRNS,  KC_NO,   KC_NO,    LSFT(LALT(KC_UP)),  LSFT(LALT(KC_DOWN)),
                                          KC_NO,  KC_NO,  
                                                  KC_NO,  
                                KC_NO,  KC_TRNS,  KC_NO,  
  // right hand
  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
                   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
  KC_NO,  KC_NO,  
  KC_NO,  
  KC_NO,  KC_NO,   KC_NO
),
/* Keymap 6: all the keys for Endless Sky
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ESC  | F11  |      |      |      |      |  L0  |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |  J   |  UP  |  L   |      |      |           |      |  C   |  E   |  Q   |  W   |  I   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | SHIFT  |      | LEFT | DWN  | RGHT |      |------|           |------|  F   |  R   |  N   |  T   |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |  G   |  H   |  D   |      |      |           |      |  A   |  M   |  S   |  B   |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 * 1col, 2col - switch sublime text layout to 1 column, 2 column etc.
 * slctup/slctdn - select up.
 */
[ESKY] = LAYOUT_ergodox(
  // left hand
  KC_ESCAPE,  KC_F11,    KC_NO,    KC_NO,     KC_NO,     KC_NO,  TO(HOME),  
  KC_NO,      KC_NO,     KC_J,     KC_UP,     KC_L,      KC_NO,  KC_NO,  
  KC_LSFT,    KC_NO,     KC_LEFT,  KC_DOWN,   KC_RIGHT,  KC_NO,  
  KC_NO,      KC_NO,     KC_G,     KC_H,      KC_D,      KC_NO,  KC_NO,  
              KC_NO,     KC_TRNS,  KC_NO,     KC_NO,     KC_NO,
                                            KC_NO,  KC_NO,  
                                                    KC_NO,  
                                   KC_NO,   KC_NO,  KC_NO,  
  // right hand
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,  
  KC_NO,  KC_C,   KC_E,   KC_Q,   KC_W,   KC_I,    KC_NO,  
          KC_F,   KC_R,   KC_N,   KC_T,   KC_NO,   KC_NO,
  KC_NO,  KC_A,   KC_M,   KC_S,   KC_B,   KC_NO,   KC_NO,  
                  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,  
  KC_NO,  KC_NO,  
  KC_NO,  
  KC_NO,  KC_NO,   KC_NO
),
};


// runs on every keypress
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (record->event.pressed) {
    switch (keycode) {
      case EPRM:
        eeconfig_init();
        return false;
    }
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  rgblight_enable_noeeprom(); // enables Rgb, without saving settings
  rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 1); // sets mode to breathing without saving
  rgblight_sethsv_noeeprom_white(); // sets the color to first layer without saving
};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  // turn all the LEDs off 
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
 
  // uint8_t layer = biton32(state);
  switch (biton32(state)) {

      case HOME:
        // pulsing white light, no LEDs
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 1);
        rgblight_sethsv_noeeprom_white();
        break;

      case SYMB:
        ergodox_right_led_1_on();  // lh LED, red
        rgblight_mode_noeeprom(1); // static colour
        rgblight_sethsv_noeeprom_red();
        break;
      
      case MDIA:
        ergodox_right_led_2_on();  // mid LED, green
        rgblight_mode_noeeprom(1); // static colour
        rgblight_sethsv_noeeprom_green();
        break;
      
      case GAME:
        ergodox_right_led_3_on();  // rh LED, blue
        rgblight_mode_noeeprom(1); // static colour
        rgblight_sethsv_noeeprom_blue();
        break;
      
      case SUBL:
        ergodox_right_led_1_on();  // lh LED, red
        ergodox_right_led_2_on();  // mid LED, green
        rgblight_mode_noeeprom(1); // static colour
        rgblight_sethsv_noeeprom_orange();
        break;

      case RGHT:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        rgblight_sethsv_noeeprom_goldenrod();

      default:
        break;
    }

  return state;
};
