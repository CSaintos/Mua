# mua-test/token.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = EXE
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = token
# <path-to-dir>
TARGET_PATH = mua-test/token
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Imua/inc/util/token \
	-Imua/inc/util
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/mua/token
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
DLINKS = \
	-ltoken
# Static link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
SLINKS =
DEFINES = 
SRCDIRS = \
	mua/test/util/token
SRCFILES = \
	TokenUtilsTest.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./make/maker.mk
