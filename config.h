#pragma once
/*
 * TinyTile example config.h
 * Copy / edit this to suit you. Included by TinyTile.c.
 * Suckless style: edit + recompile to configure.
 */

#include <stdint.h>
#include <xkbcommon/xkbcommon.h>

/* If you don't have wlroots headers in include path yet, this fallback lets
 * config.h still parse. Real values come from <wlr/types/wlr_keyboard.h> */
#ifndef WLR_MODIFIER_SHIFT
#define WLR_MODIFIER_SHIFT (1 << 0)
#define WLR_MODIFIER_CAPS  (1 << 1)
#define WLR_MODIFIER_CTRL  (1 << 2)
#define WLR_MODIFIER_ALT   (1 << 3)
#define WLR_MODIFIER_MOD2  (1 << 4)
#define WLR_MODIFIER_MOD3  (1 << 5)
#define WLR_MODIFIER_LOGO  (1 << 6)
#define WLR_MODIFIER_MOD5  (1 << 7)
#endif

/* Modkey: Super/Logo key. Use WLR_MODIFIER_ALT for Alt. */
#define MODKEY WLR_MODIFIER_LOGO

/* appearance */
static const unsigned int borderpx  = 2;   /* border pixel of windows */
static const unsigned int gappx     = 5;   /* gaps between windows */
static const unsigned int snap      = 32;  /* snap pixel */
static const int showbar            = 1;   /* 0 means no bar */
static const int topbar             = 1;   /* 0 means bottom bar */
static const float mfact            = 0.55f; /* master area size factor */
static const int nmaster            = 1;   /* number of clients in master area */

/* fonts and colors */
static const char *fonts[]        = { "monospace:size=10" };
static const char normbgcolor[]   = "#222222";
static const char normbordercolor[] = "#444444";
static const char normfgcolor[]   = "#bbbbbb";
static const char selfgcolor[]    = "#eeeeee";
static const char selbordercolor[] = "#88c0d0";
static const char selbgcolor[]    = "#005577";

/* apps */
static const char *terminal[] = { "st", NULL };
static const char *menu[]     = { "rofi -show drun", NULL };
static const char *browser[]  = { "firefox", NULL };

/* autostart: run once at startup, NULL-terminated */
static const char *autostart[] = {
    "wbg", "/usr/share/backgrounds/default.png", NULL,
    /* add more, one per line, e.g.: */
    /* "waybar", NULL, */
    NULL /* terminator */
};

/* tags / workspaces */
static const char *tags[] = { "1", "2", "3", "4", "5" };

/* layouts: first is default */
static const char *layouts[] = {
    "[]=",  /* tiling */
    "><>",  /* floating */
    "[M]",  /* monocle */
};

/* Forward-declare actions - implement these in TinyTile.c / backend.c */
typedef union {
    int i;
    unsigned int ui;
    float f;
    const void *v;
} Arg;

void spawn(const Arg *arg);
void killclient(const Arg *arg);
void quit(const Arg *arg);
void togglefloating(const Arg *arg);
void togglefullscreen(const Arg *arg);
void focusnext(const Arg *arg);
void focusprev(const Arg *arg);
void setlayout(const Arg *arg);
void view(const Arg *arg);
void tag(const Arg *arg);

/* keybinds */
typedef struct {
    uint32_t mod;
    xkb_keysym_t keysym;
    void (*func)(const Arg *arg);
    Arg arg;
} Key;

static const Key keys[] = {
    /* modifier, key, function, argument */
    { MODKEY,                    XKB_KEY_Return, spawn,           {.v = terminal} },
    { MODKEY,                    XKB_KEY_d,      spawn,           {.v = menu} },
    { MODKEY,                    XKB_KEY_w,      spawn,           {.v = browser} },
    { MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_Q,    killclient,      {0} },
    { MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_E,    quit,            {0} },
    { MODKEY,                    XKB_KEY_j,      focusnext,       {0} },
    { MODKEY,                    XKB_KEY_k,      focusprev,       {0} },
    { MODKEY,                    XKB_KEY_f,      togglefloating,  {0} },
    { MODKEY,                    XKB_KEY_m,      togglefullscreen,{0} },
    { MODKEY,                    XKB_KEY_t,      setlayout,       {.v = layouts} }, /* tiling, adapt to your setlayout impl */
    /* tags 1-5 */
    { MODKEY, XKB_KEY_1, view, {.ui = 1 << 0} },
    { MODKEY, XKB_KEY_2, view, {.ui = 1 << 1} },
    { MODKEY, XKB_KEY_3, view, {.ui = 1 << 2} },
    { MODKEY, XKB_KEY_4, view, {.ui = 1 << 3} },
    { MODKEY, XKB_KEY_5, view, {.ui = 1 << 4} },
    { MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_1, tag, {.ui = 1 << 0} },
    { MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_2, tag, {.ui = 1 << 1} },
    { MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_3, tag, {.ui = 1 << 2} },
    { MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_4, tag, {.ui = 1 << 3} },
    { MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_5, tag, {.ui = 1 << 4} },
};
