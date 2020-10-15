#include "Instrument.h"
#include "Doppler3DAll.h"
#include "gHeader.h"

#include "lib/opengl/glut.h"
#include <QtGui>
#include <QtOpenGL>
#include <math.h>

//extern int Phascan_Version;
const int CURCLE_STEP = 3600;//360;
const F32 DEST_HEIGHT = 6.0;//360;
const int PEAK_CLIP = 204;

void GLDraw1(GLPOINT* pt_, GLenum glemum_, int iDot_);
void GLDraw2(GLPOINT* pt1_, GLPOINT* pt2_, int iDot_);
void GLDrawArc(GLPOINT cf_, GLPOINT pt1_, GLPOINT pt2_, GLdouble R_, GLdouble _sign);
//float GetDepth(float h_, float ply_);

Doppler3DAll::Doppler3DAll(QWidget *parent)
    : QGLWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);

    memset(&m_ptOrigin, 0x00, sizeof(GLPOINT));

    xRot = 180.0f;
    yRot = 0.0f;
    zRot = 0.0f;

    zTra = -20.0f;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(advanceGL()));
    //timer->start(20);

    m_nGroupId = -1;
  //m_pTofd    = NULL;
    m_pGroup   = NULL;
    m_pScanner = NULL;

    m_pConfig = DopplerConfigure::Instance();
    m_process = ParameterProcess::Instance();

    // 扇扫
    m_pDraw      = NULL;
    m_pAngleZoom = NULL;
    m_pDrawRate  = NULL;
    m_pDataNo    = NULL;

    m_nWidth  = 10;
    m_nHeight = 10;

    SetGroupId(0);
}

Doppler3DAll::~Doppler3DAll(void)
{
    ReleaseMatrixBuff();
}

void Doppler3DAll::SetGroupId(int nGroupId_)
{
    if(m_nGroupId != nGroupId_) {
        m_nGroupId = nGroupId_ ;
        //m_pTofd    = m_pConfig->GetTofdConfig(m_nGroupId) ;
        m_pGroup   = &m_pConfig->group[m_nGroupId]  ;
        m_pScanner = &m_pConfig->common.scanner;
        m_iPosMax  = m_process->SAxisDistToIndex(m_pScanner->fScanend);
        m_pWeld    = m_process->GetWeld(m_nGroupId);

        m_fHeight = m_process->GetPartThickness(m_nGroupId);
        m_fWidth  = m_fHeight * 6.0;
        m_fLength = m_pScanner->fScanend - m_pScanner->fScanStart2;

        if(m_fLength < m_fHeight)
            m_fLength = m_fHeight;
        if(m_fHeight  == 0)
            m_fHeight = 1;

        m_fScale = DEST_HEIGHT / m_fHeight;
    }
}

void Doppler3DAll::CreateMatrixBuff()
{
    ReleaseMatrixBuff();

    int _nSize = m_nWidth * m_nHeight;
     //if(!_nSize) _nSize = 1 ;
    m_pDraw       =  (U8*)malloc(_nSize);
    m_pAngleZoom  =  (U8*)malloc(_nSize);
    m_pDrawRate   =  (U8*)malloc(_nSize);
    m_pDataNo     =  (int*)malloc(_nSize * sizeof(int));
    memset((void*)(m_pDraw), 0, _nSize);
}

void Doppler3DAll::ReleaseMatrixBuff()
{
    if(m_pDraw)      {free(m_pDraw); m_pDraw = NULL;}
    if(m_pAngleZoom) {free(m_pAngleZoom); m_pAngleZoom = NULL;}
    if(m_pDrawRate)  {free(m_pDrawRate); m_pDrawRate = NULL;}
    if(m_pDataNo)    {free(m_pDataNo); m_pDataNo = NULL;}
}

void Doppler3DAll::CalcMatrixAzimuthal(void)
{
    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId] ;
    LAW_CONFIG*     _law = m_process->GetLawConfig(m_nGroupId);
    int _iAngle = (int)m_process->GetProbeAngle(m_nGroupId);

    // get real window size
    float  _nAngleStart = DEGREE_TO_ARCH(_law->nAngleStartRefract / 10.0)         ;
    float   _nAngleStop = DEGREE_TO_ARCH(_law->nAngleStopRefract / 10.0)          ;
    float   _nAngleStep = DEGREE_TO_ARCH(_law->nAngleStepRefract / 10.0)          ;
    int      _nPointQty = _group.nPointQty                                        ;
    int       _nBeamQty = (int)((_nAngleStop - _nAngleStart) / _nAngleStep + 1.1) ;
    float _nSampleStart = _group.fSampleStart                                     ;
    float _nSampleRange = _group.fSampleRange                                     ;
    float  _nSampleStop = _nSampleStart + _nSampleRange                           ;
    float*  _pExitPoint = m_process->GetBeamInsertPos(m_nGroupId)                 ;
    int     _nDirection = 0                                                       ;
    //***************S
    if(_iAngle >= (int)setup_PROBE_PART_SKEW_180 )   _nDirection   =  1           ;
    //***************E

    //***************S
    float _nStartX = m_nStartX;
    //float  _nStopX = m_nStopX;
    float _nStartY = m_nStartY;
    //float  _nStopY = m_nStopY;
    float  _nStepX = m_nStepX;
    float  _nStepY = m_nStepY;

    // get real step of each pixel
    //***************S
    int  _width = m_nWidth  ;    //  图像 宽    单位 像素
    int _height = m_nHeight ;    //  图像 高    单位 像素

    // get juction of each two beam
    float _nTopLocation[256]  ;
    for(int i = 0 ; i < _nBeamQty - 1; i++)
    {
        _nTopLocation[i] = (_pExitPoint[i] + _pExitPoint[i+1]) / 2 ;
    }
    // get all values of angle
    float _nAngles[256];
    for(int i = 0 ; i < _nBeamQty ; i++)
    {
        _nAngles[i] = _nAngleStart + i * _nAngleStep ;
    }

    float _nPosJunction[256]; // 每个Y轴坐标上声线的位置
    int i, j, k, t, _index;
    float _fX, _fY, _nTmp;
    for(j = 0 ; j < _height ; j++)
    {
        _fY = _nStartY + j * _nStepY ;	// current y position

        for(k = 0 ; k < _nBeamQty ; k++)
        {// beam junctions with current y coordinates
            _nPosJunction[k] = _pExitPoint[k] + tan(_nAngles[k]) * _fY  ;
        }
        // calculate matrix
        t = 0 ;
        for(i = 0 ; i < _width ; i++)
        {
            _fX = _nStartX + _nStepX * i ;	// get current pixel position in real coordinate
            for( ; t < _nBeamQty - 1; t++)
            {// if current position is less than minimun or bigger than maximum  get out
                if(_fX > _nPosJunction[_nBeamQty - 1] || _fX < _nPosJunction[0] )
                {
                    break;
                }
                if(_fX >= _nPosJunction[t] && _fX <= _nPosJunction[t+1] )
                {
                    if(_nDirection)
                    {// if draw direction is inverse , transfer the x coordinate
                        _index = _width - i + j * _width  ;
                    }
                    else
                    {
                        _index = i + j * _width  ;
                    }
                    m_pAngleZoom[_index]  = t ;
                    _nTmp = _fX - _nTopLocation[t]  ;
                    _nTmp = sqrt(_fY * _fY + _nTmp * _nTmp) ;

                    if(_nTmp > _nSampleStop || _nTmp < _nSampleStart)
                    {// if current position is out of sample range , get out
                        break;
                    }
                    // get current point data index in data block
                    m_pDataNo[_index] = _nPointQty * (_nTmp - _nSampleStart) / _nSampleRange ;
                    if((_nPosJunction[t+1] - _fX) < FLOAT_ZERO_GATE)
                    {
                        m_pDrawRate[_index] = COLOR_STEP  ;
                    }
                    else
                    {
                        _nTmp = cos(_nAngles[t]) * (_fX - _nPosJunction[t])
                                / ( cos(_nAngles[t+1]) * (_nPosJunction[t+1] - _fX))  ;
                        _nTmp = _nTmp / (1 + _nTmp) ;
                        m_pDrawRate[_index] =  _nTmp * COLOR_STEP ;
                    }
                    m_pDraw[_index]  = 255 ;
                    break ;
                }
            }
        }
    }
}

