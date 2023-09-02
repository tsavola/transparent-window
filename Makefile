transparent-window: transparent-window.c
	$(CC) -Wall -Os -g -o $@ transparent-window.c -lX11

.PHONY: clean
clean:
	rm -f transparent-window
