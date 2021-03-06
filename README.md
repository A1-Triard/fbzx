# FBZX

**IMPORTANT: FBZX has been migrated to Gitlab**

https://gitlab.com/rastersoft/fbzx

A ZX Spectrum emulator for FrameBuffer

## DISCLAIMER

FBZX is distributed under the GPL license, version three or later, which means
that is distributed "as is", without warraty of any kind. To know more details,
read the file COPYING.

The old exception for the Z80 emulator has been removed because now FBZX uses
Z80FREE, a brand new, fully GPLv3, Z80 emulator. So finally FBZX is 100% free
software.

Amstrad have kindly given their permission for the redistribution of their
copyrighted material (the original Spectrum ROMs) but retain that copyright.
To know more details about how to distribute them, read the file AMSTRAD.

## WHAT IS FBZX?

FBZX is a Sinclair ZX Spectrum emulator, designed to work in FrameBuffer under
Linux, but can work under Xwindows too, both in full screen mode and in a
window. It uses the SDL library, so it should be easily ported to other
architectures. Please, read the file PORTS to know more details about this.

FBZX is based in Z80FREE, which you can find into the folder z80free.

To work with FBZX you need:

    * A FrameBuffer-capable graphic card (or compatible with X-windows)
    * A Linux system with FrameBuffer configured (can use X too)
    * Sound Card with ALSA or OSS drivers (optional)

In order to get the maximum performance, your FrameBuffer driver must allow to
change to 640x480 or 480x640 resolution in 8 bits. Only the old VESAFB driver can
have problems with this fact, so if you use this driver, be sure to boot your
Linux box in 640x480 in 8 bits. If you don't do this, SDL will emulate that
mode, resulting in a high performance penalty. If you use an specific Framebuffer
driver, or the VESAFB driver from kernels 2.6, just don't worry: FBZX will
automagically change the graphic mode when starts.

Of course, currently that is no problem thanks to the high speed of computers.

## WHAT CAPABILITIES HAVE FBZX?

FBZX can emulate the original 48K spectrum (issue 2 and issue 3), the original
128K, the Amstrad +2, the Amstrad +2A and the Spanish 128K.

The screen and the sound are emulated in a very acuracy way, so nearly all
the sound and screen effects should work in this emulator.

128K sound is emulated too, and can be disabled in 128K mode in order to save
CPU time procesing, if your computer is slow.

It emulates the Interface I and one microdrive unit, allowing to load from and
save to MDR files.

FBZX can handle Z80 snapshots (both load and save) and SNA (only load). In a
future, more snapshot formats will be supported.

FBZX can handle TAP files (load and save), and have a fast-load mode that allows
to load in milliseconds a TAP file. This fast-load mode is enabled by default, but
can be disabled.

FBZX can also handle TZX files (both load and save) (see README.TZX for details).

FBZX can emulate the Kempston, Cursor, Sinclair 1 and Sinclair 2 joysticks,
with the cursor keys (fire is emulated with the right ALT key, ALT-GR
key, WINDOWS MENU key or WINDOWS SYSTEM right key), or with a real
JoyStick.

## HOW DO I USE FBZX?

To run FBZX just type

    fbzx

from a console.

You can load a snapshot directly with:

    fbzx game.z80
    fbzx game.sna

or assign a TAP or TZX file with:

    fbzx game.tap
    fbzx game.tzx

(in this case you still must use LOAD ""). This allows you to asociate that
file extensions to FBZX.

You can use the option -fs to run it in FullScreen mode. If you use the -rotate
option, FBZX will run in 480x640 mode (needed for some PDAs like the Zaurus)
rotating the screen 90 degrees. There's another option, -mini, that will run
FBZX in 480x640 mode but the screen won't be rotated, but will be half width
and height (very small).

You can run it without sound too, just typing:

    fbzx -nosound

You can use this if you don't have a sound card, or it hasn't OSS support.

You can combine theses options as you like. An example:

    fbzx -nosound -fs

    fbzx -rotate -nosound

By default, FBZX will try to use ALSA sound; if it can't, it will try with OSS
sound; finally, if both fails it will use no sound and alert the user.

You can change the order with

    fbzx -oss

That way it will try firts with OSS, then with ALSA.

FBZX works in X too, but it would run slower due to the penalty of the X
Window System. Fortunately this only applies to old systems. Current
computers can run FBZX under X without problem.

The PC keyboard works exactly like the Spectrum keyboard (but only numbers and
letters). ENTER key is Return, CAPS SHIFT is in both Shift keys, and SYMBOL
SHIFT is in both Control keys. Delete, ',' and '.' works too. I hope to add
'extended keys' in a near future.