void Doppler3DAll::CalcMatrixLinear(void)
{
    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId] ;
    LAW_CONFIG*     _law = m_process->GetLawConfig(m_nGroupId);
    int _iAngle = (int)m_process->GetProbeAngle(m_nGroupId);

    int _nStartElement = _law->nFirstElemFir ;
    int  _nStopElement = _law->nLastElemFir ;
    int  _nStepElement = _law->nElemStepFir ;
    int   _nElementQty = _law->nElemQtyFir ;
    double     _fAngle = DEGREE_TO_ARCH(_law->nAngleStartRefract / 10.0)   ;
    int     _nPointQty = _group.nPointQty ;
    double     _fRange = _group.fSampleRange ;
    int         _width = m_nWidth ;
    int        _height = m_nHeight ;
    int    _bDirection = 0 ;
    float* _pExitPoint = m_process->GetBeamInsertPos(m_nGroupId) ;
    //***************S
    if(_iAngle >= (int)setup_PROBE_PART_SKEW_180 )
        _bDirection   =  1 ;
    //***************E

    int  _nBeamMaxId = (_nStopElement  - _nStartElement - _nElementQty + 1 ) / _nStepElement ;
    float _fStartPos = _pExitPoint [0] ;
    float  _fStopPos = _pExitPoint [_nBeamMaxId] ;
    double    _angle = fabs(_fAngle);

    double _real_height = _fRange * cos(_angle);				    // 实际宽度
    double  _real_width = fabs(_fStopPos - _fStartPos) + _fRange * sin(_angle) ;    // 实际高度
    double      _xScale = _width / _real_width ;		    // X轴比例(像素/实际)
    double       _xVacc = tan(_angle) * _real_height * _xScale ;    // 角度横向偏移量(像素)
    double      _fScale = _xVacc / _height ;			    // [角度横向偏移量(像素)]/[角度纵向偏移量(像素)]
    double  _beam_width = _width - _xVacc ;			    // 波束宽度(像素)

    bool _bWedgeRev = (_fStopPos - _fStartPos) > 0 ? false : true ;

    double tmpX , xxx;	    // 波束索引 中间变量
    double tmpDrawRate ;    // 波束索引
    double tmpDataNo   ;    // 数据位置索引

    int i ,  j  , index ;
    for( i = 0 ; i < _height ; i++)
    {
        tmpX = i * _fScale ;
        tmpDataNo = ((double)i) / _height ;
        for( j = 0 ; j < _width ; j++ )
        {
            if(_bDirection) // reverse
            {
                index  = _width - j + i * _width ;
            }
            else
            {
                index  = j + i * _width ;
            }
            if( _fAngle >=0 )
                xxx = j - tmpX ;
            else
                xxx = j - _xVacc + tmpX ;

            if( xxx >= 0 && xxx < _beam_width)
            {
                m_pDraw[index] = 255 ;
            }
            else
            {
                continue ;
            }

            tmpDrawRate = ( xxx / _beam_width ) *  _nBeamMaxId  ;
            if(_bWedgeRev)
            {
                m_pAngleZoom[index] = _nBeamMaxId - (U8)tmpDrawRate ;
                tmpDrawRate =  (int)(tmpDrawRate + 1) - tmpDrawRate  ;
            }
            else
            {
                m_pAngleZoom[index] = (U8)tmpDrawRate ;
                tmpDrawRate =  tmpDrawRate - (int)tmpDrawRate  ;
            }

            m_pDrawRate[index] = (U8)( tmpDrawRate * COLOR_STEP ) ;
            m_pDataNo[index]   = (int) _nPointQty * tmpDataNo ;
        }
    }
}

