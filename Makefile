CC = gcc

# Binary name
BIN = tinytile

# Sources / objects. Add new .c files here.
SRC = TinyTile.c backend.c
OBJ = $(SRC:.c=.o)
HDR = TinyTile.h config.h

# Install location (suckless style)
PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin

# wlroots pkg name changes per version: wlroots-0.17, -0.18, -0.19, -0.20...
# Override on the command line if needed, e.g.:
#   make WLR_PKG=wlroots-0.19
WLR_PKG ?= wlroots-0.20
PKGS = $(WLR_PKG) wayland-server xkbcommon

PKG_CFLAGS = $(shell pkg-config --cflags $(PKGS))
PKG_LIBS   = $(shell pkg-config --libs $(PKGS))

CFLAGS ?= -O2
CFLAGS += -std=c11 -Wall -Wextra -Wpedantic \
          -D_DEFAULT_SOURCE -D_POSIX_C_SOURCE=200809L \
          $(PKG_CFLAGS)

LDFLAGS +=
LDLIBS = $(PKG_LIBS) -lm

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)

# Suckless style: everything depends on config.h since it is #included
# and holds keybinds / settings. Recompiles on config change.
TinyTile.o: TinyTile.c $(HDR)
backend.o: backend.c $(HDR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BIN) $(OBJ)

install: all
	mkdir -p $(DESTDIR)$(BINDIR)
	install -m 755 $(BIN) $(DESTDIR)$(BINDIR)/$(BIN)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(BIN)

.PHONY: all clean install uninstall
