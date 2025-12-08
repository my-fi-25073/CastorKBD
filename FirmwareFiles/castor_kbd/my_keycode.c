#include "my_keycode.h"

static inline void press_and_release(uint16_t mod)
{
    register_code(mod);
    unregister_code(mod);
}

static inline void press_mods_and_tap(uint16_t win_mod, uint16_t mac_mod, uint16_t key, os_variant_t host)
{
    if (host == OS_WINDOWS)
    {
        register_code(win_mod);
        tap_code(key);
        unregister_code(win_mod);
    }
    else
    {
        register_code(mac_mod);
        tap_code(key);
        unregister_code(mac_mod);
    }
}

static inline void press_word_move(bool pressed, os_variant_t host, bool move_left)
{
    if (pressed)
    {
        if (host == OS_WINDOWS)
        {
            register_code(KC_LCTL);
            register_code(move_left ? KC_LEFT : KC_RIGHT);
        }
        else
        {
            register_code(KC_LALT);
            register_code(move_left ? KC_LEFT : KC_RIGHT);
        }
    }
    else
    {
        if (host == OS_WINDOWS)
        {
            unregister_code(move_left ? KC_LEFT : KC_RIGHT);
            unregister_code(KC_LCTL);
        }
        else
        {
            unregister_code(move_left ? KC_LEFT : KC_RIGHT);
            unregister_code(KC_LALT);
        }
    }
}

static bool send_os_language_switch(bool pressed, os_variant_t host)
{
    if (!pressed) return false;
    if (host == OS_WINDOWS) { tap_code(KC_RALT); }
    else { press_mods_and_tap(KC_LCTL, KC_LCTL, KC_SPACE, host); }
    return false;
}

static bool send_os_screenshot(bool pressed, os_variant_t host)
{
    if (!pressed) return false;
    if (host == OS_WINDOWS)
    {
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_S);
        unregister_code(KC_LGUI);
        unregister_code(KC_LSFT);
    }
    else
    {
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_4);
        unregister_code(KC_LGUI);
        unregister_code(KC_LSFT);
    }
    return false;
}

static bool send_word_move_left(bool pressed, os_variant_t host)
{
    press_word_move(pressed, host, true);
    return false;
}

static bool send_word_move_right(bool pressed, os_variant_t host)
{
    press_word_move(pressed, host, false);
    return false;
}

static bool send_mod_left_command_or_ctrl(bool pressed, os_variant_t host)
{
    if (host == OS_WINDOWS)
    {
        if (pressed) register_code(KC_LCTL); else unregister_code(KC_LCTL);
    }
    else
    {
        if (pressed) register_code(KC_LGUI); else unregister_code(KC_LGUI);
    }
    return false;
}

static bool send_mod_left_ctrl_or_gui(bool pressed, os_variant_t host)
{
    if (host == OS_WINDOWS)
    {
        if (pressed) register_code(KC_LGUI); else unregister_code(KC_LGUI);
    }
    else
    {
        if (pressed) register_code(KC_LCTL); else unregister_code(KC_LCTL);
    }
    return false;
}

static bool send_desktop_switch_left(bool pressed, os_variant_t host)
{
    if (!pressed) return false;
    if (host == OS_WINDOWS) { register_code(KC_LGUI); register_code(KC_LCTL); tap_code(KC_LEFT); unregister_code(KC_LCTL); unregister_code(KC_LGUI); }
    else { press_mods_and_tap(KC_LCTL, KC_LCTL, KC_LEFT, host); }
    return false;
}

static bool send_desktop_switch_right(bool pressed, os_variant_t host)
{
    if (!pressed) return false;
    if (host == OS_WINDOWS) { register_code(KC_LGUI); register_code(KC_LCTL); tap_code(KC_RIGHT); unregister_code(KC_LCTL); unregister_code(KC_LGUI); }
    else { press_mods_and_tap(KC_LCTL, KC_LCTL, KC_RIGHT, host); }
    return false;
}

static bool send_desktop_overview(bool pressed, os_variant_t host)
{
    if (!pressed) return false;
    if (host == OS_WINDOWS) { register_code(KC_LGUI); tap_code(KC_TAB); unregister_code(KC_LGUI); }
    else { press_mods_and_tap(KC_LCTL, KC_LCTL, KC_UP, host); }
    return false;
}

static bool send_visual_studio_toggle_breakpoint(bool pressed, os_variant_t host)
{
    if (!pressed) return false;
    if (host == OS_WINDOWS)
    {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_PAUS);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
    else
    {
        tap_code(KC_PAUS);
    }
    return false;
}

static inline bool send_vscode_chord(bool pressed, os_variant_t host, uint16_t chord_key)
{
    if (!pressed) return false;
    if (host == OS_WINDOWS)
    {
        register_code(KC_LCTL);
        tap_code(KC_K);
        tap_code(chord_key);
        unregister_code(KC_LCTL);
    }
    else
    {
        register_code(KC_LGUI);
        tap_code(KC_K);
        tap_code(chord_key);
        unregister_code(KC_LGUI);
    }
    return false;
}

static bool send_vscode_fold_all(bool pressed, os_variant_t host)      { return send_vscode_chord(pressed, host, KC_0); }
static bool send_vscode_unfold_all(bool pressed, os_variant_t host)    { return send_vscode_chord(pressed, host, KC_J); }
static bool send_vscode_fold_recursive(bool pressed, os_variant_t host){ return send_vscode_chord(pressed, host, KC_LBRC); }
static bool send_vscode_unfold_recursive(bool pressed, os_variant_t host){ return send_vscode_chord(pressed, host, KC_RBRC); }

typedef bool (*key_handler_t)(bool pressed, os_variant_t host);

typedef struct {
    uint16_t keycode;
    key_handler_t handler;
} key_handler_entry_t;

static const key_handler_entry_t s_key_handlers[] = {
    { OS_LANG, send_os_language_switch },
    { OS_PSCR, send_os_screenshot },
    { WO_LEFT, send_word_move_left },
    { WO_RGHT, send_word_move_right },
    { MC_LCMD, send_mod_left_command_or_ctrl },
    { MC_LCTL, send_mod_left_ctrl_or_gui },
    { GO_LEFT, send_desktop_switch_left },
    { GO_RGHT, send_desktop_switch_right },
    { GO_UP,   send_desktop_overview },
    { VS_BRCK, send_visual_studio_toggle_breakpoint },
    { VC_FLDA, send_vscode_fold_all },
    { VC_UFDA, send_vscode_unfold_all },
    { VC_FLDR, send_vscode_fold_recursive },
    { VC_UFDR, send_vscode_unfold_recursive },
};

static inline key_handler_t find_key_handler(uint16_t kc)
{
    for (size_t i = 0; i < sizeof(s_key_handlers) / sizeof(s_key_handlers[0]); i++)
    {
        if (s_key_handlers[i].keycode == kc) return s_key_handlers[i].handler;
    }
    return NULL;
}

bool process_my_custom_keycodes(uint16_t keycode, bool pressed, os_variant_t host)
{
    key_handler_t handler = find_key_handler(keycode);
    if (handler != NULL)
    {
        return handler(pressed, host);
    }
    return true;
}
