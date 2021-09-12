#include QMK_KEYBOARD_H

#include "oneshot.h"

#define LA_UPP OSL(UPP)
#define LA_SYM OSL(SYM)
#define LA_NAV LT(NAV, KC_SPC)
#define LA_NUM LT(NUM, KC_SPC)

enum layers {
    DEF,
    UPP,
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
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                          XXXXXXX, LA_UPP,  LA_NAV,  LA_NUM,  LA_SYM,  XXXXXXX
    ),

    [UPP] = LAYOUT_split_3x5_3(
        S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T), S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P),
        S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G), S(KC_H), S(KC_J), S(KC_K), S(KC_L), KC_DQUO,
        S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_N), S(KC_M), KC_SCLN, KC_COLN, KC_QUES,
                          XXXXXXX, _______, _______, _______, _______, XXXXXXX
    ),

    [SYM] = LAYOUT_split_3x5_3(
        KC_LABK, KC_LCBR, KC_LBRC, KC_LPRN, XXXXXXX, XXXXXXX, KC_RPRN, KC_RBRC, KC_RCBR, KC_RABK,
        KC_TILD, KC_ASTR, KC_EQL,  KC_MINS, KC_CIRC, KC_DLR,  KC_HASH, KC_PERC, KC_AT,   KC_EXLM,
        XXXXXXX, KC_GRV,  KC_PLUS, KC_UNDS, KC_AMPR, KC_PIPE, KC_BSLS, KC_SCLN, KC_COLN, XXXXXXX,
                          XXXXXXX, _______, _______, _______, _______, XXXXXXX
    ),

    [NAV] = LAYOUT_split_3x5_3(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TAB,  KC_UP,   KC_ENT,  KC_DEL,
        OS_GUI,  OS_ALT,  OS_SHFT, OS_CTRL, XXXXXXX, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
        C(KC_Z), C(KC_X), C(KC_C), C(KC_V), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          XXXXXXX, _______, _______, KC_BSPC, _______, XXXXXXX
    ),

    [NUM] = LAYOUT_split_3x5_3(
        KC_7,    KC_5,    KC_3,    KC_1,    KC_9,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_6,    KC_4,    KC_2,    KC_0,    KC_8,    XXXXXXX, OS_CTRL, OS_SHFT, OS_ALT,  OS_GUI,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          XXXXXXX, _______, KC_BSPC, _______, _______, XXXXXXX
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
    case LA_NAV:
    case LA_NUM:
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
