#include "setupwizard.h"

#include <QDebug>

SetupWizard::SetupWizard(QWidget *parent) :
    QWizard(parent)
{
    setWindowTitle(tr("Testwizard"));

    addPage(new IntroPage(this));
    addPage(new IntroPage(this));
}

void SetupWizard::accept()
{
    //QByteArray testVal = field("testval").toByArray();
    //qDebug << testVal;
    QDialog::accept();
}

IntroPage::IntroPage(QWidget *parent) :
    QWizardPage(parent)
{
    setTitle(tr("Testintro text"));
}
