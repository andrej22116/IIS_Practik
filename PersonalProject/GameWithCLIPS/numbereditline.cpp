#include "numbereditline.h"

NumberEditLine::NumberEditLine(QWidget* parent) : QLineEdit(parent)
{
    _evenNumberValidator = std::make_unique<QRegExpValidator>(QRegExp(tr("^[2468]{1}|^1[0246]$")));
    _oddNumberValidator = std::make_unique<QRegExpValidator>(QRegExp(tr("^[13579]{1}|^1[135]$")));

    this->setMaximumWidth(80);
    this->setMaximumHeight(80);
    this->setMinimumWidth(80);
    this->setMinimumHeight(80);

    this->setAlignment(Qt::AlignCenter);

    this->setNeutralRule();

    auto testValidTextWhenEdit = [this](const QString& newString){
        if (this->isReadOnly()) {
            return;
        }
        bool validNumber = this->hasAcceptableInput();
        if (isEven())
        {
            validNumber ? this->setStyleSheet(validEvenStyleSheet)
                        : this->setStyleSheet(invalidEvenStyleSheet);
        }
        else if (isOdd())
        {
            validNumber ? this->setStyleSheet(validOddStyleSheet)
                        : this->setStyleSheet(invalidOddStyleSheet);
        }
    };

    connect(this, &QLineEdit::textChanged, this, testValidTextWhenEdit);
}


void NumberEditLine::setEvenRule()
{
    _isEven = true;
    _isOdd = false;
    _isNeutral = false;
    this->setValidator(_evenNumberValidator.get());
    this->setReadOnly(false);
    this->setEnabled(true);
    this->setStyleSheet(invalidEvenStyleSheet);
    this->setText("");
}

void NumberEditLine::setOddRule()
{
    _isEven = false;
    _isOdd = true;
    _isNeutral = false;
    this->setValidator(_oddNumberValidator.get());
    this->setReadOnly(false);
    this->setEnabled(true);
    this->setStyleSheet(invalidOddStyleSheet);
    this->setText("");
}

void NumberEditLine::setNeutralRule()
{
    _isEven = false;
    _isOdd = false;
    _isNeutral = true;
    this->setValidator(nullptr);
    this->setReadOnly(true);
    this->setEnabled(false);
    this->setStyleSheet(neutralStyleSheet);
    this->setText("");
}

bool NumberEditLine::isEven()
{
    return _isEven;
}

bool NumberEditLine::isOdd()
{
    return _isOdd;
}

bool NumberEditLine::isNeutral()
{
    return _isNeutral;
}
