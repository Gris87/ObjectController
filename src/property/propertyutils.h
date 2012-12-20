#ifndef PROPERTYUTILS_H
#define PROPERTYUTILS_H

#include <QWidget>
#include <QString>
#include <QMetaEnum>

#include "propertyattributes.h"

QString enumToString(const QMetaEnum &aMetaEnum, const int &aValue);
QString flagsToString(const QMetaEnum &aMetaEnum, const int &aValue);
QString doubleToString(double aValue, int aDecimals=6);

#endif // PROPERTYUTILS_H
