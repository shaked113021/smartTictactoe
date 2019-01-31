#include "Headers/Window1.h"

int main(int argc, char **argv)
{
    Window1 *MainWindow = new Window1(argc, argv);

    delete MainWindow;
    return 0;
}