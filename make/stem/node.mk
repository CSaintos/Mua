# stem/node.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = STATICLIB
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = node
# <path-to-dir>
TARGET_PATH = stem/node
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Istem/inc/util/character \
	-Istem/inc/util/node \
	-Istem/inc/util/node/op_node/bin_node \
	-Istem/inc/util/node/op_node/una_node \
	-Istem/inc/util/token \
	-Istem/inc/util
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/stem/token \
	-Lbuild/stem/character
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension>
DLINKS =
# Static link files # -l<file-no-extension> or -l:<file-w-extension>
SLINKS = \
	-ltoken \
	-lcharacter
DEFINES = 
SRCDIRS = \
	stem/src/util/node \
	stem/src/util/node/op_node/bin_node \
	stem/src/util/node/op_node/una_node \
	stem/src/util
SRCFILES = \
	Node.cpp \
	ValueNode.cpp \
	BinOpNode.cpp \
	UnaOpNode.cpp \
	BinPlus.cpp \
	BinMinus.cpp \
	Asterisk.cpp \
	Caret.cpp \
	Semicolon.cpp \
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
