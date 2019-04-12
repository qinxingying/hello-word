#ifndef _DATE_FILE_CONFIGURE_
#define _DATE_FILE_CONFIGURE_


typedef struct _sizing_curve_
{
	int bTcgCalibrated;
	int bApplyToAllLaws ;

	unsigned char	mode_pos;		/*Gate/Alarm->Sizing Curves->Mode*/
	unsigned char	curve_pos;		/*Gate/Alarm->Sizing Curves->Curve*/
	unsigned char   point_pos;
	unsigned char   dac_point_qty;
	unsigned short  curve_step;
	unsigned short  mat_atten;
	short           ref_ampl_offset;
	unsigned int    linear_ref_ampl;

	unsigned int    linearamplitude[16] ;
	int             linearposition [16] ;
	int             dac_ref_ampl[256] ;
	unsigned int    amplitude[256][16];
	int             position[256][16];
	unsigned int    delay; //data_232  linear dac , start point
} SIZING_CURVES;

typedef struct _gate_info
{
	unsigned char	parameters;		// ����ģʽ 0 Positions 1 Mode //
	unsigned char	synchro;        // ͬ�� //
	unsigned char	measure;        //  //
	unsigned char	rectifier_freq; //��Ƶ //
	char	height;
	char	tt[3];
	int	start;			//��λns
	unsigned int	width;
} GATE_INFO, *GATE_INFO_P;


struct _output_info;
typedef struct _output_info OUTPUT_INFO1;

/// �����Ϣ //
struct _output_info 
{
	unsigned short	alarm_info;		// ״̬ ��ʾ16��alarm�źŵ�״̬ /
	unsigned char	count;    	    ////
	unsigned char	sound;          ///
	unsigned int	delay;			// ��λns /
	unsigned int	holdtime;       // ��λns //
};

// �����Ϣ 
typedef struct _cursors_info 
{
	short	angle;
	unsigned short	amplitude;
	unsigned short	UT;
    //char	tt[2];
    unsigned short resolution;
	int	scan;
	int	index;
} CURSORS_INFO, *CURSORS_INFO_P;

struct _simple_Probe;
typedef struct _simple_Probe st_simple_Probe;

struct _simple_Probe
{
        char	Model[20];
        char	Serial[20];
	unsigned char	PA_probe_type;		// ̽ͷ���� 1 ��Custom 3 ��angle beam 5 �� Contact 6��Immersion /
	unsigned char	Elem_qty;			// ��Ԫ�� /
	unsigned short	Frequency;			// Ƶ�� /
	unsigned short	Reference_Point;	//  /
	unsigned int	Pitch;				// ��Ԫ���ļ�� 0.001mm Ϊ��λ ��Χ��0.01~65.00mm UT ��Elemet_size 
};

struct _simple_Wedge;
typedef struct _simple_Wedge st_simple_Wedge;

struct _simple_Wedge
{
	char	Wave_type;		// 1 ��L 2 �� S //
	char	Model[20];		// ���� Ш������ //
	char	Serial[20];		// ���� Ш������ //
	char	Orientation;	// 1 Normal 0 reversal//
	unsigned short	Angle;			// ���� �Ƕȵ�λ0.1�� //
	unsigned short	Probe_delay; 	// UT nsΪ��λ //
	int	Ref_point;		// UT ʹ�� //
	unsigned int	Height;			// ��λ΢�� //
	unsigned int	Velocity_UT;
	unsigned int	Velocity_PA;	// �ٶ� mm/s //
	int	Primary_offset;	// ΢�� //
	unsigned int	Secondary_offset;	// ΢�� //
};

/// ̽ͷ(Probe)  516 byte ���̽ͷ��unknown �����һ������ //
typedef struct _Probe
{
	//PA ʱ���ȶ���4���ֽ�//
	char	A1[2];
	unsigned char	PA_probe_type;	// ̽ͷ���� 1 ��Custom 3 ��angle beam 5 �� Contact 6��Immersion //
	char	A10;
	unsigned char	UT_probe_type;	// ̽ͷ���� 1 n/a 0 converntional //
	char	A11;
	char	Model[20];		// ̽ͷ���� //
	char	Serial[20];		// ̽ͷ���� //
	unsigned char	Elem_qty;		// ��Ԫ�� //
	unsigned char	Freq2;			// UT ʱ�� Ƶ���� (freq2 << 8) + elem_qty //
	unsigned int	Pitch;			// ��Ԫ���ļ�� 0.001mm Ϊ��λ ��Χ��0.01~65.00mm UT ��Elemet_size //
	unsigned int	A3;
	unsigned short A4;
	unsigned short	Frequency;		// Ƶ�� //
	unsigned int	A5[75];
	unsigned short A6;
	unsigned short A7;
	unsigned short A8;
	unsigned short	Reference_Point; //  //
	unsigned int	A9[36];
} PROBE, *PROBE_P;

