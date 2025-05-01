# mua-test/node.mk 

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = EXE
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = node
# <path-to-dir>
TARGET_PATH = mua-test/node
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Imua/inc/util/node \
	-Imua/inc/util/node/op_node \
	-Imua/inc/util/node/node_state \
	-Imua/inc/util/token \
	-Imua/inc/util/character \
	-Imua/inc/util
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/mua/node \
	-Lbuild/mua/token \
	-Lbuild/mua/character \
	-Lbuild/mua/error
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension>
DLINKS = \
	-lnode_factory \
	-lnode_state \
	-lbase_node \
	-ltoken \
	-lcharacter \
	-lerror
# Static link files # -l<file-no-extension> or -l:<file-w-extension>
SLINKS =
DEFINES = 
SRCDIRS = \
	mua/test/util/node
SRCFILES = \
	NodeTest.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./make/maker.mk
