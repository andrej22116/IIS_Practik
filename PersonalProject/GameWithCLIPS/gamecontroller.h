#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QWidget>
#include <QStatusBar>
#include <QGridLayout>

#include <array>
#include <memory>

#include "numbereditline.h"

/*
 *  This class is singleton!
 */
class GameController
{
private:
    QWidget* _gameWidget;
    QStatusBar* _statusBar;

    GameController();
    GameController(const GameController&) = delete;
    GameController operator = (const GameController&) = delete;

    std::array<std::array<std::unique_ptr<NumberEditLine>, 7>, 7> _gameField;

    bool isInitialized = false;

public:
    void initialization(QWidget* gameWidget, QStatusBar* statusBar);
    bool loadGame(QString& fileName);
    void clearField();

    static GameController& getInstance();
};

#endif // GAMECONTROLLER_H
