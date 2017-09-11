CFLAGS= -Wall -ldl -lxcb -g -I./deps/dlist -I./deps/greatest

BINNAME=nitro

TEST_OBJS=tests/event_test.o event.o tests/ipc_test.o ipc.o

all: $(BINNAME) modules check

modules:
	cd mod && $(MAKE) && cp *.so ../modbins

clean: clean-modules
	rm *.o $(BINNAME) modbins/*.so

clean-modules:
	cd mod && $(MAKE) clean

$(BINNAME): wm.o client.o modules.o emit.o handle.o ind.o event.o xcb_handlers.o
	gcc $(CFLAGS) -o $@ $^ -Wl,--export-dynamic

tests/test_all: tests/test_all.o $(TEST_OBJS)  ind.o
	gcc $(CFLAGS) -o $@ $^

check: tests/test_all
	exec tests/test_all -v | awk -f deps/greatest/contrib/greenest

*.o: makefile

.PHONY: modules clean clean-modules check
