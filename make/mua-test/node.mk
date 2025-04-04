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
	-Imua/inc/util/node/op_node/bin_node \
	-Imua/inc/util/node/op_node/una_node \
	-Imua/inc/util/token \
	-Imua/inc/util/character \
	-Imua/inc/util
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/mua/node \
	-Lbuild/mua/token \
	-Lbuild/mua/character
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension>
DLINKS = \
	-lnode_factory \
	-lbinminus_node \
	-lbinplus_node \
	-lfslash_node \
	-lpercent_node \
	-lasterisk_node \
	-lcaret_node \
	-lequal_node \
	-llet_node \
	-lparen_node \
	-lunaminus_node \
	-lunaplus_node \
	-lsemicolon_node \
	-lbase_node \
	-ltoken \
	-lcharacter
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
