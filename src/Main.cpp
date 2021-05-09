#include "Headers/Window1.h"

int main(int argc, char **argv) {
    Window1* main_window = new Window1(argc, argv);

    delete main_window;
    return 0;
}