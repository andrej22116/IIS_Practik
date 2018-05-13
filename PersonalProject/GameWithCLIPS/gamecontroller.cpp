#include "gamecontroller.h"
#include <QFile>
#include <QTextStream>
#include <iostream>

/*
extern "C"
{
#include "clips.h"
}
*/

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

        QGridLayout* layout = (QGridLayout*)_gameWidget->layout();

        for (auto&& fieldLine : _gameField)
        {
            for (auto&& fieldCell : fieldLine)
            {
                if (offset_y % 2 == 0 || (offset_y % 2 != 0 && offset_x % 2 == 0))
                {
                    fieldCell = std::make_unique<NumberEditLine>(gameWidget);
                    layout->addWidget(fieldCell.get(), offset_y, offset_x);
                    //fieldCell->setOddRule();
                    //fieldCell->setText("+");
                }
                offset_x++;
            }
            offset_x = 0;
            offset_y++;
        }
    }

    isInitialized = true;
}

bool GameController::loadGame(const QString& fileName)
{
    if (!isInitialized) return false;

    QFile fin(fileName);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) return false;

    QTextStream input(&fin);

    for (int y = 0; y < 7; y++)
    {
        QString line = input.readLine();
        QStringList list = line.split(" ");
        int offset_x = 0;
        if (y % 2 == 0)
        {
            if (list.size() != 7)
            {
                std::cout << "Invalid line: " << y << std::endl;
                clearField();
                return false;
            }

            for (auto&& str : list)
            {
                if (offset_x % 2 == 0)
                {
                    if (!setStringWithNumberTo(str, offset_x, y))
                    {
                        return false;
                    }
                }
                else
                {
                    if (str != "x")
                    {
                        _gameField[y][offset_x]->setText(str);
                    }
                }
                offset_x++;
            }
        }
        else
        {
            if (list.size() != 4)
            {
                std::cout << "Invalid line: " << y << std::endl;
                clearField();
                return false;
            }
            for (auto&& str : list)
            {
                if (str != "x" && str != "")
                {
                    _gameField[y][offset_x]->setText(str);
                }
                offset_x += 2;
            }
        }
    }

    fin.close();
    return true;
}

bool GameController::setStringWithNumberTo(QString numberStr, int x, int y)
{
    bool valid = false;
    int num = numberStr.toInt(&valid);
    if (!valid) return false;

    if (num > 0 && num <= 16)
    {
        (num % 2 == 0) ? _gameField[y][x]->setEvenRule()
                       : _gameField[y][x]->setOddRule();
        _gameField[y][x]->setText(numberStr);
        _gameField[y][x]->setEnabled(false);
    }
    else if (num == 0)
    {
        _gameField[y][x]->setText("");
        _gameField[y][x]->setEvenRule();
    }
    else if (num == -1)
    {
        _gameField[y][x]->setText("");
        _gameField[y][x]->setOddRule();
    }
    else return false;

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
