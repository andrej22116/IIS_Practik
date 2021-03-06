#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamecontroller.h"

#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("Hello!");

    GameController::getInstance().initialization(ui->gameField, ui->statusBar);
    GameController::getInstance().loadGame("./Games/Game_2");

    updateListOfGames();
}


void MainWindow::updateListOfGames()
{
    QDir gamesDir("./Games/");
    if (gamesDir.exists())
    {
        gamesDir.setFilter(QDir::Files);
        gamesDir.setSorting(QDir::Name);

        QFileInfoList list = gamesDir.entryInfoList();
        int i = 0;
        for (auto&& fileInfo : list)
        {
            ui->listOfGames->insertItem(i++, fileInfo.fileName());
        }
    }
    else
    {
        QDir().mkdir("Games");
        ui->statusBar->showMessage("Folder \"Games\" not found!");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
