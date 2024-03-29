/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
//static const char *upvol[] = {"usr/bin/pactl", "set-sink-volume", "0", "+5%", NULL};
//static const char *downvol[] = {"/usr/bin/pactl", "set-sink-volume", "0", "-5%", NULL};
//static const char *mutevol[] = {"/usr/bin/pactl", "set-sink-mute", "0", "toggle", NULL};

//static const char *upvol[] = {"pamixer", "--increase", "5", NULL};
//static const char *downvol[] = {"pamixer", "--decrease", "5", NULL};
//static const char *mutevol[] = {"pamixer", "-t", NULL};

static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 9;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh = 7; 
static const char *fonts[]          = { "monospace:size=14", "Hurmit Nerd Font:style=Medium:size=16" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_cyan2[] = "#94B49F";
static const char col_orange[] = "#DF7861";
static const char col_lightorange[] = "#ECB390";
static const char col_green[] = "#0F3D3E";
static const char col_beige[] = "#E2DCC8";
static const char col_black[] = "#100F0F";
static const char col_darkblue[] = "#395B64";
static const char col_lightblue[] = "#A5C9CA";
static const char col_white[] = "#ffffff";

// Red Berry Color Scheme
static const char col_berry_light[] = "#701f28";
static const char col_berry_dark[] = "#381014";

// catppuccin theme 
static const char col_pucc_rosewater[] = "#f2d5cf";
static const char col_pucc_pink[] = "#f4b8e4"; 
static const char col_pucc_purple[] = "#ca9ee6";
static const char col_pucc_red[] = "#e78284";
static const char col_pucc_blugray[] = "#232634";
static const char col_pucc_dgray[] = "#1a1823";
static const char col_pucc_blugray2[] = "#131020";
static const char col_pucc_bg[] = "#303446";
static const char col_pucc_text[] = "#c6d0f5";
static const char col_pucc_yellow[] = "#e5c890";
static const char col_pucc_maroon[] = "#ea999c";
static const char col_pucc_green[] = "#a6d189";
static const char col_pucc_flamingo[] = "#eebebe";

// rose-pine theme
static const char col_pine_sel[] = "#21202e";
static const char col_pine_bg[] = "#191724";
static const char col_pine_seltext[] = "#c4a7e7";
static const char col_pine_occ[] = "#31748f";
static const char col_pine_text[] = "#e0def4";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = {col_pine_text, col_pine_bg, col_pine_occ},
    [SchemeSel] = {col_pine_seltext, col_pine_sel, col_pine_occ},
    [SchemeOccSel] = {col_pine_seltext, col_pine_sel, col_pine_occ},
    [SchemeOccNorm] = {col_pine_occ, col_pine_bg, col_pine_occ},
};

/* tagging */

static const char *tags[] = { "       ", "    󰙯    " , "        ","        ","         "};
//static const char *tags[] = {"  firefox  ", "  terminal  ", "  vpn  ", "  misc  "};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
    {MODKEY|ShiftMask, XK_Print, spawn, SHCMD("flameshot gui") },
    {MODKEY, XK_Print, spawn, SHCMD("flameshot full -c")},
    {MODKEY, XK_F11, spawn, SHCMD("pamixer --decrease 5 && pkill -RTMIN+22 dwmblocks")  },
    {MODKEY, XK_F12, spawn, SHCMD("pamixer --increase 5 && pkill -RTMIN+22 dwmblocks")},
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

