#include <iostream>
#include <QApplication>
#include <QStyleFactory>
#include <QMainWindow>
#include <internal/QCXXHighlighter.hpp>
#include <QCodeEditor>

int main(int argc, char** argv)
{
    // Creating application
    QApplication a(argc, argv);

    // Making style
    // Doing this after application creation to
    // accept system specific palette.
    // Can be changed after applying internal
    // theme system.
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    // Creating main window
    QMainWindow w;

    QCodeEditor c(&w);
    w.setCentralWidget(&c);
    c.setWordWrapMode(QTextOption::NoWrap);

    QCXXHighlighter hl(c.document());

    c.setPlainText(
R"(#include <iostream>

int main(int argc, const char**)
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

int main(int argc, const char**)
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

int main(int argc, const char**)
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

int main(int argc, const char**)
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

int main(int argc, const char**)
{
    std::cout << "Hello world" << std::endl;
    return 0;
}
)");

    w.show();

    // Running application
    return QApplication::exec();
}