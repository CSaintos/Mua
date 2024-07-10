# makefile
.PHONY: all clean $(MAKES) $(CLEANS)

PROJECTS = \
	./newmake/stem/error.mk \
	./newmake/stem/reader.mk \

MAKES = $(foreach PROJECT, $(PROJECTS), m$(PROJECT))
CLEANS = $(foreach PROJECT, $(PROJECTS), c$(PROJECT))

all: $(MAKES)
clean: $(CLEANS)

# Static pattern rules for running sub-makes
$(MAKES): m%: %
	@$(MAKE) --no-print-directory -f $<

$(CLEANS): c%: %
	@$(MAKE) --no-print-directory -f $< clean
