#include "ProcessDisplay.h"
#include "DopplerOverlays.h"
#include "gHeader.h"
#include "DopplerDataView.h"
#include "DopplerGateItem.h"
#include "DopplerLineItem.h"
#include "DopplerDrawAScan.h"
#include "DopplerDrawScan.h"
#include "DopplerDrawBScan.h"
#include "DopplerDrawCScan.h"
#include "DopplerDrawSScanSoundPath.h"
#include "DopplerDrawSScanTrueDepth.h"
#include "ParameterProcess.h"
#include "opengl/Doppler3DAll.h"
#include "util/GYSplitter.h"

#include <QScrollArea>
#include <QGridLayout>
#include "DopplerDrawSScanTrueDepth.h"
ProcessDisplay::ProcessDisplay(QObject *parent) :
	QObject(parent)
{
	m_pConfig  =  DopplerConfigure::Instance() ;
	m_nGroupId = 0;
}

static const int g_nSpliterWidth = 1 ;
//float srcrangestart,srcrangestop;
QSize ProcessDisplay::GetMinimumWidgetSize(int eType_)
{
	QSize _size ;
	int _nWidth , _nHeight;
	const int MINIMUM_WIDGET_WIDTH =  150 ;
	const int MINIMUM_WIDGET_HEIGHT=  150 ;

	switch(eType_)
	{
	case DISP_3D_ALL:
	case DISP_3D_PART:
	case DISP_3D_PROBE_WEDGE:
	case DISP_3D_WELD:
	case DISP_3D_SONIC_BEAMS:
        //_nWidth  = MINIMUM_WIDGET_WIDTH  ;
        //_nHeight = MINIMUM_WIDGET_HEIGHT ;
	case DISP_AH:
	case DISP_S:
		_nWidth  = MINIMUM_WIDGET_WIDTH  ;
		_nHeight = MINIMUM_WIDGET_HEIGHT ;
		break;
    case DISP_AH_BV:
	case DISP_AV_BV:
	case DISP_S_AV:
		_nWidth  = MINIMUM_WIDGET_WIDTH  ;
		_nHeight = MINIMUM_WIDGET_HEIGHT * 2 + g_nSpliterWidth;
		break;
	case DISP_S_AH:
		_nWidth  = MINIMUM_WIDGET_WIDTH  * 2 + g_nSpliterWidth;
		_nHeight = MINIMUM_WIDGET_HEIGHT ;
		break;
	case DISP_S_AV_BH:
	case DISP_S_AH_BV:
	case DISP_S_AV_CH:
	case DISP_S_AH_CV:
    case DISP_S_AV_CH_N:
		_nWidth  = MINIMUM_WIDGET_WIDTH  * 2 + g_nSpliterWidth;
		_nHeight = MINIMUM_WIDGET_HEIGHT * 2 + g_nSpliterWidth;
		break;
    //case DISP_S_AH_AH_AH:
    //case DISP_S_AH_AH_AH_CH:
	case DISP_S_AV_BH_CH:
	case DISP_S_AH_BH_CH:
	case DISP_S_AH_BH_CV:
	case DISP_S_AV_CH_CH:
    case DISP_S_AV_CH_BH:
		_nWidth  = MINIMUM_WIDGET_WIDTH  * 2 + g_nSpliterWidth;
		_nHeight = MINIMUM_WIDGET_HEIGHT * 3 + g_nSpliterWidth * 2;
		break;
	case DISP_S_AV_BV:
		_nWidth  = MINIMUM_WIDGET_WIDTH  * 3 + g_nSpliterWidth * 2;
		_nHeight = MINIMUM_WIDGET_HEIGHT ;
		break;
	case DISP_S_AH_CV_CV:
	case DISP_ALLGROUP:
		_nWidth  = MINIMUM_WIDGET_WIDTH  * 3 + g_nSpliterWidth * 2;
		_nHeight = MINIMUM_WIDGET_HEIGHT * 2 + g_nSpliterWidth;
		break;
    case DISP_S_AV_BH_CHH:
        _nWidth  = MINIMUM_WIDGET_WIDTH  * 3 + g_nSpliterWidth;
        _nHeight = MINIMUM_WIDGET_HEIGHT * 3 + g_nSpliterWidth;
    case DISP_TOPCMERGECOMPARE:
        _nWidth  = MINIMUM_WIDGET_WIDTH  * 2 + g_nSpliterWidth * 1;
        _nHeight = MINIMUM_WIDGET_HEIGHT * 4 + g_nSpliterWidth * 3;
        break;
	default:
		_nWidth  = 0  ;
		_nHeight = 0 ;
		break;
	};
	_size.setWidth(_nWidth);
	_size.setHeight(_nHeight);

	return _size ;
}

void ProcessDisplay::SetCurrentGroupId(int nGroupId_)
{
    m_nGroupId = nGroupId_;
}

int ProcessDisplay::CreateViews(QWidget* parent_, int eType_)
{
	int ret = 0 ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->InitScanOff(m_nGroupId);
    _process->SetupCurrentLawCursor(m_nGroupId , 0) ;
	switch(eType_)
	{
	case DISP_3D_ALL:
		CreateViews2(parent_);
		break;
	case DISP_3D_PART:
	case DISP_3D_PROBE_WEDGE:
	case DISP_3D_WELD:
	case DISP_3D_SONIC_BEAMS:
		break;
	case DISP_AH:				ret = CreateViews_AH(parent_);				break;
    case DISP_AH_BV:			ret = CreateViews_AH_BV(parent_);			break;
	case DISP_AV_BV:			ret = CreateViews_AV_BV(parent_);			break;
	case DISP_S:				ret = CreateViews_S(parent_);				break;
	case DISP_S_AH:				ret = CreateViews_S_AH(parent_);			break;
	case DISP_S_AV:				ret = CreateViews_S_AV(parent_);			break;
    //case DISP_S_AH_AH_AH:		ret = CreateViews_S_AH_AH_AH(parent_);		break;
    //case DISP_S_AH_AH_AH_CH:	ret = CreateViews_S_AH_AH_AH_CH(parent_);	break;
	case DISP_S_AV_BV:			ret = CreateViews_S_AV_BV(parent_);			break;
	case DISP_S_AV_BH:			ret = CreateViews_S_AV_BH(parent_);			break;
	case DISP_S_AH_BV:			ret = CreateViews_S_AH_BV(parent_);			break;
	case DISP_S_AV_BH_CH:		ret = CreateViews_S_AV_BH_CH(parent_);		break;
	case DISP_S_AH_BH_CH:		ret = CreateViews_S_AH_BH_CH(parent_);		break;
	case DISP_S_AH_BH_CV:		ret = CreateViews_S_AH_BH_CV(parent_);		break;
	case DISP_S_AV_CH:			ret = CreateViews_S_AV_CH(parent_);			break;
	case DISP_S_AH_CV:			ret = CreateViews_S_AH_CV(parent_);			break;
	case DISP_S_AV_CH_CH:		ret = CreateViews_S_AV_CH_CH(parent_);		break;
	case DISP_S_AH_CV_CV:		ret = CreateViews_S_AH_CV_CV(parent_);		break;
    case DISP_S_AV_CH_BH:       ret = CreateViews_S_AV_CH_BH(parent_);		break;
    case DISP_S_AV_CH_N:        ret = CreateViews_S_AV_CH_N(parent_);		break;
    case DISP_S_AV_BH_CHH:      ret = CreateViews_S_AV_BH_CHH(parent_);		break;
	case DISP_ALLGROUP:
		{
			DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
			int _nGroupQty = _pConfig->common.nGroupQty  ;
			for(int i = 0; i < _nGroupQty; i++) {
				_process->InitScanOff(i);
			}
			ret = CreateViews_AllGroups(parent_);
		}
		break;
    case DISP_TOPCMERGECOMPARE: ret = CreateViews_TOPCCompare(parent_);    break;
	default:
		break;
	}
	return ret;
}

int ProcessDisplay::CreateViews2(QWidget* pWidget_)
{
    Doppler3DAll* glWidget = new Doppler3DAll(m_nGroupId, pWidget_);

	QScrollArea* glWidgetArea;
	glWidgetArea = new QScrollArea;

	glWidgetArea->setWidget(glWidget);
	glWidgetArea->setWidgetResizable(true);
	glWidgetArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	glWidgetArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	glWidgetArea->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	glWidgetArea->setMinimumSize(50, 50);

	QGridLayout *centralLayout = new QGridLayout;
	centralLayout->addWidget(glWidgetArea, 0, 0);
	//------------------------------------------------
	DopplerDataView* _pView = new DopplerDataView(pWidget_);
	_pView->setEnabled(false);

	QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
	_pList->append(_pView);
	SetViewPara(_pView , m_nGroupId , 0 , setup_DISPLAY_MODE_A_H) ;
	_pView->hide();
	//------------------------------------------------
    //glWidget->SetGroupId(m_nGroupId);
	pWidget_->setLayout(centralLayout);

	return 0;
}
//A SCAN
int ProcessDisplay::CreateViews_AH(QWidget* pWidget_)
{
	QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight);
	_layout->setMargin(0);
	GYSplitter* split = new GYSplitter(0);
	DopplerDataView* _pView = new DopplerDataView(pWidget_);
	split->addWidget(_pView);
	_pView->SetLawIdentify(0);
	_layout->addWidget(split);
	pWidget_->setLayout(_layout);
	split->show();
	SetViewPara(_pView , m_nGroupId , 0 , setup_DISPLAY_MODE_A_H) ;

	QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
	_pList->append(_pView);


	//**************  transfer item move signal to main window
    ConnectSlots(_pView) ;
	return 0;
}

// A-B SCAN
int ProcessDisplay::CreateViews_AH_BV(QWidget* pWidget_)
{
	QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
	_layout->setMargin(0);
	GYSplitter* split = new GYSplitter(0);
	split->setOrientation(Qt::Vertical);
	split->setHandleWidth(g_nSpliterWidth);
	split->setOpaqueResize(false);

	DopplerDataView* _pView[2] ;
	_pView[0] = new DopplerDataView(pWidget_);
	_pView[1] = new DopplerDataView(pWidget_);

	split->addWidget(_pView[0]) ;
	split->addWidget(_pView[1]) ;

	//**************  set window sizes
    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId];

	int _nHeight = pWidget_->width() ;
	QList<int> _size ;
    if (!_group.displaySize[setup_DISPLAY_MODE_A_H].isNull() && !_group.displaySize[setup_DISPLAY_MODE_B_V].isNull()) {
        int h  = pWidget_->height() ;
        int AH = _group.displaySize[setup_DISPLAY_MODE_A_H].height();
        int BV = _group.displaySize[setup_DISPLAY_MODE_B_V].height();
        if ((AH + BV) > h) {
            _size.append(AH * h / (AH + BV));
            _size.append(AH * h / (AH + BV) - g_nSpliterWidth);
        } else {
            _size.append(AH);
            _size.append(BV);
        }
    } else {
        _size.append(_nHeight / 3);
        _size.append(_nHeight - _nHeight / 3 - g_nSpliterWidth);
    }
	split->setSizes(_size);
	_layout->addWidget(split);
	pWidget_->setLayout(_layout);
	//**************  set window sizes
	split->setCollapsible(0 , false);
	split->setCollapsible(1 , false);
	split->show();

	_pView[0]->SetLawIdentify(0);
	_pView[1]->SetLawIdentify(0);
	SetViewPara(_pView[0] , m_nGroupId , 0 , setup_DISPLAY_MODE_A_H) ;
    SetViewPara(_pView[1] , m_nGroupId , 0 , setup_DISPLAY_MODE_B_V) ;

	QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
	_pList->append(_pView[0]);
	_pList->append(_pView[1]);

	//**************  transfer item move signal to main window
	ConnectSingals(_pView , 2) ;

	return 0;
}

int ProcessDisplay::CreateViews_AV_BV(QWidget* pWidget_)
{
	QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
	_layout->setMargin(0);
	GYSplitter* split = new GYSplitter(0);
	split->setOrientation(Qt::Horizontal);
	split->setHandleWidth(g_nSpliterWidth);
	split->setOpaqueResize(false);

	DopplerDataView* _pView[2] ;
	_pView[0] = new DopplerDataView(pWidget_);
	_pView[1] = new DopplerDataView(pWidget_);

	split->addWidget(_pView[0]) ;
	split->addWidget(_pView[1]) ;

	//**************  set window sizes
    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId];

	int _nWidth = pWidget_->width() ;
	QList<int> _size ;
    if (!_group.displaySize[setup_DISPLAY_MODE_A_V].isNull() && !_group.displaySize[setup_DISPLAY_MODE_B_V].isNull()) {
        int AV = _group.displaySize[setup_DISPLAY_MODE_A_V].width();
        int BV = _group.displaySize[setup_DISPLAY_MODE_B_V].width();
        if ((AV + BV) > _nWidth) {
            _size.append(AV * _nWidth / (AV + BV));
            _size.append(AV * _nWidth / (AV + BV) - g_nSpliterWidth);
        } else {
            _size.append(AV);
            _size.append(BV);
        }
    } else {
        _size.append(_nWidth / 3);
        _size.append(_nWidth - _nWidth / 3 - g_nSpliterWidth);
    }
	split->setSizes(_size);
	_layout->addWidget(split);
	pWidget_->setLayout(_layout);
	//**************  set window sizes
	split->setCollapsible(0 , false);
	split->setCollapsible(1 , false);
	split->show();

	_pView[0]->SetLawIdentify(0);
	_pView[1]->SetLawIdentify(0);
	SetViewPara(_pView[0] , m_nGroupId , 0 , setup_DISPLAY_MODE_A_V) ;
	SetViewPara(_pView[1] , m_nGroupId , 0 , setup_DISPLAY_MODE_B_V) ;

	QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
	_pList->append(_pView[0]);
	_pList->append(_pView[1]);

	//**************  transfer item move signal to main window
	ConnectSingals(_pView , 2) ;

	return 0;
}

