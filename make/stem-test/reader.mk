# stem-test/reader.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = EXE
# COMPILECONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = reader
TARGET_PATH = stem-test/reader
INCLUDES = \
	-Istem/inc/front \
	-Istem/inc/util \
	-Istem/inc/util/character \
	-Istem/inc/util/error
LINKDIRS = \
	-Lbuild/stem/character \
	-Lbuild/stem/reader \
	-Lbuild/stem/error
DLINKS =
SLINKS = \
	-lreader \
	-lcharacter \
	-lerror
DEFINES =
SRCDIRS = \
	stem/test/front
SRCFILES = \
	ReaderTest.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./make/maker.mk
