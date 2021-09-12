#include QMK_KEYBOARD_H

#include "oneshot.h"

#define LA_SYM MO(SYM)
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

    SW_WIN,  // Switch to next window         (cmd-tab)
    SW_LANG, // Switch to next input language (ctl-spc)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_split_3x5_3(
        KC_Y,    KC_C,    KC_L,    KC_M,    KC_K,    KC_Z,    KC_F,    KC_U,    KC_COMM, KC_QUOT,
        KC_I,    KC_S,    KC_R,    KC_T,    KC_G,    KC_P,    KC_N,    KC_E,    KC_A,    KC_O,
        KC_Q,    KC_V,    KC_W,    KC_D,    KC_J,    KC_B,    KC_H,    KC_SCLN, KC_DOT,  KC_X,
                          XXXXXXX, LA_NAV,  KC_LSFT, KC_SPC,  LA_SYM, XXXXXXX
    ),

    [SYM] = LAYOUT_split_3x5_3(
        KC_TILD, KC_LBRC, KC_LCBR, KC_LABK, KC_AT,   XXXXXXX, KC_RABK, KC_RCBR, KC_RBRC, KC_GRV,
        KC_QUES, KC_HASH, KC_EQL,  KC_MINS, KC_PLUS, XXXXXXX, OS_SHFT, OS_CTRL, OS_ALT,  OS_GUI,
        KC_EXLM, KC_DLR,  KC_PERC, KC_SLASH,KC_ASTR, XXXXXXX, KC_BSLS, KC_PIPE, KC_AMPR, KC_CIRC,
                          XXXXXXX, _______, _______, _______, _______, XXXXXXX
    ),

    [NAV] = LAYOUT_split_3x5_3(
        KC_ESC,  XXXXXXX,  XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, KC_TAB,  KC_UP,   KC_ENT,  KC_DEL,
        OS_GUI,  OS_ALT,  OS_CTRL, OS_SHFT, XXXXXXX, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
        KC_UNDO, KC_CUT,  KC_COPY, KC_PASTE,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          XXXXXXX, _______, _______, KC_BSPC, _______, XXXXXXX
    ),

    [NUM] = LAYOUT_split_3x5_3(
        KC_7,    KC_5,    KC_3,    KC_1,    KC_9,    KC_8,    KC_0,    KC_2,    KC_4,    KC_6,
        OS_GUI,  OS_ALT,  OS_CTRL, OS_SHFT, XXXXXXX, XXXXXXX, OS_SHFT, OS_CTRL, OS_ALT,  OS_GUI,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          XXXXXXX, _______, _______, _______, _______, XXXXXXX
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
