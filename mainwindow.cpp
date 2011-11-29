#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <phonon/MediaObject>
#include <phonon/AudioOutput>

#include <QxtGlobalShortcut>

#include "data/track.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    prepareGlobalShortcuts();

    trayIcon = new QSystemTrayIcon(this);

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    QIcon icon(":/icons/images/favicon.png");
    trayIcon->setIcon(icon);

    QMenu* trayMenu = new QMenu();

    generateIcons();

    populateTrayMenu(trayMenu);

    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();

    prepareTracks();
}

MainWindow::~MainWindow()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////
// Обработка закрытия из разных источников
///////////////////////////////////////////////////////////////////////
void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            this->setVisible(!this->isVisible());
            break;
        case QSystemTrayIcon::Context:
        case QSystemTrayIcon::MiddleClick:
        case QSystemTrayIcon::Unknown:
            break;
    }
}
void addActionToMenuAndSlot(QMenu *menu, QAction *action, QObject *target, const char *slot_method){
    action->setIconVisibleInMenu(true);

    QObject::connect(action, SIGNAL(triggered()), target, slot_method);

    menu->addAction(action);
}

void MainWindow::populateTrayMenu(QMenu *trayMenu) {
    addActionToMenuAndSlot(trayMenu, new QAction(previousIcon, QString::fromUtf8("&Предыдущий"), this), this, SLOT(switchToPrevious()));
    addActionToMenuAndSlot(trayMenu, new QAction(nextIcon, QString::fromUtf8("&Следующий"), this), this, SLOT(switchToNext()));

    trayMenu->addSeparator();

    addActionToMenuAndSlot(trayMenu, new QAction(exitIcon, QString::fromUtf8("В&ыход"), this), this, SLOT(close()));
}

void MainWindow::closeEvent(QCloseEvent *event)
 {
     if (event->spontaneous()&&trayIcon->isVisible()) {
         this->hide();
         event->ignore();
     }
 }
///////////////////////////////////////////////////////////////////////
// Подготовка глобальных хоткеев
///////////////////////////////////////////////////////////////////////
void MainWindow::prepareGlobalShortcuts()
{
    QxtGlobalShortcut* shortcut = new QxtGlobalShortcut(this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(togglePlayPause()));
    shortcut->setShortcut(QKeySequence(readSettingWithFallbackAndSave("hotkeys/PlayPause","Ctrl+Shift+F12").toString()));
}

QVariant MainWindow::readSettingWithFallbackAndSave(QString key, QVariant fallback)
{
    if(!settings.contains(key)){
        settings.setValue(key, fallback);
    }

    return settings.value(key, fallback);
}


///////////////////////////////////////////////////////////////////////
// Подготовка дорожек и иконок
///////////////////////////////////////////////////////////////////////
void MainWindow::generateIcons()
{
    playIcon = QIcon::fromTheme("media-playback-start", QIcon(":/icons/images/button_grey_play.png"));
    pauseIcon = QIcon::fromTheme("media-playback-pause", QIcon(":/icons/images/button_grey_pause.png"));
    previousIcon = QIcon::fromTheme("media-skip-backward", QIcon(":/icons/images/button_grey_rewind.png"));
    nextIcon = QIcon::fromTheme("media-skip-forward", QIcon(":/icons/images/button_grey_fastforward.png"));
    exitIcon = QIcon::fromTheme("application-exit", QIcon(":/icons/images/button_grey_close.png"));

    ui->previousButton->setIcon(previousIcon);
    ui->playPauseButton->setIcon(playIcon);
    ui->nextButton->setIcon(nextIcon);
}

void MainWindow::prepareTracks()
{
    tracklist = new TrackListModel();

    tracklist->getTracks()->append(new Track("http://www.konsolentuning.de/downloads/pornophonique/8-bit_lagerfeuer/01_sad_robot.mp3", "Sad Robot"));
    tracklist->getTracks()->append(new Track("http://www.konsolentuning.de/downloads/pornophonique/8-bit_lagerfeuer/02_take_me_to_the_bonuslevel_because_i_need_an_extralife.mp3", "Take Me To the Bonuslevel Because I Need an Extra Life"));

    QListIterator<Track*> tracksIterator(*tracklist->getTracks());
    ui->trackListView->setModel(tracklist);

    playlist = new Phonon::MediaObject(this);
    Phonon::AudioOutput* audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(playlist, audioOutput);

    while(tracksIterator.hasNext()) {
        playlist->enqueue(tracksIterator.next()->getFileURL());
    }
}

///////////////////////////////////////////////////////////////////////
// Кнопки плеера
///////////////////////////////////////////////////////////////////////

void MainWindow::switchToPrevious(){
    qDebug()<<QString::fromUtf8("Предыдущий!");
}

void MainWindow::togglePlayPause(){
    if(playlist->state()==Phonon::PlayingState) {
        ui->playPauseButton->setIcon(playIcon);
        playlist->pause();
    } else {
        ui->playPauseButton->setIcon(pauseIcon);
        playlist->play();
    }
}

void MainWindow::switchToNext(){
    qDebug()<<QString::fromUtf8("Следующий!");
}
