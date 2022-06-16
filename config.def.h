/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx   = 2;        /* border pixel of windows */
static unsigned int gappx      = 16;        /* gaps between windows */
static const unsigned int snap = 8;       /* snap pixel */
static int showbar             = 1;        /* 0 means no bar */
static int topbar              = 1;        /* 0 means bottom bar */
static char tfont[]             = "Fira Code:size=11";
static char efont[]             = "Material Design Icons-Regular:size=10";
static char dmenufont[]        = "Fira Code:size=11";
static const char *fonts[]     = { tfont, efont };
static char normbgcolor[]      = "#222222";
static char normbordercolor[]  = "#444444";
static char normfgcolor[]      = "#bbbbbb";
static char selfgcolor[]       = "#eeeeee";
static char selbordercolor[]   = "#005577";
static char selbgcolor[]       = "#005577";
//TODO: replace default color
static char col_gray1[]  = "#222222";
static char col_gray3[]  = "#bbbbbb";
static char col_gray4[]  = "#eeeeee";
static char col_cyan[]   = "#005577";
static char col_black[]       = "#000000";
static char col_red[]         = "#ff0000";
static char col_yellow[]      = "#ffff00";
static char col_white[]       = "#ffffff";
static char *colors[][3] = {
    /*                      fg           bg           border   */
	[SchemeNorm]        = { normfgcolor, normbgcolor, normbordercolor },
    [SchemeSel]         = { selfgcolor,  selbgcolor,  selbordercolor  },
    [SchemeTabActive]   = { normfgcolor, normbgcolor, normbordercolor },
    [SchemeTabInactive] = { normfgcolor, normbgcolor, normbordercolor },
    [SchemeStatus]  	= { col_gray3, col_gray1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
    [SchemeTagsSel]  	= { col_gray4, col_cyan,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  	= { col_gray3, col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  	= { col_gray4, col_cyan,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  	= { col_gray3, col_gray1,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
	[SchemeWarn]		= { col_black, col_yellow, col_red },
	[SchemeUrgent]      = { col_white, col_red,    col_red }
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tagsalt[] = { "󰎚", "󰎚", "", "󰉋", "󰈰", "󰺵", "󰖷", "", "󰎄" };
static const int momentaryalttags = 0; /* 1 means alttags will show only when key is held down*/

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
        /* class               instance             title                 tags mask     iscentered     isfloating   monitor */
        { "JetBrains Toolbox", "jetbrains-toolbox", "JetBrains Toolbox",  1 << 0,       1,             1,           -1 },
        { "firefox",           NULL,                NULL,                 1 << 2,       0,             0,           -1 },
        { "mpv",               NULL,                NULL,                 1 << 4,       0,             0,           -1 },
        { "Steam",             NULL,                NULL,                 1 << 5,       0,             0,           -1 },
        { "carla",		       NULL,                NULL,                 1 << 6,       0,             0,           -1 },
        { "Thunderbird",       NULL,                NULL,                 1 << 7,       0,             0,           -1 },
        { "TelegramDesktop",   NULL,                NULL,                 1 << 7,       0,             0,           -1 },
        { "Alacritty",         "Alacritty",         NULL,                 0,            1,             0,           -1 },
        { "Alacritty",         "Alacritty",         "pulsemixer",         0,            1,             1,           -1 },
        { "Gimp",              NULL,                NULL,                 0,            1,             1,           -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 2;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

/* bartabgroups properties */
#define BARTAB_BORDERS 1       // 0 = off, 1 = on
#define BARTAB_BOTTOMBORDER 0  // 0 = off, 1 = on
#define BARTAB_TAGSINDICATOR 1 // 0 = off, 1 = on if >1 client/view tag, 2 = always on
#define BARTAB_TAGSPX 5        // # pixels for tag grid boxes
#define BARTAB_TAGSROWS 3      // # rows in tag grid (9 tags, e.g. 3x3)
static void (*bartabmonfns[])(Monitor *) = { monocle /* , customlayoutfn */ };
static void (*bartabfloatfns[])(Monitor *) = { NULL /* , customlayoutfn */ };

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "󰨝",      tile },    /* first entry is default */
	{ "󱂬",      NULL },    /* no layout function means floating behavior */
	{ "󰊓",      monocle },
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

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]        = { "alacritty", NULL };
static const char *firefoxcmd[]     = { "firefox", NULL };
static const char *thunarcmd[]      = { "thunar", NULL };
static const char *rangercmd[]      = { "alacritty", "-e", "ranger", NULL };
static const char *telegramcmd[]    = { "telegram-desktop", NULL };
static const char *kdeconnectcmd[]  = { "kdeconnect-settings", NULL };
static const char *mixercmd[]       = { "alacritty", "-e", "pulsemixer", NULL };
static const char *screenshotcmd[]  = { "scrot", "-q 100", NULL };
static const char *ytcmd[]          = { "ytfzf", "-D", NULL };

/* volume control */
static const char *upvolcmd[]   = { "pulsemixer", "--change-volume", "+1",     NULL };
static const char *downvolcmd[] = { "pulsemixer", "--change-volume", "-1",     NULL };
static const char *mutecmd[] = { "pulsemixer", "--toggle-mute", NULL };

/* screen backlight control */
static const char *upblcmd[]   = { "xbacklight", "-inc", "5", NULL };
static const char *downblcmd[] = { "xbacklight", "-dec", "5", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "dwm.normbgcolor",     STRING,  &normbgcolor },
		{ "dwm.normbordercolor", STRING,  &normbordercolor },
		{ "dwm.normfgcolor",     STRING,  &normfgcolor },
		{ "dwm.selbgcolor",      STRING,  &selbgcolor },
		{ "dwm.selbordercolor",  STRING,  &selbordercolor },
		{ "dwm.selfgcolor",      STRING,  &selfgcolor },
		{ "dwm.showbar",         INTEGER, &showbar },
		{ "dwm.topbar",          INTEGER, &topbar },
		{ "dwm.nmaster",         INTEGER, &nmaster },
		{ "dwm.borderpx",        INTEGER, &borderpx },
		{ "dwm.gappx",           INTEGER, &gappx },
		{ "dwm.resizehints",     INTEGER, &resizehints },
		{ "dwm.mfact",           FLOAT,   &mfact },
};

#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key                       function        argument */
	{ MODKEY|ShiftMask,            	XK_d,                     spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,                spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,				XK_f,	                  spawn, 		  {.v = firefoxcmd } },
    { MODKEY|ShiftMask,			    XK_e,	                  spawn,  		  {.v = thunarcmd } },
    { MODKEY|ShiftMask,             XK_t,	                  spawn,  		  {.v = telegramcmd } },
    { MODKEY,                       XK_r,                     spawn,          {.v = rangercmd } },
    { MODKEY|ControlMask,           XK_k,                     spawn,          {.v = kdeconnectcmd } },
    { MODKEY|ShiftMask,             XK_m,                     spawn,          {.v = mixercmd } },
    { MODKEY|ShiftMask,             XK_y,                     spawn,          {.v = ytcmd } },
    { MODKEY,                       XK_s,                     spawn,          {.v = screenshotcmd } },
	{ MODKEY,                       XK_b,                     togglebar,      {0} },
	{ MODKEY,                       XK_j,                     focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                     incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                     incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                     setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                     setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,                     setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,                     setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,                     setcfact,       {.f =  0.00} },
    { MODKEY|ShiftMask,             XK_j,                     pushdown,       {0} },
    { MODKEY|ShiftMask,             XK_k,                     pushup,         {0} },
	{ MODKEY|ShiftMask,             XK_Return,                zoom,           {0} },
	{ MODKEY,                       XK_Tab,                   view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,                     killclient,     {0} },
	{ MODKEY,                       XK_t,                     setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                     setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                     setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                 setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                 togglefloating, {0} },
	{ MODKEY,                       XK_0,                     view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                     tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                 focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                 tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                tagmon,         {.i = +1 } },
	{ MODKEY|ControlMask,           XK_l,                     viewnext,       {0} },
	{ MODKEY|ControlMask,           XK_h,                     viewprev,       {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_l,                     tagtonext,      {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_h,                     tagtoprev,      {0} },
	{ MODKEY,                       XK_n,                     togglealttag,   {0} },
	{ MODKEY,                       XK_minus,                 setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_plus,                  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_minus,                 setgaps,        {.i = 0  } },
    { MODKEY|ControlMask,           XK_minus, 		          setborderpx,    {.i = -1 } },
    { MODKEY|ControlMask,           XK_plus, 		          setborderpx,    {.i = +1 } },
    { MODKEY|ControlMask|ShiftMask, XK_minus, 	              setborderpx,    {.i = 0 } },
    TAGKEYS(                        XK_1,                                     0)
	TAGKEYS(                        XK_2,                                     1)
	TAGKEYS(                        XK_3,                                     2)
	TAGKEYS(                        XK_4,                                     3)
	TAGKEYS(                        XK_5,                                     4)
	TAGKEYS(                        XK_6,                                     5)
	TAGKEYS(                        XK_7,                                     6)
	TAGKEYS(                        XK_8,                                     7)
	TAGKEYS(                        XK_9,                                     8)
	{ MODKEY|ShiftMask,             XK_q,                     quit,           {0} },
    { 0,                            XF86XK_AudioRaiseVolume,  spawn,          {.v = upvolcmd } },
    { 0,                            XF86XK_AudioLowerVolume,  spawn,          {.v = downvolcmd } },
    { 0,                            XF86XK_AudioMute,         spawn,          {.v = mutecmd } },
	{ 0,                            XF86XK_MonBrightnessUp,   spawn,          {.v = upblcmd } },
	{ 0,                            XF86XK_MonBrightnessDown, spawn,          {.v = downblcmd } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

