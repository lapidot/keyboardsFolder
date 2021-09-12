#include QMK_KEYBOARD_H

#include "oneshot.h"

#define LA_SYM OSL(SYM)
#define LA_NAV MO(NAV)

enum layers {
    DEF,
    SYM,
    NAV,
    NUM,
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_GUI,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_split_3x5_3(
        KC_F,    KC_L,    KC_H,    KC_D,    KC_Z,    KC_V,    KC_W,    KC_O,    KC_U,    KC_QUOT,
        KC_S,    KC_R,    KC_N,    KC_T,    KC_K,    KC_G,    KC_Y,    KC_A,    KC_E,    KC_I,
        KC_X,    KC_J,    KC_B,    KC_M,    KC_Q,    KC_P,    KC_C,    KC_COMM, KC_DOT, KC_SLSH,
                          XXXXXXX, LA_NAV,  KC_SPC,  OSM(MOD_RSFT), LA_SYM,  XXXXXXX
    ),

    [SYM] = LAYOUT_split_3x5_3(
        KC_TILD, KC_LBRC, KC_LCBR, KC_LPRN, KC_EXLM, XXXXXXX, KC_RPRN, KC_RCBR, KC_LBRC, KC_GRV,
        KC_HASH, KC_COLN, KC_ASTR, KC_EQL,  KC_AT,   XXXXXXX, OS_CTRL, OS_SHFT, OS_ALT,  OS_GUI,
        KC_DLR,  KC_SCLN, KC_PLUS, KC_MINS, KC_PERC, XXXXXXX, KC_BSLS, KC_PIPE, KC_AMPR, KC_CIRC,
                         XXXXXXX, _______, KC_UNDS, _______, _______, XXXXXXX
    ),

    [NAV] = LAYOUT_split_3x5_3(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TAB,  KC_UP,   KC_ENT,  KC_DEL,
        OS_GUI,  OS_ALT,  OS_SHFT, OS_CTRL, XXXXXXX, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
        C(KC_Z), C(KC_X), C(KC_C), C(KC_V), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          XXXXXXX, _______, _______, KC_BSPC, _______, XXXXXXX
    ),

    [NUM] = LAYOUT_split_3x5_3(
        KC_7,    KC_5,    KC_3,    KC_1,    KC_9,    KC_8,    KC_0,    KC_2,    KC_4,    KC_6,
        OS_GUI,  OS_ALT,  OS_SHFT, OS_CTRL, XXXXXXX, XXXXXXX, OS_CTRL, OS_SHFT, OS_ALT,  OS_GUI,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, XXXXXXX, XXXXXXX, XXXXXXX, KC_COMM, KC_DOT, KC_SLSH,
                          XXXXXXX, _______, _______, KC_BSPC, _______, XXXXXXX
    ),
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_GUI:
        return true;
    default:
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_gui_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_gui_state, KC_LGUI, OS_GUI,
        keycode, record
    );

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}
