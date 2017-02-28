.POSIX:

PREFIX = /usr/local
MONTK = $(PREFIX)/lib/montk

TOOLS = cpuperc memperc sndvol thermal
BIN = montk

all: tools

tools:
	@echo Building...
	@mkdir -p bin
	@for t in $(TOOLS);do		\
		$(MAKE) -C $$t;		\
		mv -f $$t/$$t bin/;	\
	done

install: all
	@echo Installing...
	@mkdir -p $(DESTDIR)$(MONTK)/bin
	@cp -f $(BIN) $(DESTDIR)$(PREFIX)/bin
	@cp -rfv bin $(DESTDIR)$(MONTK)

uninstall:
	@echo Removing...
	@rm -fv $(DESTDIR)$(PREFIX)/bin/$(BIN)
	@rm -rfv $(DESTDIR)$(MONTK)

clean:
	@echo Cleaning...
	@rm -rfv bin

.PHONY:
	all tools install uninstall clean
