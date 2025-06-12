// keyboards/keebio/iris/keymaps/colemak_dh/keymap.c
#include QMK_KEYBOARD_H
#include "quantum.h" // For layer_state_is()
#ifdef RGB_MATRIX_ENABLE
#include "rgb_matrix.h" // Include here, *outside* the other #ifdef
#endif
#include "matrix.h"

#define _COLEMAK 0
#define _NUMPAD 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 4


// Tap Dance Definitions
typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;


// Tap dance enums
enum {
    TD_ESC_EQL = 0,
    TD_BSLS_INS = 1,
    TD_HH_GRV_LC_LA = 2,
    TD_HH_RCTL_RALT = 3,
    TD_LSFT_CAPS = 4,
    TD_RSFT_QUOT = 5
};

// Tap Dance State
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;


// Tap Dance Action Structure
typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;


// Tap Dance State Functions
td_state_t cur_dance(tap_dance_state_t *state);

// Function Prototypes
// for left control and left alt
void grv_lctl_lalt_finished(tap_dance_state_t *state, void *user_data);
void grv_lctl_lalt_reset(tap_dance_state_t *state, void *user_data);
// for right control and right alt
void rctl_ralt_finished(tap_dance_state_t *state, void *user_data);
void rctl_ralt_reset(tap_dance_state_t *state, void *user_data);

// Tap Dance Actions
tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC_EQL] = ACTION_TAP_DANCE_DOUBLE(KC_EQL, KC_ESC),
    [TD_BSLS_INS] = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_INS),
    [TD_HH_GRV_LC_LA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, grv_lctl_lalt_finished, grv_lctl_lalt_reset),
    [TD_HH_RCTL_RALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rctl_ralt_finished, rctl_ralt_reset),
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)

};

// Custom Keycodes
enum custom_keycodes {
    LIGHT = SAFE_RANGE,
    NUMPAD
    // LOWER,
    // RAISE,
    // ADJUST
 };


// Mod-Tap for KC_QUOT on tap, ALT on hold
#define MT_QUOT_ALT MT(MOD_RCTL, KC_QUOT)


// Layout (Colemak-DHm)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_COLEMAK] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
    TD(TD_ESC_EQL),  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN, TD(TD_BSLS_INS),
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
   TD(TD_LSFT_CAPS), KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                               KC_M,    KC_N,    KC_E,    KC_I,    KC_O,   RSFT_T(KC_QUOT),
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
TD(TD_HH_GRV_LC_LA),  KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,   KC_HOME,           KC_END,   KC_K,    KC_H,   KC_COMM, KC_DOT, KC_SLSH, TD(TD_HH_RCTL_RALT),
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                          KC_BSPC,  KC_DEL, MO(_LOWER),              MO(_RAISE),  KC_ENT,  KC_SPC
                                      // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
                                    ),
    [_NUMPAD] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
            _______, _______, _______, _______, _______, _______,                            KC_NUM, _______, _______, _______, _______, _______,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            _______, _______, KC_UP,   _______, _______, _______,                            KC_PAST, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, _______,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,                            KC_PSLS, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            _______, _______, _______, _______, _______, _______, _______,          _______, KC_PDOT, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                            _______, _______, _______,                    _______, _______, KC_P0
                                        // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
        ),


    [_LOWER] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
            KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            _______, _______, KC_UP,   _______, KC_PSCR, _______,                            _______, _______, _______, _______, _______, _______,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,                            _______, _______, _______, _______, _______, _______,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            _______, _______, KC_LT,   KC_LBRC, KC_LCBR, KC_LPRN, KC_MUTE,         KC_APP,   KC_RPRN, KC_RCBR, KC_RBRC, KC_GT,   KC_RALT, _______,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                          _______,  _______, _______,                   _______, _______, _______
                                      // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
        ),
    [_RAISE] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
            _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                            KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            _______, _______, _______, _______, KC_PAUS, _______,                            _______, KC_SCRL, _______, _______, _______, KC_F12,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            _______, _______, _______, _______, _______, _______,                            _______, _______, _______, KC_INS,  _______, _______,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            _______, KC_RALT, KC_LWIN, _______, _______, _______, KC_CALC,          _______, _______, _______, _______, _______, _______, _______,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                          _______, _______, _______,                    _______, _______, _______
                                      // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
        ),

    [_ADJUST] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
            _______, NUMPAD,  _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            _______, _______, _______, _______, _______, _______,                            LIGHT,   _______, _______, _______, _______, _______,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            _______, _______, _______, _______, QK_BOOT, _______,                            RGB_MOD, RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI, _______,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_LWIN, _______, _______, _______, DB_TOGG, _______,  KC_PWR,          _______,RGB_RMOD, RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD, KC_APP ,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                            _______, _______, _______,                   _______, _______, _______
                                        // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
        )
};


