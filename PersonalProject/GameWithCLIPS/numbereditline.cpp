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
        if (this->hasAcceptableInput())
        {
            this->setStyleSheet(validStyleSheet);
        }
        else
        {
            this->setStyleSheet(invalidStyleSheet);
        }
    };

    connect(this, &QLineEdit::textChanged, this, testValidTextWhenEdit);
}


void NumberEditLine::setEvenRule()
{
    this->setValidator(_evenNumberValidator.get());
    this->setReadOnly(false);
    this->setText("");
}

void NumberEditLine::setOddRule()
{
    this->setValidator(_oddNumberValidator.get());
    this->setReadOnly(false);
    this->setText("");
}

void NumberEditLine::setNeutralRule()
{
    this->setValidator(nullptr);
    this->setReadOnly(true);
    this->setStyleSheet(neutralStyleSheet);
    this->setText("");
}