int Doppler3DAll::DrawPixbuff(GLdouble y0_)
{
	U8* _pMarker = m_process->GetScanMarker(m_nGroupId)  ;
    WDATA* _pData  = m_process->GetShadowDataPointer();
    if(!_pData) return -1;

    int    _nPointQty = m_process->GetGroupPointQty(m_nGroupId);
    //int     _nBeamQty = m_process->GetGroupLawQty(m_nGroupId);
    //int _nFrameOffset = m_process->GetTotalDataSize() ;
    //int _nGroupOffset = m_process->GetGroupDataOffset(m_nGroupId);
    int     _nLawSize = _nPointQty + 32;
    float  _fScanStep = m_pConfig->common.scanner.fScanStep;

    float _fXStart, _fXStop, _fYStart, _fYStop;
    m_process->GetSScanHorizentalRange(m_nGroupId , &_fXStart , &_fXStop);
    m_process->GetSScanVerticalRange(m_nGroupId , &_fYStart , &_fYStop);

	ParameterProcess* _process = ParameterProcess::Instance();
	int _nScanMax = _process->GetScanMax();

    int _nFrameOffset = m_process->GetTotalDataSize() ;
    int _nGroupOffset = m_process->GetGroupDataOffset(m_nGroupId);

    float  _fScale = m_process->GetRefGainScale(m_nGroupId) ;
    bool _bRectify = (m_process->GetRectifierMode(m_nGroupId) == setup_RECTIFIER_RF ) ;

    float _fx, _fy, _fz1, _fz2;
    int i, j, k, _idx1, _idx2, _iData;

    U8* _pColor;
    GLPOINT _pt1[4];

    _pData += _nGroupOffset;
    for(k = 0; k < _nScanMax; k++)
    //for(k = 0; k < 1; k++)
    {
        if(_pMarker[k])
        {
            _fz1 = m_fScale * k * _fScanStep;
            _fz2 = m_fScale * (k + 1) * _fScanStep;
            for(i = 0; i < m_nHeight; i++)
            {
                _fy = m_fScale * (_fYStart + i * m_nStepY + y0_);
                //_fy = m_fScale * (GetDepth(_fYStart + i * m_nStepY, m_fHeight) + y0_);
                for(j = 0; j < m_nWidth; j++)
                {
                    _idx1 = i * m_nWidth + j;
                    if(m_pDraw[_idx1] != 0)
                    {
                        _idx2 = (int)(m_pAngleZoom[_idx1] * _nLawSize + m_pDataNo[_idx1]);
//    if(Phascan_Version == 1 || Phascan_Version == 3 || Phascan_Version == 4)
//	{
//		_iData = (int)(_pData[_idx2] * (COLOR_STEP - m_pDrawRate[_idx1]) +
//                                          _pData[_idx2 + _nLawSize] * m_pDrawRate[_idx1] ) ;
//	}
//    else if(Phascan_Version == 2 || Phascan_Version == 5)
//	{
// 		 _iData = (int)((_pData[_idx2] * 2 | 1) * (COLOR_STEP - m_pDrawRate[_idx1]) +
//                                         (_pData[_idx2 + _nLawSize] * 2 | 1) * m_pDrawRate[_idx1] ) ;
//	}
                        _iData = (int)( m_process->correctionPdata(_pData[_idx2]) * (COLOR_STEP - m_pDrawRate[_idx1]) +
                                      m_process->correctionPdata(_pData[_idx2 + _nLawSize]) * m_pDrawRate[_idx1] ) ;

                        _iData = _iData>>COLOR_SHIFT ;
                        _iData = m_process->GetRefGainScaleData(_iData, _fScale, _bRectify);

                        if(_iData > PEAK_CLIP)
                        {
                            _fx = m_fScale * (_fXStart + j * m_nStepX);

                            _pColor = (m_pColor + _iData*3);
                            glColor3f((float)_pColor[0] / 255.0, (float)_pColor[1] / 255.0, (float)_pColor[1] / 255.0);
                            InitGLPoint(_pt1, 2);
                            _pt1[0].x += _fx; _pt1[0].y += _fy; _pt1[0].z += _fz1;
                            _pt1[1].x += _fx; _pt1[1].y += _fy; _pt1[1].z += _fz2;
                            GLDraw1(_pt1, GL_LINE_STRIP, 2);
                        }
                    }
                }
            }
        }
        _pData += _nFrameOffset;
    }
    return 0;
}

void Doppler3DAll::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void Doppler3DAll::resizeGL(int width, int height)
{
    if (height == 0)
        height = 1;

    m_fWndWidth  = width;
    m_fWndHeight = height;
}

void Doppler3DAll::paintGL()
{
    BeginDraw();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, zTra);

    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);

    //glColor3f(0.0f, 0.8f, 0.8f);

    //drawFrame();
    GLdouble _x1, _x2;
    GLdouble _y0 = -m_fHeight;

    int _bMirroring = 0;

    for(int i = 0; i < 2; i++)
    {
        _bMirroring = i % 2;
        switch(m_pWeld->eSymmetry)
        {
        case setup_WELD_SYMMETRY:
            drawWeld(true, _y0, &_x1, &_x2, _bMirroring);  drawFrame(true, _y0, _x1, _x2);
            drawWeld(false, _y0, &_x1, &_x2, _bMirroring); drawFrame(false, _y0, _x1, _x2);
            break;
        case setup_WELD_RIGHT:
            drawWeld(true, _y0, &_x1, &_x2, _bMirroring);  drawFrame(true, _y0, _x1, _x2);
            break;
        case setup_WELD_LEFT:
            drawWeld(false, _y0, &_x1, &_x2, _bMirroring); drawFrame(false, _y0, _x1, _x2);
            break;
        }
        _y0 += m_fHeight;
    }

    _y0 = -m_fHeight;
    drawDefect(_y0);

}

void Doppler3DAll::BeginDraw()
{
    glViewport(0,0,m_fWndWidth, m_fWndHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat x = (GLfloat)m_fWndWidth / (GLfloat)m_fWndHeight;
	//----------------------------------------------------
	// gluPerspective 函数的代替方案
//	gluPerspective(45.0f, x, 0.1f, m_fLength);
	GLfloat zNear  = 0.1;
	GLfloat zFar   = m_fLength;
	GLfloat aspect = x;
	GLfloat fH     = tan(GLfloat(90.0/360.0*3.14159))*zNear;
	GLfloat fW     = fH * aspect;
	glFrustum(-fW, fW, -fH, fH, zNear, zFar);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(setup_RECTIFIER_RF ==  m_process->GetRectifierMode(m_nGroupId))
        m_pColor = (U8*)m_process->GetPalete(m_nGroupId , PALETTE_RECTIFY );
    else
        m_pColor = (U8*)m_process->GetPalete(m_nGroupId , PALETTE_AMP);

    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId] ;

    if(setup_GROUP_MODE_PA == _group.eGroupMode)
    {
        float _nStartX , _nStopX , _nStartY , _nStopY, _nStepX, _nStepY;
        m_process->GetSImageHorizentalRange(m_nGroupId , &_nStartX , &_nStopX);
        m_process->GetSImageVerticalRange(m_nGroupId , &_nStartY , &_nStopY);

        m_nWidth  = 300;
        m_nHeight = 500;
        int  _width = m_nWidth  ;    //  图像 宽    单位 像素
        int _height = m_nHeight ;    //  图像 高    单位 像素

        _nStepX  = (_nStopX - _nStartX) / (_width - 1) ;
        _nStepY  = _nStepX;

        _height = (_nStopY - _nStartY) / _nStepY + 1;
        //_nStepY  = (_nStopY - _nStartY) / (_height - 1) ;
        m_nHeight = _height;

        CreateMatrixBuff();

        m_nStartX = _nStartX;
        m_nStopX  = _nStopX;
        m_nStartY = _nStartY;
        m_nStopY  = _nStopY;
        m_nStepX  = _nStepX;
        m_nStepY  = _nStepY;
    }
}