// PA SCAN
int ProcessDisplay::CreateViews_S(QWidget* pWidget_)
{
    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId];
	QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
	_layout->setMargin(0);
	GYSplitter* split = new GYSplitter(0);
    DopplerDataView* _pView;
    if( _group.coupleMonitoringState)
    {
        _pView = new DopplerDataView(pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLES);
    }
    else
    {
        _pView = new DopplerDataView(pWidget_);
    }

	split->addWidget(_pView);
	_layout->addWidget(split);
	pWidget_->setLayout(_layout);
	split->show();
	_pView->SetLawIdentify(0);
	SetViewPara(_pView , m_nGroupId , 0 , setup_DISPLAY_MODE_S) ;

	QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
	_pList->append(_pView);
	//**************  transfer item move signal to main window
    ConnectSlots(_pView) ;
	return 0;
}
// PA-A SCAN
int ProcessDisplay::CreateViews_S_AH(QWidget* pWidget_)
{
    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId];
	QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
	_layout->setMargin(0);
	GYSplitter* split = new GYSplitter(0);
	split->setOrientation(Qt::Vertical);
	split->setHandleWidth(g_nSpliterWidth);
	split->setOpaqueResize(false) ;

	DopplerDataView* _pView[2] ;
    if( _group.coupleMonitoringState)
    {
        _pView[0] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLES);
    }
    else
    {
        _pView[0] = new DopplerDataView( pWidget_);
    }

	_pView[1] = new DopplerDataView(pWidget_);

	split->addWidget(_pView[0]);
	split->addWidget(_pView[1]);
	//**************  set window sizes
	int _nHeight = pWidget_->height() ;
	int _nHeightMin = _pView[0]->minimumHeight() ;
	QList<int> _size ;

    setup_DISPLAY_MODE _eType ;
    if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH)
    {
        if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
            _eType = setup_DISPLAY_MODE_S_ATHUMIZ  ;
        else
            _eType = setup_DISPLAY_MODE_S_LINEAR  ;
    }
    else
        _eType = setup_DISPLAY_MODE_S_SOUNDPATH ;

    if (!_group.displaySize[_eType].isNull() && !_group.displaySize[setup_DISPLAY_MODE_A_H].isNull()) {
        int SH = _group.displaySize[_eType].height();
        int AH = _group.displaySize[setup_DISPLAY_MODE_A_H].height();
        if ((SH + AH) > _nHeight) {
            _size.append(SH * _nHeight / (SH + AH) - g_nSpliterWidth);
            _size.append(AH * _nHeight / (SH + AH));
        } else {
            _size.append(SH);
            _size.append(AH);
        }
    } else {
        if(_nHeight > 3 * _nHeightMin)
        {
            _size.append(_nHeight- _nHeight /3 - g_nSpliterWidth);
            _size.append(_nHeight / 3);
        }
        else
        {
            _size.append(_nHeight- _nHeightMin - g_nSpliterWidth);
            _size.append(_nHeightMin );
        }
    }
	split->setSizes(_size);
	_layout->addWidget(split);
	pWidget_->setLayout(_layout);
	//**************  set window sizes

	_pView[0]->SetLawIdentify(0);
	_pView[1]->SetLawIdentify(0);
	SetViewPara(_pView[0] , m_nGroupId , 0 , setup_DISPLAY_MODE_S) ;
	SetViewPara(_pView[1] , m_nGroupId , 0 , setup_DISPLAY_MODE_A_H) ;

	split->setCollapsible(0 , false);
	split->setCollapsible(1 , false);
	split->show();
	QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
    _pList->append(_pView[0]);
	_pList->append(_pView[1]);

	//**************  transfer item move signal to main window
	ConnectSingals(_pView , 2) ;

	return 0;
}
// PA-A SCAN
int ProcessDisplay::CreateViews_S_AV(QWidget* pWidget_)
{
    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId];
	QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
	_layout->setMargin(0);
	GYSplitter* split = new GYSplitter(0);
	split->setOrientation(Qt::Horizontal);
	split->setHandleWidth(g_nSpliterWidth);
	split->setOpaqueResize(false) ;

	DopplerDataView* _pView[2] ;
    if( _group.coupleMonitoringState)
    {
        _pView[0] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLES);
    }
    else
    {
        _pView[0] = new DopplerDataView(pWidget_);
    }

	_pView[1] = new DopplerDataView(pWidget_);
	split->addWidget(_pView[0]);
	split->addWidget(_pView[1]);
	//**************  set window sizes
	int _nWidth = pWidget_->width() ;
	QList<int> _size ;
    setup_DISPLAY_MODE _eType ;
    if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH)
    {
        if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
            _eType = setup_DISPLAY_MODE_S_ATHUMIZ  ;
        else
            _eType = setup_DISPLAY_MODE_S_LINEAR  ;
    }
    else
        _eType = setup_DISPLAY_MODE_S_SOUNDPATH ;

    if (!_group.displaySize[_eType].isNull() && !_group.displaySize[setup_DISPLAY_MODE_A_V].isNull()) {
        int S = _group.displaySize[_eType].width();
        int A = _group.displaySize[setup_DISPLAY_MODE_A_V].width();
        if ((S + A) > _nWidth) {
            _size.append(S * _nWidth / (S + A) - g_nSpliterWidth);
            _size.append(A * _nWidth / (S + A));
        } else {
            _size.append(S);
            _size.append(A);
        }
    } else {
        _size.append(_nWidth- _nWidth /3 - g_nSpliterWidth);
        _size.append(_nWidth / 3);
    }
	split->setSizes(_size);
	_layout->addWidget(split);
	pWidget_->setLayout(_layout);
	//**************  set window sizes
	//identify for law marker
	_pView[0]->SetLawIdentify(0);
	_pView[1]->SetLawIdentify(0);
	SetViewPara(_pView[0]  , m_nGroupId , 0 , setup_DISPLAY_MODE_S) ;
	SetViewPara(_pView[1]  , m_nGroupId , 0 , setup_DISPLAY_MODE_A_V) ;
	// set spliter move mode
	split->setCollapsible(0 , false);
	split->setCollapsible(1 , false);
	split->show();

    QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
    _pList->append(_pView[0]);
    _pList->append(_pView[1]);

	//**************  transfer item move signal to main window
    ConnectSingals(_pView, 2);
    return 0;
}
//PA-A-A-A SCAN
int ProcessDisplay::CreateViews_S_AH_AH_AH(QWidget* pWidget_)
{    
	QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
	_layout->setMargin(0);
	GYSplitter* split[2]  ;
	DopplerDataView* _pView[4] ;
	for(int i = 0 ; i< 2 ; i++)
	{
		split[i] = new GYSplitter(0);
		split[i]->setHandleWidth(g_nSpliterWidth);
		split[i]->setOpaqueResize(false) ;
	}

	split[0]->setOrientation(Qt::Horizontal);
	split[1]->setOrientation(Qt::Vertical);

    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId];
    if( _group.coupleMonitoringState)
    {
        _pView[0] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLES);
    }
    else
    {
        _pView[0] = new DopplerDataView(pWidget_);
    }
    for(int i= 1 ; i< 4 ; i++)
	{
		_pView[i] = new DopplerDataView(pWidget_) ;
	}

	split[0]->addWidget(_pView[0]);
	split[1]->addWidget(_pView[1]);
	split[1]->addWidget(_pView[2]);
	split[1]->addWidget(_pView[3]);
	split[0]->addWidget(split[1]);
	_layout->addWidget(split[0]);
	//**************  set window sizes
	int _nWidth  = pWidget_->width()  ;
	int _nHeight = pWidget_->height() ;
	QList<int> _size ;
	_size.append(_nWidth/2);
	_size.append(_nWidth - _nWidth/2 - g_nSpliterWidth);
	split[0]->setSizes(_size);
	_size.clear();
	_size.append(_nHeight / 3);
	_size.append(_nHeight / 3);
	_size.append(_nHeight - _nHeight/3 - _nHeight/3 - g_nSpliterWidth);
	split[1]->setSizes(_size);
	//**************  set window sizes
	pWidget_->setLayout(_layout);
	split[0]->setCollapsible(0 , false);
	split[0]->setCollapsible(1 , false);
	split[1]->setCollapsible(0 , false);
	split[1]->setCollapsible(1 , false);
	split[1]->setCollapsible(2 , false);
	split[0]->show();
	split[1]->show();

	_pView[0]->SetLawIdentify(2);
	_pView[1]->SetLawIdentify(0);
	_pView[2]->SetLawIdentify(1);
	_pView[3]->SetLawIdentify(2);
	SetViewPara(_pView[0] , m_nGroupId , 0 , setup_DISPLAY_MODE_S) ;
	SetViewPara(_pView[1] , m_nGroupId , 0 , setup_DISPLAY_MODE_A_H) ;
	SetViewPara(_pView[2] , m_nGroupId , 1 , setup_DISPLAY_MODE_A_H) ;
	SetViewPara(_pView[3] , m_nGroupId , 2 , setup_DISPLAY_MODE_A_H) ;

	_pView[1]->SetTitleBarStringColor(LAW_1_COLOR);
	_pView[2]->SetTitleBarStringColor(LAW_2_COLOR);
	_pView[3]->SetTitleBarStringColor(LAW_3_COLOR);

	QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
	for(int i= 0 ; i< 4 ; i++)
		_pList->append(_pView[i]);

	//**************  transfer item move signal to main window
	ConnectSingals(_pView , 4) ;

	return 0;
}
//PA-A-A-A-C SCAN
int ProcessDisplay::CreateViews_S_AH_AH_AH_CH(QWidget* pWidget_)
{
	QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
	_layout->setMargin(0);
	GYSplitter* split[3]  ;
	DopplerDataView* _pView[5] ;
	for(int i = 0 ; i< 3 ; i++)
	{
		split[i] = new GYSplitter(0);
		split[i]->setHandleWidth(g_nSpliterWidth);
		split[i]->setOpaqueResize(false) ;
	}

	split[0]->setOrientation(Qt::Horizontal);
	split[1]->setOrientation(Qt::Vertical);
	split[2]->setOrientation(Qt::Vertical);

    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId];
    if( _group.coupleMonitoringState)
    {
        _pView[0] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLES);
    }
    else
    {
        _pView[0] = new DopplerDataView(pWidget_);
    }
    for( int i= 1; i< 5; i++)
	{
		_pView[i] = new DopplerDataView(pWidget_) ;
	}

	split[1]->addWidget(_pView[0]);
	split[1]->addWidget(_pView[1]);
	split[2]->addWidget(_pView[2]);
	split[2]->addWidget(_pView[3]);
	split[2]->addWidget(_pView[4]);
	split[0]->addWidget(split[1]);
	split[0]->addWidget(split[2]);

	_layout->addWidget(split[0]);
	pWidget_->setLayout(_layout);

	//**************  set window sizes
	int _nWidth  = pWidget_->width()  ;
	int _nHeight = pWidget_->height() ;
	QList<int> _size ;
	_size.append(_nWidth/2);
	_size.append(_nWidth - _nWidth/2 - g_nSpliterWidth);
	split[0]->setSizes(_size);
	_size.clear();
	_size.append(_nHeight / 3  + _nHeight / 3 + g_nSpliterWidth);
	_size.append(_nHeight - _nHeight/3 - _nHeight/3 - g_nSpliterWidth);
	split[1]->setSizes(_size);
	_size.clear();
	_size.append(_nHeight / 3);
	_size.append(_nHeight / 3);
	_size.append(_nHeight - _nHeight/3 - _nHeight/3 - g_nSpliterWidth);
	split[2]->setSizes(_size);
	//**************  set window sizes
	split[0]->setCollapsible(0 , false);
	split[0]->setCollapsible(1 , false);
	split[1]->setCollapsible(0 , false);
	split[1]->setCollapsible(1 , false);
	split[2]->setCollapsible(0 , false);
	split[2]->setCollapsible(1 , false);
	split[2]->setCollapsible(2 , false);
	split[0]->show();
	split[1]->show();
	split[2]->show();

	_pView[0]->SetLawIdentify(2);
	_pView[1]->SetLawIdentify(0);
	_pView[2]->SetLawIdentify(0);
	_pView[3]->SetLawIdentify(1);
	_pView[4]->SetLawIdentify(2);
	SetViewPara(_pView[0] , m_nGroupId , 0 , setup_DISPLAY_MODE_S) ;
	SetViewPara(_pView[1] , m_nGroupId , 0 , setup_DISPLAY_MODE_C_H) ;
	SetViewPara(_pView[2] , m_nGroupId , 0 , setup_DISPLAY_MODE_A_H) ;
	SetViewPara(_pView[3] , m_nGroupId , 1 , setup_DISPLAY_MODE_A_H) ;
	SetViewPara(_pView[4] , m_nGroupId , 2 , setup_DISPLAY_MODE_A_H) ;

	_pView[2]->SetTitleBarStringColor(LAW_1_COLOR);
	_pView[3]->SetTitleBarStringColor(LAW_2_COLOR);
	_pView[4]->SetTitleBarStringColor(LAW_3_COLOR);

	QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
	_pList->append(_pView[0]);
	_pList->append(_pView[1]);
	_pList->append(_pView[2]);
	_pList->append(_pView[3]);
	_pList->append(_pView[4]);

	//**************  transfer item move signal to main window
	ConnectSingals(_pView , 5) ;
	return 0;
}

//PA-A-B SCAN
int ProcessDisplay::CreateViews_S_AV_BV(QWidget* pWidget_)
{
	QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
	_layout->setMargin(0);
	GYSplitter* split = new GYSplitter(0);
	split->setOrientation(Qt::Horizontal);
	split->setHandleWidth(g_nSpliterWidth);
	split->setOpaqueResize(false) ;
	DopplerDataView* _pView[3] ;

    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId];
    if( _group.coupleMonitoringState)
    {
        _pView[0] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLES);
    }
    else
    {
        _pView[0] = new DopplerDataView(pWidget_);
    }

    for(int i = 1 ; i< 3 ; i++)
    {
        _pView[i] = new DopplerDataView(pWidget_);
    }
	for(int i = 0 ; i< 3 ; i++)
	{
		split->addWidget(_pView[i]);
	}

	_layout->addWidget(split);
	pWidget_->setLayout(_layout);
	split->setCollapsible(0 , false);
	split->setCollapsible(1 , false);
	split->setCollapsible(2 , false);

	int _nWidth  = pWidget_->width()  ;
	int _nWidthMin = _pView[0]->minimumWidth() ;
	QList<int> _size ;
    setup_DISPLAY_MODE _eType ;
    if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH)
    {
        if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
            _eType = setup_DISPLAY_MODE_S_ATHUMIZ  ;
        else
            _eType = setup_DISPLAY_MODE_S_LINEAR  ;
    }
    else
        _eType = setup_DISPLAY_MODE_S_SOUNDPATH ;

    if (!_group.displaySize[_eType].isNull() && !_group.displaySize[setup_DISPLAY_MODE_A_V].isNull() && !_group.displaySize[setup_DISPLAY_MODE_B_V].isNull()) {
        int S = _group.displaySize[_eType].width();
        int A = _group.displaySize[setup_DISPLAY_MODE_A_V].width();
        int B = _group.displaySize[setup_DISPLAY_MODE_B_V].width();
        if ((S + A + B) > _nWidth) {
            _size.append(S * _nWidth / (S + A + B)  - g_nSpliterWidth * 2);
            _size.append(A * _nWidth / (S + A + B));
            _size.append(B * _nWidth / (S + A + B));
        } else {
            _size.append(S);
            _size.append(A);
            _size.append(B);
        }
    } else {
        if(_nWidth > 4 * _nWidthMin)
        {
            _size.append( _nWidth - _nWidth / 4 - _nWidth/ 4 - g_nSpliterWidth * 2);
            _size.append( _nWidth / 4);
            _size.append( _nWidth / 4);
        }
        else
        {
            _size.append( _nWidth - _nWidthMin - _nWidthMin - g_nSpliterWidth * 2);
            _size.append( _nWidthMin);
            _size.append( _nWidthMin);
        }
    }

	split->setSizes(_size);
	split->setCollapsible(0 , false);
	split->setCollapsible(1 , false);
	split->setCollapsible(2 , false);
	split->show();

	_pView[0]->SetLawIdentify(0);
	_pView[1]->SetLawIdentify(0);
	_pView[2]->SetLawIdentify(0);
	SetViewPara(_pView[0] , m_nGroupId , 0 , setup_DISPLAY_MODE_S) ;
	SetViewPara(_pView[1] , m_nGroupId , 0 , setup_DISPLAY_MODE_A_V) ;
	SetViewPara(_pView[2] , m_nGroupId , 0 , setup_DISPLAY_MODE_B_V) ;

	QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
	for(int i = 0 ; i < 3 ; i++)	_pList->append(_pView[i]);

	//**************  transfer item move signal to main window
	ConnectSingals(_pView , 3) ;

	return 0;
}

//PA-A-B SCAN
int ProcessDisplay::CreateViews_S_AV_BH(QWidget* pWidget_)
{
	QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
	_layout->setMargin(0);

    GYSplitter* split[2] = {NULL};
    DopplerDataView* _pView[3];

    for(int i = 0 ; i < 2 ; ++i)
    {
		split[i] = new GYSplitter(0);
		split[i]->setHandleWidth(g_nSpliterWidth);
        split[i]->setOpaqueResize(false);
	}

	split[0]->setOrientation(Qt::Horizontal);
	split[1]->setOrientation(Qt::Vertical);

    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId];
    if( _group.coupleMonitoringState)
    {
        _pView[0] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLES);
    }
    else
    {
        _pView[0] = new DopplerDataView(pWidget_);
    }

    for(int i= 1 ; i< 3 ; i++)
	{
		_pView[i] = new DopplerDataView(pWidget_) ;
	}

	split[1]->addWidget(_pView[0]);
	split[1]->addWidget(_pView[1]);
	split[0]->addWidget(split[1]);
	split[0]->addWidget(_pView[2]);

	_layout->addWidget(split[0]);
	pWidget_->setLayout(_layout);
	//**************  set window sizes
	int _nWidth  = pWidget_->width()  ;
	int _nHeight = pWidget_->height() ;
	QList<int> _size ;
    setup_DISPLAY_MODE _eType ;
    if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH)
    {
        if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
            _eType = setup_DISPLAY_MODE_S_ATHUMIZ  ;
        else
            _eType = setup_DISPLAY_MODE_S_LINEAR  ;
    }
    else
        _eType = setup_DISPLAY_MODE_S_SOUNDPATH ;

    if (!_group.displaySize[_eType].isNull() && !_group.displaySize[setup_DISPLAY_MODE_B_H].isNull()
            && !_group.displaySize[setup_DISPLAY_MODE_A_V].isNull()) {
        int SH = _group.displaySize[_eType].height();
        int SW = _group.displaySize[_eType].height();
        int A = _group.displaySize[setup_DISPLAY_MODE_A_V].width();
        int B = _group.displaySize[setup_DISPLAY_MODE_B_H].height();
        if ((SH + B) > _nHeight || (SW + A) > _nWidth) {
            _size.append(SH * _nHeight / (SH + B));
            _size.append(B * _nHeight / (SH + B) - g_nSpliterWidth);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(SW * _nWidth / (SW + A));
            _size.append(A * _nWidth / (SW + A) - g_nSpliterWidth);
            split[0]->setSizes(_size);
        } else {
            _size.append(SH);
            _size.append(B);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(SW);
            _size.append(A);
            split[0]->setSizes(_size);
        }
    } else {
        _size.append(_nWidth * 2/ 3);
        _size.append(_nWidth - _nWidth * 2 / 3 - g_nSpliterWidth);
        split[1]->setSizes(_size);
        _size.clear();
        _size.append(_nHeight * 2 / 3);
        _size.append(_nHeight - _nHeight * 2 / 3 - g_nSpliterWidth);
        split[0]->setSizes(_size);
    }
	//**************  set window sizes
	split[0]->setCollapsible(0 , false);
	split[0]->setCollapsible(1 , false);
	split[1]->setCollapsible(0 , false);
	split[1]->setCollapsible(1 , false);
	split[0]->show();
	split[1]->show();

	_pView[0]->SetLawIdentify(0);
	_pView[1]->SetLawIdentify(0);
	_pView[2]->SetLawIdentify(0);
	SetViewPara(_pView[0] , m_nGroupId , 0 , setup_DISPLAY_MODE_S) ;
	SetViewPara(_pView[1] , m_nGroupId , 0 , setup_DISPLAY_MODE_B_H) ;
	SetViewPara(_pView[2] , m_nGroupId , 0 , setup_DISPLAY_MODE_A_V) ;

	QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
	for(int i = 0 ; i < 3 ; i++)	_pList->append(_pView[i]);

	//**************  transfer item move signal to main window
    ConnectSingals(_pView , 3);

	return 0;
}

//PA-A-B SCAN
int ProcessDisplay::CreateViews_S_AH_BV(QWidget* pWidget_)
{
	QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
	_layout->setMargin(0);
    GYSplitter* split[2];
    DopplerDataView* _pView[3];

    for(int i = 0 ; i< 2 ; i++)
	{
		split[i] = new GYSplitter(0);
		split[i]->setHandleWidth(g_nSpliterWidth);
		split[i]->setOpaqueResize(false) ;
	}

	split[0]->setOrientation(Qt::Horizontal);
	split[1]->setOrientation(Qt::Vertical);

    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId];
    if( _group.coupleMonitoringState)
    {
        _pView[0] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLES);
    }
    else
    {
        _pView[0] = new DopplerDataView(pWidget_);
    }

    for(int i= 1 ; i< 3 ; i++)
	{
		_pView[i] = new DopplerDataView(pWidget_) ;
	}

	split[1]->addWidget(_pView[0]);
	split[1]->addWidget(_pView[1]);
	split[0]->addWidget(split[1]);
	split[0]->addWidget(_pView[2]);

	_layout->addWidget(split[0]);
	pWidget_->setLayout(_layout);
	//**************  set window sizes
	int _nWidth  = pWidget_->width()  ;
	int _nHeight = pWidget_->height() ;
	QList<int> _size ;
    setup_DISPLAY_MODE _eType ;
    if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH)
    {
        if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
            _eType = setup_DISPLAY_MODE_S_ATHUMIZ  ;
        else
            _eType = setup_DISPLAY_MODE_S_LINEAR  ;
    }
    else
        _eType = setup_DISPLAY_MODE_S_SOUNDPATH ;

    if (!_group.displaySize[_eType].isNull() && !_group.displaySize[setup_DISPLAY_MODE_A_H].isNull()
            && !_group.displaySize[setup_DISPLAY_MODE_B_V].isNull()) {
        int SW = _group.displaySize[_eType].width();
        int SH = _group.displaySize[_eType].height();
        int A = _group.displaySize[setup_DISPLAY_MODE_A_H].height();
        int B = _group.displaySize[setup_DISPLAY_MODE_B_V].width();
        if ((SH + A) > _nHeight || (SW + B) > _nWidth) {
            _size.append(SH * _nHeight / (SH + A));
            _size.append(A * _nHeight / (SH + A) - g_nSpliterWidth);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(SW * _nWidth / (SW + B));
            _size.append(B * _nWidth / (SW + B) - g_nSpliterWidth);
            split[0]->setSizes(_size);
        } else {
            _size.append(SH);
            _size.append(A);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(SW);
            _size.append(B);
            split[0]->setSizes(_size);
        }
    } else {
        _size.append(_nWidth * 2/ 3);
        _size.append(_nWidth - _nWidth * 2 / 3 - g_nSpliterWidth);
        split[0]->setSizes(_size);
        _size.clear();
        _size.append(_nHeight * 2 / 3);
        _size.append(_nHeight - _nHeight * 2 / 3 - g_nSpliterWidth);
        split[1]->setSizes(_size);
    }
	//**************  set window sizes
	split[0]->setCollapsible(0 , false);
	split[0]->setCollapsible(1 , false);
	split[1]->setCollapsible(0 , false);
	split[1]->setCollapsible(1 , false);
	split[0]->show();
	split[1]->show();

	_pView[0]->SetLawIdentify(0);
	_pView[1]->SetLawIdentify(0);
	_pView[2]->SetLawIdentify(0);
	SetViewPara(_pView[0] , m_nGroupId , 0 , setup_DISPLAY_MODE_S) ;
	SetViewPara(_pView[1] , m_nGroupId , 0 , setup_DISPLAY_MODE_A_H) ;
	SetViewPara(_pView[2] , m_nGroupId , 0 , setup_DISPLAY_MODE_B_V) ;

	QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
	for(int i = 0 ; i < 3 ; i++)	_pList->append(_pView[i]);

	//**************  transfer item move signal to main window
    ConnectSingals(_pView, 3) ;
	return 0;
}

