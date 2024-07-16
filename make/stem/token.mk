# stem/token.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = STATICLIB
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = token
# <path-to-dir>
TARGET_PATH = stem/token
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Istem/inc/util/token \
	-Istem/inc/util
# Link Directories # -L<path-to-dir>
LINKDIRS =
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension>
DLINKS =
# Static link files # -l<file-no-extension> or -l:<file-w-extension>
SLINKS =
DEFINES = 
SRCDIRS = \
	stem/src/util/token
SRCFILES = \
	TokenUtils.cpp \
	Token.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./make/maker.mk
