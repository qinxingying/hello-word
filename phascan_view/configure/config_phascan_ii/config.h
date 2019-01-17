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

    void unpack_sample();

    void unpack_transceiver();

    void unpack_focallawer();

    void unpack_scan();

    void unpack_probe();

    void unpack_wedge();

    void unpack_specimen();

    void unpack_weld();

    void unpack_focus();

    void unpack_beams_info();

    void unpack_thickness();

    void unpack_cursor();

    void unpack_gate(GateType gateType);

    void unpack_curves();

    void unpack_dac();

    void unpack_linear_dac();

    void unpack_tcg();

    void unpack_curve_offset();

    void unpack_scanner();

    void unpack_axis(int index);

    void unpack_encoder(int index);

    void unpack_global();

    void unpack_global_transceiver();

    void unpack_alarm();

    void unpack_one_alarm_setting(int index);

    int set_bit_value(int val, int bit, int val1);
    int get_bit_value (int val, int bit);

    void convert_to_phascan_config(int groupId);
    void convert_other_to_phascan_config();

    bool is_phascan_ii_file(QFile &file);

    static Config *m_instance;
    DopplerDataFileOperateor *m_pDataFile;
    QByteArray m_dataMark;
    QByteArray m_dataSource;
    S_Groups m_groups[setup_MAX_GROUP_QTY];
    S_Groups &m_currentGroup;
    S_Scanner m_scanner;
    S_Global m_global;
    int s_alarmCount;
    bool m_isPhascanII;
};

#endif // __CONFIG_H__
