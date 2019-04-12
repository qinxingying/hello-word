#include "settings.h"
#include <QIODevice>
#include "msgpack/msgpack.h"

bool settings_read_msgpack(QIODevice &device, QSettings::SettingsMap &map)
{
    const QByteArray data = device.readAll();
    if (data.isEmpty()) {
        return false;
    }
    map = MsgPack::unpack(data).toMap();
    return true;
}

bool settings_write_msgpack(QIODevice &device, const QSettings::SettingsMap &map)
{
    if (map.isEmpty()) {
        return false;
    }
    device.write(MsgPack::pack(map));
    return true;
}