//PA-A-B-C SCAN
int ProcessDisplay::CreateViews_S_AV_BH_CH(QWidget* pWidget_)
{
	QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
	_layout->setMargin(0);
    GYSplitter* split[2];
    DopplerDataView* _pView[4];

    for(int i = 0 ; i< 2 ; i++)
	{
		split[i] = new GYSplitter(0);
		split[i]->setHandleWidth(g_nSpliterWidth);
		split[i]->setOpaqueResize(false) ;
	}

	split[0]->setOrientation(Qt::Horizontal);
	split[1]->setOrientation(Qt::Vertical);

    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId];
    if( _group.coupleMonitoringState)
    {
        _pView[0] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLES);
        _pView[2] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLECH);
    }
    else
    {
        _pView[0] = new DopplerDataView(pWidget_);
        _pView[2] = new DopplerDataView(pWidget_);
    }

    _pView[1] = new DopplerDataView(pWidget_);
    _pView[3] = new DopplerDataView(pWidget_);

	split[1]->addWidget(_pView[0]);
	split[1]->addWidget(_pView[1]);
	split[1]->addWidget(_pView[2]);
	split[0]->addWidget(split[1]);
	split[0]->addWidget(_pView[3]);

	_layout->addWidget(split[0]);
	pWidget_->setLayout(_layout);
	//**************  set window sizes
	int _nWidth  = pWidget_->width()  ;
	int _nHeight = pWidget_->height() ;
	QList<int> _size ;
    setup_DISPLAY_MODE _eType ;
    if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH)
    {
        if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
            _eType = setup_DISPLAY_MODE_S_ATHUMIZ  ;
        else
            _eType = setup_DISPLAY_MODE_S_LINEAR  ;
    }
    else
        _eType = setup_DISPLAY_MODE_S_SOUNDPATH ;

    if (!_group.displaySize[_eType].isNull() && !_group.displaySize[setup_DISPLAY_MODE_B_V].isNull()
            && !_group.displaySize[setup_DISPLAY_MODE_C_H].isNull() && !_group.displaySize[setup_DISPLAY_MODE_A_V].isNull()) {
        int SW = _group.displaySize[_eType].width();
        int SH = _group.displaySize[_eType].height();
        int A = _group.displaySize[setup_DISPLAY_MODE_A_V].width();
        int B = _group.displaySize[setup_DISPLAY_MODE_B_V].height();
        int C = _group.displaySize[setup_DISPLAY_MODE_C_H].height();
        if ((SH + B + C) > _nHeight || (SW + A) > _nWidth) {
            _size.append(SH * _nHeight / (SH + B + C));
            _size.append(B * _nHeight / (SH + B + C));
            _size.append(C * _nHeight / (SH + B + C) - g_nSpliterWidth);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(SW * _nWidth / (SW + A));
            _size.append(A * _nWidth / (SW + A) - g_nSpliterWidth);
            split[0]->setSizes(_size);
        } else {
            _size.append(SH);
            _size.append(B);
            _size.append(C);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(SW);
            _size.append(A);
            split[0]->setSizes(_size);
        }
    } else {
        _size.append(_nWidth * 2/ 3);
        _size.append(_nWidth - _nWidth * 2 / 3 - g_nSpliterWidth);
        split[0]->setSizes(_size);
        _size.clear();
        _size.append(_nHeight / 2);
        _size.append(_nHeight / 4);
        _size.append(_nHeight - _nHeight / 2 - _nHeight / 4 - g_nSpliterWidth);
        split[1]->setSizes(_size);
    }
	//**************  set window sizes
	split[0]->setCollapsible(0 , false);
	split[0]->setCollapsible(1 , false);
	split[1]->setCollapsible(0 , false);
	split[1]->setCollapsible(1 , false);
	split[1]->setCollapsible(2 , false);
	split[0]->show();
	split[1]->show();

	_pView[0]->SetLawIdentify(0);
	_pView[1]->SetLawIdentify(0);
	_pView[2]->SetLawIdentify(0);
	_pView[3]->SetLawIdentify(0);
	SetViewPara(_pView[0] , m_nGroupId , 0 , setup_DISPLAY_MODE_S) ;
    SetViewPara(_pView[1] , m_nGroupId , 0 , setup_DISPLAY_MODE_B_V) ;
	SetViewPara(_pView[2] , m_nGroupId , 0 , setup_DISPLAY_MODE_C_H) ;
	SetViewPara(_pView[3] , m_nGroupId , 0 , setup_DISPLAY_MODE_A_V) ;
    _pView[1]->setInteractionStatus(true);
    _pView[2]->setInteractionStatus(true);
    connect(_pView[1], SIGNAL(signalNotifyOtherView(QPoint,QPoint,bool)), _pView[2], SLOT(slotRespondView(QPoint,QPoint,bool)));
    connect(_pView[2], SIGNAL(signalNotifyOtherView(QPoint,QPoint,bool)), _pView[1], SLOT(slotRespondView(QPoint,QPoint,bool)));

	QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
	for(int i = 0 ; i < 4 ; i++)	_pList->append(_pView[i]);

	//**************  transfer item move signal to main window
	ConnectSingals(_pView , 4) ;
	return 0;
}

//PA-A-B-C SCAN
int ProcessDisplay::CreateViews_S_AH_BH_CH(QWidget* pWidget_)
{
	QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
	_layout->setMargin(0);
    GYSplitter* split[3];
    DopplerDataView* _pView[4];
	for(int i = 0 ; i< 3 ; i++)
	{
		split[i] = new GYSplitter(0);
		split[i]->setHandleWidth(g_nSpliterWidth);
		split[i]->setOpaqueResize(false) ;
	}

	split[0]->setOrientation(Qt::Vertical);
	split[1]->setOrientation(Qt::Horizontal);
	split[2]->setOrientation(Qt::Vertical);

    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId];
    if( _group.coupleMonitoringState)
    {
        _pView[0] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLES);
        _pView[3] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLECH);
    }
    else
    {
        _pView[0] = new DopplerDataView(pWidget_);
        _pView[3] = new DopplerDataView(pWidget_);
    }

    _pView[1] = new DopplerDataView(pWidget_);
    _pView[2] = new DopplerDataView(pWidget_);

	split[1]->addWidget(_pView[0]);
	split[2]->addWidget(_pView[1]);
	split[2]->addWidget(_pView[2]);
	split[1]->addWidget(split[2]);
	split[0]->addWidget(split[1]);
	split[0]->addWidget(_pView[3]);

	_layout->addWidget(split[0]);
	pWidget_->setLayout(_layout);
	//**************  set window sizes
	int _nWidth  = pWidget_->width()  ;
	int _nHeight = pWidget_->height() ;
	QList<int> _size ;
    setup_DISPLAY_MODE _eType ;
    if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH)
    {
        if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
            _eType = setup_DISPLAY_MODE_S_ATHUMIZ  ;
        else
            _eType = setup_DISPLAY_MODE_S_LINEAR  ;
    }
    else
        _eType = setup_DISPLAY_MODE_S_SOUNDPATH ;

    if (!_group.displaySize[_eType].isNull() && !_group.displaySize[setup_DISPLAY_MODE_A_H].isNull()
            && !_group.displaySize[setup_DISPLAY_MODE_B_H].isNull() && !_group.displaySize[setup_DISPLAY_MODE_C_H].isNull()) {
        int SW = _group.displaySize[_eType].width();
        int SH = _group.displaySize[_eType].height();
        int AH = _group.displaySize[setup_DISPLAY_MODE_A_H].height();
        //int AW = _group.displaySize[setup_DISPLAY_MODE_A_H].height();
        int BH = _group.displaySize[setup_DISPLAY_MODE_B_H].height();
        int BW = _group.displaySize[setup_DISPLAY_MODE_B_H].width();
        int C = _group.displaySize[setup_DISPLAY_MODE_C_H].height();
        if ((SH + C) > _nHeight || (SW + BW) > _nWidth) {
            _size.append(SH * _nHeight / (SH + C));
            _size.append(C * _nHeight / (SH + C) - g_nSpliterWidth);
            split[0]->setSizes(_size);
            _size.clear();
            _size.append(SW * _nWidth / (SW + BW));
            _size.append(BW * _nWidth / (SW + BW) - g_nSpliterWidth);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(AH * _nHeight / (SH + C));
            _size.append(BH * _nHeight / (SH + C) - 2 * g_nSpliterWidth);
            split[2]->setSizes(_size);
        } else {
            _size.append(SW);
            _size.append(BW);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(AH);
            _size.append(BH);
            split[2]->setSizes(_size);
            _size.clear();
            _size.append(SH);
            _size.append(C);
            split[0]->setSizes(_size);
        }
    } else {
        _size.append(_nHeight * 3 / 4);
        _size.append(_nHeight - _nHeight * 3 / 4 - g_nSpliterWidth);
        split[0]->setSizes(_size);
        _size.clear();
        _size.append(_nHeight / 4);
        _size.append(_nHeight - _nHeight / 4 - 2 * g_nSpliterWidth);
        split[2]->setSizes(_size);
        _size.clear();
        _size.append(_nWidth / 2);
        _size.append(_nWidth - _nWidth /2 -g_nSpliterWidth);
        split[1]->setSizes(_size);
    }
	//**************  set window sizes
	split[0]->setCollapsible(0 , false);
	split[0]->setCollapsible(1 , false);
	split[1]->setCollapsible(0 , false);
	split[1]->setCollapsible(1 , false);
	split[2]->setCollapsible(0 , false);
	split[2]->setCollapsible(1 , false);
	split[0]->show();
	split[1]->show();
	split[2]->show();

	SetViewPara(_pView[0] , m_nGroupId , 0 , setup_DISPLAY_MODE_S) ;
	SetViewPara(_pView[1] , m_nGroupId , 0 , setup_DISPLAY_MODE_A_H) ;
    SetViewPara(_pView[2] , m_nGroupId , 0 , setup_DISPLAY_MODE_B_H) ;
	SetViewPara(_pView[3] , m_nGroupId , 0 , setup_DISPLAY_MODE_C_H) ;
	_pView[0]->SetLawIdentify(0);
	_pView[1]->SetLawIdentify(0);
	_pView[2]->SetLawIdentify(0);
	_pView[3]->SetLawIdentify(0);

	QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
	for(int i = 0 ; i < 4 ; i++)	_pList->append(_pView[i]);

	//**************  transfer item move signal to main window
	ConnectSingals(_pView , 4) ;
	return 0;
}

//PA-A-B-C SCAN
int ProcessDisplay::CreateViews_S_AH_BH_CV(QWidget* pWidget_)
{
	QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
	_layout->setMargin(0);
    GYSplitter* split[2];
    DopplerDataView* _pView[4];
    for(int i = 0 ; i< 2 ; i++)
	{
		split[i] = new GYSplitter(0);
		split[i]->setHandleWidth(g_nSpliterWidth);
        split[i]->setOpaqueResize(false);
	}

	split[0]->setOrientation(Qt::Horizontal);
	split[1]->setOrientation(Qt::Vertical);

    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId];
    if( _group.coupleMonitoringState)
    {
        _pView[0] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLES);
        _pView[3] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLECV);
    }
    else
    {
        _pView[0] = new DopplerDataView(pWidget_);
        _pView[3] = new DopplerDataView(pWidget_);
    }

    _pView[1] = new DopplerDataView(pWidget_);
    _pView[2] = new DopplerDataView(pWidget_) ;

	split[1]->addWidget(_pView[0]);
	split[1]->addWidget(_pView[1]);
	split[1]->addWidget(_pView[2]);
	split[0]->addWidget(split[1]);
	split[0]->addWidget(_pView[3]);

	_layout->addWidget(split[0]);
	pWidget_->setLayout(_layout);
	//**************  set window sizes
	int _nWidth  = pWidget_->width()  ;
	int _nHeight = pWidget_->height() ;
	QList<int> _size ;
    setup_DISPLAY_MODE _eType ;
    if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH)
    {
        if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
            _eType = setup_DISPLAY_MODE_S_ATHUMIZ  ;
        else
            _eType = setup_DISPLAY_MODE_S_LINEAR  ;
    }
    else
        _eType = setup_DISPLAY_MODE_S_SOUNDPATH ;

    if (!_group.displaySize[_eType].isNull() && !_group.displaySize[setup_DISPLAY_MODE_A_H].isNull()
            && !_group.displaySize[setup_DISPLAY_MODE_B_H].isNull() && !_group.displaySize[setup_DISPLAY_MODE_C_V].isNull()) {
        int SW = _group.displaySize[_eType].width();
        int SH = _group.displaySize[_eType].height();
        int AH = _group.displaySize[setup_DISPLAY_MODE_A_H].height();
        int BH = _group.displaySize[setup_DISPLAY_MODE_B_H].height();
        int C = _group.displaySize[setup_DISPLAY_MODE_C_V].width();
        if ((SH + AH + BH) > _nHeight || (SW + C) > _nWidth) {
            _size.append(SH * _nHeight / (SH + AH + BH));
            _size.append(AH * _nHeight / (SH + AH + BH));
            _size.append(BH * _nHeight / (SH + AH + BH) - g_nSpliterWidth);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(SW * _nWidth / (SW + C));
            _size.append(C * _nWidth / (SW + C) - g_nSpliterWidth);
            split[0]->setSizes(_size);
        } else {
            _size.append(SH);
            _size.append(AH);
            _size.append(BH);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(SW);
            _size.append(C);
            split[0]->setSizes(_size);
        }
    } else {
        _size.append(_nWidth * 2/ 3);
        _size.append(_nWidth - _nWidth * 2 / 3 - g_nSpliterWidth);
        split[0]->setSizes(_size);
        _size.clear();
        _size.append(_nHeight / 2);
        _size.append(_nHeight / 4);
        _size.append(_nHeight - _nHeight / 2 - _nHeight / 4 - g_nSpliterWidth);
        split[1]->setSizes(_size);
    }
	//**************  set window sizes
	split[0]->setCollapsible(0 , false);
	split[0]->setCollapsible(1 , false);
	split[1]->setCollapsible(0 , false);
	split[1]->setCollapsible(1 , false);
	split[1]->setCollapsible(2 , false);
	split[0]->show();
	split[1]->show();

	_pView[0]->SetLawIdentify(0);
	_pView[1]->SetLawIdentify(0);
	_pView[2]->SetLawIdentify(0);
	_pView[3]->SetLawIdentify(0);
	SetViewPara(_pView[0] , m_nGroupId , 0 , setup_DISPLAY_MODE_S) ;
	SetViewPara(_pView[1] , m_nGroupId , 0 , setup_DISPLAY_MODE_A_H) ;
	SetViewPara(_pView[2] , m_nGroupId , 0 , setup_DISPLAY_MODE_B_H) ;
	SetViewPara(_pView[3] , m_nGroupId , 0 , setup_DISPLAY_MODE_C_V) ;

	QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
	for(int i = 0 ; i < 4 ; i++)	_pList->append(_pView[i]);

	//**************  transfer item move signal to main window
	ConnectSingals(_pView , 4) ;
	return 0;
}

//PA-A-C SCAN
int ProcessDisplay::CreateViews_S_AV_CH(QWidget* pWidget_)
{
	QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
	_layout->setMargin(0);
    GYSplitter* split[2];
    DopplerDataView* _pView[3];
    for(int i = 0 ; i< 2 ; i++)
	{
		split[i] = new GYSplitter(0);
		split[i]->setHandleWidth(g_nSpliterWidth);
		split[i]->setOpaqueResize(false) ;
	}

	split[0]->setOrientation(Qt::Horizontal);
	split[1]->setOrientation(Qt::Vertical);

    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId];
    if( _group.coupleMonitoringState)
    {
        _pView[0] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLES);
        _pView[1] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLECH);
    }
    else
    {
        _pView[0] = new DopplerDataView(pWidget_);
        _pView[1] = new DopplerDataView(pWidget_);
    }

    _pView[2] = new DopplerDataView(pWidget_);

	split[1]->addWidget(_pView[0]);
	split[1]->addWidget(_pView[1]);
	split[0]->addWidget(split[1]);
	split[0]->addWidget(_pView[2]);

	_layout->addWidget(split[0]);
	pWidget_->setLayout(_layout);
	//**************  set window sizes
	int _nWidth  = pWidget_->width()  ;
	int _nHeight = pWidget_->height() ;
	QList<int> _size ;
    setup_DISPLAY_MODE _eType ;
    if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH)
    {
        if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
            _eType = setup_DISPLAY_MODE_S_ATHUMIZ  ;
        else
            _eType = setup_DISPLAY_MODE_S_LINEAR  ;
    }
    else
        _eType = setup_DISPLAY_MODE_S_SOUNDPATH ;

    if (!_group.displaySize[_eType].isNull() && !_group.displaySize[setup_DISPLAY_MODE_C_H].isNull()
            && !_group.displaySize[setup_DISPLAY_MODE_A_V].isNull()) {
        int SW = _group.displaySize[_eType].width();
        int SH = _group.displaySize[_eType].height();
        int AW = _group.displaySize[setup_DISPLAY_MODE_A_V].width();
        int C = _group.displaySize[setup_DISPLAY_MODE_C_H].height();
        if ((SH + C) > _nHeight || (SW + AW) > _nWidth) {
            _size.append(SH * _nHeight / (SH + C));
            _size.append(C * _nHeight / (SH + C) - g_nSpliterWidth);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(SW * _nWidth / (SW + AW));
            _size.append(AW * _nWidth / (SW + AW) - g_nSpliterWidth);
            split[0]->setSizes(_size);
        } else {
            _size.append(SH);
            _size.append(C);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(SW);
            _size.append(AW);
            split[0]->setSizes(_size);
        }
    } else {
        _size.append(_nWidth * 2/ 3);
        _size.append(_nWidth - _nWidth * 2 / 3 - g_nSpliterWidth);
        split[1]->setSizes(_size);
        _size.clear();
        _size.append(_nHeight * 2 / 3);
        _size.append(_nHeight - _nHeight * 2 / 3 - g_nSpliterWidth);
        split[0]->setSizes(_size);
    }
	//**************  set window sizes
	split[0]->setCollapsible(0 , false);
	split[0]->setCollapsible(1 , false);
	split[1]->setCollapsible(0 , false);
	split[1]->setCollapsible(1 , false);
	split[0]->show();
	split[1]->show();

	_pView[0]->SetLawIdentify(0);
	_pView[1]->SetLawIdentify(0);
	_pView[2]->SetLawIdentify(0);
	SetViewPara(_pView[0] , m_nGroupId , 0 , setup_DISPLAY_MODE_S) ;
	SetViewPara(_pView[1] , m_nGroupId , 0 , setup_DISPLAY_MODE_C_H) ;
	SetViewPara(_pView[2] , m_nGroupId , 0 , setup_DISPLAY_MODE_A_V) ;

	QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
	for(int i = 0 ; i < 3 ; i++)	_pList->append(_pView[i]);

	//**************  transfer item move signal to main window
	ConnectSingals(_pView , 3) ;
	return 0;
}

