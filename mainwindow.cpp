#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    trayIcon = new QSystemTrayIcon(this);

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    QIcon icon(":/icons/favicon.png");
    trayIcon->setIcon(icon);

    QMenu* trayMenu = new QMenu();

    QAction* exitMenuAction = new QAction(QString::fromUtf8("Выход"), this);
    connect(exitMenuAction, SIGNAL(triggered()), this, SLOT(close()));

    trayMenu->addAction(exitMenuAction);

    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

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
void MainWindow::closeEvent(QCloseEvent *event)
 {

     if (event->spontaneous()&&trayIcon->isVisible()) {
         this->hide();
         event->ignore();
     }
 }
