# stem-test/generator.mk
.PHONY: all compile build clean

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = EXE
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = generator
# <path-to-dir>
TARGET_PATH = stem-test/generator
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Istem/inc/back \
	-Istem/inc/front \
	-Istem/inc/util/token \
	-Istem/inc/util \
	-Istem/inc/util/error \
	-Istem/inc/util/node \
	-Istem/inc/util/node/op_node \
	-Istem/inc/util/node/value_node \
	-Istem/inc/plugin \
	-Istem/api
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/stem/token \
	-Lbuild/stem/error \
	-Lbuild/stem/node \
	-Lbuild/stem/reader \
	-Lbuild/stem/lexer \
	-Lbuild/stem/parser \
	-Lbuild/stem/generator \
	-Lbuild/stem/PL
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
DLINKS =
# Static link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
SLINKS = \
	-lparser \
	-lgenerator \
	-llexer \
	-lnode \
	-lPL \
	-lreader \
	-ltoken \
	-lerror \

DEFINES = 
SRCDIRS = \
	stem/test/back
SRCFILES = \
	GeneratorTest.cpp
	

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./newmake/maker.mk
