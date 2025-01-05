# mua/reader.mk 

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = STATICLIB
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = reader
# <path-to-dir>
TARGET_PATH = mua/reader
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Imua/inc/front \
	-Imua/inc/util \
	-Imua/inc/util/character \
	-Imua/inc/util/error
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/mua/character \
	-Lbuild/mua/error
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension>
DLINKS =
# Static link files # -l<file-no-extension> or -l:<file-w-extension>
SLINKS = \
	-lcharacter \
	-lerror
DEFINES = 
SRCDIRS = \
	mua/src/front
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
