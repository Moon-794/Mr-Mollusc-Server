#include <iostream>
#include <QApplication>
#include <QPushButton>

int main(int argc, char** args)
{
    QApplication app(argc, args);

    QPushButton button("Hello, World!");
    button.resize(200, 100);
    button.show();

    return 0;
}