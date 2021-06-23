#ifndef DISPLAY_H
#define DISPLAY_H

#include <QObject>
#include <QVariantList>

namespace Paramters {

class Display : public QObject
{
    Q_OBJECT
public:
    explicit Display(QObject *parent = 0);

private:
    QString m_ampPalette;
    uint m_bright;
    bool m_cursor;
    QString m_depthPalette;
    QVariantList m_groups;
    uint m_language;
    uint m_layout;
    uint m_opacity;
    QString m_tofdPalette;

    friend class Config;
};

}

#endif // DISPLAY_H
