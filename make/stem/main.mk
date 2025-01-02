# stem/main.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = EXE
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = muac
# <path-to-dir>
TARGET_PATH = stem/main
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Istem/inc/back \
	-Istem/inc/front \
	-Istem/inc/util/node/op_node/bin_node \
	-Istem/inc/util/node/op_node/una_node \
	-Istem/inc/util/node \
	-Istem/inc/util/token/trie \
	-Istem/inc/util/token \
	-Istem/inc/util/character \
	-Istem/inc/util
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/stem/interpreter \
	-Lbuild/stem/definer \
	-Lbuild/stem/parser \
	-Lbuild/stem/lexer \
	-Lbuild/stem/reader \
	-Lbuild/stem/node \
	-Lbuild/stem/trie \
	-Lbuild/stem/token \
	-Lbuild/stem/character \
	-Lbuild/stem/error \
	-Lbuild/stem/writer
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
DLINKS =
# Static link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
SLINKS = \
	-linterpreter \
	-ldefiner \
	-lparser \
	-llexer \
	-lreader \
	-lnode \
	-ltrie \
	-ltoken \
	-lcharacter \
	-lerror \
	-lwriter
DEFINES =
SRCDIRS = \
	stem/src
SRCFILES = \
	Main.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./make/maker.mk
