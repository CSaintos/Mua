# stem-test/parser.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = EXE
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = parser
# <path-to-dir>
TARGET_PATH = stem-test/parser
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Istem/inc/front \
	-Istem/inc/util/token \
	-Istem/inc/util/token/trie \
	-Istem/inc/util \
	-Istem/inc/util/error \
	-Istem/inc/util/node \
	-Istem/inc/util/node/op_node \
	-Istem/inc/util/node/value_node \
	-Istem/inc/util/character
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/stem/parser \
	-Lbuild/stem/lexer \
	-Lbuild/stem/reader \
	-Lbuild/stem/node \
	-Lbuild/stem/trie \
	-Lbuild/stem/token \
	-Lbuild/stem/error \
	-Lbuild/stem/character
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
DLINKS =
# Static link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
SLINKS = \
	-lparser \
	-llexer \
	-lreader \
	-lnode \
	-ltrie \
	-ltoken \
	-lerror \
	-lcharacter
DEFINES = 
SRCDIRS = \
	stem/test/front
SRCFILES = \
	ParserTest.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./make/maker.mk
