# stem-test/generator.mk

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = EXE
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = generator
# <path-to-dir>
TARGET_PATH = stem-test/generator
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Istem/inc/back \
	-Istem/inc/front \
	-Istem/inc/util/token \
	-Istem/inc/util/token/trie \
	-Istem/inc/util \
	-Istem/inc/util/error \
	-Istem/inc/util/node \
	-Istem/inc/util/node/op_node/bin_node \
	-Istem/inc/util/node/op_node/una_node \
	-Istem/inc/util/character
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/stem/parser \
	-Lbuild/stem/generator \
	-Lbuild/stem/lexer \
	-Lbuild/stem/node \
	-Lbuild/stem/PL \
	-Lbuild/stem/reader \
	-Lbuild/stem/trie \
	-Lbuild/stem/token \
	-Lbuild/stem/error \
	-Lbuild/stem/character
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
DLINKS =
# Static link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
SLINKS = \
	-lparser \
	-lgenerator \
	-llexer \
	-lnode \
	-lPL \
	-lreader \
	-ltrie \
	-ltoken \
	-lerror \
	-lcharacter
DEFINES = 
SRCDIRS = \
	stem/test/back
SRCFILES = \
	GeneratorTest.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
	@echo copying build/plugin into build/stem-test/generator/plugin
	@xcopy build\\plugin build\\stem-test\\generator\\plugin /E /I /Y /Q
endef

include ./make/maker.mk
