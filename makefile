# makefile
.PHONY: all clean $(MAKES) $(CLEANS)

export CXX = g++
export AR = ar

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

# Static pattern rules for running sub-makes
$(MAKES): m%: %
	@$(MAKE) --no-print-directory -f $<

$(CLEANS): c%: %
	@$(MAKE) --no-print-directory -f $< clean
