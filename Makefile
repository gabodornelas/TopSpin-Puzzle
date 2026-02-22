CC              = gcc
# Diferentes opciones para archivo de debugging y el normal
CFLAGS_COMMON   = -Wall
CFLAGS_DEBUG    = $(CFLAGS_COMMON) -g3 -O0
CFLAGS_RELEASE  = $(CFLAGS_COMMON) -O2

SRC             = main.c nodo.c PDB.c

OBJ_DEBUG       = $(SRC:.c=.debug.o)
OBJ_RELEASE     = $(SRC:.c=.release.o)

TARGET_DEBUG    = topspin_debug
TARGET_RELEASE  = topspin

.PHONY: all debug release clean

all: release

debug: $(TARGET_DEBUG)

release: $(TARGET_RELEASE)

# Borra los .o intermedios. Comenta para debugging.
.INTERMEDIATE: $(OBJ_DEBUG)
.INTERMEDIATE: $(OBJ_RELEASE)

$(TARGET_DEBUG): $(OBJ_DEBUG)
	$(CC) $(CFLAGS_DEBUG) -o $@ $^

$(TARGET_RELEASE): $(OBJ_RELEASE)
	$(CC) $(CFLAGS_RELEASE) -o $@ $^

%.debug.o: %.c
	$(CC) $(CFLAGS_DEBUG) -c $< -o $@

%.release.o: %.c
	$(CC) $(CFLAGS_RELEASE) -c $< -o $@

clean:
	rm -f *.debug.o *.release.o $(TARGET_DEBUG) $(TARGET_RELEASE)
