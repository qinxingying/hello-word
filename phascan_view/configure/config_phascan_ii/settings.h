#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

extern bool settings_read_msgpack(QIODevice &device, QSettings::SettingsMap &map);
extern bool settings_write_msgpack(QIODevice &device, const QSettings::SettingsMap &map);

#endif // SETTINGS_H
