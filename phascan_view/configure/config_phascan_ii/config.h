#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <QFile>
#include "../DopplerConfigure.h"
#include <QSettings>
#include "default_settings.h"
#include "mercury_paramters/group_paramters.h"
#include "mercury_paramters/global_paramters.h"

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
    int getPhascanVersion();
    QString getFpgaCpuVersion() {return m_global.m_version.m_FpgaCpuVersion;}
    QString getFpgaPaVersion() {return m_global.m_version.m_FpgaPaVersion;}
    QString getVersion() {return m_global.m_version.m_phascanVersion;}

    char *data_mark();

    uint data_mark_length();

    bool getCurve_RL_EL_SL(int groupId, float &coupleGain);
    void getWeldData( int groupId, WELD_II & weld);
    void getTOPCWidth( int groupId, double &topcWidth);
    void getApertureSec( int groupId, unsigned int * apertureData);
    void getTofdData( int groupId, float *PCS, float *RefPoint);
    void getTMFRange(int groupId, float *start, float *range, int *pointQty);
    QStringList getColorPalette();

    void getScannerData( SCANNER &scanner);
    bool is_phascan_ii_file(QFile &file);
    double getCoupleGain(int groupId);
    int getCylinderWeldOrientation(int groupId);

protected:
    void unpack_group(int groupId);

    void unpack_version();

    void unpack_display();

    void unpack_sample(const QVariantMap &map);

    void unpack_c_scan(const QVariantMap &map);

    void unpack_transceiver(const QVariantMap &map);

    void unpack_focallawer(const QVariantMap &map);

    void unpack_scan(const QVariantMap &map);

    void unpack_probe(const QVariantMap &map);

    void unpack_wedge(const QVariantMap &map);

    void unpack_specimen(const QVariantMap &map);

    void unpack_delays(const QVariantList &list);

    void unpack_fields(const QVariantList &list);

    void unpack_gains(const QVariantList &list);

    void unpack_geometry(const QVariantMap &map);

    void unpack_geometry_plane(const QVariantMap &map, Paramters::Plane &plane);

    void unpack_geometry_cylinder(const QVariantMap &map, Paramters::Cylinder &cylinder);

    void unpack_geometry_nozzle(const QVariantMap &map);

    void unpack_geometry_fillet(const QVariantMap &map);

    void unpack_weld(const QVariantMap &map);

    void unpack_I_weld(const QVariantMap &map, Paramters::WeldI &I);

    void unpack_V_weld(const QVariantMap &map, Paramters::WeldV &V);

    void unpack_U_weld(const QVariantMap &map, Paramters::WeldU &U);

    void unpack_focus(const QVariantMap &map);

    void unpack_beams_info();

    void unpack_thickness(const QVariantMap &map);

    void unpack_tofd(const QVariantMap &map);

    void unpack_cursor(const QVariantMap &map);

    void unpack_gate(const QVariantMap &map, Paramters::Gate &gate);

    void unpack_sizing(const QVariantMap &map);

    void unpack_curves(const QVariantMap &map);

    void unpack_scanner();

    void unpack_axis(const QVariantMap &map, Paramters::Axis &axis);

    void unpack_encoder(const QVariantMap &map, Paramters::Encoder &encoder);

    void unpack_global_transceiver();

    void unpack_alarm();

    void unpack_one_alarm_setting(int index);

    int set_bit_value(int val, int bit, int val1);
    int get_bit_value (int val, int bit);

    void convert_to_phascan_config(int groupId);
    void convert_other_to_phascan_config();    

    void print_all_key(int depth, const QVariantMap &map);

    static Config *m_instance;
    DopplerDataFileOperateor *m_pDataFile;
    QByteArray m_dataMark;
    QByteArray m_dataSource;

    Paramters::Group  m_groups[setup_MAX_GROUP_QTY];
    Paramters::Global m_global;
    int m_currentGroupID;
    int s_alarmCount;
    bool m_isPhascanII;
};

#endif // __CONFIG_H__
