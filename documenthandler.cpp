#include "documenthandler.h"

#include <tesseract/baseapi.h>

#include <QImage>
#include <QSettings>
#include <QSqlError>
#include <QSqlQuery>

Q_LOGGING_CATEGORY(EDIM_DOCUMENTHANDLER, "edim.DocumentHandler")

DocumentHandler::DocumentHandler()
{
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

    QImage image(document.absoluteFilePath());
    ocr->SetImage(image.bits(), image.width(), image.height(), image.depth() / 8, image.bytesPerLine());
    QString result(ocr->GetUTF8Text());

    // Restore locale
    setlocale(LC_NUMERIC, currentLocale.c_str());

    // Clean up
    ocr->End();

    return result;
}
