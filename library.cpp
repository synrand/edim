#include "library.h"

#include "documenthandler.h"

#include <QSettings>
#include <QStandardPaths>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

Q_LOGGING_CATEGORY(EDIM_LIBRARY, "edim.Library")

Library::Library(QObject* parent) :
    QObject(parent)
{
    setupDatabase();
}

QDir Library::basePath() const
{
    QSettings settings;
    return QDir(settings.value("library/basePath", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)).toString());
}

bool Library::contains(const QFileInfo& document) const
{
    QSqlQuery q;
    q.prepare("SELECT * FROM document WHERE libraryPath = :libraryPath");
    q.bindValue(":libraryPath", libraryPath(document));
    q.exec();

    // Size hack for SQLite since it doesn't support .size() :-(
    q.last();
    return q.at() + 1 > 0;
}

void Library::import(const QFileInfo& document)
{
    QSqlQuery q;
    q.prepare("INSERT INTO document (libraryPath, content) VALUES (:libraryPath, :content)");
    q.bindValue(":libraryPath", libraryPath(document));
    q.bindValue(":content", _documentHandler.text(document));

    if (!q.exec()) {
        qCWarning(EDIM_LIBRARY) << "Could not import document into database" << q.lastError();
    }
}

void Library::update(const QFileInfo& document)
{
    Q_UNUSED(document)
}

void Library::setupDatabase()
{
    // Check data location
    QDir dataLocation(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    if (!dataLocation.exists()) {
        if (!dataLocation.mkpath(".")) {
            qCCritical(EDIM_LIBRARY) << "Could not access data location at" << dataLocation.absolutePath();
        }
    }

    // Connect to database
    QString databaseFile(dataLocation.absolutePath().append(QDir::separator()).append("data.sqlite"));
    QSqlDatabase database(QSqlDatabase::addDatabase("QSQLITE"));
    database.setDatabaseName(databaseFile);
    if (!database.open()) {
        qCCritical(EDIM_LIBRARY) << "Could not connect to database";
    }

    // Enable FOREIGN KEY support
    QSqlQuery q;
    if (!q.exec("PRAGMA foreign_keys = ON")) {
        qCWarning(EDIM_LIBRARY) << "Could not enable FOREIGN KEY support";
    }

    if (!q.exec("CREATE TABLE IF NOT EXISTS document (id INTEGER PRIMARY KEY AUTOINCREMENT, libraryPath TEXT, content TEXT)")) {
        qCWarning(EDIM_LIBRARY) << "Could not create database layout";
    }
}

QString Library::libraryPath(const QFileInfo& document) const
{
    return document.absoluteFilePath().replace(0, basePath().absolutePath().length(), ".");
}
