# dwm
My build of the dynamic window manager by [Suckless](https://suckless.org)

## Patches applied:
1. [adjacenttag](https://dwm.suckless.org/patches/adjacenttag);
2. [alternativetags](https://dwm.suckless.org/patches/alternativetags);
3. [fullgaps](https://dwm.suckless.org/patches/uselessgap);
4. [autostart](https://dwm.suckless.org/patches/autostart);
5. [fakefullscreen](https://dwm.suckless.org/patches/fakefullscreen);
6. [attachabove](https://dwm.suckless.org/patches/attachabove);
7. [center](https://dwm.suckless,org/patches/center);
8. [centeredwindowname](https://dwm.suckless.org/patches/centeredwindowname);
9. [cfacts](https://dwm.suckless.org/patches/cafcts);
10. [colorbar](https://dwm.suckless.org/patches/colorbar);
11. [push](https://dwm.suckless.org/patches/push);
12. [setborderspx](https://dwm.suckless,org/patches/setborderspx);
13. [xresources](https://dwm.suckless.org/patches/xresources);
14. [pertag](https://dwm.suckless.org/patches/pertag);

## Requirements
In order to build dwm you need the Xlib header files.


## Installation
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


## Running dwm
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

## Configuration
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
Basic configs (like colors, showbar, mfact etc.) can be edited through the Xresources file without the need to recompile.
