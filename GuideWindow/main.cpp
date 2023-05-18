#include "Headers/GuideWindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;
    my_GuideWindow ui;
    ui.setupUi(&window);
    ui.setLeftEvents();
    ui.setMainEvents();
    window.show();
    return a.exec();
}