//PA-A-C SCAN
int ProcessDisplay::CreateViews_S_AH_CV(QWidget* pWidget_)
{
	QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
	_layout->setMargin(0);
    GYSplitter* split[2];
    DopplerDataView* _pView[3];

    for(int i = 0; i < 2; i++)
	{
		split[i] = new GYSplitter(0);
		split[i]->setHandleWidth(g_nSpliterWidth);
		split[i]->setOpaqueResize(false) ;
	}

	split[0]->setOrientation(Qt::Horizontal);
	split[1]->setOrientation(Qt::Vertical);

    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId];
    if( _group.coupleMonitoringState)
    {
        _pView[0] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLES);
        _pView[2] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLECV);
    }
    else
    {
        _pView[0] = new DopplerDataView(pWidget_);
        _pView[2] = new DopplerDataView(pWidget_);
    }

    _pView[1] = new DopplerDataView(pWidget_);

	split[1]->addWidget(_pView[0]);
	split[1]->addWidget(_pView[1]);
	split[0]->addWidget(split[1]);
	split[0]->addWidget(_pView[2]);

	_layout->addWidget(split[0]);
	pWidget_->setLayout(_layout);
	//**************  set window sizes
	int _nWidth  = pWidget_->width()  ;
	int _nHeight = pWidget_->height() ;
	QList<int> _size ;
    setup_DISPLAY_MODE _eType ;
    if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH)
    {
        if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
            _eType = setup_DISPLAY_MODE_S_ATHUMIZ  ;
        else
            _eType = setup_DISPLAY_MODE_S_LINEAR  ;
    }
    else
        _eType = setup_DISPLAY_MODE_S_SOUNDPATH ;

    if (!_group.displaySize[_eType].isNull() && !_group.displaySize[setup_DISPLAY_MODE_C_V].isNull()
            && !_group.displaySize[setup_DISPLAY_MODE_A_H].isNull()) {
        int SW = _group.displaySize[_eType].width();
        int SH = _group.displaySize[_eType].height();
        int AH = _group.displaySize[setup_DISPLAY_MODE_A_H].height();
        int C = _group.displaySize[setup_DISPLAY_MODE_C_V].width();
        if ((SH + AH) > _nHeight || (SW + C) > _nWidth) {
            _size.append(SH * _nHeight / (SH + AH));
            _size.append(AH * _nHeight / (SH + AH) - g_nSpliterWidth);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(SW * _nWidth / (SW + C));
            _size.append(C * _nWidth / (SW + C) - g_nSpliterWidth);
            split[0]->setSizes(_size);
        } else {
            _size.append(SH);
            _size.append(AH);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(SW);
            _size.append(C);
            split[0]->setSizes(_size);
        }
    } else {
        _size.append(_nWidth * 2/ 3);
        _size.append(_nWidth - _nWidth * 2 / 3 - g_nSpliterWidth);
        split[1]->setSizes(_size);
        _size.clear();
        _size.append(_nHeight * 2 / 3);
        _size.append(_nHeight - _nHeight * 2 / 3 - g_nSpliterWidth);
        split[0]->setSizes(_size);
    }
	//**************  set window sizes
	split[0]->setCollapsible(0 , false);
	split[0]->setCollapsible(1 , false);
	split[1]->setCollapsible(0 , false);
	split[1]->setCollapsible(1 , false);
	split[0]->show();
	split[1]->show();

	_pView[0]->SetLawIdentify(0);
	_pView[1]->SetLawIdentify(0);
	_pView[2]->SetLawIdentify(0);
	SetViewPara(_pView[0] , m_nGroupId , 0 , setup_DISPLAY_MODE_S) ;
	SetViewPara(_pView[1] , m_nGroupId , 0 , setup_DISPLAY_MODE_A_H) ;
	SetViewPara(_pView[2] , m_nGroupId , 0 , setup_DISPLAY_MODE_C_V) ;

	QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
	for(int i = 0 ; i < 3 ; i++)	_pList->append(_pView[i]);

	//**************  transfer item move signal to main window
	ConnectSingals(_pView , 3) ;
	return 0;
}

//PA-A-C-C SCAN
int ProcessDisplay::CreateViews_S_AV_CH_CH(QWidget* pWidget_)
{
	QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
	_layout->setMargin(0);
    GYSplitter* split[2];
    DopplerDataView* _pView[4];

    for(int i = 0 ; i< 2; i++)
	{
		split[i] = new GYSplitter(0);
		split[i]->setHandleWidth(g_nSpliterWidth);
		split[i]->setOpaqueResize(false) ;
	}

	split[0]->setOrientation(Qt::Horizontal);
	split[1]->setOrientation(Qt::Vertical);

    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId];
    if( _group.coupleMonitoringState)
    {
        _pView[0] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLES);
        _pView[1] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLECH);
        _pView[2] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLECH);
    }
    else
    {
        _pView[0] = new DopplerDataView(pWidget_);
        _pView[1] = new DopplerDataView(pWidget_);
        _pView[2] = new DopplerDataView(pWidget_);
    }

    _pView[3] = new DopplerDataView(pWidget_);

	split[1]->addWidget(_pView[0]);
	split[1]->addWidget(_pView[1]);
	split[1]->addWidget(_pView[2]);
	split[0]->addWidget(split[1]);
	split[0]->addWidget(_pView[3]);

	_layout->addWidget(split[0]);
	pWidget_->setLayout(_layout);
	//**************  set window sizes
	int _nWidth  = pWidget_->width()  ;
	int _nHeight = pWidget_->height() ;
	QList<int> _size ;
    setup_DISPLAY_MODE _eType ;
    if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH)
    {
        if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
            _eType = setup_DISPLAY_MODE_S_ATHUMIZ  ;
        else
            _eType = setup_DISPLAY_MODE_S_LINEAR  ;
    }
    else
        _eType = setup_DISPLAY_MODE_S_SOUNDPATH ;

    if (!_group.displaySize[_eType].isNull() && !_group.displaySize[setup_DISPLAY_MODE_C_H].isNull()
            && !_group.displaySize[setup_DISPLAY_MODE_CC_H].isNull() && !_group.displaySize[setup_DISPLAY_MODE_A_V].isNull()) {
        int SW = _group.displaySize[_eType].width();
        int SH = _group.displaySize[_eType].height();
        int AW = _group.displaySize[setup_DISPLAY_MODE_A_V].width();
        int CH = _group.displaySize[setup_DISPLAY_MODE_C_H].height();
        int CCH = _group.displaySize[setup_DISPLAY_MODE_CC_H].height();
        if ((SH + CH + CCH) > _nHeight || (SW + AW) > _nWidth) {
            _size.append(SH * _nHeight / (SH + CH + CCH));
            _size.append(CH * _nHeight / (SH + CH + CCH));
            _size.append(CCH * _nHeight / (SH + CH + CCH) - g_nSpliterWidth);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(SW * _nWidth / (SW + AW));
            _size.append(AW * _nWidth / (SW + AW) - g_nSpliterWidth);
            split[0]->setSizes(_size);
        } else {
            _size.append(SH);
            _size.append(CH);
            _size.append(CCH);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(SW);
            _size.append(AW);
            split[0]->setSizes(_size);
        }
    } else {
        _size.append(_nWidth * 2/ 3);
        _size.append(_nWidth - _nWidth * 2 / 3 - g_nSpliterWidth);
        split[0]->setSizes(_size);
        _size.clear();
        _size.append(_nHeight / 2);
        _size.append(_nHeight / 4);
        _size.append(_nHeight - _nHeight / 2 - _nHeight / 4 - g_nSpliterWidth);
        split[1]->setSizes(_size);
    }
	//**************  set window sizes
	split[0]->setCollapsible(0 , false);
	split[0]->setCollapsible(1 , false);
	split[1]->setCollapsible(0 , false);
	split[1]->setCollapsible(1 , false);
	split[1]->setCollapsible(2 , false);
	split[0]->show();
	split[1]->show();

	_pView[0]->SetLawIdentify(0);
	_pView[1]->SetLawIdentify(0);
	_pView[2]->SetLawIdentify(0);
	_pView[3]->SetLawIdentify(0);
	SetViewPara(_pView[0] , m_nGroupId , 0 , setup_DISPLAY_MODE_S) ;
	SetViewPara(_pView[1] , m_nGroupId , 0 , setup_DISPLAY_MODE_C_H) ;
	SetViewPara(_pView[2] , m_nGroupId , 0 , setup_DISPLAY_MODE_CC_H) ;
	SetViewPara(_pView[3] , m_nGroupId , 0 , setup_DISPLAY_MODE_A_V) ;
    _pView[1]->setInteractionStatus(true);
    _pView[2]->setInteractionStatus(true);
    connect(_pView[1], SIGNAL(signalNotifyOtherView(QPoint,QPoint,bool)), _pView[2], SLOT(slotRespondView(QPoint,QPoint,bool)));
    connect(_pView[2], SIGNAL(signalNotifyOtherView(QPoint,QPoint,bool)), _pView[1], SLOT(slotRespondView(QPoint,QPoint,bool)));

	QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
	for(int i = 0 ; i < 4 ; i++)	_pList->append(_pView[i]);

	//**************  transfer item move signal to main window
	ConnectSingals(_pView , 4) ;
	return 0;
}

//PA-A-C-C SCAN
int ProcessDisplay::CreateViews_S_AH_CV_CV(QWidget* pWidget_)
{
	QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
	_layout->setMargin(0);
    GYSplitter* split[2];
    DopplerDataView* _pView[4];

    for(int i = 0; i < 2; i++)
	{
		split[i] = new GYSplitter(0);
		split[i]->setHandleWidth(g_nSpliterWidth);
		split[i]->setOpaqueResize(false) ;
	}

	split[0]->setOrientation(Qt::Horizontal);
	split[1]->setOrientation(Qt::Vertical);

    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId];
    if( _group.coupleMonitoringState)
    {
        _pView[0] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLES);
        _pView[2] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLECV);
        _pView[3] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLECV);
    }
    else
    {
        _pView[0] = new DopplerDataView(pWidget_);
        _pView[2] = new DopplerDataView(pWidget_);
        _pView[3] = new DopplerDataView(pWidget_);
    }

    _pView[1] = new DopplerDataView(pWidget_);

	split[1]->addWidget(_pView[0]);
	split[1]->addWidget(_pView[1]);
	split[0]->addWidget(split[1]);
	split[0]->addWidget(_pView[2]);
	split[0]->addWidget(_pView[3]);
	_layout->addWidget(split[0]);
	pWidget_->setLayout(_layout);
	//**************  set window sizes
	int _nWidth  = pWidget_->width()  ;
	int _nHeight = pWidget_->height() ;
	QList<int> _size ;
    setup_DISPLAY_MODE _eType ;
    if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH)
    {
        if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
            _eType = setup_DISPLAY_MODE_S_ATHUMIZ  ;
        else
            _eType = setup_DISPLAY_MODE_S_LINEAR  ;
    }
    else
        _eType = setup_DISPLAY_MODE_S_SOUNDPATH ;

    if (!_group.displaySize[_eType].isNull() && !_group.displaySize[setup_DISPLAY_MODE_A_H].isNull()
            && !_group.displaySize[setup_DISPLAY_MODE_C_V].isNull() && !_group.displaySize[setup_DISPLAY_MODE_CC_V].isNull()) {
        int SW = _group.displaySize[_eType].width();
        int SH = _group.displaySize[_eType].height();
        int AH = _group.displaySize[setup_DISPLAY_MODE_A_H].height();
        int CW = _group.displaySize[setup_DISPLAY_MODE_C_V].width();
        int CCW = _group.displaySize[setup_DISPLAY_MODE_CC_V].width();
        if ((SH + AH) > _nHeight || (SW + CW + CCW) > _nWidth) {
            _size.append(SH * _nHeight / (SH + AH));
            _size.append(AH * _nHeight / (SH + AH) - g_nSpliterWidth);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(SW * _nWidth / (SW + CW + CCW));
            _size.append(CW * _nWidth / (SW + CW + CCW));
            _size.append(CCW * _nWidth / (SW + CW + CCW) - 2 * g_nSpliterWidth);
            split[0]->setSizes(_size);
        } else {
            _size.append(SH);
            _size.append(AH);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(SW);
            _size.append(CW);
            _size.append(CCW);
            split[0]->setSizes(_size);
        }
    } else {
        _size.append(_nWidth / 2);
        _size.append(_nWidth / 4);
        _size.append(_nWidth - _nWidth / 2 - _nWidth / 4 - 2 * g_nSpliterWidth);
        split[0]->setSizes(_size);
        _size.clear();
        _size.append(_nHeight * 2 / 3);
        _size.append(_nHeight - _nHeight * 2 / 3 - g_nSpliterWidth);
        split[1]->setSizes(_size);
    }
	//**************  set window sizes
	split[0]->setCollapsible(0 , false);
	split[0]->setCollapsible(1 , false);
	split[0]->setCollapsible(2 , false);
	split[1]->setCollapsible(0 , false);
	split[1]->setCollapsible(1 , false);
	split[0]->show();
	split[1]->show();

	_pView[0]->SetLawIdentify(0);
	_pView[1]->SetLawIdentify(0);
	_pView[2]->SetLawIdentify(0);
	_pView[3]->SetLawIdentify(0);
	SetViewPara(_pView[0] , m_nGroupId , 0 , setup_DISPLAY_MODE_S) ;
	SetViewPara(_pView[1] , m_nGroupId , 0 , setup_DISPLAY_MODE_A_H) ;
	SetViewPara(_pView[2] , m_nGroupId , 0 , setup_DISPLAY_MODE_C_V) ;
	SetViewPara(_pView[3] , m_nGroupId , 0 , setup_DISPLAY_MODE_CC_V) ;
    _pView[2]->setInteractionStatus(true);
    _pView[3]->setInteractionStatus(true);
    connect(_pView[2], SIGNAL(signalNotifyOtherView(QPoint,QPoint,bool)), _pView[3], SLOT(slotRespondView(QPoint,QPoint,bool)));
    connect(_pView[3], SIGNAL(signalNotifyOtherView(QPoint,QPoint,bool)), _pView[2], SLOT(slotRespondView(QPoint,QPoint,bool)));

	QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
	for(int i = 0 ; i < 4 ; i++)	_pList->append(_pView[i]);

	//**************  transfer item move signal to main window
	ConnectSingals(_pView , 4) ;
    return 0;
}

//PA-A-C-B SCAN
int ProcessDisplay::CreateViews_S_AV_CH_BH(QWidget* pWidget_)
{
    QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
    _layout->setMargin(0);
    GYSplitter* split[2];
    DopplerDataView* _pView[4];

    for(int i = 0 ; i< 2; i++)
    {
        split[i] = new GYSplitter(0);
        split[i]->setHandleWidth(g_nSpliterWidth);
        split[i]->setOpaqueResize(false) ;
    }

    split[0]->setOrientation(Qt::Horizontal);
    split[1]->setOrientation(Qt::Vertical);

    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId];
    if( _group.coupleMonitoringState)
    {
        _pView[0] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLES);
        _pView[2] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLECH);
    }
    else
    {
        _pView[0] = new DopplerDataView(pWidget_);
        _pView[2] = new DopplerDataView(pWidget_);
    }

    _pView[1] = new DopplerDataView(pWidget_);
    _pView[3] = new DopplerDataView(pWidget_);

    split[0]->addWidget(_pView[0]);
    split[0]->addWidget(_pView[1]);
    split[1]->addWidget(split[0]);
    split[1]->addWidget(_pView[2]);
    split[1]->addWidget(_pView[3]);

    _layout->addWidget(split[1]);
    pWidget_->setLayout(_layout);
    //**************  set window sizes
    int _nWidth  = pWidget_->width()  ;
    int _nHeight = pWidget_->height() ;
    QList<int> _size ;
    setup_DISPLAY_MODE _eType ;
    if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH)
    {
        if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
            _eType = setup_DISPLAY_MODE_S_ATHUMIZ  ;
        else
            _eType = setup_DISPLAY_MODE_S_LINEAR  ;
    }
    else
        _eType = setup_DISPLAY_MODE_S_SOUNDPATH ;

    if (!_group.displaySize[_eType].isNull() && !_group.displaySize[setup_DISPLAY_MODE_A_V].isNull()
            && !_group.displaySize[setup_DISPLAY_MODE_C_H].isNull() && !_group.displaySize[setup_DISPLAY_MODE_B_V].isNull()) {
        int SW = _group.displaySize[_eType].width();
        int SH = _group.displaySize[_eType].height();
        int AW = _group.displaySize[setup_DISPLAY_MODE_A_V].width();
        int CH = _group.displaySize[setup_DISPLAY_MODE_C_H].height();
        int BH = _group.displaySize[setup_DISPLAY_MODE_B_V].height();
        if ((SH + CH + BH) > _nHeight || (SW + AW) > _nWidth) {
            _size.append(SH * _nHeight / (SH + CH + BH));
            _size.append(CH * _nHeight / (SH + CH + BH));
            _size.append(BH * _nHeight / (SH + CH + BH) - g_nSpliterWidth);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(SW * _nWidth / (SW + AW));
            _size.append(AW * _nWidth / (SW + AW - g_nSpliterWidth));
            split[0]->setSizes(_size);
        } else {
            _size.append(SW);
            _size.append(AW);
            split[0]->setSizes(_size);
            _size.clear();
            _size.append(SH);
            _size.append(CH);
            _size.append(BH);
            split[1]->setSizes(_size);
        }
    } else {
        _size.append(_nWidth * 2 / 3);
        _size.append(_nWidth - _nWidth * 2 / 3 - g_nSpliterWidth);
        split[0]->setSizes(_size);
        _size.clear();
        _size.append(_nHeight / 2);
        _size.append(_nHeight / 4);
        _size.append(_nHeight - _nHeight / 2 - _nHeight / 4 - g_nSpliterWidth);
        split[1]->setSizes(_size);
    }
    //**************  set window sizes
    split[0]->setCollapsible(0 , false);
    split[0]->setCollapsible(1 , false);
    split[1]->setCollapsible(0 , false);
    split[1]->setCollapsible(1 , false);
    split[1]->setCollapsible(2 , false);
    split[0]->show();
    split[1]->show();

    _pView[0]->SetLawIdentify(0);
    _pView[1]->SetLawIdentify(0);
    _pView[2]->SetLawIdentify(0);
    _pView[3]->SetLawIdentify(0);
    SetViewPara(_pView[0] , m_nGroupId , 0 , setup_DISPLAY_MODE_S) ;
    SetViewPara(_pView[1] , m_nGroupId , 0 , setup_DISPLAY_MODE_A_V) ;
    SetViewPara(_pView[2] , m_nGroupId , 0 , setup_DISPLAY_MODE_C_H) ;
    SetViewPara(_pView[3] , m_nGroupId , 0 , setup_DISPLAY_MODE_B_V) ;
    _pView[2]->setInteractionStatus(true);
    _pView[3]->setInteractionStatus(true);
    connect(_pView[2], SIGNAL(signalNotifyOtherView(QPoint,QPoint,bool)), _pView[3], SLOT(slotRespondView(QPoint,QPoint,bool)));
    connect(_pView[3], SIGNAL(signalNotifyOtherView(QPoint,QPoint,bool)), _pView[2], SLOT(slotRespondView(QPoint,QPoint,bool)));

    QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
    for(int i = 0 ; i < 4 ; i++)	_pList->append(_pView[i]);

    //**************  transfer item move signal to main window
    ConnectSingals(_pView , 4) ;

    return 0;
}

