#include <QApplication>
#include "UIModule/MyClicker.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MyClicker p;
    p.show();
    return app.exec();
}
