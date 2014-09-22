#include "mainwindow.h"

#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardPaths>

Q_LOGGING_CATEGORY(EDIM, "edim")

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent)
{
    setupDatabase();
    setupUi(this);
    setupConnections();
}

void MainWindow::setupDatabase()
{
    // Check data location
    QDir dataLocation(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    if (!dataLocation.exists()) {
        if (!dataLocation.mkpath(".")) {
            qCCritical(EDIM) << "Could not access data location at" << dataLocation.absolutePath();
        }
    }

    // Connect to database
    QString databaseFile(dataLocation.absolutePath().append(QDir::separator()).append("data.sqlite"));
    QSqlDatabase database(QSqlDatabase::addDatabase("QSQLITE"));
    database.setDatabaseName(databaseFile);
    if (!database.open()) {
        qCCritical(EDIM) << "Could not connect to database";
    }

    // Enable FOREIGN KEY support
    QSqlQuery q;
    if (!q.exec("PRAGMA foreign_keys = ON")) {
        qCWarning(EDIM) << "Could not enable FOREIGN KEY support";
    }
}

void MainWindow::setupConnections()
{
    connect(action_Quit, &QAction::triggered, this, &QMainWindow::close);
}