//PA-A-C SCAN
int ProcessDisplay::CreateViews_S_AV_CH_N(QWidget* pWidget_)
{
    QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
    _layout->setMargin(0);
    GYSplitter* split[2];
    DopplerDataView* _pView[3];
    for(int i = 0 ; i< 2 ; i++)
    {
        split[i] = new GYSplitter(0);
        split[i]->setHandleWidth(g_nSpliterWidth);
        split[i]->setOpaqueResize(false) ;
    }

    split[0]->setOrientation(Qt::Horizontal);
    split[1]->setOrientation(Qt::Vertical);

    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId];
    if( _group.coupleMonitoringState)
    {
        _pView[0] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLES);
        _pView[2] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLECH);
    }
    else
    {
        _pView[0] = new DopplerDataView(pWidget_);
        _pView[2] = new DopplerDataView(pWidget_);
    }

    _pView[1] = new DopplerDataView(pWidget_);

    split[0]->addWidget(_pView[0]);
    split[0]->addWidget(_pView[1]);
    split[1]->addWidget(split[0]);
    split[1]->addWidget(_pView[2]);

    _layout->addWidget(split[1]);
    pWidget_->setLayout(_layout);
    //**************  set window sizes
    int _nWidth  = pWidget_->width()  ;
    int _nHeight = pWidget_->height() ;
    QList<int> _size ;
    setup_DISPLAY_MODE _eType ;
    if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH)
    {
        if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
            _eType = setup_DISPLAY_MODE_S_ATHUMIZ  ;
        else
            _eType = setup_DISPLAY_MODE_S_LINEAR  ;
    }
    else
        _eType = setup_DISPLAY_MODE_S_SOUNDPATH ;

    if (!_group.displaySize[_eType].isNull() && !_group.displaySize[setup_DISPLAY_MODE_A_V].isNull()
            && !_group.displaySize[setup_DISPLAY_MODE_C_H].isNull()) {
        int SW = _group.displaySize[_eType].width();
        int SH = _group.displaySize[_eType].height();
        int AW = _group.displaySize[setup_DISPLAY_MODE_A_V].width();
        int CH = _group.displaySize[setup_DISPLAY_MODE_C_H].height();
        if ((SH + CH) > _nHeight || (SW + AW) > _nWidth) {
            _size.append(SH * _nHeight / (SH + CH));
            _size.append(CH * _nHeight / (SH + CH) - g_nSpliterWidth);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(SW * _nWidth / (SW + AW));
            _size.append(AW * _nWidth / (SW + AW - g_nSpliterWidth));
            split[0]->setSizes(_size);
        } else {
            _size.append(SW);
            _size.append(AW);
            split[0]->setSizes(_size);
            _size.clear();
            _size.append(SH);
            _size.append(CH);
            split[1]->setSizes(_size);
        }
    } else {
        _size.append(_nWidth * 2 / 3);
        _size.append(_nWidth - _nWidth * 2 / 3 - g_nSpliterWidth);
        split[0]->setSizes(_size);
        _size.clear();
        _size.append(_nHeight * 2 / 3);
        _size.append(_nHeight - _nHeight * 2 / 3 - g_nSpliterWidth);
        split[1]->setSizes(_size);
    }
    //**************  set window sizes
    split[0]->setCollapsible(0 , false);
    split[0]->setCollapsible(1 , false);
    split[1]->setCollapsible(0 , false);
    split[1]->setCollapsible(1 , false);
    split[0]->show();
    split[1]->show();

    _pView[0]->SetLawIdentify(0);
    _pView[1]->SetLawIdentify(0);
    _pView[2]->SetLawIdentify(0);
    SetViewPara(_pView[0] , m_nGroupId , 0 , setup_DISPLAY_MODE_S) ;
    SetViewPara(_pView[1] , m_nGroupId , 0 , setup_DISPLAY_MODE_A_V) ;
    SetViewPara(_pView[2] , m_nGroupId , 0 , setup_DISPLAY_MODE_C_H) ;

    QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
    for(int i = 0 ; i < 3 ; i++)	_pList->append(_pView[i]);

    //**************  transfer item move signal to main window
    ConnectSingals(_pView , 3) ;
    return 0;
}

int ProcessDisplay::CreateViews_S_AV_BH_CHH(QWidget* pWidget_)
{
    QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
    _layout->setMargin(0);
    GYSplitter* split[3];
    DopplerDataView* _pView[4];
    for(int i = 0 ; i< 3 ; i++)
    {
        split[i] = new GYSplitter(0);
        split[i]->setHandleWidth(g_nSpliterWidth);
        split[i]->setOpaqueResize(false) ;
    }

    split[0]->setOrientation(Qt::Vertical);
    split[1]->setOrientation(Qt::Horizontal);
    split[2]->setOrientation(Qt::Horizontal);

    GROUP_CONFIG& _group = m_pConfig->group[m_nGroupId];
    if( _group.coupleMonitoringState)
    {
        _pView[0] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLES);
        _pView[3] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLECH);
    }
    else
    {
        _pView[0] = new DopplerDataView(pWidget_);
        _pView[3] = new DopplerDataView(pWidget_);
    }

    _pView[1] = new DopplerDataView(pWidget_);
    _pView[2] = new DopplerDataView(pWidget_);

    split[1]->addWidget(_pView[3]);
    split[1]->addWidget(_pView[0]);
    split[2]->addWidget(_pView[2]);
    split[2]->addWidget(_pView[1]);
    split[0]->addWidget(split[1]);
    split[0]->addWidget(split[2]);

    _layout->addWidget(split[0]);
    pWidget_->setLayout(_layout);
    //**************  set window sizes
    int _nWidth  = pWidget_->width()  ;
    int _nHeight = pWidget_->height() ;
    QList<int> _size ;
    setup_DISPLAY_MODE _eType ;
    if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH)
    {
        if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
            _eType = setup_DISPLAY_MODE_S_ATHUMIZ  ;
        else
            _eType = setup_DISPLAY_MODE_S_LINEAR  ;
    }
    else
        _eType = setup_DISPLAY_MODE_S_SOUNDPATH ;

    if (!_group.displaySize[_eType].isNull() && !_group.displaySize[setup_DISPLAY_MODE_A_V].isNull()
            && !_group.displaySize[setup_DISPLAY_MODE_C_H].isNull() && !_group.displaySize[setup_DISPLAY_MODE_B_V].isNull()) {
        int SW = _group.displaySize[_eType].width();
        int SH = _group.displaySize[_eType].height();
        int AW = _group.displaySize[setup_DISPLAY_MODE_A_V].width();
        int CH = _group.displaySize[setup_DISPLAY_MODE_C_H].height();
        int CW = _group.displaySize[setup_DISPLAY_MODE_C_H].width();
        int BH = _group.displaySize[setup_DISPLAY_MODE_B_V].height();
        int BW = _group.displaySize[setup_DISPLAY_MODE_B_V].width();
        if ((CH + BH) > _nHeight || (SW + CW) > _nWidth) {
            _size.append(CH * _nHeight / (CH + BH));
            _size.append(BH * _nHeight / (CH + BH) - g_nSpliterWidth);
            split[0]->setSizes(_size);
            _size.clear();
            _size.append(CW * _nWidth / (SW + CW));
            _size.append(SW * _nWidth / (SW + CW) - g_nSpliterWidth);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(BW * _nWidth / (AW + BW));
            _size.append(AW * _nWidth / (AW + BW) - g_nSpliterWidth);
            split[2]->setSizes(_size);
        } else {
            _size.append(CW);
            _size.append(SW);
            split[1]->setSizes(_size);
            _size.clear();
            _size.append(BW);
            _size.append(AW);
            split[2]->setSizes(_size);
            _size.clear();
            _size.append(CH);
            _size.append(BH);
            split[0]->setSizes(_size);
        }
    } else {
        _size.append(_nHeight / 2);
        _size.append(_nHeight - _nHeight / 2 - g_nSpliterWidth);
        split[0]->setSizes(_size);
        _size.clear();
        _size.append(_nWidth * 2 / 3);
        _size.append(_nWidth - _nWidth  * 2 / 3 - g_nSpliterWidth);
        split[1]->setSizes(_size);
        split[2]->setSizes(_size);
    }
    //**************  set window sizes
    split[0]->setCollapsible(0 , false);
    split[0]->setCollapsible(1 , false);
    split[1]->setCollapsible(0 , false);
    split[1]->setCollapsible(1 , false);
    split[2]->setCollapsible(0 , false);
    split[2]->setCollapsible(1 , false);
    split[0]->show();
    split[1]->show();
    split[2]->show();

    SetViewPara(_pView[0] , m_nGroupId , 0 , setup_DISPLAY_MODE_S) ;
    SetViewPara(_pView[1] , m_nGroupId , 0 , setup_DISPLAY_MODE_A_V) ;
    SetViewPara(_pView[2] , m_nGroupId , 0 , setup_DISPLAY_MODE_B_V) ;
    SetViewPara(_pView[3] , m_nGroupId , 0 , setup_DISPLAY_MODE_C_H) ;
    _pView[2]->setInteractionStatus(true);
    _pView[3]->setInteractionStatus(true);
    connect(_pView[2], SIGNAL(signalNotifyOtherView(QPoint,QPoint,bool)), _pView[3], SLOT(slotRespondView(QPoint,QPoint,bool)));
    connect(_pView[3], SIGNAL(signalNotifyOtherView(QPoint,QPoint,bool)), _pView[2], SLOT(slotRespondView(QPoint,QPoint,bool)));
    _pView[0]->SetLawIdentify(0);
    _pView[1]->SetLawIdentify(0);
    _pView[2]->SetLawIdentify(0);
    _pView[3]->SetLawIdentify(0);

    QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
    for(int i = 0 ; i < 4 ; i++)	_pList->append(_pView[i]);

    //**************  transfer item move signal to main window
    ConnectSingals(_pView , 4) ;
    return 0;
}

//AllGroups
int ProcessDisplay::CreateViews_AllGroups(QWidget* pWidget_)
{
	int _nGroupQty = m_pConfig->common.nGroupQty ;
	QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();

	QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
	_layout->setMargin(0);
    GYSplitter* _splitBase;
    GYSplitter* _split[8];
    GYSplitter* _split_S_A[8];

	_splitBase = new GYSplitter(0);
	_splitBase->setHandleWidth(g_nSpliterWidth);
    _splitBase->setOpaqueResize(false);
	_splitBase->setOrientation(Qt::Horizontal);

	int _nQty = _nGroupQty;
    if(_nQty > setup_MAX_DISPLAY_QTY)	_nQty = setup_MAX_DISPLAY_QTY;
	U8* _pComDisp = m_pConfig->GetComDisplayPoint();
//	for(int i = 0; i < _nGroupQty; i++) {
//    if(_nQty <= 4){
        for(int i = 0; i < _nQty; i++) {
            _split_S_A[i] = NULL;

            _split[i] = new GYSplitter(0);
            _split[i]->setHandleWidth(g_nSpliterWidth);
            _split[i]->setOpaqueResize(false) ;
            _split[i]->setOrientation(Qt::Vertical);

            int _nGroup = _pComDisp[i];
            if(m_pConfig->group[_nGroup].eGroupMode == setup_GROUP_MODE_PA) {
                DopplerDataView* _pView[3] ;

                if( m_pConfig->group[_nGroup].coupleMonitoringState)
                {
                    _pView[0] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLECV);
                    _pView[1] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLES);
                }
                else
                {
                    _pView[0] = new DopplerDataView(pWidget_);
                    _pView[1] = new DopplerDataView(pWidget_);
                }

                _pView[2] = new DopplerDataView(pWidget_);

                _pView[0]->SetLawIdentify(0);
                _pList->append(_pView[0]);
                _pView[1]->SetLawIdentify(0);
                _pList->append(_pView[1]);
                _pView[2]->SetLawIdentify(0);
                _pList->append(_pView[2]);


                ConnectSingals(_pView , 3) ;

                _split_S_A[i] = new GYSplitter(0);
                _split_S_A[i]->setHandleWidth(g_nSpliterWidth);
                _split_S_A[i]->setOpaqueResize(false) ;
                _split_S_A[i]->setOrientation(Qt::Horizontal);

                _split[i]->addWidget(_pView[0]);
                _split[i]->addWidget(_split_S_A[i]);

                _split_S_A[i]->addWidget(_pView[1]);
                _split_S_A[i]->addWidget(_pView[2]);

                SetViewPara(_pView[0] , _nGroup , 0 , setup_DISPLAY_MODE_C_V) ;
                SetViewPara(_pView[1] , _nGroup , 0 , setup_DISPLAY_MODE_S) ;
                SetViewPara(_pView[2] , _nGroup , 0 , setup_DISPLAY_MODE_A_V) ;
            } else {
                DopplerDataView* _pView[2] ;
                for(int k = 0; k < 2; k++) {
                    _pView[k] = new DopplerDataView(pWidget_) ;
                    _pView[k]->SetLawIdentify(0);
                    _pList->append(_pView[k]);
                }
                ConnectSingals(_pView , 2) ;

                _split[i]->addWidget(_pView[0]);
                _split[i]->addWidget(_pView[1]);

                SetViewPara(_pView[0] , _nGroup , 0 , setup_DISPLAY_MODE_B_H) ;
                SetViewPara(_pView[1] , _nGroup , 0 , setup_DISPLAY_MODE_A_H) ;
            }

            _splitBase->addWidget(_split[i]);
        }

        //**************  set window sizes
        int _nWidth  = pWidget_->width()  ;
        int _nHeight = pWidget_->height() ;
        int _nW   = _nWidth / _nQty;
        int _nRes = _nWidth;
        int _nWTab[8];
        QList<int> _size ;

        int i = 0;
        for(i= 0 ; i < _nQty - 1 ; i++) {
            _nWTab[i] = _nW;
            _nRes -= _nW;
        }
        _nWTab[i] = _nRes;

        for(i = 0; i < _nQty; i++) {
            _size.append(_nWTab[i]);
        }
        _splitBase->setSizes(_size);
        //-----------------------
        _size.clear();
        _size.append(_nHeight * 2 / 3);
        _size.append(_nHeight - _nHeight * 2 / 3 - g_nSpliterWidth);

        for(int i= 0 ; i < _nQty ; i++) {
            _split[i]->setSizes(_size);
        }
        //-----------------------
        for(i = 0; i < _nQty; i++) {
            if(_split_S_A[i]) {
                _size.clear();
                _size.append(_nWTab[i] * 3 / 5);
                _size.append(_nWTab[i] - _nWTab[i] * 3 / 5 - g_nSpliterWidth);
                _split_S_A[i]->setSizes(_size);
            }
        }
        //-----------------------
        _layout->addWidget(_splitBase);
        pWidget_->setLayout(_layout);
        //**************  set window sizes
        for(i = 0 ; i < _nQty ; i++) {
            if(_split_S_A[i]) {
                _split_S_A[i]->setCollapsible(0 , false);
                _split_S_A[i]->show();
            }

            _split[i]->setCollapsible(0 , false);
            _split[i]->show();
        }
        _splitBase->setCollapsible(0 , false);
        _splitBase->show();
//    }else{
//        for(int i = 0; i < _nQty; i++){
//            int _nGroup = _pComDisp[i];
//            DopplerDataView* _pView;
//            if(m_pConfig->group[_nGroup].eGroupMode == setup_GROUP_MODE_PA){
//                if( m_pConfig->group[_nGroup].coupleMonitoringState){
//                     _pView = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLECV);
//                }else{
//                    _pView = new DopplerDataView(pWidget_);
//                }
//                _pView->SetLawIdentify(0);
//                _pList->append(_pView);
//                ConnectSingals(&_pView, 1);
//                SetViewPara( _pView, _nGroup, 0, setup_DISPLAY_MODE_C_V);
//            }else{
//                _pView = new DopplerDataView(pWidget_);
//                _pView->SetLawIdentify(0);
//                _pList->append(_pView);
//                ConnectSingals(&_pView, 1);
//                SetViewPara( _pView, _nGroup, 0, setup_DISPLAY_MODE_B_H);
//            }
//            _splitBase->addWidget(_pView);
//        }
//        //**************  set window sizes
//        int _nWidth  = pWidget_->width();
//        int _nHeight = pWidget_->height();
//        int _nW   = _nWidth / _nQty;
//        int _nRes = _nWidth;
//        int _nWTab[8];
//        QList<int> _size;

//        int i = 0;
//        for(i= 0 ; i < _nQty - 1 ; i++) {
//            _nWTab[i] = _nW;
//            _nRes -= _nW;
//        }
//        _nWTab[i] = _nRes;

//        for(i = 0; i < _nQty; i++) {
//            _size.append(_nWTab[i]);
//        }
//        _splitBase->setSizes(_size);

//        _layout->addWidget(_splitBase);
//        pWidget_->setLayout(_layout);
//        _splitBase->setCollapsible(0 , false);
//        _splitBase->show();
//    }
	return 0;
}

int ProcessDisplay::CreateViews_TOPCCompare(QWidget* pWidget_)
{
    QBoxLayout* _layout = new QBoxLayout(QBoxLayout::LeftToRight );
    _layout->setMargin(0);
    GYSplitter* split[2];
    DopplerDataView* _pView[5];

    for(int i = 0 ; i< 2; i++)
    {
        split[i] = new GYSplitter(0);
        split[i]->setHandleWidth(g_nSpliterWidth);
        split[i]->setOpaqueResize(false) ;
    }

    split[0]->setOrientation(Qt::Horizontal);
    split[1]->setOrientation(Qt::Vertical);

    int groupId1 = m_pConfig->common.TOPCMergeGroupId[0];
    int groupId2 = m_pConfig->common.TOPCMergeGroupId[1];
    GROUP_CONFIG& _group1 = m_pConfig->group[groupId1];
    GROUP_CONFIG& _group2 = m_pConfig->group[groupId2];
    if(_group1.coupleMonitoringState){
        _pView[0] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLES);
        _pView[2] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLECH);
    }else{
        _pView[0] = new DopplerDataView(pWidget_);
        _pView[2] = new DopplerDataView(pWidget_);
    }

    if(_group2.coupleMonitoringState){
        _pView[1] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLES);
        _pView[3] = new DopplerDataView( pWidget_, DopplerDataView::DATA_VIEW_COMPONENT_ALL_WITHCOUPLECH);
    }else{
        _pView[1] = new DopplerDataView(pWidget_);
        _pView[3] = new DopplerDataView(pWidget_);
    }
    _pView[4] = new DopplerDataView(pWidget_);

    split[0]->addWidget(_pView[0]);
    split[0]->addWidget(_pView[1]);
    split[1]->addWidget(split[0]);
    split[1]->addWidget(_pView[2]);
    split[1]->addWidget(_pView[3]);
    split[1]->addWidget(_pView[4]);

    _layout->addWidget(split[1]);
    pWidget_->setLayout(_layout);

    int _nWidth  = pWidget_->width();
    int _nHeight = pWidget_->height();
    QList<int> _size;
    _size.append(_nWidth / 2);
    _size.append(_nWidth / 2 - g_nSpliterWidth);
    split[0]->setSizes(_size);
    _size.clear();
    _size.append(_nHeight / 4);
    _size.append(_nHeight / 4);
    _size.append(_nHeight / 4);
    _size.append(_nHeight / 4 - g_nSpliterWidth * 3);
    split[1]->setSizes(_size);

    split[0]->setCollapsible(0 , false);
    split[0]->setCollapsible(1 , false);
    split[1]->setCollapsible(0 , false);
    split[1]->setCollapsible(1 , false);
    split[1]->setCollapsible(2 , false);
    split[1]->setCollapsible(3 , false);
    split[0]->show();
    split[1]->show();

    _pView[0]->SetLawIdentify(0);
    _pView[1]->SetLawIdentify(0);
    _pView[2]->SetLawIdentify(0);
    _pView[3]->SetLawIdentify(0);
    _pView[4]->SetLawIdentify(0);

    _pView[0]->SetCScanTopcDis( true, false);
    _pView[1]->SetCScanTopcDis( true, false);
    _pView[2]->SetCScanTopcDis( true, false);
    _pView[3]->SetCScanTopcDis( true, false);
    _pView[4]->SetCScanTopcDis( false, true);

    SetViewPara(_pView[0] , groupId1 , 0 , setup_DISPLAY_MODE_S);
    SetViewPara(_pView[1] , groupId2 , 0 , setup_DISPLAY_MODE_S);
    SetViewPara(_pView[2] , groupId1 , 0 , setup_DISPLAY_MODE_C_H);
    SetViewPara(_pView[3] , groupId2 , 0 , setup_DISPLAY_MODE_C_H);
    SetViewPara(_pView[4] , groupId1 , 0 , setup_DISPLAY_MODE_C_H);

    QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
    for(int i = 0 ; i < 5 ; i++)	_pList->append(_pView[i]);

    ConnectSingals(_pView , 5);

    return 0;
}

