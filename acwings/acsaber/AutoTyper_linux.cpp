#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

#include <iostream>
#include <cstring>
#include <fstream>
#include <unistd.h>

#include "AutoTyper.h"

using namespace std;

void simulate_key(Display *display, KeySym key) {
    KeyCode keycode = XKeysymToKeycode(display, key);
    // printf("simulate_key: %d\n", keycode);
    XTestFakeKeyEvent(display, keycode, True, CurrentTime);
    XTestFakeKeyEvent(display, keycode, False, CurrentTime);
    XFlush(display);
}

bool is_key_down(Display *display, KeySym key) {
    char keys[32];
    XQueryKeymap(display, keys);
    KeyCode keycode = XKeysymToKeycode(display, key);
    // printf("is_key_down: %d\n", keycode);
    return keys[keycode / 8] & (1 << (keycode % 8));
}

char test_letter[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
char test_number[] = "1234567890";
char test_symbol[] = "~!@#$%^&*()_+-={}[]|\\:\";\'<>?,./ ";
char test_escape[] = "\t\n\r";

bool validate_input(Display *display, char* test_buf) {
    bool condition = true;
    char chbuf[2] = {0, 0}; int len = strlen(test_buf);
    for (int i = 0; i < len; ++i) {
        chbuf[0] = test_buf[i];
        KeySym keysym = get_XStringToKeysym(chbuf);
        KeyCode keycode = XKeysymToKeycode(display, keysym);
        printf("ch = \'%c\', KeySym = %lu, KeyCode = %u\n", chbuf[0], keysym, keycode);
        if (keysym == 0 && keycode == 204) condition = false;
    }
    return condition;
}

int main() {
    Display *display = XOpenDisplay(NULL);
    if (!display) {
        cerr << "Unable to open X display" << endl;
        return 1;
    }

    while (true) {
        if (is_key_down(display, XK_Escape)) break; // ESC 键退出

        printf("[Validate]\n");
        bool status[4] = {
            validate_input(display, test_letter),
            validate_input(display, test_number),
            validate_input(display, test_symbol),
            validate_input(display, test_escape)
        };
        if (!(status[0] && status[1] && status[2] && status[3])) {
            printf("Status: Letter | Number | Symbol | Escape = %d %d %d %d\n", 
                status[0], status[1], status[2], status[3]);
            printf("Check failed! Exit\n");
            break; 
        }

        sleep(3);
        printf("[Start]\n");

        ifstream file("target.cpp");
        if (!file.is_open()) {
            cerr << "Error opening target.cpp" << endl;
            continue;
        }
        
        printf("[Typing...]\n");
        char chbuf[2] = {'\0', '\0'};
        while (file.get(chbuf[0])) {
            if (is_key_down(display, XK_Escape)) break;
            // if (is_key_down(display, XK_Insert) && is_key_down(display, XK_BackSpace)) break;
            KeySym keysym = get_XStringToKeysym(chbuf);
            KeyCode keycode = XKeysymToKeycode(display, keysym);
            printf("ch = \'%c\', KeySym = %lu, KeyCode = %u\n", chbuf[0], keysym, keycode);
            simulate_key(display, get_XStringToKeysym(chbuf));
            // putchar(ch);
            usleep(5000); // 延时 0.5 毫秒
        }

        file.close();
        break;
    }

    XCloseDisplay(display);
    return 0;
}
