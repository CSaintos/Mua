# mua-test/illegalCharError.mk 

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = EXE
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = illegalCharError
# Path to Target # <path-to-dir>
TARGET_PATH = mua-test/error
# Include Directories # -I<path-to-dir>
INCLUDES = \
  -Imua/inc/util
# Dynamic Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/mua/error
# for linking libraries `-l<file>` do not prepend `lib` (unless its in the name) as each `-l` is converted into `-l:` in maker.mk
# Dynamic link files # (for internal libs) `-l<file-no-extension>` or (for external libs) `-l:<file-w-extension>`)
DLINKS =
# Static link files # (for internal libs) `-l<file-no-extension>` or (for external libs) `-l:<file-w-extension>`
SLINKS = \
	-lerror
DEFINES =
SRCDIRS = \
  mua/test/util
SRCFILES = \
  ErrorTest.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)

#? Custom build cmds
define POSTBUILDCMDS
endef

include ./make/maker.mk
