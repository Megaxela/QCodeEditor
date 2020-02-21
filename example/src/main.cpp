
// Qt
#include <QApplication>

// Demo
#include <MainWindow.hpp>

int main(int argc, char** argv)
{
    // Creating application
    QApplication a(argc, argv);

    // Creating main window
    MainWindow w;
    w.show();

    return QApplication::exec();
}