# mua-test/reader.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = EXE
# COMPILECONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = reader
TARGET_PATH = mua-test/reader
INCLUDES = \
	-Imua/inc/front \
	-Imua/inc/util \
	-Imua/inc/util/character \
	-Imua/inc/util/error
LINKDIRS = \
	-Lbuild/mua/character \
	-Lbuild/mua/reader \
	-Lbuild/mua/error
DLINKS = \
	-lreader \
	-lcharacter \
	-lerror
SLINKS =
DEFINES =
SRCDIRS = \
	mua/test/front
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
