
PREFIX = /usr/local

SRC = avol.c
BIN = avol

INCS = -I/usr/include/alsa
LIBS = -lasound

CPPFLAGS = -D_FORTIFY_SOURCE=2 -D_DEFAULT_SOURCE -D_BSD_SOURCE \
	-D_XOPEN_SOURCE=700 -D_POSIX_C_SOURCE=200809L -DVERSION=\"$(VERSION)\"
CFLAGS = -Wall -Wextra -Werror -Wformat-security -Wpointer-arith \
	-Winit-self -fno-exceptions -fstack-protector-strong \
	--param=ssp-buffer-size=4 -std=c99 -Wpedantic -pedantic \
	-pipe -O2 -fpie -pie -Wl,--no-undefined -Wl,--build-id=sha1 \
	-Wl,-z,relro -Wl,-z,now -Wl,-O1a -s $(INCS) $(LIBS)

CC ?= cc

all: $(BIN)

$(BIN): $(SRC)

install: all
	@echo Installing...
	@mkdir -p $(DESTDIR)$(PREFIX)/bin
	@cp -f $(BIN) $(DESTDIR)$(PREFIX)/bin

uninstall:
	@echo Removing...
	@rm -fv $(DESTDIR)$(PREFIX)/bin/$(BIN)

clean:
	@echo Cleaning...
	@rm -fv $(BIN)

.PHONY:
	all install uninstall clean
