TARGET = EBOOT

OBJS = src/main.o \
       src/world/terrain.o \
       src/graphics/graphics.o \
       src/graphics/renderer.o \
       src/graphics/model.o

INCDIR = include src/graphics src/world

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS)
ASFLAGS = $(CFLAGS)

LIBS = -lpspgum -lpspgu -lpspge -lpspdisplay -lpspkernel

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = CCV LEGENDS

PSPSDK := $(shell psp-config --pspsdk-path)

include $(PSPSDK)/lib/build.mak
