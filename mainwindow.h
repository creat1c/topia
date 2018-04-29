#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "openglwindow.h"

class MainWindow : public OpenGLWindow
{

public:

    MainWindow();

    void initialize() override;
    void render();

private:



};

#endif // MAINWINDOW_H
