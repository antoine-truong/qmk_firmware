// keyboards/keebio/iris/keymaps/colemak_dh/keymap.c
#include QMK_KEYBOARD_H
#include "quantum.h" // For layer_state_is()
#ifdef RGB_MATRIX_ENABLE
#include "rgb_matrix.h" // Include here, *outside* the other #ifdef
#endif
#include "matrix.h"
#include "config.h"

#define _COLEMAK 0
#define _NUMPAD 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 4

// Tap Dance Declarations
enum {
    TD_LSFT_CAPS = 0,
    TD_ESC_EQL = 1,

};

// Tap Dance Actions
tap_dance_action_t tap_dance_actions[] = {
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_ESC_EQL] = ACTION_TAP_DANCE_DOUBLE(KC_EQL, KC_ESC),



};

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
   TD(TD_LSFT_CAPS),  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN, KC_BSLS,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
           KC_LSFT,  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                               KC_M,    KC_N,    KC_E,    KC_I,    KC_O,   RSFT_T(KC_QUOT),
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
           KC_LCTL,  KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,   KC_HOME,           KC_END,   KC_K,    KC_H,   KC_COMM, KC_DOT, KC_SLSH, KC_RCTL,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                          KC_BSPC,  KC_DEL, MO(_LOWER),              MO(_RAISE),  KC_ENT,  KC_SPC
                                      // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
                                    ),
    [_NUMPAD] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
            _______, _______, _______, _______, _______, _______,                            KC_NUM, _______, _______, _______, _______, _______,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            _______, _______, KC_UP,   _______, _______, _______,                            KC_PAST, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, _______,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,                            KC_PSLS, KC_P4,   KC_P5,   KC_P6,   KC_PMNS, _______,
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
            _______, KC_RALT, KC_LWIN, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
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
            KC_LWIN, _______, _______, _______, DB_TOGG, _______,_______,           _______, RGB_RMOD,RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD, _______,
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

 bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
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
                tap_code(clockwise ? KC_VOLU : KC_VOLD);
            } else {
                tap_code(clockwise ? KC_PGDN : KC_PGUP);
            }
            break;
        case _RAISE:
            if (index == 0) {
                tap_code(clockwise ? KC_BRIU : KC_BRID);
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
    update_tri_layer(_LOWER, _RAISE, _ADJUST);
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


