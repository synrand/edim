#include "documenthandler.h"

#include <QSettings>
#include <QSqlError>
#include <QSqlQuery>

Q_LOGGING_CATEGORY(EDIM_DOCUMENTHANDLER, "edim.DocumentHandler")

DocumentHandler::DocumentHandler()
{
}

void DocumentHandler::import(const QFileInfo& document) const
{
    // TODO read document contents

    QSettings settings;
    QString basePath(settings.value("library/basePath").toString());
    QString libraryPath(document.absoluteFilePath().replace(0, basePath.length(), "."));

    QSqlQuery q;
    q.prepare("INSERT INTO document (libraryPath, content) VALUES (:libraryPath, :content)");
    q.bindValue(":libraryPath", libraryPath);
    q.bindValue(":content", QString("Not yet implemented."));

    if (!q.exec()) {
        qCWarning(EDIM_DOCUMENTHANDLER) << "Could not insert document into database" << q.lastError();
    }
}
