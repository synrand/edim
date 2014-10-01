#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include "library.h"
#include "settingsdialog.h"

#include <QFileSystemModel>
#include <QGraphicsScene>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(EDIM)

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);

private:
    Library _library;
    QFileSystemModel _libraryModel;
    QGraphicsScene _previewScene;

    SettingsDialog* _settingsDialog;

    void setupModel();
    void setupConnections();

    void closeEvent(QCloseEvent* event) Q_DECL_OVERRIDE;
    void readSettings();
    void writeSettings();

private slots:
    void showSettings() const;

    void importDocument();
    void showDocument(const QModelIndex& index);
    void searchDocument(const QString& text);
};

#endif // MAINWINDOW_H
