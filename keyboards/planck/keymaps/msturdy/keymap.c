// 
// build with:
// 
//    cd ~/Projects/keyboard/qmk_firmware
//    make planck/ez:msturdy
// 

#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "muse.h"
#endif
#include "eeprom.h"
// #include "keymap_german.h"
// #include "keymap_nordic.h"
// #include "keymap_french.h"
// #include "keymap_spanish.h"
// #include "keymap_hungarian.h"
// #include "keymap_swedish.h"
#include "keymap_br_abnt2.h"
// #include "keymap_canadian_multilingual.h"
// #include "keymap_german_ch.h"
// #include "keymap_jp.h"

// #define KC_MAC_UNDO LGUI(KC_Z)
// #define KC_MAC_CUT LGUI(KC_X)
// #define KC_MAC_COPY LGUI(KC_C)
// #define KC_MAC_PASTE LGUI(KC_V)
// #define KC_PC_UNDO LCTL(KC_Z)
// #define KC_PC_CUT LCTL(KC_X)
// #define KC_PC_COPY LCTL(KC_C)
// #define KC_PC_PASTE LCTL(KC_V)
// #define ES_LESS_MAC KC_GRAVE
// #define ES_GRTR_MAC LSFT(KC_GRAVE)
// #define ES_BSLS_MAC ALGR(KC_6)
// #define NO_PIPE_ALT KC_GRAVE
// #define NO_BSLS_ALT KC_EQUAL
#define KC_TRANS KC_TRANSPARENT

enum planck_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  BR_LSPO,
  BR_RSPC,
};

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
};

