# mua/node_state.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = STATICLIB
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = node_state
# <path-to-dir>
TARGET_PATH = mua/node
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-I../mua/inc/util/node/node_state \
	-I../mua/inc/util/node \
	-I../mua/inc/util \
	-I../mua/inc/util/token \
	-I../mua/inc/util/node/op_node \
	-I../mua/inc/util/character
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/mua/node \
	-Lbuild/mua/token \
	-Lbuild/mua/character
# if on linux or windows, for linking libraries `-l<file>` do not prepend `lib` to the link flag (unless its in the file name) as each `-l` is converted into `-l:` in maker.mk
# if on osx, use -l (internal lib) syntax only, every lib file must begin with `lib`. if lib is static, it must end in `.a`, else if lib dynamic, it must end in `.dylib`
# Dynamic link files # (for internal libs) `-l<file-no-extension>` or (for external libs) `-l:<file-w-extension>` # Order from most dependent to least dependent.
DLINKS =
# Static link files # (for internal libs) `-l<file-no-extension>` or (for external libs) `-l:<file-w-extension>` # Order from most dependent to least dependent.
SLINKS = \
	-lbase_node \
	-ltoken \
	-lcharacter
DEFINES = 
SRCDIRS = \
	../mua/src/util/node/node_state
SRCFILES = \
	Asterisk.cpp \
	BinMinus.cpp \
	BinOpState.cpp \
	BinPlus.cpp \
	Caret.cpp \
	Equal.cpp \
	FSlash.cpp \
	Let.cpp \
	Paren.cpp \
	Percent.cpp \
	Semicolon.cpp \
	UnaMinus.cpp \
	UnaOpState.cpp \
	UnaPlus.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./make/maker.mk
