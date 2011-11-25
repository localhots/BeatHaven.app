#ifndef TRACK_H
#define TRACK_H

#include <QObject>
#include <QMetaType>

class Track : public QObject
{
    Q_OBJECT
public:
    Track(QString _fileURL, QString _title = "");

private:
    QString title;
    Q_PROPERTY(QString title READ getTitle WRITE setTitle)

    QString fileURL;
    Q_PROPERTY(QString fileURL READ getFileURL WRITE setFileURL)

public:
    QString getTitle();
    void setTitle(QString newTitle);

    QString getFileURL();
    void setFileURL(QString newFileURL);
};

Q_DECLARE_METATYPE(Track*)

#endif // TRACK_H
