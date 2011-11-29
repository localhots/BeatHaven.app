#ifndef TRACKLISTMODEL_H
#define TRACKLISTMODEL_H

#include <QAbstractListModel>

#include "track.h"

class TrackListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TrackListModel(QObject *parent = 0);

    //Reimplementing required ListModel API
    int rowCount(const QModelIndex &parent = QModelIndex() ) const;
    QVariant data(const QModelIndex &index, int role) const;

    QList<Track*> *getTracks() const;

signals:

public slots:

private:
    QList<Track*> *tracks;

};

#endif // TRACKLISTMODEL_H
