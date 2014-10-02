#include "settingsdialog.h"

#include <QFileDialog>
#include <QSettings>

SettingsDialog::SettingsDialog(QWidget* parent) :
    QDialog(parent)
{
    setupUi(this);
    QSettings settings;

    // Library
    lineEditBasePath->setText(settings.value("library/basePath").toString());

    // OCR
    comboBoxOCRLanguage->addItem(QIcon(":icons/flag_us.png"), tr("English"), QVariant("eng"));
    comboBoxOCRLanguage->addItem(QIcon(":icons/flag_de.png"), tr("German"), QVariant("deu"));

    int current = comboBoxOCRLanguage->findData(settings.value("ocr/language"));
    if (current < 0) {
        current = 0;
    }

    comboBoxOCRLanguage->setCurrentIndex(current);

    setupConnections();
}

void SettingsDialog::accept()
{
    // TODO save settings here
    QDialog::accept();
}

void SettingsDialog::setupConnections()
{
    connect(buttonBox, &QDialogButtonBox::accepted, this, &SettingsDialog::accept);

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
