#ifndef SETUPWIZARD_H
#define SETUPWIZARD_H

#include <QWizard>

class SetupWizard : public QWizard
{
    Q_OBJECT

public:
    SetupWizard(QWidget *parent = 0);

    void accept() Q_DECL_OVERRIDE;

private:
};

class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    IntroPage(QWidget *parent = 0);

private:
};

#endif // SETUPWIZARD_H