///Ш�� (Wedge)//
typedef struct _Wedge
{
	unsigned char	A1[2];			// 0x03000300 PA 0x01000100 UT//
	char	Wave_type;		// 1 ��L 2 �� S //
	char	A11;
	char	Model[20];		// ���� Ш������ //
	char	Serial[20];		// ���� Ш������ //
	unsigned short	Angle;			// ���� �Ƕȵ�λ0.1�� //
	unsigned short	A7;
	unsigned short	Probe_delay; 	// UT nsΪ��λ //
	char	A2;
	char	A10;			// UT 1 SW 0 LW//
	int	Ref_point;		// UT ʹ�� //
	//����ط� �� ���һ���ֽ� //
	unsigned int	Height;			// ��λ΢�� //
	unsigned int	Velocity_UT;
	unsigned int	A8;
	unsigned int	Velocity_PA;	// �ٶ� mm/s //
	char	Orientation;	// 1 Normal 0 reversal//
	char	A4[3];
	int	Primary_offset;	// ΢�� //
	unsigned int	Secondary_offset;	// ΢�� //
	int	A6[107];
} WEDGE, *WEDGE_P;

struct _Encoder;
typedef struct _Encoder st_Enc;

struct _Encoder {
	char Polarity;
	char Type;
	char Preset;
	char Enable;
	unsigned int Resolution;
	unsigned int Origin;
};

struct _Part;
typedef struct _Part st_PART;

/// ���� (Part) 12�ֽ� �Ѿ�ȫ������ֻ��CONFIG�ṹ���õ����� �ȴ����� //
struct _Part
{
	unsigned char	Geometry;		// ������״ FLAT/ID/OD/BALL //
        unsigned char	Material_pos;   	// ���� //
	unsigned char	Weld;			// ���� //
	unsigned char   symmetry;		// �Գ� //
        unsigned int	Thickness;		// ��� //
	unsigned int	Diameter;		// ֱ�� //

	unsigned int    weland_height;
	unsigned int    weland_offset;
	unsigned int	fizone_height;
	unsigned int	fizone_angle;
	unsigned int	fizone_radius;
	unsigned int    weldtype_pos ;
};

/// һ����Ԫ�ľ۽���Ϣ//
typedef struct _law_elem
{
	unsigned char	E_number;
	unsigned char	Amplitude;		// ��ѹ ��λV //
	unsigned short	FL_gain;		// Focal Gain 0.1db��λ //
	unsigned short	R_delay;		//  //
	unsigned short	T_delay;		// 0-25560 ��λ ns 65535���״̬ //
	unsigned short	P_width;		// 50-500 ��λns//
	unsigned char	tt[2];
}LAW_ELEM, *LAW_ELEM_P;

/// һ��beam�ľ۽���Ϣ //
typedef struct _law_beam
{
	//    char Version[32];	//
	//    int  N_laws;			//

	unsigned char	N_ActiveElements;	// ͬʱ��������Ԫ�� //
	unsigned char	cycle;
	//unsigned char	sumgain;			//  //
	unsigned char	mode;				// 0 T/R 1 Pulse-echo//
	unsigned char	filter;				// 0 no filter 1 0.5-5 2 2-10 3 5-15 //
	unsigned char	T_first;
	unsigned char	R_first;
	char	tt;					// ռλ�� //
	unsigned short	frequency;			// Ƶ��0.001Mhz Ϊ��λ //
	short	R_angle;
	unsigned short	S_angle;
	char	tt1[2];				// ռλ�� //
	unsigned int	Scan_offset;		// ��λ 0.001 mm//
	unsigned int	Index_offset;		// ��λ 0.001 mm//
	int	G_delay;			// ��λns Wedge Delay + Law Delay //
	int	beam_delay;			// ��λns Law Delay //
	int	F_depth;			// ��λ ΢�� //
	unsigned int	M_velocity;			// ��λ m/s //
}LAW_BEAM, *LAW_BEAM_P;

typedef struct _law_focal
{
	char		version[16];
	short		beam_qty;		// ���focal�м���beam //
	LAW_BEAM_P	*law_beam_p;
	LAW_ELEM_P	*law_elem_p;
} LAW_FOCAL, *LAW_FOCAL_P;

