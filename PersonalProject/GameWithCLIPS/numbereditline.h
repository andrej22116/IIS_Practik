#ifndef NUMBEREDITLINE_H
#define NUMBEREDITLINE_H

#include <QLineEdit>
#include <QValidator>
#include <memory>

class NumberEditLine : public QLineEdit
{
    Q_OBJECT

public:
    NumberEditLine(QWidget* parent);

    void setEvenRule();
    void setOddRule();
    void setNeutralRule();

protected:
    QString invalidStyleSheet =    "QLineEdit{"
                                                "background-color: rgba(255, 255, 255, 0);"
                                                "border: 2px solid rgb(255, 150, 150);"
                                                "font-size: 36pt;"
                                                "color: rgb(100, 100, 200);"
                                                "text-align: center"
                                                "}";

    QString validStyleSheet =  "QLineEdit{"
                                            "background-color: rgba(255, 255, 255, 0);"
                                            "border: 2px solid rgb(150, 150, 200);"
                                            "font-size: 36pt;"
                                            "color: rgb(100, 100, 200);"
                                            "text-align: center"
                                            "}";

    QString neutralStyleSheet =  "QLineEdit{"
                                                "background-color: rgba(255, 255, 255, 0);"
                                                "border: 0px solid rgb(150, 150, 200);"
                                                "font-size: 36pt;"
                                                "color: rgb(100, 100, 200);"
                                                "text-align: center"
                                                "}";
private:
    std::unique_ptr<QRegExpValidator> _evenNumberValidator;
    std::unique_ptr<QRegExpValidator> _oddNumberValidator;
};

#endif // NUMBEREDITLINE_H
