#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

#include <phonon/MediaObject>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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
    void populateTrayMenu(QMenu *trayMenu);
    void generateIcons();

    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;

    Phonon::MediaObject* playlist;

    QIcon playIcon;
    QIcon pauseIcon;
    QIcon previousIcon;
    QIcon nextIcon;
    QIcon exitIcon;
};

#endif // MAINWINDOW_H
