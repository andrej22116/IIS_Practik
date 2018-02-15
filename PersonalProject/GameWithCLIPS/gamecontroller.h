#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QStatusBar>

class GameController
{
private:
    QStatusBar _statusBar;

    GameController(QStatusBar statusBar);
    GameController(const GameController&) = delete;
    GameController operator = (const GameController&) = delete;

public:
};

#endif // GAMECONTROLLER_H
