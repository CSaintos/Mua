# makefile
.PHONY: all clean $(MAKES) $(CLEANS)

export CXX = g++
export AR = ar

#? List of submakes ex. # ./make/submake1.mk
PROJECTS = \
	./make/stem/error.mk \
	./make/stem/reader.mk \
	./make/stem/token.mk \
	./make/stem/node.mk \
	./make/stem/lexer.mk \
	./make/stem/parser.mk \
	./make/stem/PL.mk \
	./make/plugin/plus.mk \
	./make/stem/generator.mk \
	./make/stem-test/illegalCharError.mk \
	./make/stem-test/token.mk \
	./make/stem-test/reader.mk \
	./make/stem-test/node.mk \
	./make/stem-test/lexer.mk \
	./make/stem-test/parser.mk \
	./make/stem-test/PL.mk \
	./make/stem-test/generator.mk

MAKES = $(foreach PROJECT, $(PROJECTS), m$(PROJECT))
CLEANS = $(foreach PROJECT, $(PROJECTS), c$(PROJECT))

all: $(MAKES)
clean: $(CLEANS)

#? Submake dependencies (allows make -j to work) ex. # m./make/submake1.mk: m./make/submake2.mk
#? A submake dependes on another if it uses the target of the other (such as the form of a library) 
m./make/stem/node.mk: m./make/stem/token.mk
m./make/stem/lexer.mk: m./make/stem/error.mk m./make/stem/token.mk
m./make/stem/parser.mk: m./make/stem/error.mk m./make/stem/token.mk m./make/stem/node.mk
m./make/stem/generator.mk: m./make/stem/node.mk
m./make/plugin/plus.mk: m./make/stem/node.mk
m./make/stem-test/illegalCharError.mk: m./make/stem/error.mk
m./make/stem-test/token.mk: m./make/stem/token.mk
m./make/stem-test/reader.mk: m./make/stem/reader.mk
m./make/stem-test/lexer.mk: m./make/stem/lexer.mk m./make/stem/reader.mk
m./make/stem-test/node.mk: m./make/stem/node.mk
m./make/stem-test/parser.mk: m./make/stem/parser.mk m./make/stem/lexer.mk m./make/stem/reader.mk
m./make/stem-test/PL.mk: m./make/stem/PL.mk
m./make/stem-test/generator.mk: m./make/stem/generator.mk m./make/stem/PL.mk m./make/stem/parser.mk m./make/stem/lexer.mk m./make/stem/reader.mk

# Static pattern rules for running sub-makes
$(MAKES): m%: %
	@$(MAKE) --no-print-directory -f $<

$(CLEANS): c%: %
	@$(MAKE) --no-print-directory -f $< clean