/****************************************************************************
  Description: 连接信号到主窗口
  Input: 【pWidget_：窗口指针】
*****************************************************************************/
void ProcessDisplay::ConnectSingals(DopplerDataView** pViews_, int nQty_)
{
	for(int i = 0 ; i < nQty_ ; i++)
	{
        ConnectSlots(pViews_[i]) ;
	}
}

void ProcessDisplay::ConnectSlots(DopplerDataView* pViews_)
{
	connect(pViews_ , SIGNAL(signalItemMoved(DopplerDataView*,DopplerGraphicsItem*)) ,
			   g_pMainWnd ,   SLOT(slotItemMoved(DopplerDataView*,DopplerGraphicsItem*))) ;

	connect(pViews_ , SIGNAL(signalDataViewResized(DopplerDataView*)) ,
			g_pMainWnd ,  SLOT(slotDataViewResized(DopplerDataView*)) /*, Qt::QueuedConnection*/) ;

    connect(pViews_ , SIGNAL(signalMouseDoubleClicked(DopplerDataView*, QPointF)),
            g_pMainWnd , SLOT(slotDataViewMouseDoubleClicked(DopplerDataView*,QPointF)));
}

/****************************************************************************
  Description: 更新指定窗口
  Input: 【pWidget_：窗口指针】
*****************************************************************************/
void ProcessDisplay::UpdateAll(DopplerDataView* pWidget_, bool flash)
{
	int _nGroupId , _nLawId , _nDisplay  ;
	pWidget_->GetDataViewConfigure(&_nGroupId , &_nLawId , &_nDisplay);
	//if( _nDisplay == setup_DISPLAY_MODE_S ||
	//	_nDisplay == setup_DISPLAY_MODE_S_SOUNDPATH ||
	//	_nDisplay == setup_DISPLAY_MODE_S_ATHUMIZ ||
	//	_nDisplay == setup_DISPLAY_MODE_S_LINEAR )
	if(_nDisplay >= setup_DISPLAY_MODE_S ) //当配置文件变化时，调用此函数更新刷图窗口，需要根据参数重新设置S扫窗口类型
	{
		setup_DISPLAY_MODE _eType ;
		GROUP_CONFIG& _group = m_pConfig->group[_nGroupId] ;
		if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH)
		{
			if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
				_eType = setup_DISPLAY_MODE_S_ATHUMIZ  ;
			else
				_eType = setup_DISPLAY_MODE_S_LINEAR  ;
		}
		else
			_eType = setup_DISPLAY_MODE_S_SOUNDPATH ;
		pWidget_->SetDataViewConfigure(_nGroupId ,  _nLawId ,  _eType);
	}
	else
	{
		pWidget_->SetDataViewConfigure(_nGroupId ,  _nLawId ,  _nDisplay);
	}
	// 刷新窗口标尺，色条和标题栏
	UpdateDataViewFrame(pWidget_);
	// 刷新窗口绘图区设置
    UpdateDataViewDraw(pWidget_, flash);
	// 刷新光标
	DopplerOverlays _overlay(pWidget_);
	_overlay.CreateOverlays();
	UpdateDataViewTitle(pWidget_);
}


void ProcessDisplay::SetViewPara(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_ , setup_DISPLAY_MODE eDisplay_)
{
	pWidget_->SetDataViewConfigure(nGroupId_ ,  nLawId_ ,  eDisplay_);
    UpdateAll(pWidget_, false);
}

int ProcessDisplay::IsSizeAvailable(int nId_, QWidget* pWidget_)
{
	QSize _size = GetMinimumWidgetSize(nId_)  ;

	if(_size.width() >= pWidget_->width())  return -1;
	if(_size.height() >= pWidget_->height()) return -1;
	return 0 ;
}

void ProcessDisplay::UpdateDataViewFrameAH(DopplerDataView* pWidget_, int nGroupId_, int nLawId_)
{
	ParameterProcess* _process = ParameterProcess::Instance();
    QString _strLeftUnit("%");
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    GROUP_CONFIG& _group = _pConfig->group[nGroupId_];
	
    bool _bRectify = (_process->GetRectifierMode(nGroupId_) == setup_RECTIFIER_RF );

	if(_bRectify)
	pWidget_->SetRulerRange( 100, -100, 100, -100, DopplerDataView::DATA_VIEW_RULER_LEFT);
	else

    pWidget_->SetRulerRange( 100, 0,  100,  0, DopplerDataView::DATA_VIEW_RULER_LEFT);
	pWidget_->SetRulerUnit (&_strLeftUnit, DopplerDataView::DATA_VIEW_RULER_LEFT );

    QString _strBottomUnit =  _process->GetSonicAxisUnit(nGroupId_);
    double _fStart = _process->GetSampleStart(nGroupId_, nLawId_);
    double _fRange = _process->GetSampleRange(nGroupId_, nLawId_);
    float pcs = _pConfig->TOFD[nGroupId_].fPCS;

	SYSTEM_ENVIRMENT& _appEvn = m_pConfig->AppEvn;
	if(_appEvn.bTrueDepth_A_S_Sync) {
		GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
		if(_group.eGroupMode == setup_GROUP_MODE_PA && _group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH) {
			float _fS, _fE;
			_process->GetSScanVerticalRange(nGroupId_ , &_fS ,  &_fE);
			_fStart = _fS;
			_fRange = _fE - _fS;
		}
	}
    if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH && _group.eGroupMode != setup_GROUP_MODE_PA){
        pWidget_->SetTofdSampleStart(_group.afCursor[setup_CURSOR_TFOD_LW], DopplerDataView::DATA_VIEW_RULER_BOTTOM);
        _process->SetTofdSampleStart(_group.afCursor[setup_CURSOR_TFOD_LW]);
        pWidget_->SetTofdDepth(true, pcs, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
    }else{
        pWidget_->SetTofdDepth(false, pcs, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
    }

    pWidget_->SetRulerRange( _fStart , _fStart + _fRange , _fStart, _fStart + _fRange, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
	pWidget_->SetRulerUnit(&_strBottomUnit , DopplerDataView::DATA_VIEW_RULER_BOTTOM );
	
	if(_bRectify)
        pWidget_->SetRulerRange(100, -100, 100, -100, DopplerDataView::DATA_VIEW_RULER_RIGHT);
	else
	//---------------------------------------------
    pWidget_->SetRulerRange(100, 0,  100, 0, DopplerDataView::DATA_VIEW_RULER_RIGHT);

    void* _pColor;
	if(setup_RECTIFIER_RF ==  _process->GetRectifierMode(nGroupId_))
        _pColor = _process->GetPalete(nGroupId_, PALETTE_RECTIFY );
	else
        _pColor = _process->GetPalete(nGroupId_, PALETTE_AMP);
	pWidget_->SetColorBarColorIndex(_pColor);
}

void ProcessDisplay::UpdateDataViewFrameAV(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_)
{
	ParameterProcess* _process = ParameterProcess::Instance();
    QString _strLeftUnit = _process->GetSonicAxisUnit(nGroupId_) ;
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    GROUP_CONFIG& _group = _pConfig->group[nGroupId_];
	double _fStart = _process->GetSampleStart(nGroupId_ , nLawId_) ;
	double _fRange = _process->GetSampleRange(nGroupId_ , nLawId_) ;
    float pcs = _pConfig->TOFD[nGroupId_].fPCS;
	//---------------
	SYSTEM_ENVIRMENT& _appEvn = m_pConfig->AppEvn;
	if(_appEvn.bTrueDepth_A_S_Sync) {
		GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
		if(_group.eGroupMode == setup_GROUP_MODE_PA && _group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH) {
			float _fS, _fE;
			_process->GetSScanVerticalRange(nGroupId_ , &_fS ,  &_fE);
			_fStart = _fS;
			_fRange = _fE - _fS;
		}
	}
	//---------------
    if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH && _group.eGroupMode != setup_GROUP_MODE_PA){
        pWidget_->SetTofdSampleStart(_group.afCursor[setup_CURSOR_TFOD_LW], DopplerDataView::DATA_VIEW_RULER_LEFT);
        _process->SetTofdSampleStart(_group.afCursor[setup_CURSOR_TFOD_LW]);
        pWidget_->SetTofdDepth(true, pcs, DopplerDataView::DATA_VIEW_RULER_LEFT);
    }else{
        pWidget_->SetTofdDepth(false, pcs, DopplerDataView::DATA_VIEW_RULER_LEFT);
    }
	pWidget_->SetRulerRange( _fStart , _fStart + _fRange , _fStart , _fStart + _fRange ,DopplerDataView::DATA_VIEW_RULER_LEFT);
	pWidget_->SetRulerUnit(&_strLeftUnit , DopplerDataView::DATA_VIEW_RULER_LEFT );

	QString _strBottomUnit("%")  ;
	//---------------------------------------------
	
	bool _bRectify = (_process->GetRectifierMode(nGroupId_) == setup_RECTIFIER_RF ) ;

	if(_bRectify)
		pWidget_->SetRulerRange( -100, 100 ,  -100, 100 ,DopplerDataView::DATA_VIEW_RULER_BOTTOM);
	else
	//---------------------------------------------
	pWidget_->SetRulerRange( 0 , 100 ,   0 , 100 , DopplerDataView::DATA_VIEW_RULER_BOTTOM);
	pWidget_->SetRulerUnit (&_strBottomUnit, DopplerDataView::DATA_VIEW_RULER_BOTTOM );

	pWidget_->SetRulerRange( 100 , 0 ,  100 , 0 ,DopplerDataView::DATA_VIEW_RULER_RIGHT);

	void* _pColor ;
	if(setup_RECTIFIER_RF ==  _process->GetRectifierMode(nGroupId_))
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_RECTIFY );
	else
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_AMP);
	pWidget_->SetColorBarColorIndex(_pColor);
}

void ProcessDisplay::UpdateDataViewFrameBH(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_)
{
	ParameterProcess* _process = ParameterProcess::Instance();
	QString _strLeftUnit = _process->GetScanAxisUnit()  ;
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    GROUP_CONFIG& _group = _pConfig->group[nGroupId_];
	double _fStart , _fStop , _fSliderStart , _fSliderStop;
    //SCANNER& _scan = m_pConfig->common.scanner ;
    int _nScanend    = _process->SAxisstoptoIndex(_process->GetScanend());
    int _nHeight = pWidget_->height() - 35;

	pWidget_->GetRulerRange(&_fStop , &_fStart , &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT ) ;
    if(_nHeight < _nScanend)
    {
        _process->GetBScanScanAxisRange(nGroupId_ ,  _nHeight , &_fStart , &_fStop, &_fSliderStart , &_fSliderStop) ;
    }
    else
    {
        _process->GetBScanScanAxisRange(nGroupId_ ,  _nScanend , &_fStart , &_fStop, &_fSliderStart , &_fSliderStop) ;
    }
	pWidget_->SetRulerRange( _fStop , _fStart , _fSliderStart , _fSliderStop,DopplerDataView::DATA_VIEW_RULER_LEFT);
	pWidget_->SetRulerUnit (&_strLeftUnit, DopplerDataView::DATA_VIEW_RULER_LEFT );

    QString _strBottomUnit = _process->GetSonicAxisUnit(nGroupId_) ;
	_fStart = _process->GetSampleStart(nGroupId_ , nLawId_) ;
	_fStop  = _fStart + _process->GetSampleRange(nGroupId_ , nLawId_) ;
//    srcrangestart = _fStart;
//    srcrangestop = _fStop;
//    _group.currentRangeStart = _fStart;
//    _group.currentRangeStop = _fStop;
    float pcs = _pConfig->TOFD[nGroupId_].fPCS;
    if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH && _group.eGroupMode != setup_GROUP_MODE_PA){
        pWidget_->SetTofdSampleStart(_group.afCursor[setup_CURSOR_TFOD_LW], DopplerDataView::DATA_VIEW_RULER_BOTTOM);
        _process->SetTofdSampleStart(_group.afCursor[setup_CURSOR_TFOD_LW]);
        pWidget_->SetTofdDepth(true, pcs, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
    }else{
       pWidget_->SetTofdDepth(false, pcs, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
    }
	pWidget_->SetRulerRange( _fStart , _fStop ,  _fStart , _fStop , DopplerDataView::DATA_VIEW_RULER_BOTTOM);
	pWidget_->SetRulerUnit(&_strBottomUnit , DopplerDataView::DATA_VIEW_RULER_BOTTOM );
	pWidget_->SetRulerRange( 100 , 0 ,  100 , 0 , DopplerDataView::DATA_VIEW_RULER_RIGHT);

	void* _pColor ;
	if(setup_RECTIFIER_RF ==  _process->GetRectifierMode(nGroupId_))
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_RECTIFY );
	else
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_AMP);
	pWidget_->SetColorBarColorIndex(_pColor);
}

void ProcessDisplay::UpdateDataViewFrameBV(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_)
{
	ParameterProcess* _process = ParameterProcess::Instance();
	QString _strLeftUnit = _process->GetScanAxisUnit()  ;
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    GROUP_CONFIG& _group = _pConfig->group[nGroupId_];

	double _fStart , _fStop , _fSliderStart, _fSliderStop;
	pWidget_->GetRulerRange(&_fStart , &_fStop , &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM ) ;
    int _nScanend    = _process->SAxisstoptoIndex(_process->GetScanend());
    int _nWidth	   = pWidget_->width() - 50 ;
    if(_nWidth < _nScanend)
    {
        _process->GetBScanScanAxisRange(nGroupId_ ,  _nWidth , &_fStart , &_fStop, &_fSliderStart , &_fSliderStop) ;
    }
    else
    {
        _process->GetBScanScanAxisRange(nGroupId_ ,  _nScanend , &_fStart , &_fStop, &_fSliderStart , &_fSliderStop) ;
    }
	pWidget_->SetRulerRange( _fStart , _fStop ,  _fSliderStart , _fSliderStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
	pWidget_->SetRulerUnit (&_strLeftUnit, DopplerDataView::DATA_VIEW_RULER_BOTTOM );

    QString _strBottomUnit = _process->GetSonicAxisUnit(nGroupId_) ;
	_fStart = _process->GetSampleStart(nGroupId_ , nLawId_)  ;
	_fStop =  _fStart + _process->GetSampleRange(nGroupId_ , nLawId_)  ;
//    srcrangestart = _fStart;
//    srcrangestop = _fStop;
//    _group.currentRangeStart = _fStart;
//    _group.currentRangeStop = _fStop;
    float pcs = _pConfig->TOFD[nGroupId_].fPCS;
    if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH && _group.eGroupMode != setup_GROUP_MODE_PA){
        pWidget_->SetTofdSampleStart(_group.afCursor[setup_CURSOR_TFOD_LW], DopplerDataView::DATA_VIEW_RULER_LEFT);
        _process->SetTofdSampleStart(_group.afCursor[setup_CURSOR_TFOD_LW]);
        pWidget_->SetTofdDepth(true, pcs, DopplerDataView::DATA_VIEW_RULER_LEFT);
    }else{
        pWidget_->SetTofdDepth(false, pcs, DopplerDataView::DATA_VIEW_RULER_LEFT);
    }
	pWidget_->SetRulerRange( _fStart , _fStop ,  _fStart , _fStop , DopplerDataView::DATA_VIEW_RULER_LEFT);
	pWidget_->SetRulerUnit(&_strBottomUnit , DopplerDataView::DATA_VIEW_RULER_LEFT );

	pWidget_->SetRulerRange( 100 , 0 ,   100 , 0 ,DopplerDataView::DATA_VIEW_RULER_RIGHT);

	void* _pColor ;
	if(setup_RECTIFIER_RF ==  _process->GetRectifierMode(nGroupId_))
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_RECTIFY );
	else
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_AMP);
	pWidget_->SetColorBarColorIndex(_pColor);
}

void ProcessDisplay::UpdateDataViewFrameCH(DopplerDataView* pWidget_ , int nGroupId_ , int /*nLawId_*/)
{
	ParameterProcess* _process = ParameterProcess::Instance();
	setup_DISPLAY_MODE _eMode  = (setup_DISPLAY_MODE)pWidget_->GetDataViewDrawType() ;

	setup_CSCAN_SOURCE_MODE _eSource ;
	if( _eMode == setup_DISPLAY_MODE_C_H )
		_eSource = _process->GetCScanSource(nGroupId_ , 0) ;
	else
		_eSource = _process->GetCScanSource(nGroupId_ , 1) ;

	QString _strLeftUnit = _process->GetCscanIndexUnit(nGroupId_)  ;
	double _fScanStart , _fScanStop , _fSliderStart, _fSliderStop;
	_process->GetCScanIndexAxisRange(nGroupId_ ,  &_fScanStart , &_fScanStop) ;
	pWidget_->SetRulerRange(_fScanStart, _fScanStop , _fScanStart, _fScanStop , DopplerDataView::DATA_VIEW_RULER_LEFT);
    pWidget_->SetRulerUnit (&_strLeftUnit, DopplerDataView::DATA_VIEW_RULER_LEFT );
    int _nWidth	   = pWidget_->width() - 50 ;
	QString _strBottomUnit = _process->GetScanAxisUnit() ;
	pWidget_->GetRulerRange(&_fScanStart , &_fScanStop , &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM ) ;
    //SCANNER& _scan = m_pConfig->common.scanner ;
    int _nScanend    = _process->SAxisstoptoIndex(_process->GetScanend());
    if(_nWidth < _nScanend)
    {
        _process->GetCScanScanAxisRange(nGroupId_ ,  _nWidth , &_fScanStart , &_fScanStop, &_fSliderStart, &_fSliderStop) ;
    }
    else
    {
        _process->GetCScanScanAxisRange(nGroupId_ ,  _nScanend , &_fScanStart , &_fScanStop, &_fSliderStart, &_fSliderStop) ;
    }
    pWidget_->SetRulerRange( _fScanStart , _fScanStop ,  _fSliderStart, _fSliderStop,DopplerDataView::DATA_VIEW_RULER_BOTTOM);
	pWidget_->SetRulerUnit(&_strBottomUnit , DopplerDataView::DATA_VIEW_RULER_BOTTOM );
    pWidget_->SetCopleCScanDisplayRange( _fScanStart, _fScanStop);

	if(_eSource == setup_CSCAN_AMP_A || _eSource == setup_CSCAN_AMP_B )
	{
		pWidget_->SetRulerRange( 100 , 0 ,   100 , 0 ,  DopplerDataView::DATA_VIEW_RULER_RIGHT);
		void* _pColor ;
		if(setup_RECTIFIER_RF ==  _process->GetRectifierMode(nGroupId_))
			_pColor = _process->GetPalete(nGroupId_ , PALETTE_RECTIFY );
		else
			_pColor = _process->GetPalete(nGroupId_ , PALETTE_AMP);
		pWidget_->SetColorBarColorIndex(_pColor);
        pWidget_->SetCoupleCScanBarColorIndex(_pColor);
	}
	else
	{
		float _fStart  = _process->GetCScanThicknessStart(nGroupId_) ;
		float _fStop   = _process->GetCScanThicknessStop(nGroupId_);
		pWidget_->SetRulerRange( _fStop , _fStart ,  _fStop , _fStart , DopplerDataView::DATA_VIEW_RULER_RIGHT);
		void* _pColor = _process->GetPalete(nGroupId_ , PALETTE_THICKNESS);
		pWidget_->SetColorBarColorIndex(_pColor);
        pWidget_->SetCoupleCScanBarColorIndex(_pColor);
	}
}

