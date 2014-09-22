#include "mainwindow.h"

#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardPaths>

Q_LOGGING_CATEGORY(EDIM, "edim")

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    _libraryModel(this)
{
    setupDatabase();

    setupModel();

    setupUi(this);
    treeViewLibrary->setModel(&_libraryModel);
    treeViewLibrary->setRootIndex(_libraryModel.index(_libraryModel.rootPath()));
    treeViewLibrary->hideColumn(1);
    treeViewLibrary->hideColumn(2);
    treeViewLibrary->hideColumn(3);

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

void MainWindow::setupModel()
{
    QDir documentsLocation(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    _libraryModel.setRootPath(documentsLocation.absolutePath());
}

void MainWindow::setupConnections()
{
    connect(actionQuit, &QAction::triggered, this, &QMainWindow::close);
}
