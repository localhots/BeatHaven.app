#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QSettings>

#include <phonon/MediaObject>

#include "data/tracklistmodel.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QVariant readSettingWithFallbackAndSave(QString key, QVariant fallback);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

    void switchToPrevious();
    void togglePlayPause();
    void switchToNext();

private:
    Ui::MainWindow *ui;

    void prepareTracks();
    void prepareGlobalShortcuts();
    void populateTrayMenu(QMenu *trayMenu);
    void generateIcons();

    QSettings settings;

    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;

    TrackListModel* tracklist;
    Phonon::MediaObject* playlist;

    QIcon playIcon;
    QIcon pauseIcon;
    QIcon previousIcon;
    QIcon nextIcon;
    QIcon exitIcon;
};

#endif // MAINWINDOW_H
