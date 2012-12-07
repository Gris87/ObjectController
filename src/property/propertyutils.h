#ifndef PROPERTYUTILS_H
#define PROPERTYUTILS_H

#include <QWidget>
#include <QString>

#include "propertyattributes.h"

QString doubleToString(double aValue, int aDecimals=6);
void applyAttributesToPalette(QWidget *aWidget, const PropertyAttributes *aAttributes);

#endif // PROPERTYUTILS_H