void ProcessDisplay::UpdateDataViewFrameCV(DopplerDataView* pWidget_ , int nGroupId_ , int /*nLawId_*/)
{
	ParameterProcess* _process = ParameterProcess::Instance();
	setup_DISPLAY_MODE _eMode  = (setup_DISPLAY_MODE)pWidget_->GetDataViewDrawType();

	setup_CSCAN_SOURCE_MODE _eSource ;
	if( _eMode == setup_DISPLAY_MODE_C_V )
		_eSource = _process->GetCScanSource(nGroupId_ , 0) ;
	else
		_eSource = _process->GetCScanSource(nGroupId_ , 1) ;

    int _nHeight	   = pWidget_->height() - 35 ;
	QString _strLeftUnit = _process->GetScanAxisUnit()  ;
	double _fScanStart , _fScanStop , _fSliderStart, _fSliderStop ;

//	pWidget_->GetRulerRange(&_fScanStart , &_fScanStop , &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT ) ;
//	_process->GetCScanScanAxisRange(nGroupId_ ,  pWidget_->height() - 35 , &_fScanStart , &_fScanStop, &_fSliderStart, &_fSliderStop) ;
//	pWidget_->SetRulerRange( _fScanStart , _fScanStop ,  _fSliderStart, _fSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT);
	pWidget_->GetRulerRange(&_fScanStop , &_fScanStart , &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT ) ;
    //SCANNER& _scan = m_pConfig->common.scanner ;
    int _nScanend    = _process->SAxisstoptoIndex(_process->GetScanend());
    if(_nHeight < _nScanend)
    {
        _process->GetCScanScanAxisRange(nGroupId_ ,  _nHeight , &_fScanStart , &_fScanStop, &_fSliderStart, &_fSliderStop) ;
    }
    else
    {
        _process->GetCScanScanAxisRange(nGroupId_ ,  _nScanend , &_fScanStart , &_fScanStop, &_fSliderStart, &_fSliderStop) ;
    }
	pWidget_->SetRulerRange(_fScanStop , _fScanStart ,  _fSliderStart, _fSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT);
	pWidget_->SetRulerUnit (&_strLeftUnit, DopplerDataView::DATA_VIEW_RULER_LEFT );
    pWidget_->SetCopleCScanDisplayRange( _fScanStart, _fScanStop);

	QString _strBottomUnit = _process->GetCscanIndexUnit(nGroupId_) ;
	_process->GetCScanIndexAxisRange(nGroupId_ , &_fScanStart, &_fScanStop) ;
	pWidget_->SetRulerRange( _fScanStart , _fScanStop ,  _fScanStart , _fScanStop , DopplerDataView::DATA_VIEW_RULER_BOTTOM);
	pWidget_->SetRulerUnit(&_strBottomUnit , DopplerDataView::DATA_VIEW_RULER_BOTTOM );

	if(_eSource == setup_CSCAN_AMP_A || _eSource == setup_CSCAN_AMP_B )
	{
		pWidget_->SetRulerRange( 100 , 0 , 100 , 0 , DopplerDataView::DATA_VIEW_RULER_RIGHT);
		void* _pColor ;
		if(setup_RECTIFIER_RF ==  _process->GetRectifierMode(nGroupId_))
			_pColor = _process->GetPalete(nGroupId_ , PALETTE_RECTIFY );
		else
			_pColor = _process->GetPalete(nGroupId_ , PALETTE_AMP);
		pWidget_->SetColorBarColorIndex(_pColor);
        pWidget_->SetCoupleCScanBarColorIndex(_pColor);
	}
	else
	{
		float _fStart  = _process->GetCScanThicknessStart(nGroupId_) ;
		float _fStop   = _process->GetCScanThicknessStop(nGroupId_);
		pWidget_->SetRulerRange( _fStop , _fStart , _fStop , _fStart , DopplerDataView::DATA_VIEW_RULER_RIGHT);
		void* _pColor = _process->GetPalete(nGroupId_ , PALETTE_THICKNESS);
		pWidget_->SetColorBarColorIndex(_pColor);
        pWidget_->SetCoupleCScanBarColorIndex(_pColor);
	}
}

void ProcessDisplay::UpdateDataViewFrameSS(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_)
{
	ParameterProcess* _process = ParameterProcess::Instance();
    QString _strLeftUnit = _process->GetSonicAxisUnit(nGroupId_)  ;
	float _fLStart = _process->GetGroupLawQty(nGroupId_) + 0.5;
	float _fLStop  =  0.5;
	pWidget_->SetRulerRange( _fLStart , _fLStop,  _fLStart , _fLStop, DopplerDataView::DATA_VIEW_RULER_LEFT);
	pWidget_->SetRulerUnit (&_strLeftUnit, DopplerDataView::DATA_VIEW_RULER_LEFT );

    QString _strBottomUnit =  _process->GetSonicAxisUnit(nGroupId_) ;
	double _fStart = _process->GetSampleStart(nGroupId_ , nLawId_) ;
	double _fRange = _process->GetSampleRange(nGroupId_ , nLawId_) ;
	pWidget_->SetRulerRange( _fStart , _fStart + _fRange , _fStart , _fStart + _fRange , DopplerDataView::DATA_VIEW_RULER_BOTTOM);
	pWidget_->SetRulerUnit(&_strBottomUnit , DopplerDataView::DATA_VIEW_RULER_BOTTOM );

	pWidget_->SetRulerRange( 100 , 0 , 100 , 0 , DopplerDataView::DATA_VIEW_RULER_RIGHT);

	void* _pColor ;
	if(setup_RECTIFIER_RF ==  _process->GetRectifierMode(nGroupId_))
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_RECTIFY );
	else
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_AMP);
	pWidget_->SetColorBarColorIndex(_pColor);
    pWidget_->SetCoupleSScanBarColorIndex(_pColor);
}

void ProcessDisplay::UpdateDataViewFrameSA(DopplerDataView* pWidget_ , int nGroupId_ , int /*nLawId_*/)
{
	ParameterProcess* _process = ParameterProcess::Instance();
    QString _strLeftUnit = _process->GetSonicAxisUnit(nGroupId_)  ;
	float _fStart , _fStop  ;
	_process->GetSScanVerticalRange(nGroupId_ , &_fStart ,  &_fStop);

	pWidget_->SetRulerRange( _fStart , _fStop,  _fStart , _fStop, DopplerDataView::DATA_VIEW_RULER_LEFT);

    pWidget_->SetRulerUnit (&_strLeftUnit, DopplerDataView::DATA_VIEW_RULER_LEFT );

	QString _strBottomUnit =  _process->GetIndexAxisUnit() ;
	_process->GetSScanHorizentalRange(nGroupId_ , &_fStart , &_fStop) ;
	pWidget_->SetRulerRange( _fStart , _fStop , _fStart , _fStop , DopplerDataView::DATA_VIEW_RULER_BOTTOM);
	pWidget_->SetRulerUnit(&_strBottomUnit , DopplerDataView::DATA_VIEW_RULER_BOTTOM );

	pWidget_->SetRulerRange( 100 , 0 , 100 , 0 , DopplerDataView::DATA_VIEW_RULER_RIGHT);

	void* _pColor ;
	if(setup_RECTIFIER_RF ==  _process->GetRectifierMode(nGroupId_))
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_RECTIFY );
	else
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_AMP);
	pWidget_->SetColorBarColorIndex(_pColor);
    pWidget_->SetCoupleSScanBarColorIndex(_pColor);
}

void ProcessDisplay::UpdateDataViewFrameSL(DopplerDataView* pWidget_ , int nGroupId_ , int /*nLawId_*/)
{
	ParameterProcess* _process = ParameterProcess::Instance();
    QString _strLeftUnit = _process->GetSonicAxisUnit(nGroupId_)  ;
	float _fStart , _fStop  ;
	_process->GetSScanVerticalRange(nGroupId_ , &_fStart ,  &_fStop);
	pWidget_->SetRulerRange( _fStart , _fStop,   _fStart , _fStop, DopplerDataView::DATA_VIEW_RULER_LEFT);
	pWidget_->SetRulerUnit (&_strLeftUnit, DopplerDataView::DATA_VIEW_RULER_LEFT );

	QString _strBottomUnit =  _process->GetIndexAxisUnit() ;
	_process->GetSScanHorizentalRange(nGroupId_ , &_fStart , &_fStop) ;
	pWidget_->SetRulerRange( _fStart , _fStop , _fStart , _fStop , DopplerDataView::DATA_VIEW_RULER_BOTTOM);
	pWidget_->SetRulerUnit(&_strBottomUnit , DopplerDataView::DATA_VIEW_RULER_BOTTOM );

	pWidget_->SetRulerRange( 100 , 0 ,  100 , 0 , DopplerDataView::DATA_VIEW_RULER_RIGHT);

	void* _pColor ;
	if(setup_RECTIFIER_RF ==  _process->GetRectifierMode(nGroupId_))
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_RECTIFY );
	else
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_AMP);
	pWidget_->SetColorBarColorIndex(_pColor);
    pWidget_->SetCoupleSScanBarColorIndex(_pColor);
}


void ProcessDisplay::UpdateDataViewDrawAH(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_, bool flash)
{
	GROUP_CONFIG* _pGroup = &m_pConfig->group[nGroupId_];
	DrawInfo info ;
	info.nPointQty = _pGroup->nPointQty ;
	info.nGroupId  = nGroupId_  ;
	info.nBeamId   = nLawId_	;
	DopplerDrawAScanH* _pDraw = (DopplerDrawAScanH*)pWidget_->GetDrawScan() ;
	if(!_pDraw)
	{
		_pDraw = new DopplerDrawAScanH() ;
		pWidget_->SetDrawScan(_pDraw) ;
	}
	_pDraw->SetDrawInfo(&info)	;
	_pDraw->UpdateDrawInfo();
    if(flash){
        pWidget_->UpdateDrawing();
    }
}

void ProcessDisplay::UpdateDataViewDrawAV(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_, bool flash)
{
	GROUP_CONFIG* _pGroup = &m_pConfig->group[nGroupId_];
	DrawInfo info ;

	info.nPointQty = _pGroup->nPointQty ;
	info.nGroupId  = nGroupId_  ;
	info.nBeamId   = nLawId_	;
	DopplerDrawAScanV* _pDraw = (DopplerDrawAScanV*)pWidget_->GetDrawScan() ;
	if(!_pDraw)
	{
		_pDraw = new DopplerDrawAScanV() ;
		pWidget_->SetDrawScan(_pDraw) ;
	}
	_pDraw->SetDrawInfo(&info)	;
	_pDraw->UpdateDrawInfo();
    if(flash){
        pWidget_->UpdateDrawing();
    }
}

void ProcessDisplay::UpdateDataViewDrawBH(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_, bool flash)
{
	GROUP_CONFIG* _pGroup = &m_pConfig->group[nGroupId_];
	DrawInfo info ;
	info.nPointQty = _pGroup->nPointQty ;
	info.nGroupId  = nGroupId_  ;
	info.nBeamId   = nLawId_	;

	DopplerDrawBScanH* _pDraw = (DopplerDrawBScanH*)pWidget_->GetDrawScan() ;
	if(!_pDraw)
	{
		_pDraw = new DopplerDrawBScanH() ;
		pWidget_->SetDrawScan(_pDraw) ;
		connect(_pDraw, SIGNAL(signalScanRangeMove(int, int, int)) , pWidget_, SLOT(slotScanRangeMove(int, int, int))) ;
	}
	_pDraw->SetDrawInfo(&info)	;
	_pDraw->UpdateDrawInfo();


	ParameterProcess* _process = ParameterProcess::Instance();
	void* _pColor ;
	if(setup_RECTIFIER_RF ==  _process->GetRectifierMode(nGroupId_))
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_RECTIFY );
	else
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_AMP);
	_pDraw->SetColorIndex(_pColor);
    if(flash){
        pWidget_->UpdateDrawing();
    }
}

void ProcessDisplay::UpdateDataViewDrawBV(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_, bool flash)
{
	GROUP_CONFIG* _pGroup = &m_pConfig->group[nGroupId_];
	DrawInfo info ;
	info.nPointQty = _pGroup->nPointQty ;
	info.nGroupId  = nGroupId_  ;
	info.nBeamId   = nLawId_	;

	DopplerDrawBScanV* _pDraw = (DopplerDrawBScanV*)pWidget_->GetDrawScan() ;
	if(!_pDraw)
	{
		_pDraw = new DopplerDrawBScanV();
		pWidget_->SetDrawScan(_pDraw);
		connect(_pDraw, SIGNAL(signalScanRangeMove(int, int, int)) , pWidget_, SLOT(slotScanRangeMove(int, int, int))) ;
	}
	_pDraw->SetDrawInfo(&info);
	_pDraw->UpdateDrawInfo();
	ParameterProcess* _process = ParameterProcess::Instance();
	void* _pColor ;
	if(setup_RECTIFIER_RF ==  _process->GetRectifierMode(nGroupId_))
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_RECTIFY );
	else
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_AMP);
	_pDraw->SetColorIndex(_pColor);
    if(flash){
        pWidget_->UpdateDrawing();
    }
}

void ProcessDisplay::UpdateDataViewDrawCH(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_, bool flash)
{
	setup_DISPLAY_MODE _eMode = (setup_DISPLAY_MODE)pWidget_->GetDataViewDrawType();
	ParameterProcess* _process = ParameterProcess::Instance();
	setup_CSCAN_SOURCE_MODE _eSource ;
	if( _eMode == setup_DISPLAY_MODE_C_H )
		_eSource = _process->GetCScanSource(nGroupId_ , 0) ;
	else
		_eSource = _process->GetCScanSource(nGroupId_ , 1) ;

	GROUP_CONFIG* _pGroup = &m_pConfig->group[nGroupId_];
	DrawInfo info ;
	info.nPointQty = _pGroup->nPointQty ;
	info.nGroupId  = nGroupId_  ;
	info.nBeamId   = nLawId_	;

	DopplerDrawCScanH* _pDraw = (DopplerDrawCScanH*)pWidget_->GetDrawScan() ;
	if(!_pDraw)
	{

        _pDraw = new DopplerDrawCScanH();
        bool topc, topcMerge;
        pWidget_->GetCScanTopcDis( topc, topcMerge);
        if( topc == false && topcMerge == false){
            _pDraw->topcShow = false;
            _pDraw->topcMergShow = false;
        }else if( topc){
            _pDraw->topcShow = true;
            _pDraw->topcMergShow = false;
        }else{
            _pDraw->topcShow = false;
            _pDraw->topcMergShow = true;
        }
		pWidget_->SetDrawScan(_pDraw) ;
        connect(_pDraw, SIGNAL(signalScanRangeMove(int, int, int)) , pWidget_, SLOT(slotScanRangeMove(int, int, int))) ;
        connect(_pDraw, SIGNAL(signalIndexRangeMove(int,int,double,double)), pWidget_, SLOT(slotIndexRangeMove(int,int,double,double)));
	}
	void* _pColor = NULL;
	if(_eSource == setup_CSCAN_AMP_A || _eSource == setup_CSCAN_AMP_B)
	{
		if(setup_RECTIFIER_RF ==  _process->GetRectifierMode(nGroupId_))
			_pColor = _process->GetPalete(nGroupId_ , PALETTE_RECTIFY );
		else
			_pColor = _process->GetPalete(nGroupId_ , PALETTE_AMP);
	}
	else
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_THICKNESS);
	_pDraw->SetColorIndex(_pColor);

	_pDraw->SetDrawInfo(&info)  ;
	_pDraw->SetCScanType(CSCAN_TYPE(_eSource));
	_pDraw->UpdateDrawInfo ();

    if(flash){
        pWidget_->UpdateDrawing();
    }
}

void ProcessDisplay::UpdateDataViewDrawCV(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_, bool flash)
{
	setup_DISPLAY_MODE _eMode = (setup_DISPLAY_MODE)pWidget_->GetDataViewDrawType();
	ParameterProcess* _process = ParameterProcess::Instance();
	setup_CSCAN_SOURCE_MODE _eSource ;
	if( _eMode == setup_DISPLAY_MODE_C_V )
		_eSource = _process->GetCScanSource(nGroupId_ , 0) ;
	else
		_eSource = _process->GetCScanSource(nGroupId_ , 1) ;

	GROUP_CONFIG* _pGroup = &m_pConfig->group[nGroupId_];
	DrawInfo info ;
	info.nPointQty = _pGroup->nPointQty ;
	info.nGroupId  = nGroupId_  ;
	info.nBeamId   = nLawId_	;

	DopplerDrawCScanV* _pDraw = (DopplerDrawCScanV*)pWidget_->GetDrawScan() ;
	if(!_pDraw)
	{
		_pDraw = new DopplerDrawCScanV() ;
		pWidget_->SetDrawScan(_pDraw) ;
        connect(_pDraw, SIGNAL(signalScanRangeMove(int, int, int)) , pWidget_, SLOT(slotScanRangeMove(int, int, int))) ;
        connect(_pDraw, SIGNAL(signalIndexRangeMove(int,int,double,double)), pWidget_, SLOT(slotIndexRangeMove(int,int,double,double)));
	}
	void* _pColor = NULL;
	if(_eSource == setup_CSCAN_AMP_A || _eSource == setup_CSCAN_AMP_B)
	{
		if(setup_RECTIFIER_RF ==  _process->GetRectifierMode(nGroupId_))
			_pColor = _process->GetPalete(nGroupId_ , PALETTE_RECTIFY );
		else
			_pColor = _process->GetPalete(nGroupId_ , PALETTE_AMP );
	}
	else
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_THICKNESS);
	_pDraw->SetColorIndex(_pColor);

	_pDraw->SetDrawInfo(&info)  ;
	_pDraw->SetCScanType(CSCAN_TYPE(_eSource));
	_pDraw->UpdateDrawInfo ();

    if(flash){
        pWidget_->UpdateDrawing();
    }
}

