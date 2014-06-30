#ifndef OPTIONBAR_H
#define OPTIONBAR_H

#include <QWidget>
#include <QMenuBar>

class OptionBar : public QMenuBar
{
    Q_OBJECT

public:
    OptionBar(QWidget * parent = 0);
    ~OptionBar();
private:

protected:

};

#endif // MENUBAR_H
