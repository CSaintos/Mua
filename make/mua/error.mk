# mua/error.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = STATICLIB
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = error
# <path-to-dir>
TARGET_PATH = mua/error
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Imua/inc/util
# Link Directories # -L<path-to-dir>
LINKDIRS =
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension>
DLINKS =
# Static link files # -l<file-no-extension> or -l:<file-w-extension>
SLINKS =
DEFINES = 
SRCDIRS = \
	mua/src/util
SRCFILES = \
	Error.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = bin/mua
TARGETCLEANDIR = build/mua

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./make/maker.mk
