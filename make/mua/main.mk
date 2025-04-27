# mua/main.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = EXE
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = muac
# <path-to-dir>
TARGET_PATH = mua/main
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Imua/inc/back \
	-Imua/inc/front \
	-Imua/inc/cmd \
	-Imua/inc/util/node/node_state \
	-Imua/inc/util/node/op_node \
	-Imua/inc/util/node \
	-Imua/inc/util/token/trie \
	-Imua/inc/util/token \
	-Imua/inc/util/character \
	-Imua/inc/util
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/mua/interpreter \
	-Lbuild/mua/definer \
	-Lbuild/mua/parser \
	-Lbuild/mua/lexer \
	-Lbuild/mua/reader \
	-Lbuild/mua/node \
	-Lbuild/mua/trie \
	-Lbuild/mua/token \
	-Lbuild/mua/character \
	-Lbuild/mua/error \
	-Lbuild/mua/writer \
	-Lbuild/mua/cmd
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
DLINKS = \
	-linterpreter \
	-ldefiner \
	-lparser \
	-llexer \
	-lreader \
	-lnode_factory \
	-lnode_state \
	-lbase_node \
	-ltrie \
	-ltoken \
	-lcharacter \
	-lerror \
	-lwriter \
	-lcmd
# Static link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
SLINKS =
DEFINES =
SRCDIRS = \
	mua/src
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
