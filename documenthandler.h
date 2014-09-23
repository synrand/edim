#ifndef DOCUMENTHANDLER_H
#define DOCUMENTHANDLER_H

#include <QFileInfo>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(EDIM_DOCUMENTHANDLER)

class DocumentHandler
{
public:
    DocumentHandler();

    void import(const QFileInfo& document) const;
};

#endif // DOCUMENTHANDLER_H
