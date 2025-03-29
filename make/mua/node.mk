# mua/node.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = STATICLIB
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = node
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
	-Lbuild/mua/token \
	-Lbuild/mua/character
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension>
DLINKS =
# Static link files # -l<file-no-extension> or -l:<file-w-extension>
SLINKS = \
	-ltoken \
	-lcharacter
DEFINES = 
SRCDIRS = \
	mua/src/util/node \
	mua/src/util/node/op_node/bin_node \
	mua/src/util/node/op_node/una_node \
	mua/src/util
SRCFILES = \
	Node.cpp \
	ValueNode.cpp \
	BinOpNode.cpp \
	UnaOpNode.cpp \
	BinPlus.cpp \
	BinMinus.cpp \
	Asterisk.cpp \
	FSlash.cpp \
	Percent.cpp \
	Caret.cpp \
	Equal.cpp \
	UnaPlus.cpp \
	UnaMinus.cpp \
	Paren.cpp \
	Let.cpp \
	Semicolon.cpp \
	NodeFactory.cpp \
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
