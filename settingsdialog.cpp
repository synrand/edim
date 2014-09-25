#include "settingsdialog.h"

#include <QFileDialog>
#include <QSettings>

SettingsDialog::SettingsDialog(QWidget* parent) :
    QDialog(parent)
{
    setupUi(this);
    QSettings settings;
    lineEditBasePath->setText(settings.value("library/basePath").toString());

    setupConnections();
}

void SettingsDialog::setupConnections()
{
    connect(listWidgetCategory, &QListWidget::currentItemChanged, this, &SettingsDialog::setCategory);

    connect(toolButtonBasePath, &QToolButton::clicked, this, &SettingsDialog::setBasePath);
}

void SettingsDialog::setCategory(QListWidgetItem* current, QListWidgetItem* previous)
{
    Q_UNUSED(previous)

    if (current == nullptr) {
        return;
    }

    labelPageTitle->setText(current->text());
    stackedWidgetPage->setCurrentIndex(listWidgetCategory->row(current));
}

void SettingsDialog::setBasePath()
{
    QFileDialog fileDialog(this, tr("Select Base Path"));
    fileDialog.setFileMode(QFileDialog::DirectoryOnly);
    if (fileDialog.exec()) {
        lineEditBasePath->setText(fileDialog.selectedFiles().first());
    }
}
