# stem-test/illegalCharError.mk 

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = EXE
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = illegalCharError
# Path to Target # <path-to-dir>
TARGET_PATH = stem-test
# Include Directories # -I<path-to-dir>
INCLUDES = \
  -Istem/inc/util/error \
  -Istem/inc/util
# Dynamic Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/stem
# Dynamic link files # -l<file-no-extension> or -l:<file-w-extension>
DLINKS =
# Static link files # -l<file-no-extension> or -l:<file-w-extension>
SLINKS = \
	-l:error.lib
DEFINES =
SRCDIRS = \
  stem/test/util/error
SRCFILES = \
  IllegalCharErrorTest.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./make/maker.mk
