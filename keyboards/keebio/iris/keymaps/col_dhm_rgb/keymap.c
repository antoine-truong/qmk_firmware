// Iris Rev6 Custom QMK Layout (Corrected for split_4x6_4)
#include QMK_KEYBOARD_H
#include "tap_dance.h"

// Layer names
enum layers {
    _BASE,
    _NAV,
    _NUM,
    _RGB
};

// Custom Tap Dance definitions
enum {
    TD_ESC_EQL,
    TD_LCTL_LALT,
    TD_RCTL_RALT,
    TD_LSFT_CAPS,
    TD_RSFT_QUOT
};


// Keymap Layout
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_split_4x6_4(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     TD(TD_ESC_EQL), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_TAB, KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                            KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,
TD(TD_LSFT_CAPS),KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                            KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    RSFT_T(KC_QUOT),
   TD_LCTL_LALT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,  KC_HOME,       KC_END, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, TD_RCTL_RALT,
                                         KC_BSPC,  KC_DEL,  TG_NAV,         TG_RGB,  KC_ENT,  KC_SPC
),

[_NAV] = LAYOUT_split_4x6_4(
     KC_ESC,  _______, _______, _______, _______, _______,                          _______, KC_INS,  KC_HOME, KC_PGUP, KC_TAB,  KC_BSPC,
     _______, _______, KC_UP,   _______, _______, _______,                          _______, KC_DEL,  KC_END,  KC_PGDN, _______, _______,
     _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,                          _______, _______, _______, _______, _______, _______,
     _______, _______, KC_LT,   KC_LBRC, KC_LCBR, KC_LPRN, _______,        _______, KC_RPRN, KC_RCBR, KC_RBRC, KC_GT,   _______, _______,
                                         _______, _______, _______,        _______, _______, _______
),

[_NUM] = LAYOUT_split_4x6_4(
     _______, _______, _______, _______, _______, _______,                           KC_NUM,  _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,                           KC_PAST, KC_P7,   KC_P8,   KC_P9,    KC_PPLS, _______,
     _______, _______, _______, _______, _______, _______,                           KC_PSLS, KC_P4,   KC_P5,   KC_P6,    KC_PMNS, _______,
     _______, _______, _______, _______, _______, _______, _______,         _______, _______, KC_P1,   KC_P2,   KC_P3,    KC_PENT, _______,
                                         _______, _______, _______,         _______, KC_PDOT, KC_0
),

[_RGB] = LAYOUT_split_4x6_4(
     _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                             KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
     _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, KC_F12,
     _______, _______, _______, _______, QK_BOOT, _______,                          _______, RGB_TOG, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______, _______,         _______, _______, RGB_MOD, _______, _______, _______, _______,
                                         _______, _______, _______,         _______, _______, _______
)
};

// Encoder handling
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        tap_code(clockwise ? KC_RGHT : KC_LEFT);
    } else if (index == 1) {
        tap_code(clockwise ? KC_UP : KC_DOWN);
    }
    return false;
}

bool encoder_pressed_user(uint8_t index) {
    if (index == 0) {
        tap_code(KC_HOME);
    } else if (index == 1) {
        tap_code(KC_END);
    }
    return true;
}

// Tap dance setup
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC_EQL] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_EQL),
    [TD_LCTL_LALT] = ACTION_TAP_DANCE_DOUBLE_HOLD(KC_LCTL, KC_LALT),
    [TD_RCTL_RALT] = ACTION_TAP_DANCE_DOUBLE_HOLD(KC_RCTL, KC_RALT),
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE_HOLD(KC_LSFT, KC_CAPS),
    [TD_RSFT_QUOT] = ACTION_TAP_DANCE_TAP_HOLD(KC_QUOT, KC_RSFT),
};

// RGB Lighting for specific layers
const rgblight_segment_t PROGMEM nav_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 1, HSV_RED},  // Left Arrow
    {4, 1, HSV_RED},  // Down Arrow
    {5, 1, HSV_RED},  // Right Arrow
    {0, 1, HSV_BLUE}, // <
    {1, 1, HSV_GREEN}, // [
    {2, 1, HSV_YELLOW}, // {
    {6, 1, HSV_ORANGE}, // (
    {7, 1, HSV_ORANGE}, // )
    {8, 1, HSV_YELLOW}, // }
    {9, 1, HSV_GREEN}, // ]
    {10,1, HSV_BLUE}   // >
);

const rgblight_segment_t PROGMEM num_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 5, HSV_WHITE}, // Numbers
    {10, 4, HSV_GREEN} // Operators
);

const rgblight_segment_t PROGMEM rgb_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, HSV_CYAN},
    {6, 6, HSV_PURPLE},
    {12, 4, HSV_PINK}
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    nav_layer,
    num_layer,
    rgb_layer
);

void keyboard_post_init_user(void) {
    rgblight_layers = rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _NAV));
    rgblight_set_layer_state(1, layer_state_cmp(state, _NUM));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RGB));
    return state;
}

// Custom layer toggle logic
bool nav_active = false;
bool rgb_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TG_NAV:
            if (record->event.pressed) {
                nav_active = !nav_active;
                layer_clear();
                if (nav_active) layer_on(_NAV);
                if (rgb_active) layer_on(_RGB);
                if (nav_active && rgb_active) {
                    layer_off(_NAV);
                    layer_off(_RGB);
                    layer_on(_NUM);
                }
            }
            return false;

        case TG_RGB:
            if (record->event.pressed) {
                rgb_active = !rgb_active;
                layer_clear();
                if (nav_active) layer_on(_NAV);
                if (rgb_active) layer_on(_RGB);
                if (nav_active && rgb_active) {
                    layer_off(_NAV);
                    layer_off(_RGB);
                    layer_on(_NUM);
                }
            }
            return false;
    }
    return true;
}
