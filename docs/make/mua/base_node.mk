# mua/base_node.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = STATICLIB
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = base_node
# <path-to-dir>
TARGET_PATH = mua/node
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-I../mua/inc/util/character \
	-I../mua/inc/util/node \
	-I../mua/inc/util/node/op_node \
	-I../mua/inc/util/node/node_state \
	-I../mua/inc/util/token \
	-I../mua/inc/util/error \
	-I../mua/inc/util
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/mua/token \
	-Lbuild/mua/character \
	-Lbuild/mua/error
# if on linux or windows, for linking libraries `-l<file>` do not prepend `lib` to the link flag (unless its in the file name) as each `-l` is converted into `-l:` in maker.mk
# if on osx, use -l (internal lib) syntax only, every lib file must begin with `lib`. if lib is static, it must end in `.a`, else if lib dynamic, it must end in `.dylib`
# Dynamic link files # (for internal libs) `-l<file-no-extension>` or (for external libs) `-l:<file-w-extension>` # Order from most dependent to least dependent.
DLINKS =
# Static link files # (for internal libs) `-l<file-no-extension>` or (for external libs) `-l:<file-w-extension>` # Order from most dependent to least dependent.
SLINKS = \
	-ltoken \
	-lcharacter \
	-lerror
DEFINES = 
SRCDIRS = \
	../mua/src/util/node \
	../mua/src/util/node/op_node \
	../mua/src/util
SRCFILES = \
	Node.cpp \
	ValueNode.cpp \
	BinOpNode.cpp \
	UnaOpNode.cpp \
	NodeUtils.cpp \
	NumberUtils.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./make/maker.mk
