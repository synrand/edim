#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "ui_settingsdialog.h"

class SettingsDialog : public QDialog, private Ui::SettingsDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget* parent = 0);

private:
    void setupConnections();

private slots:
    void setCategory(QListWidgetItem* current, QListWidgetItem* previous);
};

#endif // SETTINGSDIALOG_H