/**
 * @brief Cycle between no lighting, rainbow animation and solid back lighting modes. Using a custom
 *          "no light" mode instead of RGB_MATRIX_NONE (for some reason, the keyboard keeps going to
 *          RGB_MATRIX_SOLID_COLOR when we try using RGB_MATRIX_NONE).
 */
 void next_light_mode(void) {
    switch(rgb_matrix_get_mode()) {
       case RGB_MATRIX_CUSTOM_no_light:
          rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
          break;
       case RGB_MATRIX_SOLID_COLOR:
          rgb_matrix_mode(RGB_MATRIX_CYCLE_LEFT_RIGHT);
          break;
       default:
          rgb_matrix_mode(RGB_MATRIX_CUSTOM_no_light);
          break;
    }
 }


 // Custom keycode processing
 bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // tap_dance_action_t *action;

    switch (keycode) {

/*         case TD(CT_CLN):  // list all tap dance keycodes with tap-hold configurations
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            return false;
            break; */
       case LIGHT:
            if (record->event.pressed) {
                next_light_mode();
            }
            return false;
            break;
       case NUMPAD:
            if (record->event.pressed) {
                layer_invert(_NUMPAD);
            }
            return false;
            break;
/*        case LOWER:
          if (record->event.pressed) {
             layer_on(_LOWER);
             update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
             layer_off(_LOWER);

             update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
       case RAISE:
          if (record->event.pressed) {
             layer_on(_RAISE);
             update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
             layer_off(_RAISE);
             update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
       case ADJUST:
          if (record->event.pressed) {
             layer_on(_ADJUST);
          } else {
             layer_off(_ADJUST);
          }
          return false;
          break;
*/
    }
    return true;
 }


// Encoder support
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case _COLEMAK:
            if (index == 0) {
                tap_code16(clockwise ? KC_RGHT : KC_LEFT);
            } else {
                tap_code16(clockwise ? KC_DOWN : KC_UP);
            }
            break;
        case _LOWER:
            if (index == 0) {
                tap_code(clockwise ? KC_BRIU  : KC_BRID);
            } else {
                tap_code(clockwise ? KC_PGDN : KC_PGUP);
            }
            break;
        case _RAISE:
            if (index == 0) {
                tap_code(clockwise ? KC_VOLU: KC_VOLD);
            } else {
                tap_code(clockwise ? KC_MPLY : KC_MUTE);
            }
            break;
        case _ADJUST:
            if (index == 0) {
                tap_code16(clockwise ? BL_UP : BL_DOWN );
            } else {
                tap_code16(clockwise ? KC_WBAK : KC_WFWD);
            }
            break;
    }
    return false;
}

