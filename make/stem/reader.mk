# stem/reader.mk 

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = STATICLIB
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = reader
# <path-to-dir>
TARGET_PATH = stem/reader
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Istem/inc/front \
	-Istem/inc/util \
	-Istem/inc/util/character
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/stem/character
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension>
DLINKS =
# Static link files # -l<file-no-extension> or -l:<file-w-extension>
SLINKS = \
	-lcharacter
DEFINES = 
SRCDIRS = \
	stem/src/front
SRCFILES = \
	Reader.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./make/maker.mk
