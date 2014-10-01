#ifndef LIBRARY_H
#define LIBRARY_H

#include <QObject>

#include "documenthandler.h"

#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(EDIM_LIBRARY)

class Library : public QObject
{
public:
    Library(QObject* parent = nullptr);

    QDir basePath() const;

    bool contains(const QFileInfo& document) const;

    QList<QFileInfo> search(const QString& text) const;

public slots:
    void import(const QFileInfo& document);
    void update(const QFileInfo& document);

private:
    DocumentHandler _documentHandler;

    void setupDatabase();
    QString libraryPath(const QFileInfo& document) const;
};

#endif // LIBRARY_H
