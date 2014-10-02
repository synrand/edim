#ifndef LIBRARY_H
#define LIBRARY_H

#include <QSortFilterProxyModel>

#include "documenthandler.h"

#include <QDir>
#include <QFileInfo>
#include <QFileSystemModel>
#include <QList>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(EDIM_LIBRARY)

class Library : public QSortFilterProxyModel
{
public:
    enum ItemDataRole {
        DocumentContentRole = Qt::UserRole
    };

    Library(QObject* parent = nullptr);

    QDir basePath() const;

    bool contains(const QFileInfo& document) const;

    QList<QFileInfo> search(const QString& text) const;

    using QSortFilterProxyModel::index;
    QModelIndex index(const QFileInfo& document) const;

    QFileInfo fileInfo(const QModelIndex& index) const;

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

public slots:
    void import(const QFileInfo& document);
    void update(const QFileInfo& document);

private:
    QFileSystemModel _sourceModel;
    DocumentHandler _documentHandler;

    void setupDatabase();
    QString libraryPath(const QFileInfo& document) const;
};

#endif // LIBRARY_H