void Doppler3DAll::InitGLPoint(GLPOINT* point_, int iLen_)
{
    memset(point_, 0x00, iLen_*sizeof(GLPOINT));
    for(int i = 0; i < iLen_; i++) {
        point_[i] = m_ptOrigin;
    }
}

void Doppler3DAll::drawFrame(bool bPositive_, GLdouble y0_, GLdouble x1_, GLdouble x2_)
{
    GLdouble _sign = 1;
    if(!bPositive_)
        _sign = -1;

    GLdouble _fHeight = m_fHeight * m_fScale;
    GLdouble _fWidth  = _sign * m_fWidth * m_fScale;
    GLdouble _fLength = m_fLength * m_fScale;

    GLdouble _YU = y0_ * m_fScale;
    GLdouble _YD = _YU + _fHeight;

    GLPOINT _pt[4];

    // 上
    InitGLPoint(_pt, 4);
    _pt[0].x += x1_;           _pt[0].y += _YU;   _pt[0].z += _fLength;
    _pt[1].x += _fWidth / 2;   _pt[1].y += _YU;   _pt[1].z += _fLength;
    _pt[2].x += _fWidth / 2;   _pt[2].y += _YU;   _pt[2].z += 0;
    _pt[3].x += x1_;           _pt[3].y += _YU;   _pt[3].z += 0;
    glColor3f(0.0f, 0.8f, 0.8f);
    GLDraw1(_pt, GL_LINE_STRIP, 4);
    // 中
    InitGLPoint(_pt, 4);
    _pt[0].x += _fWidth / 2;  _pt[0].y += _YU;   _pt[0].z += 0;
    _pt[1].x += _fWidth / 2;  _pt[1].y += _YD;    _pt[1].z += 0;
    glColor3f(0.0f, 0.8f, 0.8f);
    GLDraw1(_pt, GL_LINES, 2);

    InitGLPoint(_pt, 4);
    _pt[0].x += _fWidth / 2;  _pt[0].y += _YU;   _pt[0].z += _fLength;
    _pt[1].x += _fWidth / 2;  _pt[1].y += _YD;    _pt[1].z += _fLength;
    glColor3f(1.0f, 0.8f, 0.0f);
    GLDraw1(_pt, GL_LINES, 2);
    // 下
    InitGLPoint(_pt, 4);
    _pt[0].x += x2_;           _pt[0].y += _YD;   _pt[0].z += _fLength;
    _pt[1].x += _fWidth / 2;   _pt[1].y += _YD;   _pt[1].z += _fLength;
    _pt[2].x += _fWidth / 2;   _pt[2].y += _YD;   _pt[2].z += 0;
    _pt[3].x += x2_;           _pt[3].y += _YD;   _pt[3].z += 0;
    glColor3f(0.0f, 0.0f, 1.0f);
    GLDraw1(_pt, GL_LINE_STRIP, 4);//GL_LINE_LOOP
}

void Doppler3DAll::drawWeld(bool bPositive_, GLdouble y0_, GLdouble* x1_, GLdouble* x2_, int bMirroring_)
{
    switch(m_pWeld->eType)
    {
    case setup_WELD_I:  drawIShapeWeld(bPositive_, y0_, x1_, x2_, bMirroring_);         break;
    case setup_WELD_V:  drawVShapeWeld(bPositive_, y0_, x1_, x2_, bMirroring_);         break;
    case setup_WELD_DV: drawDoubleVShapeWeld(bPositive_, y0_, x1_, x2_, bMirroring_);   break;
    case setup_WELD_U:  drawUShapeWeld(bPositive_, y0_, x1_, x2_, bMirroring_);         break;
	default:
		break;
    }
}

void Doppler3DAll::drawIShapeWeld(bool bPositive_, GLdouble y0_, GLdouble* x1_, GLdouble* x2_, int bMirroring_)
{
    Q_UNUSED(bMirroring_);
    GLdouble _sign = 1;
    if(!bPositive_)
        _sign = -1;

    GLdouble _XOff = _sign * m_fScale * m_pWeld->weland_offset / 2.0;
    GLdouble _YOff = m_fScale * y0_;
    GLdouble _ZOff = m_fScale * m_fLength;
    GLdouble _High = m_fScale * m_pWeld->weland_height;

    GLPOINT _pt1[2];
    GLPOINT _pt2[2];

    ////glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xAAAA);

    glColor3f(0.5f, 5.0f, 0.5f);

    InitGLPoint(_pt1, 2);
    _pt1[0].x += _XOff;  _pt1[0].y += _YOff;        _pt1[0].z += 0;
    _pt1[1].x += _XOff;  _pt1[1].y += _YOff+_High;  _pt1[1].z += 0;
    //glColor3f(0.5f, 5.0f, 0.5f);
    GLDraw1(_pt1, GL_LINE_STRIP, 2);

    InitGLPoint(_pt2, 2);
    _pt2[0].x += _XOff;  _pt2[0].y += _YOff;        _pt2[0].z += _ZOff;
    _pt2[1].x += _XOff;  _pt2[1].y += _YOff+_High;  _pt2[1].z += _ZOff;
    //glColor3f(0.5f, 5.0f, 0.5f);
    GLDraw1(_pt2, GL_LINE_STRIP, 2);

    GLDraw2(_pt1, _pt2, 2);

    //glDisable(GL_LINE_STIPPLE);

    *x1_ = _pt1[0].x;
    *x2_ = _pt1[1].x;
}

