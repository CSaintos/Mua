# makefile
.PHONY: all clean dirs $(MAKES) $(CLEANS) $(DIRS)

export CXX = g++
export AR = ar
export CXXFLAGS = -std=c++23

#? List of submakes ex. # ./make/submake1.mk
PROJECTS = \
	./make/stem/error.mk \
	./make/stem/character.mk \
	./make/stem/reader.mk \
	./make/stem/token.mk \
	./make/stem/trie.mk \
	./make/stem/node.mk \
	./make/stem/lexer.mk \
	./make/stem/parser.mk \
	./make/stem/definer.mk \
	./make/stem/interpreter.mk \
	./make/stem/generator.mk \
	./make/stem-test/error.mk \
	./make/stem-test/character.mk \
	./make/stem-test/token.mk \
	./make/stem-test/reader.mk \
	./make/stem-test/node.mk \
	./make/stem-test/lexer.mk \
	./make/stem-test/parser.mk \
	./make/stem-test/definer.mk \
	./make/stem-test/interpreter.mk \
	./make/stem-test/generator.mk

#? List of TARGET_PATHs to be created first. (Only useful if running `make -j` and there are shared TARGET_PATHs) # ./make/submake1.mk 
PROJECTDIRS = \
	./make/stem/error.mk \
	./make/stem-test/error.mk

DIRS = $(foreach PROJECTDIR, $(PROJECTDIRS), d$(PROJECTDIR))
MAKES = $(foreach PROJECT, $(PROJECTS), m$(PROJECT))
CLEANS = $(foreach PROJECT, $(PROJECTS), c$(PROJECT))

all: $(MAKES)
clean: $(CLEANS)
dirs: $(DIRS)

#? Submake dependencies (allows `make -j` to work) ex. # m./make/submake1.mk: m./make/submake2.mk
#? A submake dependes on another if it uses the target of the other (such as the form of a library) 
m./make/stem/trie.mk: m./make/stem/token.mk
m./make/stem/node.mk: m./make/stem/token.mk
m./make/stem/lexer.mk: m./make/stem/error.mk m./make/stem/trie.mk m./make/stem/character.mk
m./make/stem/parser.mk: m./make/stem/error.mk m./make/stem/node.mk
m./make/stem/definer.mk: m./make/stem/error.mk m./make/stem/node.mk m./make/stem/trie.mk
m./make/stem/interpreter.mk: m./make/stem/node.mk
m./make/stem/reader.mk: m./make/stem/character.mk m./make/stem/error.mk
m./make/stem/generator.mk: m./make/stem/node.mk
m./make/plugin/plus.mk: m./make/stem/node.mk
m./make/stem-test/error.mk: m./make/stem/error.mk
m./make/stem-test/character.mk: m./make/stem/character.mk
m./make/stem-test/token.mk: m./make/stem/token.mk
m./make/stem-test/reader.mk: m./make/stem/reader.mk
m./make/stem-test/lexer.mk: m./make/stem/lexer.mk m./make/stem/reader.mk
m./make/stem-test/node.mk: m./make/stem/node.mk
m./make/stem-test/parser.mk: m./make/stem/parser.mk m./make/stem/lexer.mk m./make/stem/reader.mk
m./make/stem-test/definer.mk: m./make/stem/definer.mk m./make/stem/parser.mk m./make/stem/lexer.mk m./make/stem/reader.mk
m./make/stem-test/interpreter.mk: m./make/stem/interpreter.mk m./make/stem/definer.mk m./make/stem/parser.mk m./make/stem/lexer.mk m./make/stem/reader.mk
m./make/stem-test/generator.mk: m./make/stem/generator.mk m./make/stem/parser.mk m./make/stem/lexer.mk m./make/stem/reader.mk

# Static pattern rules for running sub-makes
$(DIRS): d%: %
	@$(MAKE) --no-print-directory -f $< dirs

$(MAKES): m%: % $(DIRS)
	@$(MAKE) --no-print-directory -f $<

$(CLEANS): c%: %
	@$(MAKE) --no-print-directory -f $< clean
