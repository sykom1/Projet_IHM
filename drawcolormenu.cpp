

#include "drawcolormenu.h"

#include <QtWidgets>
#include <iostream>

drawColorMenu::drawColorMenu(QWidget *widget) : QComboBox(widget)
{
    populateList();
}

QColor drawColorMenu::color() const
{
    return qvariant_cast<QColor>(itemData(currentIndex(), Qt::DecorationRole));
}

void drawColorMenu::setColor(const QColor &color)
{
    setCurrentIndex(findData(color, Qt::DecorationRole));

}

void drawColorMenu::populateList()
{
    const QStringList colorNames = QColor::colorNames();

    for (int i = 0; i < colorNames.size(); ++i) {
        QColor color(colorNames[i]);

        insertItem(i, colorNames[i]);
        setItemData(i, color, Qt::DecorationRole);
    }
}