void Doppler3DAll::drawVShapeWeld(bool bPositive_, GLdouble y0_, GLdouble* x1_, GLdouble* x2_, int bMirroring_)
{
    GLdouble _sign = 1;
    if(!bPositive_)
        _sign = -1;

    GLdouble _Angle = DEGREE_TO_ARCH(m_pWeld->fizone_angle);

    GLdouble _XOff1 = _sign * m_fScale * (m_pWeld->weland_offset + m_pWeld->fizone_height * tan(_Angle));
    GLdouble _XOff2 = _sign * m_fScale * m_pWeld->weland_offset;
    GLdouble _YOff1 = m_fScale * (0 + y0_);
    GLdouble _YOff2 = m_fScale * (m_pWeld->fizone_height + y0_);
    GLdouble _YOff3 = m_fScale * (m_pWeld->fizone_height + m_pWeld->weland_height + y0_);
    GLdouble _ZOff1 = 0;
    GLdouble _ZOff2 = m_fScale * m_fLength;
    if(bMirroring_)
    {
        _YOff1 = m_fScale * (0 + y0_);
        _YOff2 = _YOff3 - _YOff2;
        _YOff3 = m_fScale * m_fHeight;
    }

    GLPOINT _pt1[3];
    GLPOINT _pt2[3];

    //glEnable(GL_LINE_STIPPLE);
    //glLineStipple(1, 0xAAAA);

    glColor3f(0.5f, 5.0f, 0.5f);

    InitGLPoint(_pt1, 3);
    if(bMirroring_) {
        _pt1[0].x += _XOff2;  _pt1[0].y += _YOff1;  _pt1[0].z += _ZOff1;
        _pt1[1].x += _XOff2;  _pt1[1].y += _YOff2;  _pt1[1].z += _ZOff1;
        _pt1[2].x += _XOff1;  _pt1[2].y += _YOff3;  _pt1[2].z += _ZOff1;
    } else {
        _pt1[0].x += _XOff1;  _pt1[0].y += _YOff1;  _pt1[0].z += _ZOff1;
        _pt1[1].x += _XOff2;  _pt1[1].y += _YOff2;  _pt1[1].z += _ZOff1;
        _pt1[2].x += _XOff2;  _pt1[2].y += _YOff3;  _pt1[2].z += _ZOff1;
    }
    GLDraw1(_pt1, GL_LINE_STRIP, 3);


    InitGLPoint(_pt2, 3);
    if(bMirroring_) {
        _pt2[0].x += _XOff2;  _pt2[0].y += _YOff1;  _pt2[0].z += _ZOff2;
        _pt2[1].x += _XOff2;  _pt2[1].y += _YOff2;  _pt2[1].z += _ZOff2;
        _pt2[2].x += _XOff1;  _pt2[2].y += _YOff3;  _pt2[2].z += _ZOff2;
    } else {
        _pt2[0].x += _XOff1;  _pt2[0].y += _YOff1;  _pt2[0].z += _ZOff2;
        _pt2[1].x += _XOff2;  _pt2[1].y += _YOff2;  _pt2[1].z += _ZOff2;
        _pt2[2].x += _XOff2;  _pt2[2].y += _YOff3;  _pt2[2].z += _ZOff2;
    }
    GLDraw1(_pt2, GL_LINE_STRIP, 3);

    GLDraw2(_pt1, _pt2, 3);

    //glDisable(GL_LINE_STIPPLE);

    *x1_ = _pt1[0].x;
    *x2_ = _pt1[2].x;
}

void Doppler3DAll::drawDoubleVShapeWeld(bool bPositive_, GLdouble y0_, GLdouble* x1_, GLdouble* x2_, int bMirroring_)
{
    Q_UNUSED(bMirroring_);
    GLdouble _sign = 1;
    if(!bPositive_)
        _sign = -1;

    GLdouble _Angle = DEGREE_TO_ARCH(m_pWeld->fizone_angle);

    GLdouble _XOff1 = _sign * m_fScale * (m_pWeld->weland_offset + m_pWeld->fizone_height * tan(_Angle));
    GLdouble _XOff2 = _sign * m_fScale * m_pWeld->weland_offset;
    GLdouble _YOff1 = m_fScale * (0 + y0_);
    GLdouble _YOff2 = m_fScale * (m_pWeld->fizone_height + y0_);
    GLdouble _YOff3 = m_fScale * (m_pWeld->fizone_height + m_pWeld->weland_height + y0_);
    GLdouble _YOff4 = m_fScale * (2*m_pWeld->fizone_height + m_pWeld->weland_height + y0_);
    GLdouble _ZOff1 = 0;
    GLdouble _ZOff2 = m_fScale * m_fLength;

    GLPOINT _pt1[4];
    GLPOINT _pt2[4];

    //glEnable(GL_LINE_STIPPLE);
    //glLineStipple(1, 0xAAAA);

    glColor3f(0.5f, 5.0f, 0.5f);

    InitGLPoint(_pt1, 4);
    _pt1[0].x += _XOff1;  _pt1[0].y += _YOff1;  _pt1[0].z += _ZOff1;
    _pt1[1].x += _XOff2;  _pt1[1].y += _YOff2;  _pt1[1].z += _ZOff1;
    _pt1[2].x += _XOff2;  _pt1[2].y += _YOff3;  _pt1[2].z += _ZOff1;
    _pt1[3].x += _XOff1;  _pt1[3].y += _YOff4;  _pt1[3].z += _ZOff1;
    GLDraw1(_pt1, GL_LINE_STRIP, 4);


    InitGLPoint(_pt2, 4);
    _pt2[0].x += _XOff1;  _pt2[0].y += _YOff1;  _pt2[0].z += _ZOff2;
    _pt2[1].x += _XOff2;  _pt2[1].y += _YOff2;  _pt2[1].z += _ZOff2;
    _pt2[2].x += _XOff2;  _pt2[2].y += _YOff3;  _pt2[2].z += _ZOff2;
    _pt2[3].x += _XOff1;  _pt2[3].y += _YOff4;  _pt2[3].z += _ZOff2;
    GLDraw1(_pt2, GL_LINE_STRIP, 4);

    GLDraw2(_pt1, _pt2, 4);

    //glDisable(GL_LINE_STIPPLE);

    *x1_ = _pt1[0].x;
    *x2_ = _pt1[3].x;
}

