# mua-test/lexer.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = EXE
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = lexer
# <path-to-dir>
TARGET_PATH = mua-test/lexer
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Imua/inc/front \
	-Imua/inc/util/token \
	-Imua/inc/util/token/trie \
	-Imua/inc/util \
	-Imua/inc/util/error \
	-Imua/inc/util/character
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/mua/lexer \
	-Lbuild/mua/reader \
	-Lbuild/mua/trie \
	-Lbuild/mua/token \
	-Lbuild/mua/error \
	-Lbuild/mua/character
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension> # Order from least dependent (most depending) to most dependent (least depending) 
DLINKS =
# Static link files # -l<file-no-extension> or -l:<file-w-extension> # Order from least dependent (most depending) to most dependent (least depending)
SLINKS = \
	-llexer \
	-lreader \
	-ltrie \
	-ltoken \
	-lerror \
	-lcharacter
DEFINES = 
SRCDIRS = \
	mua/test/front
SRCFILES = \
	LexerTest.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./make/maker.mk
