# plugin/plus.mk
.PHONY: all compile build clean

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = DYNAMICLIB
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = plus
# <path-to-dir>
TARGET_PATH = plugin
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Iplugin/algebra \
	-Istem/inc/util \
	-Istem/inc/util/token \
	-Istem/inc/util/node \
	-Istem/inc/util/node/op_node \
	-Istem/inc/util/node/value_node \
	-Istem/api
# Link Directories # -L<path-to-dir>
LINKDIRS =
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
DLINKS = \
	-Lbuild/stem/node \
	-Lbuild/stem/token
# Static link files # -l<file-no-extension> or -l:<file-w-extension> # Order from most dependent to least dependent.
SLINKS = \
	-lnode \
	-ltoken
DEFINES = 
SRCDIRS = \
	plugin/algebra
SRCFILES = \
	Plus.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./newmake/maker.mk
