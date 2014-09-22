#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(EDIM)

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);

private:
    void setupDatabase();
    void setupConnections();
};

#endif // MAINWINDOW_H
