# stem-test/reader.mk
.PHONY: all compile build clean

#? Variables
# STATICLIB, DYNAMICLIB, or EXE # (no space after)
BUILDTYPE = EXE
# COMPILECONLY, LINKONLY, or BOTH # (no space after)
PROCESS = BOTH
TARGET_NAME = reader-test
TARGET_PATH = stem-test/reader-test
INCLUDES = \
	-Istem/inc/front
LDFLAGS = \
	-Lbuild/stem/reader
LINKS = \
	-lreader
DEFINES =
SRCDIRS = \
	stem/test/front
SRCFILES = \
	ReaderTest.cpp

#? Constants
OBJDIR = bin/$(TARGET_PATH)
TARGETDIR = build/$(TARGET_PATH)
OBJCLEANDIR = $(OBJDIR)
TARGETCLEANDIR = $(TARGETDIR)
CXX = g++

#? Custom build cmds
define POSTBUILDCMDS
endef

#* First class functions
find_srcs = $(wildcard $(addprefix $(addsuffix /, $(SRCDIR)), $(SRCFILES)))
list_rm = $(wordlist 2, $(words $1), $1)
pairmap = $(and $(strip $2), $(strip $3), $(call $1, $(firstword $2), $(firstword $3)) $(call pairmap, $1, $(call list_rm, $2), $(call list_rm, $3)))
compile_exe_cmd = $(CXX) $(INCLUDES) -c $1 -o $2
compile_lib_cmd = $(CXX) -fPIC $(INCLUDES) -c $1 -o $2

#* Constants
SRCS = $(foreach SRCDIR, $(SRCDIRS), $(find_srcs))
OBJECTS = $(addprefix $(OBJDIR)/, $(patsubst %.cpp, %.o, $(SRCFILES)))
TARGET = $(TARGETDIR)/$(TARGET_NAME)
ifeq ($(BUILDTYPE), EXE)
TARGET := $(TARGET).exe
else ifeq ($(BUILDTYPE), STATICLIB)
TARGET := $(TARGET).lib
else ifeq ($(BUILDTYPE), DYNAMICLIB)
TARGET := $(TARGET).dll
endif

#* Process execution
ifeq ($(PROCESS), BOTH)
all: $(OBJDIR) $(OBJECTS) $(TARGETDIR) $(TARGET)
	$(POSTBUILDCMDS)
else ifeq ($(PROCESS), COMPILEONLY)
all: $(OBJDIR) $(OBJECTS)
else ifeq ($(PROCESS), LINKONLY)
all: $(TARGETDIR) $(TARGET)
	$(POSTBUILDCMDS)
else
all: 
	@echo error: invalid process
endif

# Create bin directory
$(OBJDIR):
ifeq ($(wildcard $(OBJDIR)),)
	@mkdir $(subst /,\\,$(OBJDIR))
	@echo create bin directory
endif

# Compile sources into objects
$(OBJECTS): $(SRCS)
ifeq ($(BUILDTYPE), EXE)
	$(call pairmap, compile_exe_cmd, $(SRCS), $(OBJECTS))
else ifeq ($(BUILDTYPE), STATICLIB)
	$(call pairmap, compile_lib_cmd, $(SRCS), $(OBJECTS))
else ifeq ($(BUILDTYPE), DYNAMICLIB)
	$(call pairmap, compile_lib_cmd, $(SRCS), $(OBJECTS))
else 
	@echo invalid buildtype
endif
	@echo compile

# Create build directory
$(TARGETDIR):
ifeq ($(wildcard $(TARGETDIR)),)
	@mkdir $(subst /,\\,$(TARGETDIR))
	@echo create build directory
endif

# Build target from objects
$(TARGET): $(OBJECTS)
ifeq ($(BUILDTYPE), EXE)
	@$(CXX) $(OBJECTS) $(LDFLAGS) $(LINKS) -o $(TARGET)
else ifeq ($(BUILDTYPE), STATICLIB)
	@$(AR) -rcs $(TARGET) $(OBJECTS)
else ifeq ($(BUILDTYPE), DYNAMICLIB)
	@$(CXX) -shared -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(LINKS)
endif
	@echo build

compile: $(OBJDIR) | $(OBJECTS)
build: $(TARGETDIR) | $(TARGET)
	$(POSTBUILDCMDS)

clean:
ifneq ($(wildcard $(OBJCLEANDIR)),)
	rmdir /s /q $(subst /,\\,$(OBJCLEANDIR))
endif
ifneq ($(wildcard $(TARGETCLEANDIR)),)
	rmdir /s /q $(subst /,\\,$(TARGETCLEANDIR))
endif
	@echo clean
