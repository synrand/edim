#include "documenthandler.h"

#include <tesseract/baseapi.h>

#include <leptonica/allheaders.h>

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
    q.bindValue(":content", text(document));

    if (!q.exec()) {
        qCWarning(EDIM_DOCUMENTHANDLER) << "Could not insert document into database" << q.lastError();
    }
}

QString DocumentHandler::text(const QFileInfo& document) const
{
    // tesseract crashes with LC_NUMERIC != C
    std::string currentLocale(setlocale(LC_NUMERIC, nullptr));
    setlocale(LC_NUMERIC, "C");

    tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI();
    // TODO read proper language from settings
    if (ocr->Init(nullptr, "deu")) {
        qCWarning(EDIM_DOCUMENTHANDLER) << "Could not initialize OCR library.";
    }

    Pix* image(pixRead(document.absoluteFilePath().toStdString().c_str()));
    ocr->SetImage(image);
    QString result(ocr->GetUTF8Text());

    // Restore locale
    setlocale(LC_NUMERIC, currentLocale.c_str());

    // Clean up
    pixDestroy(&image);
    ocr->End();

    return result;
}
