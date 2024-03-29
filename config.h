/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack:size=13" };
static const char dmenufont[]       = "Hack:size=13";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class				instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "qutebrowser",		NULL,	  NULL,			  1,		 0,          0,           1,        -1 },
	{ "Google-chrome",		NULL,	  NULL,			  1,		 0,          0,           1,        -1 },
	{ "Pcmanfm",			NULL,	  NULL,			  2,		 0,          0,           0,        -1 },
	{ "Steam",				NULL,	  NULL,			  8,		 0,          0,           0,        -1 },
	{ "URxvt",				NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,					NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

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
	{ MODKEY|Mod1Mask,              KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-i", "-p", "open", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *passcmd[] = { "passmenu", "-i", "-p", "pass", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "urxvt", NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = passcmd } },
	{ MODKEY,						XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       0,		   setmfact,       {.f = -0.05} },
	{ MODKEY,                       0,		   setmfact,       {.f = +0.05} },
	{ MODKEY|Mod1Mask,              XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_e,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_w,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|Mod1Mask,              XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,						XK_h,	   shiftview,	   {.i = -1 } },
	{ MODKEY,						XK_l,	   shiftview,	   {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|Mod1Mask,              XK_e,		quit,           {0} },
	{ 0, XF86XK_AudioRaiseVolume,				spawn,		   SHCMD("amixer set Master 5%+") },
	{ 0, XF86XK_AudioLowerVolume,				spawn,		   SHCMD("amixer set Master 5%-") },
	{ 0, XF86XK_AudioMute,						spawn,		   SHCMD("amixer set Master toggle") },
	{ 0, XF86XK_AudioMicMute,					spawn,		   SHCMD("amixer set Capture toggle") },
	{ 0, XF86XK_MonBrightnessUp,				spawn,		   SHCMD("xbacklight -inc 10") },
	{ 0, XF86XK_MonBrightnessDown,				spawn,		   SHCMD("xbacklight -dec 10") },
	{ 0, XK_Print,								spawn,		   SHCMD("maim | tee $(xdg-user-dir PICTURES)/$(hostnamectl hostname)_$(date +%s).png | xclip -selection clipboard -t image/png") },
	{ MODKEY, XK_Print,							spawn,		   SHCMD("maim -s | tee $(xdg-user-dir PICTURES)/$(hostnamectl hostname)_$(date +%s).png | xclip -selection clipboard -t image/png") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,			0,				Button4,		shiftview,		{.i = -1 } },
	{ ClkTagBar,			0,				Button5,		shiftview,		{.i = 1 } },
	{ ClkWinTitle,			0,				Button1,		focusstack,		{.i = +1 } },
	{ ClkWinTitle,			0,				Button3,		focusstack,		{.i = -1 } },
	{ ClkWinTitle,			0,				Button4,		focusstack,		{.i = +1 } },
	{ ClkWinTitle,			0,				Button5,		focusstack,		{.i = -1 } },
};
