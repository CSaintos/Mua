# maker.mk
.PHONY: all compile build dirs clean

#* Make functions
# eq uses makefile substitution reference
define eq
$(if $(1:$(2)=),,$(if $(2:$(1)=),,T))
endef

#* Compiler flags
CXXFLAGS += -MD -MP -g
ifeq ($(SYS), Windows)
SLINK_TYPE = lib
DLINK_TYPE = dll
EXE_TYPE = .exe
else ifeq ($(filter-out Linux OSX, $(SYS)),)
SLINK_TYPE = a
DLINK_TYPE = so
EXE_TYPE =
endif
ifeq ($(SYS),OSX)
STATIC_LINK_FLAG=
DYNAMIC_LINK_FLAG=
AS_NEED_LINK_FLAG=
else ifeq ($(filter-out Linux Windows, $(SYS)),)
STATIC_LINK_FLAG=-Wl,-Bstatic
DYNAMIC_LINK_FLAG=-Wl,-Bdynamic
AS_NEED_LINK_FLAG=-Wl,--as-needed
endif
ifneq ($(SYS),OSX)
SLINK_FILES := $(patsubst -l%, %.$(SLINK_TYPE), $(patsubst -l:%, %, $(SLINKS)))
DLINK_FILES := $(patsubst -l%, %.$(DLINK_TYPE), $(patsubst -l:%, %, $(DLINKS)))
SLINKS = $(patsubst %, -l:%, $(SLINK_FILES))
DLINKS = $(patsubst %, -l:%, $(DLINK_FILES))
else
SLINK_FILES := $(patsubst -l%, %, $(patsubst -l:%.*, %, $(SLINKS)))
DLINK_FILES := $(patsubst -l%, %, $(patsubst -l:%.*, %, $(DLINKS)))
SLINKS = $(patsubst %, -l%, $(SLINK_FILES))
DLINKS = $(patsubst %, -l%, $(DLINK_FILES))
endif

LINKS = $(SLINK_FILES) $(DLINK_FILES)

#* First class functions
find_srcs = $(wildcard $(addprefix $(addsuffix /, $(SRCDIR)), $(SRCFILES)))
find_libs = $(wildcard $(addprefix $(addsuffix /, $(LINKDIR)), $(LINKS)))
list_rm = $(wordlist 2, $(words $1), $1)
pairmap = $(and $(strip $2), $(strip $3), $(call $1, $(firstword $2), $(firstword $3)) $(call pairmap, $1, $(call list_rm, $2), $(call list_rm, $3)))
compile_exe_cmd = $(shell $(CXX) $(INCLUDES) -c$1 -o$2 $(CXXFLAGS) -MF$(2:%.o=%.d))
compile_lib_cmd = $(shell $(CXX) -fPIC $(INCLUDES) -c$1 -o$2 $(CXXFLAGS) -MF$(2:%.o=%.d))

#* Constants
SRCS = $(foreach SRCDIR, $(SRCDIRS), $(find_srcs))
LIBS = $(foreach LINKDIR, $(patsubst -L%, %, $(LINKDIRS)), $(find_libs))
OBJECTS = $(addprefix $(OBJDIR)/, $(patsubst %.cpp, %.o, $(SRCFILES)))
# FIXME
ifneq ($(and $(call eq,$(SYS),OSX), $(call eq,$(filter-out STATICLIB DYNAMICLIB, $(BUILDTYPE)),)),)
TARGET = $(TARGETDIR)/lib$(TARGET_NAME)
else
TARGET = $(TARGETDIR)/$(TARGET_NAME)
endif
ifeq ($(BUILDTYPE), EXE)
TARGET := $(TARGET)$(EXE_TYPE)
else ifeq ($(BUILDTYPE), STATICLIB)
TARGET := $(TARGET).$(SLINK_TYPE)
else ifeq ($(BUILDTYPE), DYNAMICLIB)
TARGET := $(TARGET).$(DLINK_TYPE)
endif

#* Process execution
ifeq ($(filter-out BOTH LINKONLY, $(PROCESS)),)
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
ifeq ($(SYS),Windows)
	@mkdir $(subst /,\\,$(OBJDIR))
else ifeq ($(filter-out Linux OSX, $(SYS)),)
	@mkdir -p $(OBJDIR)
endif
	@echo create bin directory
endif

# Compile sources into objects
$(OBJECTS): $(SRCS) | $(OBJDIR)
	@echo compile $(SRCS)
ifeq ($(BUILDTYPE), EXE)
	$(call pairmap, compile_exe_cmd, $(SRCS), $(OBJECTS))
else ifeq ($(filter-out STATICLIB DYNAMICLIB, $(BUILDTYPE)),)
	$(call pairmap, compile_lib_cmd, $(SRCS), $(OBJECTS))
else
	@echo invalid buildtype
endif
	@echo compiled $(SRCS)

# Create build directory
$(TARGETDIR):
ifeq ($(wildcard $(TARGETDIR)),)
ifeq ($(SYS),Windows)
	@mkdir $(subst /,\\,$(TARGETDIR))
else ifeq ($(filter-out Linux OSX, $(SYS)),)
	@mkdir -p $(TARGETDIR)
endif
	@echo create build directory
endif

# Build target from objects
ifeq ($(PROCESS), LINKONLY)
$(TARGET): $(LIBS) | $(TARGETDIR)
else
$(TARGET): $(OBJECTS) $(LIBS) | $(TARGETDIR)
endif
	@echo build $(TARGET)
ifeq ($(BUILDTYPE), EXE)
	$(CXX) $(OBJECTS) $(LINKDIRS) $(STATIC_LINK_FLAG) $(SLINKS) $(DYNAMIC_LINK_FLAG) $(DLINKS) $(AS_NEED_LINK_FLAG) -o $(TARGET)
else ifeq ($(BUILDTYPE), STATICLIB)
	$(AR) -rcs $(TARGET) $(OBJECTS)
else ifeq ($(BUILDTYPE), DYNAMICLIB)
	$(CXX) -shared -o $(TARGET) $(OBJECTS) $(LINKDIRS) $(STATIC_LINK_FLAG) $(SLINKS) $(DYNAMIC_LINK_FLAG) $(DLINKS) $(AS_NEED_LINK_FLAG)
endif
	@echo built $(TARGET)

compile: $(OBJECTS)
build: $(TARGET)
	$(POSTBUILDCMDS)
dirs: $(OBJDIR) $(TARGETDIR)
#DEBUG	@echo $(CXXFLAGS)

clean: 
	@echo clean
ifneq ($(wildcard $(OBJCLEANDIR)),)
ifeq ($(SYS),Windows)
	rmdir /s /q $(subst /,\\,$(OBJCLEANDIR))
else ifeq ($(SYS),Linux)
	rmdir /s /q $(OBJCLEANDIR)
else ifeq ($(SYS),OSX)
	rm -r $(OBJCLEANDIR)
endif
endif
ifneq ($(wildcard $(TARGETCLEANDIR)),)
ifeq ($(SYS),Windows)
	rmdir /s /q $(subst /,\\,$(TARGETCLEANDIR))
else ifeq ($(SYS),Linux)
	rmdir /s /q $(TARGETCLEANDIR)
else ifeq ($(SYS),OSX)
	rm -r $(TARGETCLEANDIR)
endif
endif
	@echo cleaned

-include $(OBJECTS:%.o=%.d)
