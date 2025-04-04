# mua/caret_node.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = DYNAMICLIB
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = caret_node
# <path-to-dir>
TARGET_PATH = mua/node
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Imua/inc/util/character \
	-Imua/inc/util/node \
	-Imua/inc/util/node/op_node/bin_node \
	-Imua/inc/util/node/op_node/una_node \
	-Imua/inc/util/token \
	-Imua/inc/util
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/mua/node \
	-Lbuild/mua/token \
	-Lbuild/mua/character
# if on linux or windows, for linking libraries `-l<file>` do not prepend `lib` to the link flag (unless its in the file name) as each `-l` is converted into `-l:` in maker.mk
# if on osx, use -l (internal lib) syntax only, every lib file must begin with `lib`. if lib is static, it must end in `.a`, else if lib dynamic, it must end in `.dylib`
# Dynamic link files # (for internal libs) `-l<file-no-extension>` or (for external libs) `-l:<file-w-extension>` # Order from most dependent to least dependent.
DLINKS = \
	-lbase_node \
	-ltoken \
	-lcharacter
# Static link files # (for internal libs) `-l<file-no-extension>` or (for external libs) `-l:<file-w-extension>` # Order from most dependent to least dependent.
SLINKS =
DEFINES = 
SRCDIRS = \
	mua/src/util/node/op_node/bin_node
SRCFILES = \
	Caret.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./make/maker.mk