Whit ESC you exit FBZX.

F1 shows a help page with all the available keys.

F2 sends you to a menu where you can load and save snapshots.

F3 sends you to a menu where you can choose a TAP/TZX file, rewind it,
choose if you want normal speed or fast speed for loading, enable or
disable the write protection, and create a new (and empty) TAP or TZX file.
Also, allows to enable the TURBO WHILE PLAYING mode, that makes the emulator
run at the maximum possible speed while the tape is running, allowing to
do a fast load even with protected tapes.

F4 send you to a menu where you can choose the emulation type you want (48K,
128K, +2, +2A or spanish 128K), the joystick, enable or disable the AY
emulation and enable or disable the Interface I.

F5 stops the tape when normal speed is selected. With fast speed, it does
nothing.

F6 plays the tape when normal speed is selected. With fast speed, it does
nothing.

F7 allows to choose a MDR file (microdrive), protect and unprotect it,
and create a new (and empty) one.

F8 allows to shows a picture with the keyboard layout, or insert POKE values

F9 toggles between fullscreen/windowed mode

F10 resets the spectrum.

F11 is volume down.

F12 is volume up.

If your system doesn't have function keys, you can use TAB plus keys 0 to 9
to emulate them (F11 is TAB and O, and F12 is TAB and P).

## HOW DO I CHOOSE A FILE WITH THE TAP/TZX OR Z80/SNA SELECTOR?

You can choose a file just by moving the white bar with the cursor keys. You
can use also the RePag and AvPag to jump over 12 positions.

The files are in white ink, the directories in green ink, and the upper
directory are the two red dots.

When you choose a TAP file, it is marked as "save protected", so if you want
to save programs, you must enable it. If you create a new TAP file, it is
marked as "save enabled", so you can start to save directly.

The SAVE option works only with the classic ROM routine, so you will be able
to save from programs that use them (it can save programs without header, too,
since the emulator intercepts the call to SA-BYTES). Each new block is added at
the end of the file, but only if the SAVE operation is enabled for this file.

## HOW DOES WORK THE FAST SPEED LOAD FOR TAP/TZX FILES?

Just type LOAD "" in the emulator (or choose the TAPE LOADER option in the 128K
menu) and the tape will automagically load. This only works with programs that
uses the ROM to load all the blocks. If you have a TAP file with a program that
uses a custom routine to load the blocks, then you must use the NORMAL SPEED.
To do this, press F3 to go to the TAP menu and choose NORMAL SPEED. Then return
to the emulation (with ESC) and use LOAD "" (or the TAPE LOADER option).
Finally, put the tape in Play with F6. You can stop the tape with F5 and start
it again with F6 as many times you want.

When the tape ends, is automatically stoped. You can rewind the
tape when you want with the right option in the TAP menu (F3 key).

In a near future a block manager will be added, in order to allow the user to
choose a block into the TAP file (thinking in multistage games).

Remember that the Fast Speed is available both for TAP and TZX files, but it
only works with some parts (only when the ROM is called, never for specific
loader routines). In the last case you can go to the TAP/TZX menu (F3) and
change the TURBO WHILE PLAYING mode to ENABLED, so the computer (and the tape)
will run faster when the tape is playing (F6 key), but will return to normal
speed when the tape is paused (F5 key or end-of-tape).

## HOW DOES WORK THE FAST SPEED SAVE FOR TAP/TZX FILES?

If write is enabled, using the SAVE command will add blocks to the currently
selected tape file, no matter if FAST-LOAD is enabled or not. By default,
write is disabled whenever a file is selected, but is enabled whenever a
new TAP/TZX file is created from scratch. This functionality works with any
program that uses the SA-BYTES ROM routine, no matter if enters at 04C2 (like
the classic spectrum 48K rom) or at 04C6 (like the Spectrum +3).

## HOW DOES WORK THE INTERFACE I AND MICRODRIVE EMULATION?

FBZX can emulate an Interface I with one microdrive attached, but only when
working as Spectrum 48K, 128K or +2, never as +2A/+3 since it's incompatible.

You just have to choose an MDR file (or create a new MDR file) using the F7
key, and you will be able to use all the Interface I commands and programs.
Remember to format your cartridge (MDR file) after creating one.

When you save something to the cartridge, the MDR file is updated as soon as
the Spectrum stops the "motor" of the drive.

## CONTACTING THE AUTHOR

Sergio Costas Rodriguez  
rastersoft@gmail.com  
http://www.rastersoft.com  
https://gitlab.com/rastersoft/fbzx
