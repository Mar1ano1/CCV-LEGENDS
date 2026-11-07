TARGET = EBOOT
OBJS = src/main.o

INCDIR = include
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS)
ASFLAGS = $(CFLAGS)

LIBS = -lpspdebug -lpspdisplay -lpspkernel

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = CCV LEGENDS

include $(PSPSDK)/lib/build.mak
