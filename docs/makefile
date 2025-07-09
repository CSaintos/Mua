# makefile
.PHONY: all clean dirs $(MAKES) $(CLEANS) $(DIRS)

export CXX := emcc
export AR := emar
ifeq ($(CXX_VERSION),)
CXX_VERSION:=c++23
endif
export CXXFLAGS := -std=$(CXX_VERSION)
ifeq ($(SYS),)
ifeq ($(OS),Windows_NT)
SYS := Windows
else ifeq ($(shell uname -s),Linux)
SYS := Linux
else ifeq ($(shell uname -s),Darwin)
SYS := OSX
endif
endif
ifeq ($(FILESYS),)
FILESYS := $(SYS)
endif
ifeq ($(filter-out emcc em++, $(CXX)),)
SYS := Web
endif

export SYS
export FILESYS

#? List of submakes ex. # ./make/submake1.mk
PROJECTS := \
	./make/mua/mua_api.mk \
	./make/mua/interpreter.mk \
	./make/mua/definer.mk \
	./make/mua/parser.mk \
	./make/mua/node_factory.mk \
	./make/mua/node_state.mk \
	./make/mua/base_node.mk \
	./make/mua/lexer.mk \
	./make/mua/trie.mk \
	./make/mua/token.mk \
	./make/mua/character.mk \
	./make/mua/error.mk

#? List of TARGET_PATHs to be created first. (Only useful if running `make -j` and there are shared TARGET_PATHs) ex. # ./make/submake1.mk
PROJECTDIRS := \
	./make/mua/error.mk

DIRS := $(foreach PROJECTDIR, $(PROJECTDIRS), d$(PROJECTDIR))
MAKES := $(foreach PROJECT, $(PROJECTS), m$(PROJECT))
CLEANS := $(foreach PROJECT, $(PROJECTS), c$(PROJECT))

all: $(MAKES)
clean: $(CLEANS)
dirs: $(DIRS)

#? Submake dependencies (allows `make -j` to work) ex. # m./make/submake1.mk: m./make/submake2.mk
#? A submake depends on another if it uses the target of the other (such as the form of a library)
m./make/mua/character.mk: m./make/mua/error.mk
m./make/mua/trie.mk: m./make/mua/token.mk
m./make/mua/lexer.mk: m./make/mua/character.mk m./make/mua/trie.mk
m./make/mua/base_node.mk: m./make/mua/token.mk m./make/mua/character.mk
m./make/mua/node_state.mk: m./make/mua/base_node.mk
m./make/mua/node_factory.mk: m./make/mua/node_state.mk
m./make/mua/parser.mk: m./make/mua/node_factory.mk
m./make/mua/definer.mk: m./make/mua/node_factory.mk m./make/mua/trie.mk
m./make/mua/interpreter.mk: m./make/mua/base_node.mk
m./make/mua/mua_api.mk: m./make/mua/interpreter.mk m./make/mua/definer.mk m./make/mua/parser.mk m./make/mua/lexer.mk

# Static pattern rules for running sub-makes
$(DIRS): d%: %
	@$(MAKE) --no-print-directory -f $< dirs

$(MAKES): m%: % $(DIRS)
	@$(MAKE) --no-print-directory -f $<

$(CLEANS): c%: %
	@$(MAKE) --no-print-directory -f $< clean
