# stem/trie.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = STATICLIB
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = trie
# <path-to-dir>
TARGET_PATH = stem/trie
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Istem/inc/util/token \
	-Istem/inc/util/token/trie
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/stem/token
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
DLINKS = \
# Static link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
SLINKS = \
	-ltoken
DEFINES = 
SRCDIRS = \
	stem/src/util/token/trie
SRCFILES = \
	TokenTrie.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./make/maker.mk
