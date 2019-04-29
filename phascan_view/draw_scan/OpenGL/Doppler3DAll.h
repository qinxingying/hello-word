#include <QGLWidget>

#include "ParameterProcess.h"

typedef struct _GLPOINT {
    float x;
    float y;
    float z;
}GLPOINT;

class Doppler3DAll : public QGLWidget
{
    Q_OBJECT

public:
    Doppler3DAll(QWidget *parent = 0);
    ~Doppler3DAll(void);
    void SetGroupId(int nGroupId_);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    GLdouble  m_fHeight;
    GLdouble  m_fWidth;
    GLdouble  m_fLength;
    GLdouble  m_fScale;

    GLdouble m_fWndWidth;
    GLdouble m_fWndHeight;

    DopplerConfigure* m_pConfig;
    ParameterProcess* m_process;
    GROUP_CONFIG*     m_pGroup;
    SCANNER*          m_pScanner;
    WELD*             m_pWeld;
    int               m_iPosMax;
    //TOFD_PARA*        m_pTofd ;
    int               m_nGroupId ;
    GLPOINT           m_ptOrigin;
    U8*               m_pColor;

    void BeginDraw();
    void InitGLPoint(GLPOINT* point_, int iLen);
    void drawFrame(bool bPositive_, GLdouble y0_, GLdouble x1_, GLdouble x2_);
    //void drawFrame();

    void drawWeld(bool bPositive_, GLdouble y0_, GLdouble* x1_, GLdouble* x2_, int bMirroring_);
    void drawIShapeWeld(bool bPositive_, GLdouble y0_, GLdouble* x1_, GLdouble* x2_, int bMirroring_);
    void drawVShapeWeld(bool bPositive_, GLdouble y0_, GLdouble* x1_, GLdouble* x2_, int bMirroring_);
    void drawDoubleVShapeWeld(bool bPositive_, GLdouble y0_, GLdouble* x1_, GLdouble* x2_, int bMirroring_);
    void drawUShapeWeld(bool bPositive_, GLdouble y0_, GLdouble* x1_, GLdouble* x2_, int bMirroring_);
 //   void drawDoubleUShapeWeld(bool bPositive_, GLdouble y0_, GLdouble* x1_, GLdouble* x2_, int bMirroring_);

    void drawDefect(GLdouble y0_);
    void drawDefectAzimuthal(GLdouble y0_);
    void drawDefectLiner(GLdouble y0_);

    GLfloat xRot;
    GLfloat yRot;
    GLfloat zRot;
    GLfloat zTra;

    QPoint lastPos;
    QTimer *timer;

private:
    // 扇扫
    U8*  m_pAngleZoom;	//[BUFF_MAX_SIZE] ;// 处于哪个角度区间
    U8*  m_pDraw;	//[BUFF_MAX_SIZE] ;// 是否扇形区域
    U8*  m_pDrawRate;	//[BUFF_MAX_SIZE] ;// 填充比例
    int* m_pDataNo;	//[BUFF_MAX_SIZE] ;

    int  m_nWidth;
    int  m_nHeight;

    float m_nStartX , m_nStopX , m_nStartY , m_nStopY , m_nStepX , m_nStepY ;

    void CreateMatrixBuff();
    void ReleaseMatrixBuff();
    void CalcMatrixAzimuthal();
    void CalcMatrixLinear();
    int DrawPixbuff(GLdouble y0_);

private slots:
    void advanceGL();
};

