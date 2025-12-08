// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "my_keycode.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
     * │Tab│ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │Bsp│
     * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
     * │Ctl│ A │ S │ D │ F │ G │       │ H │ J │ K │ L │ ; │ ' │
     * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
     * │Sft│ Z │ X │ C │ V │ B │       │ N │ M │ , │ . │ / │Sft│
     * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
     *               ┌───┐                   ┌───┐
     *               │GUI├───┐           ┌───┤Alt│
     *               └───┤Bsp├───┐   ┌───┤Ent├───┘
     *                   └───┤   │   │   ├───┘
     *                       └───┘   └───┘
     */
   [0] = LAYOUT(
       QK_GESC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
       MC_LCMD, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
       KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    LO_COMM, RA_DOT,  PT_SLSH, KC_RSFT,
                                           KC_LALT, KC_SPC,  LOWER,   RAISE,   LOWER,   MC_LCTL
   ),

   [1] = LAYOUT(
       QK_GESC, XXXXXXX, KC_7,    KC_8,    KC_9,    KC_0,                      KC_GRV,  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
       MC_LCMD, XXXXXXX, KC_4,    KC_5,    KC_6,    XXXXXXX,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, KC_QUOT,
       KC_LSFT, XXXXXXX, KC_1,    KC_2,    KC_3,    XXXXXXX,                   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, KC_RSFT,
                                           KC_LALT, XXXXXXX, _______, _______, _______, MC_LCTL
   ),

   [2] = LAYOUT(
       KC_TAB,  XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F10,                    XXXXXXX, XXXXXXX, KC_INS,  XXXXXXX, OS_PSCR, KC_DEL,
       MC_LCMD, XXXXXXX, KC_F4,   KC_F5,   KC_F6,   KC_F11,                    XXXXXXX, KC_RCTL, KC_RSFT, OS_LANG, KC_RGUI, XXXXXXX,
       KC_LSFT, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F12,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT,
                                           KC_LALT, XXXXXXX, _______, _______, _______, MC_LCTL
   ),

   [3] = LAYOUT(
       KC_ESC,  XXXXXXX, GO_UP,   XXXXXXX, VC_FLDR, VC_UFDR,                   QK_RBT,  QK_BOOT, EE_CLR,  XXXXXXX, XXXXXXX, KC_DEL,
       MC_LCMD, GO_LEFT, XXXXXXX, GO_RGHT, VC_FLDA, VC_UFDA,                   WO_LEFT, XXXXXXX, XXXXXXX, WO_RGHT, XXXXXXX, XXXXXXX,
       KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, VS_BRCK,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT,
                                           KC_LALT, XXXXXXX, _______, _______, XXXXXXX, MC_LCTL
   ),

   [4] = LAYOUT(
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       MC_LCMD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT,
                                           KC_LALT, XXXXXXX, _______, _______, XXXXXXX, MC_LCTL
   ),

   [5] = LAYOUT(
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       MC_LCMD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT,
                                           KC_LALT, XXXXXXX, _______, _______, XXXXXXX, MC_LCTL
   )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    os_variant_t host = detected_host_os();
    if (!process_my_custom_keycodes(keycode, record->event.pressed, host)) {
        return false;
    }
    return true;
}
