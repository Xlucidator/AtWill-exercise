#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

void simulate_key(Display *display, KeySym key) {
    KeyCode keycode = XKeysymToKeycode(display, key);
    XTestFakeKeyEvent(display, keycode, True, CurrentTime);
    XTestFakeKeyEvent(display, keycode, False, CurrentTime);
    XFlush(display);
}

bool is_key_down(Display *display, KeySym key) {
    char keys[32];
    XQueryKeymap(display, keys);
    KeyCode keycode = XKeysymToKeycode(display, key);
    return keys[keycode / 8] & (1 << (keycode % 8));
}

int main() {
    Display *display = XOpenDisplay(NULL);
    if (!display) {
        cerr << "Unable to open X display" << endl;
        return 1;
    }

    while (true) {
        if (is_key_down(display, XK_Escape)) break; // ESC 键退出
        if (is_key_down(display, XK_Insert) && is_key_down(display, XK_BackSpace)) break; // Insert + BackSpace 退出

        // usleep(3000 * 1000); // 延时 3000 毫秒
        sleep(3);

        ifstream file("target.cpp");
        if (!file.is_open()) {
            cerr << "Error opening target.cpp" << endl;
            continue;
        }

        char ch;
        while (file.get(ch)) {
            if (is_key_down(display, XK_Insert) && is_key_down(display, XK_BackSpace)) break;
            simulate_key(display, XStringToKeysym(&ch));
            usleep(500); // 延时 0.5 毫秒
        }

        file.close();
    }

    XCloseDisplay(display);
    return 0;
}
