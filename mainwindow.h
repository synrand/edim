#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include "documenthandler.h"
#include "settingsdialog.h"

#include <QFileSystemModel>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(EDIM)

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);

private:
    DocumentHandler _documentHandler;
    QFileSystemModel _libraryModel;

    SettingsDialog* _settingsDialog;

    void initializeSettings();
    void setupDatabase();
    void setupModel();
    void setupConnections();

    void closeEvent(QCloseEvent* event) Q_DECL_OVERRIDE;
    void readSettings();
    void writeSettings();

private slots:
    void import(const QModelIndex& index) const;

    void showSettings() const;
};

#endif // MAINWINDOW_H
