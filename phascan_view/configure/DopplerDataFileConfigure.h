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
	unsigned char	parameters;		// 调节模式 0 Positions 1 Mode //
	unsigned char	synchro;        // 同步 //
	unsigned char	measure;        //  //
	unsigned char	rectifier_freq; //射频 //
	char	height;
	char	tt[3];
	int	start;			//单位ns
	unsigned int	width;
} GATE_INFO, *GATE_INFO_P;


struct _output_info;
typedef struct _output_info OUTPUT_INFO1;

/// 输出信息 //
struct _output_info 
{
	unsigned short	alarm_info;		// 状态 表示16个alarm信号的状态 /
	unsigned char	count;    	    ////
	unsigned char	sound;          ///
	unsigned int	delay;			// 单位ns /
	unsigned int	holdtime;       // 单位ns //
};

// 光标信息 
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
	unsigned char	PA_probe_type;		// 探头类型 1 是Custom 3 是angle beam 5 是 Contact 6是Immersion /
	unsigned char	Elem_qty;			// 阵元数 /
	unsigned short	Frequency;			// 频率 /
	unsigned short	Reference_Point;	//  /
	unsigned int	Pitch;				// 阵元中心间距 0.001mm 为单位 范围是0.01~65.00mm UT 是Elemet_size 
};

struct _simple_Wedge;
typedef struct _simple_Wedge st_simple_Wedge;

struct _simple_Wedge
{
	char	Wave_type;		// 1 是L 2 是 S //
	char	Model[20];		// 共用 楔块名字 //
	char	Serial[20];		// 共用 楔块名字 //
	char	Orientation;	// 1 Normal 0 reversal//
	unsigned short	Angle;			// 共用 角度单位0.1度 //
	unsigned short	Probe_delay; 	// UT ns为单位 //
	int	Ref_point;		// UT 使用 //
	unsigned int	Height;			// 单位微米 //
	unsigned int	Velocity_UT;
	unsigned int	Velocity_PA;	// 速度 mm/s //
	int	Primary_offset;	// 微米 //
	unsigned int	Secondary_offset;	// 微米 //
};

/// 探头(Probe)  516 byte 如果探头是unknown 必须给一个参数 //
typedef struct _Probe
{
	//PA 时候先读走4个字节//
	char	A1[2];
	unsigned char	PA_probe_type;	// 探头类型 1 是Custom 3 是angle beam 5 是 Contact 6是Immersion //
	char	A10;
	unsigned char	UT_probe_type;	// 探头类型 1 n/a 0 converntional //
	char	A11;
	char	Model[20];		// 探头名字 //
	char	Serial[20];		// 探头名字 //
	unsigned char	Elem_qty;		// 阵元数 //
	unsigned char	Freq2;			// UT 时候 频率是 (freq2 << 8) + elem_qty //
	unsigned int	Pitch;			// 阵元中心间距 0.001mm 为单位 范围是0.01~65.00mm UT 是Elemet_size //
	unsigned int	A3;
	unsigned short A4;
	unsigned short	Frequency;		// 频率 //
	unsigned int	A5[75];
	unsigned short A6;
	unsigned short A7;
	unsigned short A8;
	unsigned short	Reference_Point; //  //
	unsigned int	A9[36];
} PROBE, *PROBE_P;