void Doppler3DAll::drawUShapeWeld(bool bPositive_, GLdouble y0_, GLdouble* x1_, GLdouble* x2_, int bMirroring_)
{
    GLdouble _R = m_pWeld->fizone_radius;
    GLdouble _A = DEGREE_TO_ARCH(m_pWeld->fizone_angle);
    GLdouble _O = m_pWeld->weland_offset;

    GLdouble _TmpY1 = sqrt(_R * _R - _O * _O);
    GLdouble _TmpY2 = _R * sin(_A);

    if(_TmpY2 > _TmpY1)
    {
        drawVShapeWeld(bPositive_, y0_, x1_, x2_, bMirroring_);
        return;
    }

    GLdouble _Y = m_pWeld->fizone_height - (_TmpY1 - _TmpY2);

    GLdouble _sign = 1;
    if(!bPositive_)
        _sign = -1;

    GLdouble _X1 = _sign * m_fScale * (_Y * tan(_A) + _R * cos(_A));
    GLdouble _X2 = _sign * m_fScale * _R * cos(_A);
    GLdouble _X3 = _sign * m_fScale * _O;
    GLdouble _X4 = _X3;

    GLdouble _Y1 = m_fScale * (0 + y0_);
    GLdouble _Y2 = m_fScale * (_Y + y0_);
    GLdouble _Y3 = m_fScale * (m_pWeld->fizone_height + y0_);
    GLdouble _Y4 = m_fScale * (m_pWeld->fizone_height + m_pWeld->weland_height + y0_);
    if(bMirroring_)
    {
        _Y1 = m_fScale * (0 + y0_);
        _Y2 = m_fScale * (m_pWeld->weland_height + y0_);
        _Y3 = m_fScale * (m_pWeld->weland_height + (m_pWeld->fizone_height - _Y) + y0_);
        _Y4 = m_fScale * (m_pWeld->weland_height + m_pWeld->fizone_height + y0_);
    }

    GLdouble _Z1 = 0;
    GLdouble _Z2 = m_fScale * m_fLength;

    GLPOINT _pt1[4];
    GLPOINT _pt2[4];

    GLdouble _r = m_fScale * _R;
    GLPOINT _cf;

    glColor3f(0.5f, 5.0f, 0.5f);

    InitGLPoint(_pt1, 4);
    if(bMirroring_) {
        _pt1[0].x += _X4;  _pt1[0].y += _Y1;  _pt1[0].z += _Z1;
        _pt1[1].x += _X3;  _pt1[1].y += _Y2;  _pt1[1].z += _Z1;
        _pt1[2].x += _X2;  _pt1[2].y += _Y3;  _pt1[2].z += _Z1;
        _pt1[3].x += _X1;  _pt1[3].y += _Y4;  _pt1[3].z += _Z1;

        InitGLPoint(&_cf, 1);
        _cf.x += _Z1;
        _cf.y += _Y2 + m_fScale * _TmpY1;
    } else {
        _pt1[0].x += _X1;  _pt1[0].y += _Y1;  _pt1[0].z += _Z1;
        _pt1[1].x += _X2;  _pt1[1].y += _Y2;  _pt1[1].z += _Z1;
        _pt1[2].x += _X3;  _pt1[2].y += _Y3;  _pt1[2].z += _Z1;
        _pt1[3].x += _X4;  _pt1[3].y += _Y4;  _pt1[3].z += _Z1;

        InitGLPoint(&_cf, 1);
        _cf.x += _Z1;
        _cf.y += _Y3 - m_fScale * _TmpY1;
    }

    GLDraw1(_pt1, GL_LINE_STRIP, 2);
    GLDrawArc(_cf, _pt1[1], _pt1[2], _r, _sign);
    GLDraw1(&_pt1[2], GL_LINE_STRIP, 2);

    InitGLPoint(_pt2, 4);
    if(bMirroring_) {
        _pt2[0].x += _X4;  _pt2[0].y += _Y1;  _pt2[0].z += _Z2;
        _pt2[1].x += _X3;  _pt2[1].y += _Y2;  _pt2[1].z += _Z2;
        _pt2[2].x += _X2;  _pt2[2].y += _Y3;  _pt2[2].z += _Z2;
        _pt2[3].x += _X1;  _pt2[3].y += _Y4;  _pt2[3].z += _Z2;

        InitGLPoint(&_cf, 1);
        _cf.z += _Z2;
        _cf.y += _Y2 + m_fScale * _TmpY1;
    } else {
        _pt2[0].x += _X1;  _pt2[0].y += _Y1;  _pt2[0].z += _Z2;
        _pt2[1].x += _X2;  _pt2[1].y += _Y2;  _pt2[1].z += _Z2;
        _pt2[2].x += _X3;  _pt2[2].y += _Y3;  _pt2[2].z += _Z2;
        _pt2[3].x += _X4;  _pt2[3].y += _Y4;  _pt2[3].z += _Z2;

        InitGLPoint(&_cf, 1);
        _cf.z += _Z2;
        _cf.y += _Y3 - m_fScale * _TmpY1;
   }


    GLDraw1(_pt2, GL_LINE_STRIP, 2);
    GLDrawArc(_cf, _pt2[1], _pt2[2], _r, _sign);
    GLDraw1(&_pt2[2], GL_LINE_STRIP, 2);
/*
    InitGLPoint(_pt2, 4);
    if(bMirroring_)
    {
        _pt2[0].x += _X4;  _pt2[0].y += _Y1;  _pt2[0].z += _Z2;
        _pt2[1].x += _X3;  _pt2[1].y += _Y2;  _pt2[1].z += _Z2;
        _pt2[2].x += _X2;  _pt2[2].y += _Y3;  _pt2[2].z += _Z2;
        _pt2[3].x += _X1;  _pt2[3].y += _Y4;  _pt2[3].z += _Z2;

        InitGLPoint(&_cf, 1);
        _cf.x += _Z2;
        _cf.y += _pt1[1].y + m_fScale * _TmpY1;
    }
    else
    {
        _pt2[0].x += _X1;  _pt2[0].y += _Y1;  _pt2[0].z += _Z2;
        _pt2[1].x += _X2;  _pt2[1].y += _Y2;  _pt2[1].z += _Z2;
        _pt2[2].x += _X3;  _pt2[2].y += _Y3;  _pt2[2].z += _Z2;
        _pt2[3].x += _X4;  _pt2[3].y += _Y4;  _pt2[3].z += _Z2;

        InitGLPoint(&_cf, 1);
        _cf.x += _Z2;
        _cf.y += _Y3 - m_fScale * _TmpY1;
    }

    GLDraw1(_pt2, GL_LINE_STRIP, 2);
    GLDrawArc(_cf, _pt2[1], _pt2[2], _r, _sign);
    GLDraw1(&_pt2[2], GL_LINE_STRIP, 2);*/

    GLDraw2(_pt1, _pt2, 4);

    *x1_ = _pt1[0].x;
    *x2_ = _pt1[3].x;
}

void Doppler3DAll::drawDefect(GLdouble y0_)
{
    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId] ;
    if(setup_GROUP_MODE_PA == _group.eGroupMode)
    {
        if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
        {
            CalcMatrixAzimuthal();
        }
        else
        {
            CalcMatrixLinear();
        }
        DrawPixbuff(y0_);
    }
}

