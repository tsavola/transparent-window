#include <stddef.h>
#include <string.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

int main(int argc, char **argv)
{
	Display *display = XOpenDisplay(NULL);

	XVisualInfo vinfo;
	XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &vinfo);

	Window root = DefaultRootWindow(display);

	XSetWindowAttributes attr;
	memset(&attr, 0, sizeof attr);
	attr.colormap = XCreateColormap(display, root, vinfo.visual, AllocNone);

	Window w = XCreateWindow(display, root, 0, 0, 256, 256, 0, vinfo.depth, InputOutput, vinfo.visual, CWColormap | CWBorderPixel | CWBackPixel, &attr);
	XSelectInput(display, w, StructureNotifyMask);

	XSetWindowBorderWidth(display, w, 0);

	Atom atom = XInternAtom(display, "WM_DELETE_WINDOW", 0);
	XSetWMProtocols(display, w, &atom, 1);

	XMapWindow(display, w);

	while (1) {
		XEvent event;
		XNextEvent(display, &event);

		if (event.type == ClientMessage && event.xclient.message_type == XInternAtom(display, "WM_PROTOCOLS", 1) && (Atom) event.xclient.data.l[0] == XInternAtom(display, "WM_DELETE_WINDOW", 1))
			return 0;
	}
}
