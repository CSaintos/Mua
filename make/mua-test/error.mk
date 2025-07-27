# mua-test/error.mk 

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = EXE
# COMPILEONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = illegalCharError
# <path-to-dir>
TARGET_PATH = mua-test/error
# Include Directories # -I<path-to-dir>
INCLUDES = \
	-Imua/inc/util/error \
  -Imua/inc/util
# Dynamic Link Directories # -L<path-to-dir>
LINKDIRS = \
	-Lbuild/mua/error
# if on linux or windows, for linking libraries `-l<file>` do not prepend `lib` (unless its in the name) as each `-l` is converted into `-l:` in maker.mk
# if on osx, use -l (internal lib) syntax only, every lib file must be prepended with `lib`, and if static must end in `.a`, if dynamic must end in `.dylib`
# Dynamic link files # (for internal libs) `-l<file-no-extension>` or (for external libs) `-l:<file-w-extension>`
DLINKS = \
	-lerror
# Static link files # (for internal libs) `-l<file-no-extension>` or (for external libs) `-l:<file-w-extension>`
SLINKS =
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