void Doppler3DAll::drawDefectAzimuthal(GLdouble y0_)
{
    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId] ;
    //ParameterProcess* _process = ParameterProcess::Instance();

    LAW_CONFIG* _law = m_process->GetLawConfig(m_nGroupId);

    GLdouble _nAngleStart = DEGREE_TO_ARCH(_law->nAngleStartRefract / 10.0);
    GLdouble  _nAngleStep = DEGREE_TO_ARCH(_law->nAngleStepRefract / 10.0);

    //***************S
    int _nDirection = 0;
    int _iAngle = (int)m_process->GetProbeAngle(m_nGroupId);
    if(_iAngle >= (int)setup_PROBE_PART_SKEW_180 )   _nDirection   =  1           ;
    //***************E

    int    _nPointQty = m_process->GetGroupPointQty(m_nGroupId);
    //int  _nBeamQty = (int)((_nAngleStop - _nAngleStart) / _nAngleStep + 1.1) ;
    int     _nBeamQty = m_process->GetGroupLawQty(m_nGroupId);
    int _nFrameOffset = m_process->GetTotalDataSize() ;
    int _nGroupOffset = m_process->GetGroupDataOffset(m_nGroupId);
    int     _nLawSize = _nPointQty + 32;

    float* _pExitPoint = m_process->GetBeamInsertPos(m_nGroupId) ;
    float  _fStart, _fStop;
    m_process->GetSScanHorizentalRange(m_nGroupId , &_fStart , &_fStop) ;
    GLdouble _fExitOff[256];
    if(_nDirection)  {
        GLdouble _fOff = fabs(_pExitPoint[0]) - _fStop;
        for(int i = 0; i < _nBeamQty; i++) {
            _fExitOff[i] =  fabs(_pExitPoint[i]) - _fOff;
        }
    } else {
        GLdouble _fOff = _pExitPoint[0] - _fStart;
        for(int i = 0; i < _nBeamQty; i++) {
            _fExitOff[i] =  _pExitPoint[i] - _fOff;
        }
    }

    GLdouble  _fSamStart = _group.fSampleStart;
    GLdouble  _fSamRange = _group.fSampleRange;

    //GLdouble  _fScanStart = m_pConfig->common.scanner.fScanStart;
    GLdouble  _fScanStep = m_pConfig->common.scanner.fScanStep;

//	ParameterProcess* _process = ParameterProcess::Instance();
//	int _nScanMax = _process->GetScanMax();

    GLdouble _nAngles[256];
    GLdouble _fSin[256];
    GLdouble _fCos[256];
    for(int i = 0 ; i < _nBeamQty ; i++)
    {
        _nAngles[i] = _nAngleStart + i * _nAngleStep ;
        _fSin[i] = sin((double)_nAngles[i]);
        _fCos[i] = cos((double)_nAngles[i]);
    }

    WDATA* _pData  = m_process->GetShadowDataPointer();// + _nGroupOffset;
    if(!_pData) return ;
    _pData += _nGroupOffset;
	U8* _pMarker = m_process->GetScanMarker(m_nGroupId)  ;

    GLdouble _fS, _fx, _fy, _fz1, _fz2;
    WDATA* _pData1;
    int i, n, k, _iData;
    U8* _pColor;
    GLPOINT _pt1[4];
    //glColor3f(1.0f, 1.0f, 1.0f);
    //for(k = 0; k < _nScanMax - 1; k++)
    for(k = 0; k < 1; k++)
    {
        if(_pMarker[k])
        {
            _pData1 = _pData;
            _fz1 = m_fScale * k * _fScanStep;
            _fz2 = m_fScale * (k + 1) * _fScanStep;
            for(n = 0 ; n < _nBeamQty ; n++)
            {
                for(i = 0; i < _nPointQty; i++)
                {
                    _iData = m_process->correctionPdata(_pData1[i]);
                    if( _iData > 255) _iData = 255;
                    //if(_iData > PEAK_CLIP)
                    {
                        _fS = _fSamStart + i * _fSamRange / _nPointQty;
                        if(_nDirection)  {
                            _fx = m_fScale * (_fExitOff[n] - _fS * _fSin[n]);
                        } else {
                            _fx = m_fScale * (_fExitOff[n] + _fS * _fSin[n]);
                        }
                        //_fy = m_fScale * (_fS * _fCos[n] + y0_);
                        _fy = m_fScale * (GetDepth(_fS * _fCos[n], m_fHeight)  + y0_);

                        _pColor = (m_pColor + 3 * _iData);
                        glColor3f((float)_pColor[0] / 255.0, (float)_pColor[1] / 255.0, (float)_pColor[2] / 255.0);
                        InitGLPoint(_pt1, 2);
                        _pt1[0].x += _fx; _pt1[0].y += _fy; _pt1[0].z += _fz1;
                        _pt1[1].x += _fx; _pt1[1].y += _fy; _pt1[1].z += _fz2;
                        GLDraw1(_pt1, GL_LINE_STRIP, 2);
                    }
                }
                _pData1 += _nLawSize;
            }
        }
        _pData +=_nFrameOffset;
    }
}

void Doppler3DAll::drawDefectLiner(GLdouble y0_)
{
    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId] ;
    LAW_CONFIG* _law = m_process->GetLawConfig(m_nGroupId);

    GLdouble _nAngleStart = DEGREE_TO_ARCH(_law->nAngleStartRefract / 10.0);

    //***************S
    int _nDirection = 0;
    int _iAngle = (int)m_process->GetProbeAngle(m_nGroupId);
    if(_iAngle >= (int)setup_PROBE_PART_SKEW_180 )   _nDirection   =  1           ;
    //***************E

    int    _nPointQty = m_process->GetGroupPointQty(m_nGroupId);
    //int  _nBeamQty = (int)((_nAngleStop - _nAngleStart) / _nAngleStep + 1.1) ;
    int     _nBeamQty = m_process->GetGroupLawQty(m_nGroupId);
    int _nFrameOffset = m_process->GetTotalDataSize() ;
    int _nGroupOffset = m_process->GetGroupDataOffset(m_nGroupId);
    int     _nLawSize = _nPointQty + 32;

    float* _pExitPoint = m_process->GetBeamInsertPos(m_nGroupId) ;
    float  _fStart, _fStop;
    m_process->GetSScanHorizentalRange(m_nGroupId , &_fStart , &_fStop) ;
    GLdouble _fExitOff[256];
    if(_nDirection)  {
        GLdouble _fOff = fabs(_pExitPoint[0]) - _fStop;
        for(int i = 0; i < _nBeamQty; i++) {
            _fExitOff[i] =  fabs(_pExitPoint[i]) - _fOff;
        }
    } else {
        GLdouble _fOff = _pExitPoint[0] - _fStart;
        for(int i = 0; i < _nBeamQty; i++) {
            _fExitOff[i] =  _pExitPoint[i] - _fOff;
        }
    }

    GLdouble  _fSamStart = _group.fSampleStart;
    GLdouble  _fSamRange = _group.fSampleRange;

    //GLdouble  _fScanStart = m_pConfig->common.scanner.fScanStart;
    GLdouble  _fScanStep = m_pConfig->common.scanner.fScanStep;

