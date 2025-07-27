# mua/trie.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = STATICLIB
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = trie
# <path-to-dir>
TARGET_PATH = mua/trie
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-I../mua/inc/util \
	-I../mua/inc/util/token \
	-I../mua/inc/util/token/trie
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/mua/token
# if on linux or windows, for linking libraries `-l<file>` do not prepend `lib` to the link flag (unless its in the file name) as each `-l` is converted into `-l:` in maker.mk
# if on osx, use -l (internal lib) syntax only, every lib file must begin with `lib`. if lib is static, it must end in `.a`, else if lib dynamic, it must end in `.dylib`
# Dynamic link files # (for internal libs) `-l<file-no-extension>` or (for external libs) `-l:<file-w-extension>` # Order from most dependent to least dependent.
DLINKS =
# Static link files # (for internal libs) `-l<file-no-extension>` or (for external libs) `-l:<file-w-extension>` # Order from most dependent to least dependent.
SLINKS = \
	-ltoken
DEFINES = 
SRCDIRS = \
	../mua/src/util/token/trie \
	../mua/src/util
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
