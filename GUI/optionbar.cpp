#include "optionbar.h"
#include <QWidget>
#include <QMenu>

OptionBar::OptionBar(QWidget *parent)
{
    addMenu("File");
}

OptionBar::~OptionBar()
{

}
