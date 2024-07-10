# stem/error.mk
.PHONY: all compile build clean

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = STATICLIB
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = error
# <path-to-dir>
TARGET_PATH = stem/error
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Istem/inc/util/error \
	-Istem/inc/util
# Link Directories # -L<path-to-dir>
LINKDIRS =
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension>
DLINKS =
# Static link files # -l<file-no-extension> or -l:<file-w-extension>
SLINKS =
DEFINES = 
SRCDIRS = \
	stem/src/util/error
SRCFILES = \
	Error.cpp \
	IllegalCharError.cpp \
	SyntaxError.cpp

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
