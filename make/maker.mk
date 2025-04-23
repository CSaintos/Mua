# maker.mk
.PHONY: all compile build dirs clean

#* Make functions
# eq uses makefile substitution reference
define eq
$(if $(1:$(2)=),,$(if $(2:$(1)=),,T))
endef

#* Compiler flags
CXXFLAGS += -MMD -g
ifeq ($(SYS), Windows)
SLINK_TYPE = lib
DLINK_TYPE = dll
EXE_TYPE = .exe
else ifeq ($(SYS), Linux)
SLINK_TYPE = a
DLINK_TYPE = so
EXE_TYPE =
else ifeq ($(SYS), OSX)
SLINK_TYPE = a
DLINK_TYPE = dylib
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
SLINK_FILES := $(patsubst -l%, %.$(SLINK_TYPE), $(patsubst -l:%.$(SLINK_TYPE), %, $(SLINKS)))
DLINK_FILES := $(patsubst -l%, %.$(DLINK_TYPE), $(patsubst -l:%.$(DLINK_TYPE), %, $(DLINKS)))
SLINKS = $(patsubst %, -l%, $(SLINK_FILES))
DLINKS = $(patsubst %, -l%, $(DLINK_FILES))
endif

#* First class functions
find_file = $(wildcard $(addprefix $(addsuffix /, $2), $1))
compile_exe_cmd = $(CXX) -o $2 -c $1 $(INCLUDES) $(CXXFLAGS) -MF $(2:%.o=%.d)
compile_lib_cmd = $(CXX) -o $2 -c $1 $(INCLUDES) -fPIC $(CXXFLAGS) -MF $(2:%.o=%.d)
ifeq ($(SYS), Windows)
cp = copy $(subst /,\,$1) $(subst /,\,$2)
else ifeq ($(filter-out Linux OSX, $(SYS)),)
cp = cp $1 $2
endif

#* Constants
vpath %.cpp $(SRCDIRS)
DLIBS = $(foreach LINKDIR, $(patsubst -L%, %, $(LINKDIRS)), $(call find_file, $(DLINK_FILES), $(LINKDIR)))
SLIBS = $(foreach LINKDIR, $(patsubst -L%, %, $(LINKDIRS)), $(call find_file, $(SLINK_FILES), $(LINKDIR)))
OUT_DLIBS = $(foreach DLINK_FILE, $(DLINK_FILES), $(TARGETDIR)/$(DLINK_FILE))
vpath %.$(DLINK_TYPE) $(patsubst -L%, %, $(LINKDIRS))
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
	mkdir $(subst /,\,$(OBJDIR))
else ifeq ($(filter-out Linux OSX, $(SYS)),)
	mkdir -p $(OBJDIR)
endif
endif

# Compile sources into objects
$(OBJECTS): $(OBJDIR)/%.o : %.cpp | $(OBJDIR)
ifeq ($(BUILDTYPE), EXE)
	$(call compile_exe_cmd,$<,$@)
else ifeq ($(filter-out STATICLIB DYNAMICLIB, $(BUILDTYPE)),)
	$(call compile_lib_cmd,$<,$@)
else
	@echo invalid buildtype
endif

# Create build directory
$(TARGETDIR):
ifeq ($(wildcard $(TARGETDIR)),)
ifeq ($(SYS),Windows)
	mkdir $(subst /,\,$(TARGETDIR))
else ifeq ($(filter-out Linux OSX, $(SYS)),)
	mkdir -p $(TARGETDIR)
endif
endif

# Build target from objects
ifeq ($(PROCESS), LINKONLY)
$(TARGET): $(SLIBS) | $(TARGETDIR) $(DLIBS)
else
$(TARGET): $(OBJECTS) $(SLIBS) | $(TARGETDIR) $(DLIBS)
endif
ifeq ($(BUILDTYPE), EXE)
	$(CXX) -o $(TARGET) $(OBJECTS) $(LINKDIRS) $(STATIC_LINK_FLAG) $(SLINKS) $(DYNAMIC_LINK_FLAG) $(DLINKS) $(AS_NEED_LINK_FLAG)
else ifeq ($(BUILDTYPE), STATICLIB)
	$(AR) -rcs $(TARGET) $(OBJECTS)
else ifeq ($(BUILDTYPE), DYNAMICLIB)
	$(CXX) -shared -o $(TARGET) $(OBJECTS) $(LINKDIRS) $(STATIC_LINK_FLAG) $(SLINKS) $(DYNAMIC_LINK_FLAG) $(DLINKS) $(AS_NEED_LINK_FLAG)
endif
	@echo built $(TARGET)
	@echo .

# Copy Dynamic Libraries
ifeq ($(BUILDTYPE),EXE)
$(TARGET): | $(OUT_DLIBS)
$(OUT_DLIBS): $(TARGETDIR)/% : % | $(TARGETDIR)
	$(call cp, $<, $(TARGETDIR)) 
endif

compile: $(OBJECTS)
build: $(TARGET)
	$(POSTBUILDCMDS)
dirs: $(OBJDIR) $(TARGETDIR)
#DEBUG	@echo $(CXXFLAGS)

clean: 
	@echo clean
ifneq ($(wildcard $(OBJCLEANDIR)),)
ifeq ($(SYS),Windows)
	rmdir /s /q $(subst /,\,$(OBJCLEANDIR))
else ifeq ($(SYS),Linux)
	rmdir /s /q $(OBJCLEANDIR)
else ifeq ($(SYS),OSX)
	rm -r $(OBJCLEANDIR)
endif
endif
ifneq ($(wildcard $(TARGETCLEANDIR)),)
ifeq ($(SYS),Windows)
	rmdir /s /q $(subst /,\,$(TARGETCLEANDIR))
else ifeq ($(SYS),Linux)
	rmdir /s /q $(TARGETCLEANDIR)
else ifeq ($(SYS),OSX)
	rm -r $(TARGETCLEANDIR)
endif
endif
	@echo cleaned

-include $(OBJECTS:%.o=%.d)
