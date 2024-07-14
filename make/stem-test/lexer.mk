# stem-test/lexer.mk
.PHONY: all compile build clean

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = EXE
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = lexer
# <path-to-dir>
TARGET_PATH = stem-test/lexer
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Istem/inc/front \
	-Istem/inc/util/token \
	-Istem/inc/util \
	-Istem/inc/util/error
# Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/stem/token \
	-Lbuild/stem/error \
	-Lbuild/stem/reader \
	-Lbuild/stem/lexer
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension> # Order from least dependent (most depending) to most dependent (least depending) 
DLINKS =
# Static link files # -l<file-no-extension> or -l:<file-w-extension> # Order from least dependent (most depending) to most dependent (least depending)
SLINKS = \
	-llexer \
	-lreader \
	-ltoken \
	-lerror
DEFINES = 
SRCDIRS = \
	stem/test/front
SRCFILES = \
	LexerTest.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./newmake/maker.mk
