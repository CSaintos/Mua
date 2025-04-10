# mua/interpreter.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = DYNAMICLIB
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = interpreter
# <path-to-dir>
TARGET_PATH = mua/interpreter
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Imua/inc/front \
	-Imua/inc/back \
	-Imua/inc/util/node/op_node \
	-Imua/inc/util/node/node_state \
	-Imua/inc/util/node \
	-Imua/inc/util/token \
	-Imua/inc/util \
	-Imua/inc/util/character
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/mua/node \
	-Lbuild/mua/token \
	-Lbuild/mua/character
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
DLINKS = \
	-lbase_node \
	-ltoken \
	-lcharacter
# Static link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
SLINKS =
DEFINES = 
SRCDIRS = \
	mua/src/back
SRCFILES = \
	Interpreter.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./make/maker.mk
