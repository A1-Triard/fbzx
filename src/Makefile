CC=g++ -c -O2 -g
CPP=g++ -c -O2 -g
LN=g++ -O2 -g

CFLAGS += `pkg-config --cflags sdl libpulse-simple alsa` -D D_SOUND_PULSE -D D_SOUND_ALSA -D D_SOUND_OSS
CPPFLAGS += `pkg-config --cflags sdl libpulse-simple alsa` -D D_SOUND_PULSE -D D_SOUND_ALSA -D D_SOUND_OSS
LDFLAGS += `pkg-config --libs sdl libpulse-simple alsa`


fbzx: cargador.o cmdline.o computer.o emulator.o keyboard.o llscreen.o llsound.o menus.o microdrive.o mouse.o osd.o screen.o signals.o spk_ay.o tape.o Z80free.o Z80free_codes.o Z80free_codesCB.o Z80free_codesED.o Z80free_codesDD.o Z80free_codesFD.o Z80free_codesDDCB.o Z80free_codesFDCB.o
	$(LN) -o fbzx cargador.o cmdline.o computer.o emulator.o keyboard.o llscreen.o llsound.o menus.o microdrive.o mouse.o osd.o screen.o signals.o spk_ay.o tape.o Z80free.o Z80free_codes.o Z80free_codesCB.o Z80free_codesED.o Z80free_codesDD.o Z80free_codesFD.o Z80free_codesDDCB.o Z80free_codesFDCB.o  $(LDFLAGS)

Z80free.o: z80free/Z80free.c z80free/Z80free.h
	$(CC) -o Z80free.o z80free/Z80free.c

Z80free_codes.o: z80free/Z80free_codes.c z80free/Z80free.h
	$(CC) -o Z80free_codes.o z80free/Z80free_codes.c
	
Z80free_codesCB.o: z80free/Z80free_codesCB.c z80free/Z80free.h
	$(CC) -o Z80free_codesCB.o z80free/Z80free_codesCB.c

Z80free_codesED.o: z80free/Z80free_codesED.c z80free/Z80free.h
	$(CC) -o Z80free_codesED.o z80free/Z80free_codesED.c
	
Z80free_codesDD.o: z80free/Z80free_codesDD.c z80free/Z80free.h
	$(CC) -o Z80free_codesDD.o z80free/Z80free_codesDD.c
	
Z80free_codesFD.o: z80free/Z80free_codesFD.c z80free/Z80free.h
	$(CC) -o Z80free_codesFD.o z80free/Z80free_codesFD.c

Z80free_codesDDCB.o: z80free/Z80free_codesDDCB.c z80free/Z80free.h
	$(CC) -o Z80free_codesDDCB.o z80free/Z80free_codesDDCB.c
	
Z80free_codesFDCB.o: z80free/Z80free_codesFDCB.c z80free/Z80free.h
	$(CC) -o Z80free_codesFDCB.o z80free/Z80free_codesFDCB.c

cargador.o: cargador.cpp spk_ay.hh keyboard.hh emulator.hh screen.hh osd.hh z80free/Z80free.h computer.hh signals.hh llscreen.hh tape.hh cargador.hh
	$(CPP) $(CPPFLAGS) -o cargador.o cargador.cpp

cmdline.o: cmdline.cpp cmdline.hh
	$(CPP) $(CPPFLAGS) -o cmdline.o cmdline.cpp

computer.o: computer.cpp z80free/Z80free.h llsound.hh mouse.hh keyboard.hh computer.hh screen.hh signals.hh llscreen.hh tape.hh emulator.hh osd.hh spk_ay.hh microdrive.hh menus.hh
	$(CPP) $(CPPFLAGS) -o computer.o computer.cpp

emulator.o: emulator.cpp mouse.hh z80free/Z80free.h spk_ay.hh keyboard.hh llsound.hh cmdline.hh computer.hh screen.hh signals.hh llscreen.hh tape.hh emulator.hh osd.hh microdrive.hh menus.hh cargador.hh
	$(CPP) $(CPPFLAGS) -o emulator.o emulator.cpp

keyboard.o: keyboard.cpp menus.hh llscreen.hh llsound.hh computer.hh screen.hh signals.hh z80free/Z80free.h tape.hh emulator.hh osd.hh keyboard.hh
	$(CPP) $(CPPFLAGS) -o keyboard.o keyboard.cpp

llscreen.o: llscreen.cpp osd.hh font.h llscreen.hh
	$(CPP) $(CPPFLAGS) -o llscreen.o llscreen.cpp

llsound.o: llsound.cpp emulator.hh screen.hh osd.hh z80free/Z80free.h computer.hh signals.hh llscreen.hh tape.hh llsound.hh
	$(CPP) $(CPPFLAGS) -o llsound.o llsound.cpp

menus.o: menus.cpp mouse.hh z80free/Z80free.h spk_ay.hh microdrive.hh keyboard.hh llsound.hh llscreen.hh menus.hh tape.hh signals.hh emulator.hh screen.hh osd.hh computer.hh cargador.hh
	$(CPP) $(CPPFLAGS) -o menus.o menus.cpp

microdrive.o: microdrive.cpp osd.hh emulator.hh screen.hh z80free/Z80free.h computer.hh signals.hh llscreen.hh tape.hh microdrive.hh
	$(CPP) $(CPPFLAGS) -o microdrive.o microdrive.cpp

mouse.o: mouse.cpp osd.hh keyboard.hh emulator.hh screen.hh z80free/Z80free.h computer.hh signals.hh llscreen.hh tape.hh mouse.hh
	$(CPP) $(CPPFLAGS) -o mouse.o mouse.cpp

osd.o: osd.cpp osd.hh
	$(CPP) $(CPPFLAGS) -o osd.o osd.cpp

screen.o: screen.cpp keyboard.hh computer.hh screen.hh signals.hh llscreen.hh z80free/Z80free.h tape.hh emulator.hh osd.hh
	$(CPP) $(CPPFLAGS) -o screen.o screen.cpp

signals.o: signals.cpp signals.hh
	$(CPP) $(CPPFLAGS) -o signals.o signals.cpp

spk_ay.o: spk_ay.cpp spk_ay.hh llsound.hh computer.hh screen.hh signals.hh llscreen.hh z80free/Z80free.h tape.hh emulator.hh osd.hh
	$(CPP) $(CPPFLAGS) -o spk_ay.o spk_ay.cpp

tape.o: tape.cpp z80free/Z80free.h tape.hh signals.hh emulator.hh screen.hh osd.hh computer.hh llscreen.hh
	$(CPP) $(CPPFLAGS) -o tape.o tape.cpp
