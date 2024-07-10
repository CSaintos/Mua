# stem-test/reader.mk
.PHONY: all compile build clean

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = EXE
# COMPILECONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = reader-test
TARGET_PATH = stem-test/reader-test
INCLUDES = \
	-Istem/inc/front
LINKDIRS = \
	-Lbuild/stem/reader
SLINKS = \
	-lreader
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
CXX = g++
AR = ar

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./newmake/maker.mk
