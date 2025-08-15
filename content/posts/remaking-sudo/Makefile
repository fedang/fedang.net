CFLAGS ?= -g -O1
SUDO ?= sudo

ifdef PAM
CFLAGS += -DPAM
LIBS = -lpam -lpam_misc
else
LIBS = -lcrypt
endif

all: sus

sus: sus.o readpassphrase.o
	$(CC) -o $@ $^ $(LIBS)
	$(SUDO) chown root:root $@
	$(SUDO) chmod u+s $@

%.o: %.c
	$(CC) -o $@ $< -c $(CFLAGS)

clean:
	rm -rf *.o sus