//Tap Dance Declarations
enum {
  TD_SHFT_CAPS = 0,
  TD_COMMA_ACT,
  TD_QUOTE_TLD,
  TD_COLON_CDL,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

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
  // // once for -  twice for ´`
  [TD_COMMA_ACT]  = ACTION_TAP_DANCE_DOUBLE(KC_COMMA, BR_ACUT),
  // once for '  twice for ~^
  [TD_QUOTE_TLD]  = ACTION_TAP_DANCE_DOUBLE(BR_QUOT, BR_TILD),
  // once for :  twice for çÇ
  [TD_COLON_CDL]  = ACTION_TAP_DANCE_DOUBLE(BR_SCLN, BR_CCDL),
  // Tap once for Shift, twice for Caps Lock
  [TD_SHFT_CAPS]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_caps_lock_finished, dance_caps_lock_reset),
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | ; ç  | ' ~  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Hyper| GUI  |  Alt |Lower |    Space    |Raise |   /  | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
  [_BASE] = LAYOUT_planck_grid(
    KC_ESCAPE,        KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,     KC_Y,  KC_U,  KC_I,             KC_O,    KC_P,             KC_BSPACE,
    LSFT_T(KC_TAB),   KC_A,    KC_S,    KC_D,    KC_F,  KC_G,     KC_H,  KC_J,  KC_K,             KC_L,    TD(TD_COLON_CDL), TD(TD_QUOTE_TLD),
    TD(TD_SHFT_CAPS), KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,     KC_N,  KC_M,  TD(TD_COMMA_ACT), KC_DOT,  KC_UP,            KC_ENTER,
    KC_LCTRL,         KC_HYPR, KC_LGUI, KC_LALT, LOWER, KC_SPACE, KC_NO, RAISE, BR_SLSH,          KC_LEFT, KC_DOWN,          KC_RIGHT
  ),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |      |      |  ª   |   º  |  °   |      |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | Home | End  |  €   |  £   |      |      |      |      |MsWhUp| MsUp |MsWhDn|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Ms 1 | Ms 3 | Ms 2 |      |             |      |      | MsLft| MsDn | MsRgt|
 * `-----------------------------------------------------------------------------------'
 */
  [_LOWER] = LAYOUT_planck_grid(
    KC_TILD,   KC_EXLM,    KC_AT,       KC_HASH,       KC_DLR,        KC_PERC,       KC_CIRC,  KC_AMPR,  KC_ASTR,   KC_LPRN,     KC_RPRN,  KC_TRANS,
    KC_DELETE, KC_TRANS,   KC_TRANS,    RALT(BR_LBRC), RALT(BR_RBRC), RALT(BR_SLSH), KC_TRANS, KC_UNDS,  KC_PLUS,   BR_LCBR,     BR_RCBR,  BR_PIPE,
    KC_TRANS,  KC_HOME,    KC_END,      RALT(KC_E),    RALT(KC_4),    KC_TRANS,      KC_TRANS, KC_TRANS, KC_TRANS,  KC_MS_WH_UP, KC_MS_U,  KC_MS_WH_DOWN,
    KC_TRANS,  KC_MS_BTN1, KC_MS_BTN3,  KC_MS_BTN2,    KC_TRANS,      KC_TRANS,      KC_NO,    KC_TRANS, KC_TRANS,  KC_MS_L,     KC_MS_D,  KC_MS_R
  ),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      | PgUp | PgDn |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
  [_RAISE] = LAYOUT_planck_grid(
    KC_GRAVE,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,   KC_7,          KC_8,                KC_9,              KC_0,            KC_TRANS,
    KC_DELETE, KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,  KC_MINUS,      KC_EQUAL,            BR_LBRC,           BR_RBRC,         BR_BSLS,
    KC_TRANS,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12, KC_NONUS_HASH, KC_NONUS_BSLASH,     KC_PGUP,           KC_PGDOWN,       KC_TRANS,
    KC_TRANS,  KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_NO,  KC_TRANS,      KC_MEDIA_NEXT_TRACK, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, KC_MEDIA_PLAY_PAUSE
  ),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  DEL |      |Aud on|AudOff|AudTog|      |      |RGBTog| brg+ | brg- |      |RESET |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |Mus on|MusOff|MusTog|      |      | Anim | hue+ | hue- |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
  [_ADJUST] = LAYOUT_planck_grid(
    KC_TRANS,   KC_TRANS,  KC_TRANS,  KC_TRANS,  KC_TRANS,  KC_TRANS,  KC_TRANS,  KC_TRANS,  KC_TRANS,  KC_TRANS,  KC_TRANS,  KC_TRANS,
    KC_DELETE,  KC_TRANS,  AU_ON,     AU_OFF,    AU_TOG,    KC_TRANS,  KC_TRANS,  RGB_TOG,   RGB_VAI,   RGB_VAD,   KC_TRANS,  RESET,
    KC_TRANS,   KC_TRANS,  MU_ON,     MU_OFF,    MU_TOG,    KC_TRANS,  KC_TRANS,  RGB_MOD,   RGB_HUI,   RGB_HUD,   KC_TRANS,  KC_TRANS,
    KC_TRANS,   KC_TRANS,  KC_TRANS,  KC_TRANS,  KC_TRANS,  KC_TRANS,  KC_NO,     KC_TRANS,  KC_TRANS,  KC_TRANS,  KC_TRANS,  KC_TRANS
  ),

};

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}


#define MY_WHT {0, 0, 255}
#define MY_RED {12, 225, 241}
#define MY_YLW {32, 255, 234}
#define MY_BLU {146, 224, 255}
#define MY_NOC {0, 0, 0}
// #define MY_GRN {0, 255, 118}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [0] = { MY_YLW, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_YLW, 
            MY_YLW, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_BLU, MY_BLU, 
            MY_YLW, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_BLU, MY_BLU, MY_WHT, MY_YLW, 
            MY_YLW, MY_YLW, MY_YLW, MY_YLW, MY_WHT,    MY_WHT,      MY_WHT, MY_BLU, MY_WHT, MY_WHT, MY_WHT 
          },

    [1] = { MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_NOC, 
            MY_YLW, MY_NOC, MY_NOC, MY_BLU, MY_BLU, MY_BLU, MY_NOC, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, 
            MY_NOC, MY_YLW, MY_YLW, MY_BLU, MY_BLU, MY_NOC, MY_NOC, MY_NOC, MY_NOC, MY_WHT, MY_WHT, MY_WHT, 
            MY_NOC, MY_WHT, MY_WHT, MY_WHT, MY_NOC,    MY_NOC,      MY_NOC, MY_NOC, MY_WHT, MY_WHT, MY_WHT 
          },

    [2] = { MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, MY_NOC, 
            MY_YLW, MY_BLU, MY_BLU, MY_BLU, MY_BLU, MY_BLU, MY_BLU, MY_RED, MY_RED, MY_RED, MY_RED, MY_RED, 
            MY_NOC, MY_BLU, MY_BLU, MY_BLU, MY_BLU, MY_BLU, MY_BLU, MY_WHT, MY_WHT, MY_YLW, MY_YLW, MY_NOC, 
            MY_NOC, MY_NOC, MY_NOC, MY_NOC, MY_NOC,    MY_NOC,      MY_NOC, MY_NOC, MY_NOC, MY_NOC, MY_NOC 
          },

    [3] = { MY_NOC, MY_NOC, MY_NOC, MY_NOC, MY_NOC, MY_NOC, MY_NOC, MY_NOC, MY_NOC, MY_NOC, MY_NOC, MY_NOC, 
            MY_YLW, MY_NOC, MY_WHT, MY_WHT, MY_WHT, MY_NOC, MY_NOC, MY_NOC, MY_NOC, MY_NOC, MY_NOC, MY_BLU, 
            MY_NOC, MY_NOC, MY_WHT, MY_WHT, MY_WHT, MY_NOC, MY_NOC, MY_NOC, MY_NOC, MY_NOC, MY_NOC, MY_NOC, 
            MY_NOC, MY_NOC, MY_NOC, MY_NOC, MY_NOC,    MY_NOC,      MY_NOC, MY_NOC, MY_NOC, MY_NOC, MY_NOC 
          },

};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (g_suspend_state || keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BR_LSPO:
      perform_space_cadet(record, KC_LSFT, KC_LSFT, KC_9);
      return false;
    case BR_RSPC:
      perform_space_cadet(record, KC_LSFT, KC_LSFT, KC_0);
      return false;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }
  return true;
}

#ifdef AUDIO_ENABLE
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo+=1;
            } else {
                muse_tempo-=1;
            }
        }
    } else {
        if (clockwise) {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_DOWN);
            unregister_code(KC_MS_WH_DOWN);
        #else
            register_code(KC_PGDN);
            unregister_code(KC_PGDN);
        #endif
        } else {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_UP);
            unregister_code(KC_MS_WH_UP);
        #else
            register_code(KC_PGUP);
            unregister_code(KC_PGUP);
        #endif
        }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
    case RAISE:
    case LOWER:
        return false;
    default:
        return true;
    }
}
#endif

uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}