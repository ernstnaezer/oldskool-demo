CC = wpp386
CFLAGS = -fpi87 -fp5 -mf -d3 
LINKER = wlink

# Directories
OBJDIR = .\build
LIBS = .\LIB\USM\USMPWS.LIB

OBJECTS = $(OBJDIR)\demo.obj &
          $(OBJDIR)\vesa.obj &
          $(OBJDIR)\sound.obj &
          $(OBJDIR)\timer.obj &
          $(OBJDIR)\graphics.obj &
          $(OBJDIR)\framebuf.obj

TARGET = demo.exe

# Rules
all: $(TARGET)

$(OBJDIR)\demo.obj: demo.cpp
	$(CC) $(CFLAGS) $< -fo=$@

$(OBJDIR)\vesa.obj: lib\vesa.cpp
	$(CC) $(CFLAGS) $< -fo=$@

$(OBJDIR)\timer.obj: lib\timer.cpp
	$(CC) $(CFLAGS) $< -fo=$@

$(OBJDIR)\sound.obj: lib\sound.cpp
	$(CC) $(CFLAGS) $< -fo=$@

$(OBJDIR)\framebuf.obj: lib\framebuf.cpp
	$(CC) $(CFLAGS) $< -fo=$@

$(OBJDIR)\graphics.obj: lib\graphics.cpp
	$(CC) $(CFLAGS) $< -fo=$@

$(TARGET) : $(OBJECTS)
    %write wmake.tmp file { $(OBJECTS) }
    %write wmake.tmp library { $(LIBS) }
    %write wmake.tmp name $(TARGET)
    # %write wmake.tmp system dos4g
    # %write wmake.tmp option stub=$(STUB)
    %write wmake.tmp option caseexact
    wlink @wmake.tmp
    del wmake.tmp

clean:
	del $(OBJDIR)\*.obj
	del $(TARGET)