/// �۽�������Ϣ(law_info) //
typedef struct _law_info
{
	unsigned char	Focal_type;			// �۽����� //
	unsigned char	Focal_point_type;	// �۽����� //
	unsigned char	Tx_connect;			// pulser�÷����̽ͷ�����һ����Ԫ�����ӿڵı�� //
	unsigned char	Rx_connect;			// receiver //
	unsigned char	Elem_qty;			// �۽���Ԫ�� //
	short	        First_tx_elem;		// ����ʹ�õĵ�һ��������Ԫ �շ�����ʱ�� tx rx ��һ�� //
	short	        First_rx_elem;		// ����ʹ�õĵ�һ��������Ԫ //
	unsigned char	Last_tx_elem;		// ����ʹ�õ����һ��������Ԫ //
	unsigned char	Last_rx_elem;		// ����ʹ�õ����һ��������Ԫ //
	unsigned char	Elem_step;			// ��ɨʱ�����������Ԫ��� //
	unsigned char	Wave_type;			// �ݲ� ���� �Შ //
	unsigned char	res1;
	short	        Angle_min;			// PA ʱ���ǿ�ʼ�Ƕ� UTʱ���¼̽ͷ�Ƕ� //
	short	        Angle_max;			// ��ɨʱ��������õĽǶ� 0.01��Ϊ��λ //
	unsigned short	Angle_step;			// ��ɨʱ��������õĽǶȲ��� //
	short	        Angle_beam_skew_min;		
	short	        Angle_beam_skew_max;		
	unsigned short	Angle_beam_skew_step;	// 2D��ʱ��beam skew angle //
	unsigned short	law_index_start;		// �۽��������� ��������� //
	unsigned short  law_index_end;			//  //
	unsigned int	Focus_depth;			// ��ɨʱ��Ϊ���� ��ɨ����� 0.001mmΪ��λ //
	unsigned int	Position_start;
	int				Position_end;
	int				Position_step;
	int				Offset_start;
	unsigned int	Depth_start;
	int				Offset_end;
	unsigned int	Depth_end;
} LAW_INFO, *LAW_INFO_P;

//AWS calibration

struct AWS_D_15
{
	int a ;
	int b;
	double c ;
};
/// ����Ϣ //

struct GROUP_INFO 
{
	unsigned char	ut_unit;
	unsigned char	group_mode;   

	unsigned char	selection;
	unsigned char	source;
	unsigned char	ascan_color;		
	unsigned char	ascan_envelope;		
	unsigned char	ascan_source;		
	unsigned char	ascan_appearance;	
	unsigned char	ascan_overlay;		
	unsigned char	col_select_pos;
	unsigned char	col_start;
	unsigned char	col_end;
	unsigned char	col_contrast;
	unsigned char	col_brightness;
	unsigned char	col_mode;
	unsigned char	pulser1;
	unsigned char	receiver1;		
	unsigned char	filter1;		
	unsigned char	rectifier1;		
	unsigned char	averaging1;		
	unsigned char	point_qty_pos;
	unsigned char   sum_gain_pos;	
	unsigned char	gate_pos;		
	unsigned char	filter_pos1;	
	unsigned char	tx_rxmode1;		
	unsigned char	freq_pos1;		
	unsigned char	pw_pos1;		
	unsigned char	prf_pos1;		
	unsigned short	frequency1;		
	unsigned short	pulser_width1;	
	short	gain;			
	short	gainr;			
	unsigned short	s_refmeas;
	unsigned short	cursors_angle;
	unsigned short	skew;				/**/
	unsigned short	skew_pos;
	unsigned short	point_qty;		/* ����� */
	unsigned short	sum_gain;
    short	        per_reference;
    short           per_measure;
    int             u_reference;
    int             u_measure;
    int             s_reference;
    int             s_measure;
    int             i_reference;
    int             i_measure;

	unsigned int	col_min;
	unsigned int	col_max;
	unsigned int	min_thickness;
	unsigned int	max_thickness;
	
    int             scan_offset;
    int             index_offset;
    int             angle;
    int             agate_start;
    unsigned int	agate_width;
	int		wedge_delay;
	int		range;	
	int		start;	
	int		velocity;
	int		on_off_status;
	int		prf1;

	int     VelocityCalibrated ;
	int     WedgeDelayCalibrated;
	int     SensationCalibrated;
	int             nReferenceData[8];
	unsigned short	gain_offset[256];
	unsigned int    beam_delay[256];
	float           field_distance[256];
    st_PART	        part;
	AWS_D_15        AwsCalibration   ;
	
	CURSORS_INFO	cursors_info[4];
	GATE_INFO		gate[3];
    SIZING_CURVES   SizingCurves ;
	LAW_INFO		law_info;
	PROBE			probe;
	WEDGE			wedge;
};//__attribute__((aligned(8)));//  align is very important // vs2008 compatibility

struct DRAW_INFO_PACK
{
    int nGroupNum;           //�ܵ�������
    int nBeamNum[8];
    int nJunction[8];

    int nScanStart ;
    int nScanEnd   ;
    int nScanResolution ;
    int nInspecStart    ;
    int nInspecEnd      ;
    int nInspecResolution ;
    int nEncodeType ;                     //�������ͣ���0λ���������룬0λʱ�����
    unsigned char bScanMark[1024 * 256] ;
};

struct INSPEC_DATA_FILE
{
    int type;       // ����
    int version;    // �ļ��ܴ�С  ���ֽڣ� version = size + reserved
    int size;       // �ļ�ͷ����Ϣͷ  �ܴ�С
    int reserved;   // �������ݴ�С
};

#endif  //_DATE_FILE_CONFIGURE_