//	ParameterProcess* _process = ParameterProcess::Instance();
//	int _nScanMax = _process->GetScanMax();

    WDATA* _pData  = m_process->GetShadowDataPointer();// + _nGroupOffset;
    if(!_pData) return ;
    _pData += _nGroupOffset;
	U8* _pMarker = m_process->GetScanMarker(m_nGroupId)  ;

    GLdouble _fSin = sin(_nAngleStart);
    GLdouble _fCos = cos(_nAngleStart);
    GLdouble _fS, _fx, _fy, _fz1, _fz2;

    WDATA* _pData1;
    int i, n, k, _iData;
    U8* _pColor;
    GLPOINT _pt1[4];
    //glColor3f(1.0f, 1.0f, 1.0f);
    //for(k = 0; k < _nScanMax - 1; k++)
    for(k = 0; k < 1; k++)
    {
        if(_pMarker[k])
        {
            _pData1 = _pData;
            _fz1 = m_fScale * k * _fScanStep;
            _fz2 = m_fScale * (k + 1) * _fScanStep;
            for(n = 0 ; n < _nBeamQty ; n++)
            {
                for(i = 0; i < _nPointQty; i++)
                {
                    _iData = m_process->correctionPdata(_pData1[i]);
                    if(_iData > 255) _iData = 255;
                    //if(_iData > PEAK_CLIP)
                    {
                        _fS = _fSamStart + i * _fSamRange / _nPointQty;
                        if(_nDirection)  {
                            _fx = m_fScale * (_fExitOff[n] - _fS * _fSin);
                        } else {
                            _fx = m_fScale * (_fExitOff[n] + _fS * _fSin);
                        }
                        //_fy = m_fScale * (_fS * _fCos[n] + y0_);
                        _fy = m_fScale * (GetDepth(_fS * _fCos, m_fHeight)  + y0_);

                        _pColor = (m_pColor + 3 * _iData);
                        glColor3f((float)_pColor[0] / 255.0, (float)_pColor[1] / 255.0, (float)_pColor[2] / 255.0);
                        InitGLPoint(_pt1, 2);
                        _pt1[0].x += _fx; _pt1[0].y += _fy; _pt1[0].z += _fz1;
                        _pt1[1].x += _fx; _pt1[1].y += _fy; _pt1[1].z += _fz2;
                        GLDraw1(_pt1, GL_LINE_STRIP, 2);
                    }
                }
                _pData1 += _nLawSize;
            }
        }
        _pData +=_nFrameOffset;
    }
}

void Doppler3DAll::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        memset(&m_ptOrigin, 0x00, sizeof(GLPOINT));
        xRot = 180.0f;
        yRot = 0.0f;
        zRot = 0.0f;
        zTra = -20.0f;
    }
    else if (event->key() == Qt::Key_Left)
    {
        yRot -= 1.0f;
    }
    else if (event->key() == Qt::Key_Right)
    {
        yRot += 1.0f;
    }
    else if (event->key() == Qt::Key_Down)
    {
        xRot += 1.0f;
    }
    else if (event->key() == Qt::Key_Up)
    {
        xRot -= 1.0f;
    }
    else if (event->key() == Qt::Key_PageDown)
    {
        //zTra -= 1.0f;
        m_ptOrigin.z -= 1.0;
    }
    else if (event->key() == Qt::Key_PageUp)
    {
        //zTra += 1.0f;
        m_ptOrigin.z += 1.0;
    }

    updateGL();
}

void Doppler3DAll::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void Doppler3DAll::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        xRot += (GLfloat)dy;
        yRot += (GLfloat)dx;
        updateGL();
    }
    else if (event->buttons() & Qt::RightButton)
    {
        xRot += (GLfloat)dy;
        zRot += (GLfloat)dx;
        updateGL();
    }

    lastPos = event->pos();
}

void Doppler3DAll::wheelEvent(QWheelEvent *event)
{
    event->delta() > 0 ? m_ptOrigin.z += 1.0f : m_ptOrigin.z -= 1.0f;
    updateGL();
}

void Doppler3DAll::advanceGL()
{
    updateGL();
}


void GLDraw1(GLPOINT* pt_, GLenum glemum_, int iDot_)
{
    glBegin(glemum_);
    for(int i = 0; i < iDot_; i++)
    {
        glVertex3f(pt_[i].x, pt_[i].y, pt_[i].z);
    }
    glEnd();
}

void GLDraw2(GLPOINT* pt1_, GLPOINT* pt2_, int iDot_)
{
    glBegin(GL_LINES);
    for(int i = 0; i < iDot_; i++)
    {
        glVertex3f(pt1_[i].x, pt1_[i].y, pt1_[i].z);
        glVertex3f(pt2_[i].x, pt2_[i].y, pt2_[i].z);
    }
    glEnd();
}

void GLDrawArc(GLPOINT cf_, GLPOINT pt1_, GLPOINT pt2_, GLdouble R_, GLdouble _sign)
{
    GLdouble _A1 = asin((pt1_.y - cf_.y) / R_);
    GLdouble _A2 = asin((pt2_.y - cf_.y) / R_);
    GLdouble _A;

    if(_A1 > _A2)
    {
        _A = _A1;
        _A1 = _A2;
        _A2 = _A;
    }

    GLdouble _fStep = DEGREE_TO_ARCH(0.1);
    int _iStep = ((_A2 - _A1) / DEGREE_TO_ARCH(0.1) + 0.5);

    GLdouble _xf = 0;
    GLdouble _yf = 0;
    glBegin(GL_LINE_STRIP);
    for(int i = 0; i < _iStep; i++)
    {
       _A = _A1 + i *  _fStep;
       _xf = cf_.x + R_*cos(_A);
       _yf = cf_.y + R_*sin(_A);
       glVertex3f(_sign * _xf, _yf, cf_.z);
    }
    glEnd();
}
