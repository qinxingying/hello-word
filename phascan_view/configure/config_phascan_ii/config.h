#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <QFile>
#include "../DopplerConfigure.h"
#include <QSettings>
#include "default_settings.h"

class DopplerDataFileOperateor;

class Config : public QSettings
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = NULL);

    static Config *instance();

    bool load(const QString &filename, DopplerDataFileOperateor *dataFile);

    void set_is_phascan_ii(bool flag);
    bool is_phascan_ii();

protected:
    void unpack_group(int groupId);

    void unpack_display();

    void unpack_sample(const QVariantMap &map);

    void unpack_c_scan(const QVariantMap &map);

    void unpack_transceiver(const QVariantMap &map);

    void unpack_focallawer(const QVariantMap &map);

    void unpack_scan(const QVariantMap &map);

    void unpack_probe(const QVariantMap &map);

    void unpack_wedge(const QVariantMap &map);

    void unpack_specimen(const QVariantMap &map);

    void unpack_geometry(const QVariantMap &map);

    void unpack_geometry_plane(const QVariantMap &map);

    void unpack_geometry_cylinder(const QVariantMap &map, S_Cylinder &cylinder);

    void unpack_geometry_nozzle(const QVariantMap &map);

    void unpack_weld(const QVariantMap &map);

    void unpack_I_weld(const QVariantMap &map, S_WeldI &I);

    void unpack_V_weld(const QVariantMap &map, S_WeldV &V);

    void unpack_U_weld(const QVariantMap &map, S_WeldU &U);

    void unpack_focus(const QVariantMap &map);

    void unpack_beams_info();

    void unpack_thickness();

    void unpack_cursor(const QVariantMap &map);

    void unpack_gate(const QVariantMap &map, S_Gate &gate);

    void unpack_curves();

    void unpack_dac();

    void unpack_linear_dac();

    void unpack_tcg();

    void unpack_curve_offset();

    void unpack_scanner();

    void unpack_axis(const QVariantMap &map, S_Axis &axis);

    void unpack_encoder(const QVariantMap &map, S_Encoder &encoder);

    void unpack_global();

    void unpack_global_transceiver();

    void unpack_alarm();

    void unpack_one_alarm_setting(int index);

    int set_bit_value(int val, int bit, int val1);
    int get_bit_value (int val, int bit);

    void convert_to_phascan_config(int groupId);
    void convert_other_to_phascan_config();

    bool is_phascan_ii_file(QFile &file);

    void print_all_key(int depth, const QVariantMap &map);

    static Config *m_instance;
    DopplerDataFileOperateor *m_pDataFile;
    QByteArray m_dataMark;
    QByteArray m_dataSource;

    S_Groups m_groups[setup_MAX_GROUP_QTY];
    S_Groups &m_currentGroup;
    S_Global m_global;
    int s_alarmCount;
    bool m_isPhascanII;
};

#endif // __CONFIG_H__
