# mua/trie.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = DYNAMICLIB
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = trie
# <path-to-dir>
TARGET_PATH = mua/trie
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Imua/inc/util \
	-Imua/inc/util/token \
	-Imua/inc/util/token/trie
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/mua/token
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
DLINKS = \
	-ltoken
# Static link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
SLINKS =
DEFINES = 
SRCDIRS = \
	mua/src/util/token/trie \
	mua/src/util
SRCFILES = \
	TokenTrie.cpp \
	NameTrie.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./make/maker.mk
