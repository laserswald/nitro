
CFLAGS=-g 

all: xcb.so

%.so: %.c
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^

clean: 
	rm *.so

.PHONY: clean all
