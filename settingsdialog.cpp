#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget* parent) :
    QDialog(parent)
{
    setupUi(this);
    setupConnections();
}

void SettingsDialog::setupConnections()
{
    connect(listWidgetCategory, &QListWidget::currentItemChanged, this, &SettingsDialog::setCategory);
}

void SettingsDialog::setCategory(QListWidgetItem* current, QListWidgetItem* previous)
{
    if (current == nullptr) {
        return;
    }

    labelPageTitle->setText(current->text());
    stackedWidgetPage->setCurrentIndex(listWidgetCategory->row(current));
}
