CFLAGS  += -ansi -pedantic -Wall -O2
LIBS    := -lc

SRC  := bfc.c consume.c consume3.c getbf.c getbf2.c printop.c zalloc.c parse.c run.c
BIN  := bfc

ODIR := obj
OBJ  := $(patsubst %.c,$(ODIR)/%.o,$(SRC))

IDIR := include

CFLAGS  += -I$(ODIR)/include -I$(IDIR)
LDFLAGS += -L$(ODIR)/lib

all: $(BIN)

clean:
	@rm -rf $(BIN) obj/*

$(BIN): $(OBJ)
	@echo LINK $(BIN)
	@cc $(LDFLAGS) -o $@ $^ $(LIBS)

$(OBJ): $(ODIR)

$(ODIR):
	@mkdir -p $@

$(ODIR)/%.o : %.c
	@echo CC $<
	@cc $(CFLAGS) -c -o $@ $<

# ------------

.PHONY: all clean

.SUFFIXES:
.SUFFIXES: .c .o

vpath %.c   src
vpath %.h   include
