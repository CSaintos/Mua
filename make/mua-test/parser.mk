# mua-test/parser.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = EXE
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = parser
# <path-to-dir>
TARGET_PATH = mua-test/parser
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Imua/inc/front \
	-Imua/inc/util/token \
	-Imua/inc/util/token/trie \
	-Imua/inc/util \
	-Imua/inc/util/node \
	-Imua/inc/util/node/op_node/bin_node \
	-Imua/inc/util/node/op_node/una_node \
	-Imua/inc/util/character
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/mua/parser \
	-Lbuild/mua/lexer \
	-Lbuild/mua/reader \
	-Lbuild/mua/node \
	-Lbuild/mua/trie \
	-Lbuild/mua/token \
	-Lbuild/mua/error \
	-Lbuild/mua/character
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
DLINKS = \
	-lparser \
	-llexer \
	-lreader \
	-lnode_factory \
	-lbinminus_node \
	-lbinplus_node \
	-lfslash_node \
	-lpercent_node \
	-lasterisk_node \
	-lcaret_node \
	-lequal_node \
	-llet_node \
	-lparen_node \
	-lunaminus_node \
	-lunaplus_node \
	-lsemicolon_node \
	-lbase_node \
	-ltrie \
	-ltoken \
	-lerror \
	-lcharacter
# Static link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
SLINKS =
DEFINES = 
SRCDIRS = \
	mua/test/front
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