void ProcessDisplay::UpdateDataViewDrawSS(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_, bool flash)
{
	GROUP_CONFIG* _pGroup = &m_pConfig->group[nGroupId_];
	DrawInfo info ;
	info.nPointQty = _pGroup->nPointQty ;
	info.nGroupId  = nGroupId_  ;
	info.nBeamId   = nLawId_	;
	DopplerDrawSScanSoundPath* _pDraw = (DopplerDrawSScanSoundPath*)pWidget_->GetDrawScan() ;
    if(flash){
        _pDraw = new DopplerDrawSScanSoundPath() ;
        pWidget_->SetDrawScan(_pDraw);
    }else{
        if(!_pDraw)
        {
            _pDraw = new DopplerDrawSScanSoundPath() ;
            pWidget_->SetDrawScan(_pDraw) ;
        }
    }

	_pDraw->SetDrawInfo(&info);
	_pDraw->UpdateDrawInfo ();

	ParameterProcess* _process = ParameterProcess::Instance();
	void* _pColor ;
	if(setup_RECTIFIER_RF ==  _process->GetRectifierMode(nGroupId_))
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_RECTIFY );
	else
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_AMP);
	_pDraw->SetColorIndex(_pColor);
    if(flash){
        pWidget_->UpdateDrawing();
    }
}

void ProcessDisplay::UpdateDataViewDrawSA(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_, bool flash)
{
	GROUP_CONFIG* _pGroup = &m_pConfig->group[nGroupId_];
	DrawInfo info ;
	info.nPointQty = _pGroup->nPointQty ;
	info.nGroupId  = nGroupId_  ;
	info.nBeamId   = nLawId_	;

	DopplerDrawSScanTrueDepth* _pDraw = (DopplerDrawSScanTrueDepth*)pWidget_->GetDrawScan() ;
    if(flash){
        _pDraw = new DopplerDrawSScanTrueDepth() ;
        pWidget_->SetDrawScan(_pDraw) ;
    }else{
        if(!_pDraw)
        {
            _pDraw = new DopplerDrawSScanTrueDepth() ;
            pWidget_->SetDrawScan(_pDraw) ;
        }
    }
    connect(_pDraw,SIGNAL(updateAllItem()),pWidget_,SLOT(updateAllItem()));
	_pDraw->SetDrawInfo(&info);
	_pDraw->UpdateDrawInfo ();
	ParameterProcess* _process = ParameterProcess::Instance();
	void* _pColor ;
	if(setup_RECTIFIER_RF ==  _process->GetRectifierMode(nGroupId_))
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_RECTIFY );
	else
		_pColor = _process->GetPalete(nGroupId_ , PALETTE_AMP);
	_pDraw->SetColorIndex(_pColor);
    if(flash){
        pWidget_->UpdateDrawing();
    }
}

void ProcessDisplay::UpdateDataViewDrawSL(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_, bool flash)
{
    UpdateDataViewDrawSA(pWidget_ , nGroupId_ , nLawId_, flash);
}

/****************************************************************************
  Description: 更新指定窗口的画图操作
  Input: 【pWidget_：窗口指针】
*****************************************************************************/
void ProcessDisplay::UpdateDataViewDraw(DopplerDataView* pWidget_, bool flash)
{
	int _nGroupId , _nLawId , _nDisplay  ;
	setup_DISPLAY_MODE _eMode  ;
	pWidget_->GetDataViewConfigure( &_nGroupId ,  &_nLawId ,  &_nDisplay);
	_eMode = (setup_DISPLAY_MODE)_nDisplay  ;
	switch(_eMode)
	{
	case  setup_DISPLAY_MODE_A_H:
        UpdateDataViewDrawAH(pWidget_ , _nGroupId , _nLawId, flash) ;
		break;
	case  setup_DISPLAY_MODE_A_V:
        UpdateDataViewDrawAV(pWidget_ , _nGroupId , _nLawId, flash) ;
		break;
	case  setup_DISPLAY_MODE_B_H:
        UpdateDataViewDrawBH(pWidget_ , _nGroupId , _nLawId, flash) ;
		break;
	case setup_DISPLAY_MODE_B_V:
        UpdateDataViewDrawBV(pWidget_ , _nGroupId , _nLawId, flash) ;
		break;
	case setup_DISPLAY_MODE_C_H:
	case setup_DISPLAY_MODE_CC_H:
        UpdateDataViewDrawCH(pWidget_ , _nGroupId , _nLawId, flash) ;
		break;
	case setup_DISPLAY_MODE_C_V:
	case setup_DISPLAY_MODE_CC_V:
        UpdateDataViewDrawCV(pWidget_ , _nGroupId , _nLawId, flash) ;
		break;
	case setup_DISPLAY_MODE_S_SOUNDPATH:
        UpdateDataViewDrawSS (pWidget_ , _nGroupId , _nLawId, flash) ;
		break;
	case setup_DISPLAY_MODE_S_ATHUMIZ:
        UpdateDataViewDrawSA (pWidget_ , _nGroupId , _nLawId, flash) ;
		break;
	case setup_DISPLAY_MODE_S_LINEAR:
        UpdateDataViewDrawSL (pWidget_ , _nGroupId , _nLawId, flash) ;
		break;
	default:
		break;
	};
}

/****************************************************************************
  Description: 更新指定窗口的标尺
  Input: 【pWidget_：窗口指针】
*****************************************************************************/
void ProcessDisplay::UpdateDataViewFrame(DopplerDataView* pWidget_)
{
	int _nGroupId , _nLawId , _nDisplay  ;
	setup_DISPLAY_MODE _eMode  ;
	pWidget_->GetDataViewConfigure( &_nGroupId ,  &_nLawId ,  &_nDisplay);
	_eMode = (setup_DISPLAY_MODE)_nDisplay  ;
	switch(_eMode)
	{
	case  setup_DISPLAY_MODE_A_H:
		UpdateDataViewFrameAH(pWidget_ , _nGroupId , _nLawId) ;
		break;
	case  setup_DISPLAY_MODE_A_V:
		UpdateDataViewFrameAV(pWidget_ , _nGroupId , _nLawId) ;
		break;
	case  setup_DISPLAY_MODE_B_H:
		UpdateDataViewFrameBH(pWidget_ , _nGroupId , _nLawId) ;
		break;
	case setup_DISPLAY_MODE_B_V:
		UpdateDataViewFrameBV(pWidget_ , _nGroupId , _nLawId) ;
		break;
	case setup_DISPLAY_MODE_C_H:
	case setup_DISPLAY_MODE_CC_H:
		UpdateDataViewFrameCH(pWidget_ , _nGroupId , _nLawId) ;
		break;
	case setup_DISPLAY_MODE_C_V:
	case setup_DISPLAY_MODE_CC_V:
		UpdateDataViewFrameCV(pWidget_ , _nGroupId , _nLawId) ;
		break;
	case setup_DISPLAY_MODE_S_SOUNDPATH:
		UpdateDataViewFrameSS (pWidget_ , _nGroupId , _nLawId) ;
		break;
	case setup_DISPLAY_MODE_S_ATHUMIZ:
		UpdateDataViewFrameSA (pWidget_ , _nGroupId , _nLawId) ;
		break;
	case setup_DISPLAY_MODE_S_LINEAR:
		UpdateDataViewFrameSL (pWidget_ , _nGroupId , _nLawId) ;
		break;
	default:
		break;
	};
}
/****************************************************************************
  Description: 更新指定窗口的标题
  Input: 【pWidget_：窗口指针】
*****************************************************************************/
void ProcessDisplay::UpdateDataViewTitle(DopplerDataView* pWidget_)
{
	QString _strTitle ;

	int _nGroupId , _nLawId , _nDisplay  ;
	setup_DISPLAY_MODE _eMode  ;
	pWidget_->GetDataViewConfigure( &_nGroupId ,  &_nLawId ,  &_nDisplay);
	_eMode = (setup_DISPLAY_MODE)_nDisplay  ;
	ParameterProcess* _process = ParameterProcess::Instance();
	float _fAngle = _process->GetLawAngle( _nGroupId ,  _nLawId) ;
    bool topc, topcMerge;
    pWidget_->GetCScanTopcDis( topc, topcMerge);
	switch(_eMode)
	{
	case  setup_DISPLAY_MODE_A_H:
	case  setup_DISPLAY_MODE_A_V:
		_strTitle.sprintf("GROUP-%d/A SCAN/LAW-%d/ANGLE-%2.1f", _nGroupId + 1 , _nLawId + 1 , _fAngle) ;
		break;
	case  setup_DISPLAY_MODE_B_H:
	case setup_DISPLAY_MODE_B_V:
		_strTitle.sprintf("GROUP-%d/B SCAN/LAW-%d/ANGLE-%2.1f", _nGroupId + 1 , _nLawId + 1 , _fAngle) ;
		break;
	case setup_DISPLAY_MODE_C_H:
	case setup_DISPLAY_MODE_C_V:
	case setup_DISPLAY_MODE_CC_H:
	case setup_DISPLAY_MODE_CC_V:
    {
        GROUP_CONFIG* _pGroup = &m_pConfig->group[_nGroupId];
        if(topcMerge){
            _strTitle.sprintf("GROUP-%d/TOPCMerge SCAN/LAW-%d/ANGLE-%2.1f", _nGroupId + 1 , _nLawId + 1 , _fAngle);
        }else if(_pGroup->TopCInfo.TOPCStatus || topc){
            _strTitle.sprintf("GROUP-%d/TOPC SCAN/LAW-%d/ANGLE-%2.1f", _nGroupId + 1 , _nLawId + 1 , _fAngle);
        }else{
            _strTitle.sprintf("GROUP-%d/C SCAN/LAW-%d/ANGLE-%2.1f", _nGroupId + 1 , _nLawId + 1 , _fAngle);
        }
    }
		break;
	case setup_DISPLAY_MODE_S_SOUNDPATH:
	case setup_DISPLAY_MODE_S_ATHUMIZ:
	case setup_DISPLAY_MODE_S_LINEAR:
		//int DopplerDataView::GetSScanLawQty()
		//int DopplerDataView::GetSScanLaw(int index_)
		//_strTitle.sprintf("GROUP-%d/S SCAN/LAW-%d/ANGLE-%2.1f", _nGroupId + 1 , _nLawId + 1 , _fAngle) ;
		{
			char _str[256], _tmp[256];
			sprintf(_str, "GROUP-%d/S SCAN/", _nGroupId + 1);

			int _nQty = pWidget_->GetSScanLawQty();
			for(int i = 0; i < _nQty; i++) {
				_nLawId = pWidget_->GetSScanLaw(i);
				_fAngle = _process->GetLawAngle( _nGroupId ,  _nLawId) ;
				sprintf(_tmp, "[LAW-%d/ANGLE-%2.1f]", _nLawId + 1, _fAngle);
				strcat(_str, _tmp);
			}
			_strTitle = QString(tr(_str));
		}
		break;
	default:
		break;
	};
	//pWidget_->SetTitleBarColor(g_TitleBgColor);
	//pWidget_->SetTitleBarStringColor(g_TitleFgColor);
	pWidget_->SetTitleBarString(_strTitle);
}

/****************************************************************************
  Description: 更新窗口的全部设置
  Input: 【pWidget_：窗口指针】
*****************************************************************************/
void ProcessDisplay::UpdateAllView()
{
	for(int j = 0 ; j < g_pMainWnd->GetDisplayTableQty() ; j++)
    {
		QList<QWidget*>* pList = g_pMainWnd->GetDisplayTableWidgetList(j);

		for(int i = 0 ; i < pList->count() ; i++)
		{
            UpdateAll((DopplerDataView*)pList->at(i), false);
		}
	}
}

/****************************************************************************
  Description: 更新指定窗口的光标、闸门
  Input: 【pWidget_：窗口指针】
*****************************************************************************/
void ProcessDisplay::UpdateDataViewOverlay(DopplerDataView* pWidget_)
{
	DopplerOverlays _overlay(pWidget_);
	_overlay.UpdateOverlays();
	UpdateDataViewTitle(pWidget_);
}

/****************************************************************************
  Description: 更新所有窗口的光标、闸门
*****************************************************************************/
void ProcessDisplay::UpdateAllViewOverlay()
{
	for(int j = 0 ; j < g_pMainWnd->GetDisplayTableQty() ; j++)
	{
		QList<QWidget*>* pList = g_pMainWnd->GetDisplayTableWidgetList(j);
		for(int i = 0 ; i < pList->count() ; i++)
		{
			UpdateDataViewOverlay((DopplerDataView*)pList->at(i));
		}
	}
}

/****************************************************************************
  Description: 更新所有窗口的标尺和标题
*****************************************************************************/

void ProcessDisplay::UpdateAllViewFrame()
{
	for(int j = 0 ; j < g_pMainWnd->GetDisplayTableQty() ; j++)
	{
		QList<QWidget*>* pList = g_pMainWnd->GetDisplayTableWidgetList(j);
		for(int i = 0 ; i < pList->count() ; i++)
		{
			UpdateDataViewFrame((DopplerDataView*)pList->at(i));
		}
	}
}

/****************************************************************************
  Description: 更新所有指定组窗口的标尺和标题
  Input:   【nGroupId_ ： 组ID】
*****************************************************************************/
void ProcessDisplay::UpdateAllViewFrameOfGroup(int nGroupId_)
{
	int _nGroupId , _nLawId , _nDisplay  ;
	DopplerDataView* _pView  ;
	for(int j = 0 ; j < g_pMainWnd->GetDisplayTableQty() ; j++)
	{
		QList<QWidget*>* pList = g_pMainWnd->GetDisplayTableWidgetList(j);
		for(int i = 0 ; i < pList->count() ; i++)
		{
			_pView =  (DopplerDataView*)pList->at(i)  ;
			_pView->GetDataViewConfigure(&_nGroupId , &_nLawId , &_nDisplay );
			if(_nGroupId == nGroupId_)
				UpdateDataViewFrame(_pView);
		}
	}
}

/****************************************************************************
  Description: 更新所有指定组窗口的光标
  Input:   【nGroupId_ ： 组ID】
*****************************************************************************/
void ProcessDisplay::UpdateAllViewOverlayOfGroup(int nGroupId_)
{
	int _nGroupId , _nLawId , _nDisplay  ;
	DopplerDataView* _pView  ;
	for(int j = 0 ; j < g_pMainWnd->GetDisplayTableQty() ; j++)
	{
		QList<QWidget*>* pList = g_pMainWnd->GetDisplayTableWidgetList(j);
		for(int i = 0 ; i < pList->count() ; i++)
		{
			_pView =  (DopplerDataView*)pList->at(i)  ;
			_pView->GetDataViewConfigure(&_nGroupId , &_nLawId , &_nDisplay );
			if(_nGroupId == nGroupId_)
				UpdateDataViewOverlay(_pView);
		}
	}
}

/****************************************************************************
  Description: 更新所有指定组窗口，包括标尺、标题、光标
  Input:   【nGroupId_ ： 组ID】
*****************************************************************************/
void ProcessDisplay::UpdateAllViewOfGroup(int nGroupId_)
{
	UpdateAllViewFrameOfGroup(nGroupId_);
	UpdateAllViewOverlayOfGroup(nGroupId_);
}

/****************************************************************************
  Description: 更新所有指定组窗口，包括标尺、标题、光标、窗口绘图区
  Input:   【nGroupId_ ： 组ID】 flash : true 重新创建绘图区
*****************************************************************************/
void ProcessDisplay::UpdateAllViewOfGroupAndScanDraw(int nGroupId_, bool flash)
{
    int _nGroupId, _nLawId, _nDisplay;
    DopplerDataView* _pView;
    for(int j = 0 ; j < g_pMainWnd->GetDisplayTableQty() ; j++){
        QList<QWidget*>* pList = g_pMainWnd->GetDisplayTableWidgetList(j);
        for(int i = 0 ; i < pList->count() ; i++){
            _pView =  (DopplerDataView*)pList->at(i);
            _pView->GetDataViewConfigure(&_nGroupId , &_nLawId , &_nDisplay);
            if(_nGroupId == nGroupId_){
                UpdateAll(_pView, flash);
            }
        }
    }
}

/****************************************************************************
  Description: 更新所有指定组窗口的闸门位置
  Input:   【nGroupId_ ： 组ID】
*****************************************************************************/
void ProcessDisplay::UpdateAllViewGateOfGroup(int nGroupId_)
{
	int _nGroupId , _nLawId , _nDisplay  ;
	DopplerDataView* _pView  ;
	for(int j = 0 ; j < g_pMainWnd->GetDisplayTableQty() ; j++)
	{
		QList<QWidget*>* pList = g_pMainWnd->GetDisplayTableWidgetList(j);
		for(int i = 0 ; i < pList->count() ; i++)
		{
			_pView =  (DopplerDataView*)pList->at(i)  ;
			_pView->GetDataViewConfigure(&_nGroupId , &_nLawId , &_nDisplay );
			if(_nGroupId == nGroupId_)
			{
				 DopplerOverlays _overlay(_pView);
				 _overlay.UpdateGate();
				 UpdateDataViewTitle(_pView);
			}
		}
	}
}

void ProcessDisplay::ShowDefectInfo(int nGroupId_,int id)
{
    int _nGroupId , _nLawId , _nDisplay  ;
    DopplerDataView* _pView  ;
    for(int j = 0 ; j < g_pMainWnd->GetDisplayTableQty() ; j++)
    {
        QList<QWidget*>* pList = g_pMainWnd->GetDisplayTableWidgetList(j);
        for(int i = 0 ; i < pList->count() ; i++)
        {
            _pView =  (DopplerDataView*)pList->at(i)  ;
            _pView->GetDataViewConfigure(&_nGroupId , &_nLawId , &_nDisplay );
            if(_nGroupId == nGroupId_)
            {
                 _pView->SetDefect(id);
            }
        }
    }
}

void ProcessDisplay::ResetDefectInfo(int nGroupId_)
{
    int _nGroupId , _nLawId , _nDisplay  ;
    DopplerDataView* _pView  ;
    for(int j = 0 ; j < g_pMainWnd->GetDisplayTableQty() ; j++)
    {
        QList<QWidget*>* pList = g_pMainWnd->GetDisplayTableWidgetList(j);
        for(int i = 0 ; i < pList->count() ; i++)
        {
            _pView =  (DopplerDataView*)pList->at(i)  ;
            _pView->GetDataViewConfigure(&_nGroupId , &_nLawId , &_nDisplay );
            if(_nGroupId == nGroupId_)
            {
                 _pView->ResetDefect();
            }
        }
    }
}

/****************************************************************************
  Description: 更新所有指定组窗口的光标显示
  Input:   【nGroupId_ ： 组ID】
*****************************************************************************/
void ProcessDisplay::UpdateAllViewCursorOfGroup(int)
{
	int _nGroupId , _nLawId , _nDisplay  ;
	DopplerDataView* _pView  ;
	for(int j = 0 ; j < g_pMainWnd->GetDisplayTableQty() ; j++)
	{
		QList<QWidget*>* pList = g_pMainWnd->GetDisplayTableWidgetList(j);
		for(int i = 0 ; i < pList->count() ; i++)
		{
			_pView =  (DopplerDataView*)pList->at(i)  ;
			_pView->GetDataViewConfigure(&_nGroupId , &_nLawId , &_nDisplay );
			//if(_nGroupId == nGroupId_)
			{
				 DopplerOverlays _overlay(_pView);
                 _overlay.UpdateCursor();
				 UpdateDataViewTitle(_pView);
			}

		}
	}
}



