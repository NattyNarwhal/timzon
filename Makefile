CC := gcc
# This means a GNU iconv dep
CFLAGS := -gxcoff -maix64
LDFLAGS :=

PGM := timzon
OBJ := qwcrtvtz.o ebcdic.o main.o
DEPS := qwcrtvtz.h ebcdic.h

.PHONY: all clean

all: $(PGM)

clean:
	rm -f $(OBJ) $(PGM) core

$(OBJ): %.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(PGM): $(OBJ)
	$(CC) -o $@ $^ -L/QOpenSys/usr/lib -liconv $(CFLAGS) $(LDFLAGS)