// Add this function to enable tri-layer logic:
void matrix_scan_user(void) {
    if (layer_state_is(_LOWER) || layer_state_is(_RAISE)) {
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
}


uint8_t min(uint8_t a, uint8_t b) {
    if (a < b) {
       return a;
    }
    return b;
 }

 uint8_t max(uint8_t a, uint8_t b) {
    if (a > b) {
       return a;
    }
    return b;
 }


void set_range(uint8_t start, uint8_t stop, uint8_t led_min, uint8_t led_max, uint8_t red, uint8_t green, uint8_t blue) {
    if (stop < led_min || led_max < start) {
       // Out of range
       return;
    }

    for(uint8_t i=max(start, led_min); i < min(stop, led_max); i++) {
       rgb_matrix_set_color(i, red, green, blue);
    }
 }

 bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_user()) {
       return false;
    }

    // Underglow lights for base layer.
    if (IS_LAYER_ON_STATE(default_layer_state, _COLEMAK)) {
       set_range(28, 31, led_min, led_max, 0, 0, 125);
       set_range(62, 65, led_min, led_max, 0, 0, 125);
       set_range(31, 34, led_min, led_max, 0, 125, 0);
       set_range(65, 68, led_min, led_max, 0, 125, 0);
    }

    // Keylights for numpad.
    if (IS_LAYER_ON(_NUMPAD)) {
       for (uint8_t i = led_min; i < led_max; i++) {
          if (i == 40 || i == 51 || i == 44 || i == 47 ) {
             // operaters
             rgb_matrix_set_color(i, 75, 0, 128);
          } else if (i == 52) {
             // numpad decimal
             rgb_matrix_set_color(i, 0, 0, 50);
          } else if (i == 56) {
             // numpad enter
             rgb_matrix_set_color(i, 150, 150, 150);
          } else if (i == 39) {
             // numpad lock
             rgb_matrix_set_color(i, 200, 0, 0);
          } else if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_KEYLIGHT)) {
             rgb_matrix_set_color(i, RGB_OFF);
          }
       }
    } else if (IS_LAYER_ON(_LOWER)) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if ((i >= 13 && i <= 15) || i == 9) {
                // arrow keys
                rgb_matrix_set_color(i, 179, 0, 0);
            } else if (i == 57) {
                // ALT key
                rgb_matrix_set_color(i, 200, 200, 0);
            } else if (i == 21 || i == 55) {
                // < and > keys
                rgb_matrix_set_color(i, 20, 60, 220);
            } else if (i == 20 || i == 54) {
                // [ and ] keys
                rgb_matrix_set_color(i, 0, 60, 120);
            } else if (i == 19 || i == 53) {
                // { and } keys
                rgb_matrix_set_color(i, 250, 250, 0);
            } else if (i == 18 || i == 52) {
                // ( and ) keys
                rgb_matrix_set_color(i, 250, 120, 0);

            } else if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_KEYLIGHT)) {
                rgb_matrix_set_color(i, RGB_OFF);
            }
        }
    } else if (IS_LAYER_ON(_RAISE)) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (i == 7) {
                // pause key
                rgb_matrix_set_color(i, 200, 0, 0);
            } else if (i == 23) {
                // ALT key
                rgb_matrix_set_color(i, 200, 200, 0);
            } else if (i == 41) {
                // scroll lock key
                rgb_matrix_set_color(i, 0, 200, 0);
            } else if (i == 48) {
                // insert
                rgb_matrix_set_color(i, 0, 0, 200);
            } else if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_KEYLIGHT)) {
                rgb_matrix_set_color(i, RGB_OFF);            }
        }
    }
    return true;
 }


/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicative that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currently not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustrating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t grv_lctl_lalt_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t rctl_ralt_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Tap Dance Functions for left control and left alt
// This function is called when the tap dance is finished
void grv_lctl_lalt_finished(tap_dance_state_t *state, void *user_data) {
    grv_lctl_lalt_tap_state.state = cur_dance(state);
    switch (grv_lctl_lalt_tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_GRV); break;
        case TD_SINGLE_HOLD: register_code(KC_LCTL); break;
        case TD_DOUBLE_TAP: register_code(KC_HOME); break;
        case TD_DOUBLE_HOLD: register_code(KC_LALT); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        // case TD_DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X); break;
        default: break;
    }
}

// Reset function for the left control and left alt tap dance
void rctl_ralt_finished(tap_dance_state_t *state, void *user_data) {
    rctl_ralt_tap_state.state = cur_dance(state);
    switch (rctl_ralt_tap_state.state) {
        case TD_SINGLE_HOLD: register_code(KC_RCTL); break;
        case TD_DOUBLE_HOLD: register_code(KC_RALT); break;
        case TD_DOUBLE_TAP: register_code(KC_END); break;
        // case TD_DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X); break;
        default: break;
    }
}
// Reset function for the right control and right alt tap dance
// This function is called when the tap dance is reset
void grv_lctl_lalt_reset(tap_dance_state_t *state, void *user_data) {
    switch (grv_lctl_lalt_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_GRV); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LCTL); break;
        case TD_DOUBLE_TAP: unregister_code(KC_HOME); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LALT); break;
        // case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X); break;
        default: break;
    }
    grv_lctl_lalt_tap_state.state = TD_NONE;
}

// Reset function for the right control and right alt tap dance
void rctl_ralt_reset(tap_dance_state_t *state, void *user_data) {
    switch (rctl_ralt_tap_state.state) {
        case TD_SINGLE_HOLD: unregister_code(KC_RCTL); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_RALT); break;
        case TD_DOUBLE_TAP: unregister_code(KC_END); break;
        // case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X); break;
        default: break;
    }
    rctl_ralt_tap_state.state = TD_NONE;
}

