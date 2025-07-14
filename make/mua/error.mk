# mua/error.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = DYNAMICLIB
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = error
# <path-to-dir>
TARGET_PATH = mua/error
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Imua/inc/util/error \
	-Imua/inc/util
# Link Directories # -L<path-to-dir>
LINKDIRS =
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension>
DLINKS =
# Static link files # -l<file-no-extension> or -l:<file-w-extension>
SLINKS =
DEFINES = 
SRCDIRS = \
	mua/src/util/error
SRCFILES = \
	Error.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
endef
#$(if $(wildcard build/mua-test/error), $(cp $(TARGET) build/mua-test/error/))

include ./make/maker.mk
