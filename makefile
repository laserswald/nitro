CFLAGS= -Wall -ldl -lxcb -g -I./deps/dlist

BINNAME=nitro

all: $(BINNAME) modules

modules:
	cd mod && $(MAKE) && cp *.so ../modbins

clean: clean-modules
	rm *.o $(BINNAME) modbins/*.so

clean-modules:
	cd mod && $(MAKE) clean

$(BINNAME): wm.o client.o modules.o emit.o handle.o ind.o event.o xcb_handlers.o
	gcc $(CFLAGS) -o $@ $^ -Wl,--export-dynamic

.PHONY: modules clean clean-modules
