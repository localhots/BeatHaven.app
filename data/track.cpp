#include "track.h"
#include <QStringList>

Track::Track(QString _fileURL, QString _title) :
    QObject(0)
{
    fileURL = _fileURL;

    if (_title.isEmpty()) {
        _title = fileURL.split('/', QString::SkipEmptyParts).last();
    }
    title = _title;
}
QString Track::getTitle() {
    return title;
}
void Track::setTitle(QString newTitle) {
    title = newTitle;
}

QString Track::getFileURL() {
    return fileURL;
}
void Track::setFileURL(QString newFileURL) {
    fileURL = newFileURL;
}
