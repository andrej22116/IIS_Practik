#include "gamecontroller.h"

GameController::GameController()
{
    for (auto&& fieldLine : _gameField)
    {
        for (auto&& fieldCell : fieldLine)
        {
            fieldCell = nullptr;
        }
    }
}


void GameController::initialization(QWidget* gameWidget, QStatusBar* statusBar)
{
    if (!gameWidget || !statusBar) return;

    _gameWidget = gameWidget;
    _statusBar = statusBar;

    if (!isInitialized)
    {
        int offset_x = 0;
        int offset_y = 0;

        QGridLayout* layout = (QGridLayout*)_gameWidget->layout(); //new QGridLayout();

        for (auto&& fieldLine : _gameField)
        {
            for (auto&& fieldCell : fieldLine)
            {
                fieldCell = std::make_unique<NumberEditLine>(gameWidget);
                layout->addWidget(fieldCell.get(), offset_y, offset_x);
                fieldCell->setText("+");
                offset_x++;
            }
            offset_x = 0;
            offset_y++;
        }

        //_gameWidget->setLayout(layout);
    }

    isInitialized = true;
}

bool GameController::loadGame(QString& fileName)
{
    if (!isInitialized) return false;

    return true;
}

void GameController::clearField()
{
    if (!isInitialized) return;

}

GameController& GameController::getInstance()
{
    static GameController instance;
    return instance;
}
