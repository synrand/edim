#include "mainwindow.h"

#include "settingsdialog.h"

#include <QDir>
#include <QGraphicsPixmapItem>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardPaths>

Q_LOGGING_CATEGORY(EDIM, "edim")

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    _library(this),
    _libraryModel(this),
    _settingsDialog(new SettingsDialog(this))
{
    setupModel();

    setupUi(this);
    treeViewLibrary->setModel(&_libraryModel);
    treeViewLibrary->setRootIndex(_libraryModel.index(_libraryModel.rootPath()));
    treeViewLibrary->hideColumn(1);
    treeViewLibrary->hideColumn(2);
    treeViewLibrary->hideColumn(3);
    graphicsViewPreview->setScene(&_previewScene);

    setupConnections();
    readSettings();
}

void MainWindow::setupModel()
{
    _libraryModel.setRootPath(_library.basePath().absolutePath());
}

void MainWindow::setupConnections()
{
    // Actions
    connect(actionQuit, &QAction::triggered, this, &QMainWindow::close);
    connect(actionSettings, &QAction::triggered, _settingsDialog, &QDialog::show);

    // UI elements
    connect(actionImport, &QAction::triggered, this, &MainWindow::importDocument);
    connect(treeViewLibrary, &QTreeView::clicked, this, &MainWindow::showDocument);
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
    restoreState(settings.value("state").toByteArray());
    settings.endGroup();
}

void MainWindow::writeSettings()
{
    QSettings settings;
    settings.beginGroup("MainWindow");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("state", saveState());
    settings.endGroup();
}

void MainWindow::showSettings() const
{
    _settingsDialog->show();
}

void MainWindow::importDocument()
{
    QFileInfo document(_libraryModel.fileInfo(treeViewLibrary->currentIndex()));

    if (!_library.contains(document)) {
        _library.import(document);
    } else {
        // TODO Add an "Update entry instead?" dialog here
        qCDebug(EDIM) << "Library already contains document" << document.absoluteFilePath();
    }
}

void MainWindow::showDocument(const QModelIndex& index)
{
    _previewScene.clear();

    // TODO add sanity checks
    QFileInfo document(_libraryModel.fileInfo(index));
    _previewScene.addItem(new QGraphicsPixmapItem(QPixmap::fromImage(QImage(document.absoluteFilePath()))));
    graphicsViewPreview->fitInView(_previewScene.sceneRect(), Qt::KeepAspectRatio);
}