///楔块 (Wedge)//
typedef struct _Wedge
{
	unsigned char	A1[2];			// 0x03000300 PA 0x01000100 UT//
	char	Wave_type;		// 1 是L 2 是 S //
	char	A11;
	char	Model[20];		// 共用 楔块名字 //
	char	Serial[20];		// 共用 楔块名字 //
	unsigned short	Angle;			// 共用 角度单位0.1度 //
	unsigned short	A7;
	unsigned short	Probe_delay; 	// UT ns为单位 //
	char	A2;
	char	A10;			// UT 1 SW 0 LW//
	int	Ref_point;		// UT 使用 //
	//这个地方 得 多读一个字节 //
	unsigned int	Height;			// 单位微米 //
	unsigned int	Velocity_UT;
	unsigned int	A8;
	unsigned int	Velocity_PA;	// 速度 mm/s //
	char	Orientation;	// 1 Normal 0 reversal//
	char	A4[3];
	int	Primary_offset;	// 微米 //
	unsigned int	Secondary_offset;	// 微米 //
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

/// 工件 (Part) 12字节 已经全部移走只有CONFIG结构体用到了它 等待隐藏 //
struct _Part
{
	unsigned char	Geometry;		// 几何形状 FLAT/ID/OD/BALL //
    unsigned char	Material_pos;   // 材料 //
	unsigned char	Weld;			// 焊缝 //
	unsigned char   symmetry;		// 对称 //
    unsigned int	Thickness;		// 厚度 //
	unsigned int	Diameter;		// 直径 //

	unsigned int    weland_height;
	unsigned int    weland_offset;
	unsigned int	fizone_height;
	unsigned int	fizone_angle;
	unsigned int	fizone_radius;
	unsigned int    weldtype_pos ;
};

/// 一个阵元的聚焦信息//
typedef struct _law_elem
{
	unsigned char	E_number;
	unsigned char	Amplitude;		// 电压 单位V //
	unsigned short	FL_gain;		// Focal Gain 0.1db单位 //
	unsigned short	R_delay;		//  //
	unsigned short	T_delay;		// 0-25560 单位 ns 65535不活动状态 //
	unsigned short	P_width;		// 50-500 单位ns//
	unsigned char	tt[2];
}LAW_ELEM, *LAW_ELEM_P;

/// 一条beam的聚焦信息 //
typedef struct _law_beam
{
	//    char Version[32];	//
	//    int  N_laws;			//

	unsigned char	N_ActiveElements;	// 同时激发的阵元数 //
	unsigned char	cycle;
	//unsigned char	sumgain;			//  //
	unsigned char	mode;				// 0 T/R 1 Pulse-echo//
	unsigned char	filter;				// 0 no filter 1 0.5-5 2 2-10 3 5-15 //
	unsigned char	T_first;
	unsigned char	R_first;
	char	tt;					// 占位置 //
	unsigned short	frequency;			// 频率0.001Mhz 为单位 //
	short	R_angle;
	unsigned short	S_angle;
	char	tt1[2];				// 占位置 //
	unsigned int	Scan_offset;		// 单位 0.001 mm//
	unsigned int	Index_offset;		// 单位 0.001 mm//
	int	G_delay;			// 单位ns Wedge Delay + Law Delay //
	int	beam_delay;			// 单位ns Law Delay //
	int	F_depth;			// 单位 微粒 //
	unsigned int	M_velocity;			// 单位 m/s //
}LAW_BEAM, *LAW_BEAM_P;

typedef struct _law_focal
{
	char		version[16];
	short		beam_qty;		// 这个focal有几个beam //
	LAW_BEAM_P	*law_beam_p;
	LAW_ELEM_P	*law_elem_p;
} LAW_FOCAL, *LAW_FOCAL_P;

/// 聚焦法则信息(law_info) //
typedef struct _law_info
{
	unsigned char	Focal_type;			// 聚焦类型 //
	unsigned char	Focal_point_type;	// 聚焦类型 //
	unsigned char	Tx_connect;			// pulser该法则的探头发射第一个阵元其连接口的编号 //
	unsigned char	Rx_connect;			// receiver //
	unsigned char	Elem_qty;			// 聚焦阵元数 //
	short	        First_tx_elem;		// 法则使用的第一个发射阵元 收发分离时候 tx rx 不一样 //
	short	        First_rx_elem;		// 法则使用的第一个接收阵元 //
	unsigned char	Last_tx_elem;		// 法则使用的最后一个发射阵元 //
	unsigned char	Last_rx_elem;		// 法则使用的最后一个接收阵元 //
	unsigned char	Elem_step;			// 线扫时候可以设置阵元间隔 //
	unsigned char	Wave_type;			// 纵波 或者 横波 //
	unsigned char	res1;
	short	        Angle_min;			// PA 时候是开始角度 UT时候记录探头角度 //
	short	        Angle_max;			// 扇扫时候可以设置的角度 0.01度为单位 //
	unsigned short	Angle_step;			// 扇扫时候可以设置的角度步进 //
	short	        Angle_beam_skew_min;		
	short	        Angle_beam_skew_max;		
	unsigned short	Angle_beam_skew_step;	// 2D的时候beam skew angle //
	unsigned short	law_index_start;		// 聚焦法则索引 计算出来的 //
	unsigned short  law_index_end;			//  //
	unsigned int	Focus_depth;			// 扇扫时候为声程 线扫是深度 0.001mm为单位 //
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
/// 组信息 //

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
	unsigned short	point_qty;		/* 点个数 */
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
    int nGroupNum;
    int nBeamNum[8];
    int nJunction[8];

    int nScanStart ;
    int nScanEnd   ;
    int nScanResolution ;
    int nInspecStart    ;
    int nInspecEnd      ;
    int nInspecResolution ;
    int nEncodeType ;
    unsigned char bScanMark[1024 * 256] ;
};

struct INSPEC_DATA_FILE
{
    int type;       // 类型
    int version;    // 文件总大小  （字节） version = size + reserved
    int size;       // 文件头，信息头  总大小
    int reserved;   // 采样数据大小
};

#endif  //_DATE_FILE_CONFIGURE_

