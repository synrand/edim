#include "mainwindow.h"

#include "settingsdialog.h"

#include <QDir>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardPaths>

Q_LOGGING_CATEGORY(EDIM, "edim")

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    _libraryModel(this),
    _settingsDialog(new SettingsDialog(this))
{
    initializeSettings();
    setupDatabase();
    setupModel();

    setupUi(this);
    treeViewLibrary->setModel(&_libraryModel);
    treeViewLibrary->setRootIndex(_libraryModel.index(_libraryModel.rootPath()));
    treeViewLibrary->hideColumn(1);
    treeViewLibrary->hideColumn(2);
    treeViewLibrary->hideColumn(3);

    setupConnections();
    readSettings();
}

void MainWindow::initializeSettings()
{
    QSettings settings;

    // Initialize default values
    settings.beginGroup("library");
    if (!settings.value("basePath").isValid()) {
        settings.setValue("basePath", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    }
    settings.endGroup();
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

    if (!q.exec("CREATE TABLE IF NOT EXISTS document (id INTEGER PRIMARY KEY AUTOINCREMENT, libraryPath TEXT, content TEXT)")) {
        qCWarning(EDIM) << "Could not create database layout";
    }
}

void MainWindow::setupModel()
{
    QSettings settings;

    _libraryModel.setRootPath(settings.value("library/basePath").toString());
}

void MainWindow::setupConnections()
{
    // Actions
    connect(actionQuit, &QAction::triggered, this, &QMainWindow::close);
    connect(actionSettings, &QAction::triggered, _settingsDialog, &QDialog::show);

    // UI elements
    connect(treeViewLibrary, &QTreeView::clicked, this, &MainWindow::import);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    writeSettings();

    QMainWindow::closeEvent(event);
}

void MainWindow::readSettings()
{
    QSettings settings;
    settings.beginGroup("MainWindow");
    restoreGeometry(settings.value("geometry").toByteArray());
    settings.endGroup();
}

void MainWindow::writeSettings()
{
    QSettings settings;
    settings.beginGroup("MainWindow");
    settings.setValue("geometry", saveGeometry());
    settings.endGroup();
}

void MainWindow::import(const QModelIndex& index) const
{
    _documentHandler.import(QFileInfo(_libraryModel.fileInfo(index)));
}

void MainWindow::showSettings() const
{
    _settingsDialog->show();
}
