# makefile
.PHONY: all clean $(MAKES) $(CLEANS)

export CXX = g++
export AR = ar

PROJECTS = \
	./newmake/stem/error.mk \
	./newmake/stem/reader.mk \
	./newmake/stem/token.mk \
	./newmake/stem/node.mk \
	./newmake/stem/lexer.mk \
	./newmake/stem/parser.mk \
	./newmake/stem/PL.mk \
	./newmake/plugin/plus.mk \
	./newmake/stem/generator.mk \
	./newmake/stem-test/illegalCharError.mk \
	./newmake/stem-test/token.mk \
	./newmake/stem-test/reader.mk \
	./newmake/stem-test/node.mk \
	./newmake/stem-test/lexer.mk \
	./newmake/stem-test/parser.mk \
	./newmake/stem-test/PL.mk \
	./newmake/stem-test/generator.mk

MAKES = $(foreach PROJECT, $(PROJECTS), m$(PROJECT))
CLEANS = $(foreach PROJECT, $(PROJECTS), c$(PROJECT))

all: $(MAKES)
clean: $(CLEANS)

# Static pattern rules for running sub-makes
$(MAKES): m%: %
	@$(MAKE) --no-print-directory -f $<

$(CLEANS): c%: %
	@$(MAKE) --no-print-directory -f $< clean
