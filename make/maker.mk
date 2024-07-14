# maker.mk

#* First class functions
find_srcs = $(wildcard $(addprefix $(addsuffix /, $(SRCDIR)), $(SRCFILES)))
list_rm = $(wordlist 2, $(words $1), $1)
pairmap = $(and $(strip $2), $(strip $3), $(call $1, $(firstword $2), $(firstword $3)) $(call pairmap, $1, $(call list_rm, $2), $(call list_rm, $3)))
compile_exe_cmd = $(shell $(CXX) $(INCLUDES) -c$1 -o$2)
compile_lib_cmd = $(shell $(CXX) -fPIC $(INCLUDES) -c$1 -o$2)

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
ifneq ($(filter $(PROCESS), BOTH LINKONLY),)
all: $(TARGET)
	$(POSTBUILDCMDS)
else ifeq ($(PROCESS), COMPILEONLY)
all: $(OBJECTS)
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
$(OBJECTS): $(SRCS) | $(OBJDIR)
	@echo compile
ifeq ($(BUILDTYPE), EXE)
	$(call pairmap, compile_exe_cmd, $(SRCS), $(OBJECTS))
else ifneq ($(filter $(BUILDTYPE), STATICLIB DYNAMICLIB),)
	$(call pairmap, compile_lib_cmd, $(SRCS), $(OBJECTS))
else
	@echo invalid buildtype
endif
	@echo compiled

# Create build directory
$(TARGETDIR):
ifeq ($(wildcard $(TARGETDIR)),)
	@mkdir $(subst /,\\,$(TARGETDIR))
	@echo create build directory
endif

# Build target from objects
ifeq ($(PROCESS), LINKONLY)
$(TARGET): | $(TARGETDIR)
else
$(TARGET): $(OBJECTS) | $(TARGETDIR)
endif
	@echo build
ifeq ($(BUILDTYPE), EXE)
	$(CXX) $(OBJECTS) $(LINKDIRS) -Wl,-Bstatic $(SLINKS) -Wl,-Bdynamic $(DLINKS) -Wl,--as-needed -o $(TARGET)
else ifeq ($(BUILDTYPE), STATICLIB)
	$(AR) -rcs $(TARGET) $(OBJECTS)
else ifeq ($(BUILDTYPE), DYNAMICLIB)
	$(CXX) -shared -o $(TARGET) $(OBJECTS) $(LINKDIRS) -Wl,-Bstatic $(SLINKS) -Wl,-Bdynamic $(DLINKS) -Wl,--as-needed
endif
	@echo built

compile: $(OBJECTS)
build: $(TARGET)
	$(POSTBUILDCMDS)

clean: 
	@echo clean
ifneq ($(wildcard $(OBJCLEANDIR)),)
	rmdir /s /q $(subst /,\\,$(OBJCLEANDIR))
endif
ifneq ($(wildcard $(TARGETCLEANDIR)),)
	rmdir /s /q $(subst /,\\,$(TARGETCLEANDIR))
endif
	@echo cleaned
