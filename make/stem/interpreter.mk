# stem/interpreter.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = STATICLIB
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = interpreter
# <path-to-dir>
TARGET_PATH = stem/interpreter
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Istem/inc/front \
	-Istem/inc/back \
	-Istem/inc/util/node/op_node/bin_node \
	-Istem/inc/util/node/op_node/una_node \
	-Istem/inc/util/node \
	-Istem/inc/util/token \
	-Istem/inc/util
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/stem/node \
	-Lbuild/stem/token
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
DLINKS = \
# Static link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
SLINKS = \
	-lnode \
	-ltoken
DEFINES = 
SRCDIRS = \
	stem/src/back
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
