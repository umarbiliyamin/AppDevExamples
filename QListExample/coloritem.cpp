#include "coloritem.h"

QString ColorItem::name() const
{
    return m_name;
}

void ColorItem::setName(const QString &name)
{
    m_name = name;
}

QString ColorItem::colorCode() const
{
    return m_colorCode;
}

void ColorItem::setColorCode(const QString &colorCode)
{
    m_colorCode = colorCode;
}

ColorItem::ColorItem(QObject *parent) : QObject(parent)
{

}
