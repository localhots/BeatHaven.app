#include "tracklistmodel.h"

TrackListModel::TrackListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    tracks = new QList<Track*>();
}

int TrackListModel::rowCount(const QModelIndex &parent) const
{
    return tracks->size();
}
QVariant TrackListModel::data(const QModelIndex &index, int role) const
{
    if ((role!=Qt::DisplayRole)||(index.row()>=rowCount())) {
        return QVariant::Invalid;
    }

    Track *t = tracks->value(index.row());
    return QVariant(t->getTitle());
}

QList<Track*>* TrackListModel::getTracks() const
{
    return tracks;
}

