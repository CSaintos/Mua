# mua/lexer.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = STATICLIB
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = lexer
# <path-to-dir>
TARGET_PATH = mua/lexer
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-I../mua/inc/front \
	-I../mua/inc/util/token \
	-I../mua/inc/util/token/trie \
	-I../mua/inc/util \
	-I../mua/inc/util/error \
	-I../mua/inc/util/character
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/mua/error \
	-Lbuild/mua/character \
	-Lbuild/mua/token \
	-Lbuild/mua/trie
# if on linux or windows, for linking libraries `-l<file>` do not prepend `lib` to the link flag (unless its in the file name) as each `-l` is converted into `-l:` in maker.mk
# if on osx, use -l (internal lib) syntax only, every lib file must begin with `lib`. if lib is static, it must end in `.a`, else if lib dynamic, it must end in `.dylib`
# Dynamic link files # (for internal libs) `-l<file-no-extension>` or (for external libs) `-l:<file-w-extension>` # Order from most dependent to least dependent.
DLINKS =
# Static link files # (for internal libs) `-l<file-no-extension>` or (for external libs) `-l:<file-w-extension>` # Order from most dependent to least dependent.
SLINKS = \
	-ltrie \
	-ltoken \
	-lcharacter \
	-lerror
DEFINES = 
SRCDIRS = \
	../mua/src/front
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
