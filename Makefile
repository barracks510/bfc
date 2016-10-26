CFLAGS  += -std=c99 -pedantic -Wall -O2
LIBS    := -lc

SRC  := bfc.c consume.c getbf.c printop.c zalloc.c
BIN  := bfc

ODIR := obj
OBJ  := $(patsubst %.c,$(ODIR)/%.o,$(SRC))

IDIR := include

CFLAGS  += -I$(ODIR)/include -I$(IDIR)
LDFLAGS += -L$(ODIR)/lib

all: $(BIN)

clean:
	$(RM) -rf $(BIN) obj/*

$(BIN): $(OBJ)
	@echo LINK $(BIN)
	@$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

$(OBJ): $(ODIR)

$(ODIR):
	@mkdir -p $@

$(ODIR)/%.o : %.c
	@echo CC $<
	@$(CC) $(CFLAGS) -c -o $@ $<

# ------------

.PHONY: all clean

.SUFFIXES:
.SUFFIXES: .c .o

vpath %.c   src
vpath %.h   include
