# mua/lexer.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = DYNAMICLIB
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = lexer
# <path-to-dir>
TARGET_PATH = mua/lexer
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
	-Lbuild/mua/error \
	-Lbuild/mua/character \
	-Lbuild/mua/token \
	-Lbuild/mua/trie
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension>
DLINKS = \
	-ltrie \
	-ltoken \
	-lcharacter \
	-lerror
# Static link files # -l<file-no-extension> or -l:<file-w-extension>
SLINKS =
DEFINES = 
SRCDIRS = \
	mua/src/front
SRCFILES = \
	Lexer.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./make/maker.mk
