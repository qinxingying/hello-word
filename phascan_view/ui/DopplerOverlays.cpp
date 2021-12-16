﻿#include "DopplerOverlays.h"
#include "DopplerConfigure.h"
#include "DopplerViewItems.h"
#include "DopplerDrawSScanTrueDepth.h"

extern int bHideCursor;
extern int HideMode;
int m_nWidth , m_nHeight;
DopplerOverlays::DopplerOverlays(QObject *parent) :
	QObject(parent)
{
	if(parent)
	{

		m_pView = (DopplerDataView*) parent ;
		m_pView->GetDataViewConfigure(&m_nGroup , &m_nLaw , &m_eDisp) ;
	}
	else
	{
		m_pView   = 0 ;
		m_nGroup  = 0 ;
		m_nLaw	= 0 ;
		m_eDisp   = 0 ;
	}

	m_pConfigure = DopplerConfigure::Instance();
	m_pProcess   = ParameterProcess::Instance();
}

void DopplerOverlays::CreateOverlays()
{
	switch(m_eDisp)
	{
	case setup_DISPLAY_MODE_A_H :
		CreateOverlaysAH() ;
		break;
	case setup_DISPLAY_MODE_A_V :
		CreateOverlaysAV() ;
		break;
	case setup_DISPLAY_MODE_B_H  :
		CreateOverlaysBH() ;
		break;
	case setup_DISPLAY_MODE_B_V :
		CreateOverlaysBV() ;
		break;
	case setup_DISPLAY_MODE_C_H  :
        CreateOverlaysCH() ;
		break;
	case setup_DISPLAY_MODE_C_V :
		CreateOverlaysCV() ;
		break;
	case setup_DISPLAY_MODE_CC_H  :
		CreateOverlaysCH() ;
		break;
	case setup_DISPLAY_MODE_CC_V  :
		CreateOverlaysCV() ;
		break;
	case setup_DISPLAY_MODE_S_SOUNDPATH :
		CreateOverlaysSS() ;
		break;
    case setup_DISPLAY_MODE_S_ATHUMIZ :
		CreateOverlaysSA() ;
        break;
	case setup_DISPLAY_MODE_S_LINEAR:
		CreateOverlaysSL() ;
		break;
	default:
		break;
	}
}

void DopplerOverlays::CreateOverlaysAH()
{
	GROUP_CONFIG&		   _group = m_pConfigure->group[m_nGroup];
	DopplerViewItems* _pItemGroup = m_pView->GetItemGroup() ;
	if(_group.eTxRxMode == setup_TX_RX_MODE_TOFD)
	{
		if(_group.bShowLwBw) {
			_pItemGroup->EnableItems(OVERLAYS_LW_BW);
			_pItemGroup->SetLwBwPos(_group.afCursor[setup_CURSOR_TFOD_LW], _group.afCursor[setup_CURSOR_TFOD_BW]);
			_pItemGroup->SetLwBwId(setup_CURSOR_TFOD_LW, setup_CURSOR_TFOD_BW);
		}
        if(_group.bShowDepthCal) {
            _pItemGroup->EnableItems(OVERLAYS_CALIBRATION);
            _pItemGroup->SetCalibrationPos(_group.afCursor[setup_CURSOR_TOFD_CAL]);
            _pItemGroup->SetCalibrationId(setup_CURSOR_TOFD_CAL);
        }
	}
	//-------------------------------------------------------------------

    if(_group.eTxRxMode != setup_TX_RX_MODE_TOFD)
    {
		_pItemGroup->EnableItems(OVERLAYS_GATE);
		_pItemGroup->SetGateDrawMode(GATE_MODE_GATE_HORIZENTAL);
        int _nScanPos = m_pProcess->GetScanIndexPos();
		PEAK_CONFIG _info[setup_GATE_MAX];
        m_pProcess->GetGatePeakInfos(m_nGroup, _nScanPos, m_nLaw, _info);
        //m_pProcess->GetGateRangeInfos(m_nGroup, m_nLaw, _info);
		_pItemGroup->SetGatePos(0 , _info[setup_GATE_A].fGs, _info[setup_GATE_A].fGw, _info[setup_GATE_A].fGh) ;
		_pItemGroup->SetGatePos(1 , _info[setup_GATE_B].fGs, _info[setup_GATE_B].fGw, _info[setup_GATE_B].fGh) ;
		_pItemGroup->SetGatePos(2 , _info[setup_GATE_I].fGs, _info[setup_GATE_I].fGw, _info[setup_GATE_I].fGh) ;
    }

	if(_group.bShowCursor)
	{
		int _ScanIndex = m_pProcess->GetScanIndexPos();

		_group.afCursor[setup_CURSOR_A_REF] = m_pProcess->GetPeakTraceHeight(m_nGroup,
										   _ScanIndex,
										   m_nLaw,
										   _group.afCursor[setup_CURSOR_U_REF]);
		_group.afCursor[setup_CURSOR_A_MES] = m_pProcess->GetPeakTraceHeight(m_nGroup,
										   _ScanIndex,
										   m_nLaw,
										   _group.afCursor[setup_CURSOR_U_MES]);

		_pItemGroup->EnableItems(OVERLAYS_CURSOR);
		_pItemGroup->SetCursorPos(0 , _group.afCursor[setup_CURSOR_A_REF]);
		_pItemGroup->SetCursorPos(1 , _group.afCursor[setup_CURSOR_A_MES]);
		_pItemGroup->SetCursorPos(2 , _group.afCursor[setup_CURSOR_U_REF]);
		_pItemGroup->SetCursorPos(3 , _group.afCursor[setup_CURSOR_U_MES]);
		_pItemGroup->SetCursorId(0 , setup_CURSOR_A_REF);
		_pItemGroup->SetCursorId(1 , setup_CURSOR_A_MES);
		_pItemGroup->SetCursorId(2 , setup_CURSOR_U_REF);
		_pItemGroup->SetCursorId(3 , setup_CURSOR_U_MES);
        if(bHideCursor)
        {
            HideMode = -1;
        }
	}

	if(_group.bShowThickness)
	{
		_pItemGroup->EnableItems(OVERLAYS_THICKNESS);
		_pItemGroup->SetThicknessDirection(true);
		_pItemGroup->SetThicknessInterval(_group.part.afSize[0]);
	}

	_pItemGroup->UpdateItems();

}

void DopplerOverlays::CreateOverlaysAV()
{
	GROUP_CONFIG&		   _group = m_pConfigure->group[m_nGroup];
	DopplerViewItems* _pItemGroup = m_pView->GetItemGroup() ;
	if(_group.eTxRxMode == setup_TX_RX_MODE_TOFD)
	{
		if(_group.bShowLwBw) {
			_pItemGroup->EnableItems(OVERLAYS_LW_BW);
			_pItemGroup->SetLwBwPos(_group.afCursor[setup_CURSOR_TFOD_LW], _group.afCursor[setup_CURSOR_TFOD_BW]);
			_pItemGroup->SetLwBwId(setup_CURSOR_TFOD_LW, setup_CURSOR_TFOD_BW);
		}
        if(_group.bShowDepthCal) {
            _pItemGroup->EnableItems(OVERLAYS_CALIBRATION);
            _pItemGroup->SetCalibrationPos(_group.afCursor[setup_CURSOR_TOFD_CAL]);
            _pItemGroup->SetCalibrationId(setup_CURSOR_TOFD_CAL);
        }
	}
    if(_group.eTxRxMode != setup_TX_RX_MODE_TOFD)
    {
		_pItemGroup->EnableItems(OVERLAYS_GATE);
		_pItemGroup->SetGateDrawMode(GATE_MODE_GATE_VERTICAL);
        int _nScanPos = m_pProcess->GetScanIndexPos();
		PEAK_CONFIG _info[setup_GATE_MAX];
        //m_pProcess->GetGateRangeInfos(m_nGroup, m_nLaw, _info);
        m_pProcess->GetGatePeakInfos(m_nGroup, _nScanPos, m_nLaw, _info);
		_pItemGroup->SetGatePos(0 , _info[setup_GATE_A].fGs, _info[setup_GATE_A].fGw, _info[setup_GATE_A].fGh) ;
		_pItemGroup->SetGatePos(1 , _info[setup_GATE_B].fGs, _info[setup_GATE_B].fGw, _info[setup_GATE_B].fGh) ;
		_pItemGroup->SetGatePos(2 , _info[setup_GATE_I].fGs, _info[setup_GATE_I].fGw, _info[setup_GATE_I].fGh) ;
    }

	if(_group.bShowCursor)
	{
		int _ScanIndex = m_pProcess->GetScanIndexPos();

		_group.afCursor[setup_CURSOR_A_REF] = m_pProcess->GetPeakTraceHeight(m_nGroup,
										   _ScanIndex,
										   m_nLaw,
										   _group.afCursor[setup_CURSOR_U_REF]);
		_group.afCursor[setup_CURSOR_A_MES] = m_pProcess->GetPeakTraceHeight(m_nGroup,
										   _ScanIndex,
										   m_nLaw,
										   _group.afCursor[setup_CURSOR_U_MES]);
		//----------------------------------------------------------------

		_pItemGroup->EnableItems(OVERLAYS_CURSOR);
		_pItemGroup->SetCursorPos(0 , _group.afCursor[setup_CURSOR_U_REF]);
		_pItemGroup->SetCursorPos(1 , _group.afCursor[setup_CURSOR_U_MES]);
		_pItemGroup->SetCursorPos(2 , _group.afCursor[setup_CURSOR_A_REF]);
		_pItemGroup->SetCursorPos(3 , _group.afCursor[setup_CURSOR_A_MES]);
		_pItemGroup->SetCursorId(0 , setup_CURSOR_U_REF);
		_pItemGroup->SetCursorId(1 , setup_CURSOR_U_MES);
		_pItemGroup->SetCursorId(2 , setup_CURSOR_A_REF);
		_pItemGroup->SetCursorId(3 , setup_CURSOR_A_MES);
        if(bHideCursor)
        {
            HideMode = -1;
        }
	}

	if(_group.bShowThickness)
	{
		_pItemGroup->EnableItems(OVERLAYS_THICKNESS);
		_pItemGroup->SetThicknessDirection(false);
		_pItemGroup->SetThicknessInterval(_group.part.afSize[0]);
	}

	_pItemGroup->UpdateItems();
}

void DopplerOverlays::CreateOverlaysBH()
{
	GROUP_CONFIG&          _group = m_pConfigure->group[m_nGroup];
	DopplerViewItems* _pItemGroup = m_pView->GetItemGroup() ;

	if(_group.bShowDefect)
	{
		_pItemGroup->EnableItems(OVERLAYS_DEFECT);

		QRectF _rect;
		int _iNO = m_pConfigure->GetDefectCnt(m_nGroup);
		float _fStart, _fData;
		_pItemGroup->SetDefectIndex(m_pConfigure->m_dfParam[m_nGroup].index);
		_pItemGroup->ClearDefect();
		for(int i = 0; i < _iNO; i++)
		{
			_fData = m_pConfigure->DefectHeightPos(m_nGroup, &_fStart, i);
			_rect.setLeft(_fStart);
			_rect.setRight(_fStart + _fData);

			_fData = m_pConfigure->DefectLengthPos(m_nGroup, &_fStart, i);
			_rect.setTop(_fStart);
			_rect.setBottom(_fStart + _fData);

			_pItemGroup->SetDefect(i, _rect);
		}
	}
	if(_group.eTxRxMode == setup_TX_RX_MODE_TOFD)
	{
		if(_group.bShowLwBw) {
			_pItemGroup->EnableItems(OVERLAYS_LW_BW);
			_pItemGroup->SetLwBwPos(_group.afCursor[setup_CURSOR_TFOD_LW], _group.afCursor[setup_CURSOR_TFOD_BW]);
			_pItemGroup->SetLwBwId(setup_CURSOR_TFOD_LW, setup_CURSOR_TFOD_BW);
		}
        if(_group.bShowDepthCal) {
            _pItemGroup->EnableItems(OVERLAYS_CALIBRATION);
            _pItemGroup->SetCalibrationPos(_group.afCursor[setup_CURSOR_TOFD_CAL]);
            _pItemGroup->SetCalibrationId(setup_CURSOR_TOFD_CAL);
        }
	}
    if(_group.eTxRxMode != setup_TX_RX_MODE_TOFD)
    {
		_pItemGroup->EnableItems(OVERLAYS_GATE);
		_pItemGroup->SetGateDrawMode(GATE_MODE_LINE_HORIZENTAL);
        int _nScanPos = m_pProcess->GetScanIndexPos();
		PEAK_CONFIG _info[setup_GATE_MAX];
        m_pProcess->GetGatePeakInfos(m_nGroup, _nScanPos, m_nLaw, _info);
        //m_pProcess->GetGateRangeInfos(m_nGroup, m_nLaw, _info);
		_pItemGroup->SetGatePos(0 , _info[setup_GATE_A].fGs, _info[setup_GATE_A].fGw, _info[setup_GATE_A].fGh) ;
		_pItemGroup->SetGatePos(1 , _info[setup_GATE_B].fGs, _info[setup_GATE_B].fGw, _info[setup_GATE_B].fGh) ;
		_pItemGroup->SetGatePos(2 , _info[setup_GATE_I].fGs, _info[setup_GATE_I].fGw, _info[setup_GATE_I].fGh) ;
    }

	if(_group.bShowCursor)
	{
		_pItemGroup->EnableItems(OVERLAYS_CURSOR);
		_pItemGroup->SetCursorPos(2 , _group.afCursor[setup_CURSOR_U_REF]);
		_pItemGroup->SetCursorPos(3 , _group.afCursor[setup_CURSOR_U_MES]);
		_pItemGroup->SetCursorPos(0 , _group.afCursor[setup_CURSOR_S_REF]);
		_pItemGroup->SetCursorPos(1 , _group.afCursor[setup_CURSOR_S_MES]);
		_pItemGroup->SetCursorId(0 , setup_CURSOR_S_REF);
		_pItemGroup->SetCursorId(1 , setup_CURSOR_S_MES);
		_pItemGroup->SetCursorId(2 , setup_CURSOR_U_REF);
		_pItemGroup->SetCursorId(3 , setup_CURSOR_U_MES);
		//  tofd parabola
		if(_group.eTxRxMode == setup_TX_RX_MODE_TOFD)
		{
			_pItemGroup->EnableItems(OVERLAYS_PARABOLA);
			_pItemGroup->SetParabolaDirection(false);
		}
        if(bHideCursor)
        {
            HideMode = -1;
        }
	}

	if(_group.bShowThickness)
	{
		_pItemGroup->EnableItems(OVERLAYS_THICKNESS);
		_pItemGroup->SetThicknessDirection(true);
		_pItemGroup->SetThicknessInterval(_group.part.afSize[0]);
	}

	_pItemGroup->EnableItems(OVERLAYS_SCAN_MARKER);
	_pItemGroup->SetScanMarkerDirectionHorizental(true);
//	_pItemGroup->SetScanMarkerPos(m_pConfigure->common.scanner.fScanPos);
    if(m_pConfigure->common.scanner.fScanStart2 > m_pConfigure->common.scanner.fScanPos) {
       _pItemGroup->SetScanMarkerPos(m_pConfigure->common.scanner.fScanStart2);
    } else {
        _pItemGroup->SetScanMarkerPos(m_pConfigure->common.scanner.fScanPos);
    }

	_pItemGroup->UpdateItems();
}

void DopplerOverlays::CreateOverlaysBV()
{
	GROUP_CONFIG&		   _group = m_pConfigure->group[m_nGroup];
	DopplerViewItems* _pItemGroup = m_pView->GetItemGroup() ;

	if(_group.bShowDefect)
	{
		_pItemGroup->EnableItems(OVERLAYS_DEFECT);

		QRectF _rect;
		int _iNO = m_pConfigure->GetDefectCnt(m_nGroup);
		float _fStart, _fData;
		_pItemGroup->SetDefectIndex(m_pConfigure->m_dfParam[m_nGroup].index);
		_pItemGroup->ClearDefect();
		for(int i = 0; i < _iNO; i++)
		{
			_fData = m_pConfigure->DefectHeightPos(m_nGroup, &_fStart, i);
			_rect.setTop(_fStart);
			_rect.setBottom(_fStart + _fData);

			_fData = m_pConfigure->DefectLengthPos(m_nGroup, &_fStart, i);
			_rect.setLeft(_fStart);
			_rect.setRight(_fStart + _fData);

			_pItemGroup->SetDefect(i, _rect);
		}
	}
	if(_group.eTxRxMode == setup_TX_RX_MODE_TOFD)
	{
        if(_group.bShowLwBw){
			_pItemGroup->EnableItems(OVERLAYS_LW_BW);
			_pItemGroup->SetLwBwPos(_group.afCursor[setup_CURSOR_TFOD_LW], _group.afCursor[setup_CURSOR_TFOD_BW]);
			_pItemGroup->SetLwBwId(setup_CURSOR_TFOD_LW, setup_CURSOR_TFOD_BW);
		}
        if(_group.bShowDepthCal) {
            _pItemGroup->EnableItems(OVERLAYS_CALIBRATION);
            _pItemGroup->SetCalibrationPos(_group.afCursor[setup_CURSOR_TOFD_CAL]);
            _pItemGroup->SetCalibrationId(setup_CURSOR_TOFD_CAL);
        }
	}
	//-------------------------------------------------------------------
    if(_group.eTxRxMode != setup_TX_RX_MODE_TOFD)
    {
		_pItemGroup->EnableItems(OVERLAYS_GATE);
		_pItemGroup->SetGateDrawMode(GATE_MODE_LINE_VERTICAL);
        int _nScanPos = m_pProcess->GetScanIndexPos();
		PEAK_CONFIG _info[setup_GATE_MAX];
        m_pProcess->GetGatePeakInfos(m_nGroup, _nScanPos, m_nLaw, _info);
        //m_pProcess->GetGateRangeInfos(m_nGroup, m_nLaw, _info);
		_pItemGroup->SetGatePos(0 , _info[setup_GATE_A].fGs, _info[setup_GATE_A].fGw, _info[setup_GATE_A].fGh) ;
		_pItemGroup->SetGatePos(1 , _info[setup_GATE_B].fGs, _info[setup_GATE_B].fGw, _info[setup_GATE_B].fGh) ;
		_pItemGroup->SetGatePos(2 , _info[setup_GATE_I].fGs, _info[setup_GATE_I].fGw, _info[setup_GATE_I].fGh) ;
    }

	if(_group.bShowCursor)
	{
		_pItemGroup->EnableItems(OVERLAYS_CURSOR);
		_pItemGroup->SetCursorPos(0 , _group.afCursor[setup_CURSOR_U_REF]);
		_pItemGroup->SetCursorPos(1 , _group.afCursor[setup_CURSOR_U_MES]);
		_pItemGroup->SetCursorPos(2 , _group.afCursor[setup_CURSOR_S_REF]);
		_pItemGroup->SetCursorPos(3 , _group.afCursor[setup_CURSOR_S_MES]);
		_pItemGroup->SetCursorId(0 , setup_CURSOR_U_REF);
		_pItemGroup->SetCursorId(1 , setup_CURSOR_U_MES);
		_pItemGroup->SetCursorId(2 , setup_CURSOR_S_REF);
		_pItemGroup->SetCursorId(3 , setup_CURSOR_S_MES);
		//  tofd parabola
		if(_group.eTxRxMode == setup_TX_RX_MODE_TOFD)
		{
			_pItemGroup->EnableItems(OVERLAYS_PARABOLA);
			_pItemGroup->SetParabolaDirection(true);
		}
        if(bHideCursor)
        {
            HideMode = -1;
        }
	}

	if(_group.bShowThickness)
	{
		_pItemGroup->EnableItems(OVERLAYS_THICKNESS);
		_pItemGroup->SetThicknessDirection(false);
		_pItemGroup->SetThicknessInterval(_group.part.afSize[0]);
	}

	_pItemGroup->EnableItems(OVERLAYS_SCAN_MARKER);
	_pItemGroup->SetScanMarkerDirectionHorizental(false);
//	_pItemGroup->SetScanMarkerPos(m_pConfigure->common.scanner.fScanPos);
    if(m_pConfigure->common.scanner.fScanStart2 > m_pConfigure->common.scanner.fScanPos) {
       _pItemGroup->SetScanMarkerPos(m_pConfigure->common.scanner.fScanStart2);
    } else {
        _pItemGroup->SetScanMarkerPos(m_pConfigure->common.scanner.fScanPos);
    }

	_pItemGroup->UpdateItems();
}

void DopplerOverlays::CreateOverlaysCH()
{
	GROUP_CONFIG&            group = m_pConfigure->group[m_nGroup];
	DopplerViewItems* _pItemGroup  = m_pView->GetItemGroup() ;
    ParameterProcess* _process = ParameterProcess::Instance();
    if(group.bShowDefect)
    {
        _pItemGroup->EnableItems(OVERLAYS_DEFECT);

        QRectF _rect;
        int _iNO = m_pConfigure->GetDefectCnt(m_nGroup);
        float _fStart, _fData;
        _pItemGroup->SetDefectIndex(m_pConfigure->m_dfParam[m_nGroup].index);
        _pItemGroup->ClearDefect();
        for(int i = 0; i < _iNO; i++)
        {
            _fData = m_pConfigure->DefectLengthPos(m_nGroup, &_fStart, i);
            _rect.setLeft(_fStart);
            _rect.setRight(_fStart + _fData);

            if (!group.TopCInfo.TOPCStatus) {
                _fData = m_pConfigure->DefectVPAPos(m_nGroup, &_fStart, i);
            } else {
                _fData = m_pConfigure->DefectWidthPos(m_nGroup, &_fStart, i);
            }
            _rect.setTop(_fStart);
            _rect.setBottom(_fStart + _fData);

            _pItemGroup->SetDefect(i, _rect);
        }
    }

    if(group.bShowCursor)
	{
        _pItemGroup->EnableItems(OVERLAYS_CURSOR);
        bool topc, topcMerge;
        m_pView->GetCScanTopcDis(topc, topcMerge);
        if(group.TopCInfo.TOPCStatus || topc || topcMerge){

            _pItemGroup->SetCursorPos(0 , group.afCursor[setup_CURSOR_I_REF]);
            _pItemGroup->SetCursorPos(1 , group.afCursor[setup_CURSOR_I_MES]);
            _pItemGroup->SetCursorId(0 , setup_CURSOR_I_REF);
            _pItemGroup->SetCursorId(1 , setup_CURSOR_I_MES);

        }else{
            _pItemGroup->SetCursorPos(0 , group.afCursor[setup_CURSOR_VPA_REF]);
            _pItemGroup->SetCursorPos(1 , group.afCursor[setup_CURSOR_VPA_MES]);
            _pItemGroup->SetCursorId(0 , setup_CURSOR_VPA_REF);
            _pItemGroup->SetCursorId(1 , setup_CURSOR_VPA_MES);
        }

        _pItemGroup->SetCursorPos(2 , group.afCursor[setup_CURSOR_S_REF]);
        _pItemGroup->SetCursorPos(3 , group.afCursor[setup_CURSOR_S_MES]);
        _pItemGroup->SetCursorId(2 , setup_CURSOR_S_REF);
        _pItemGroup->SetCursorId(3 , setup_CURSOR_S_MES);

        if(bHideCursor)
        {
            HideMode = 0;
        }
	}

    if(m_pConfigure->common.scanner.eScanType == setup_SCAN_TYPE_ONE_LINE){
        //qDebug()<<"setup_CURSOR_C_ANGLE"<<group.afCursor[setup_CURSOR_LAW];
        _pItemGroup->SetCursorPos(4 , group.afCursor[setup_CURSOR_C_ANGLE]);
//        if(group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL){
//            _pItemGroup->SetCursorPos(4 , group.afCursor[setup_CURSOR_C_ANGLE]);
//            _pItemGroup->SetCursorId(4 , setup_CURSOR_C_ANGLE);
//        }else{
//            _pItemGroup->SetCursorPos(4 , group.afCursor[setup_CURSOR_LAW]);
//            _pItemGroup->SetCursorId(4 , setup_CURSOR_LAW);
//        }
    }else{
//        float indexPos = m_pConfigure->common.scanner.fIndexPos;
//        float coverlength = _process->GetRasterCoveredLength(m_nGroup);
//        int beamQty = _process->GetGroupLawQty(m_nGroup);
//        int curLaw = group.afCursor[setup_CURSOR_LAW];
//        float curPos = curLaw * coverlength / beamQty;
        float indexPos = _process->GetRasterCurrentIndexPos(m_nGroup);
        _pItemGroup->SetCursorPos( 4, indexPos);
        //_pItemGroup->SetCursorId(4 , setup_CURSOR_C_ANGLE);
    }

    _pItemGroup->SetCursorId(4 , setup_CURSOR_C_ANGLE);
	_pItemGroup->EnableItems(OVERLAYS_SCAN_MARKER);
	_pItemGroup->SetScanMarkerDirectionHorizental(false);


    if(m_pConfigure->common.scanner.fScanStart2 > m_pConfigure->common.scanner.fScanPos) {
       _pItemGroup->SetScanMarkerPos(m_pConfigure->common.scanner.fScanStart2);
    } else{
        _pItemGroup->SetScanMarkerPos(m_pConfigure->common.scanner.fScanPos);
    }
    if(!group.TopCInfo.TOPCStatus){
        _pItemGroup->EnableItems(OVERLAYS_LAW_MARKER_C_SCAN);
    }
    if(group.TopCInfo.TOPCValid){
        _pItemGroup->EnableItems( OVERLAYS_C_WELD_BORDER);
        _pItemGroup->SetWeldBorderDirection(true);
    }
	_pItemGroup->UpdateItems();

}

void DopplerOverlays::CreateOverlaysCV()
{
	GROUP_CONFIG&            group = m_pConfigure->group[m_nGroup];
	DopplerViewItems* _pItemGroup  = m_pView->GetItemGroup() ;
    ParameterProcess* _process = ParameterProcess::Instance();
    if(group.bShowDefect)
    {
        _pItemGroup->EnableItems(OVERLAYS_DEFECT);

        QRectF _rect;
        int _iNO = m_pConfigure->GetDefectCnt(m_nGroup);
        float _fStart, _fData;
        _pItemGroup->SetDefectIndex(m_pConfigure->m_dfParam[m_nGroup].index);
        _pItemGroup->ClearDefect();
        for(int i = 0; i < _iNO; i++)
        {
            _fData = m_pConfigure->DefectLengthPos(m_nGroup, &_fStart, i);
            _rect.setTop(_fStart);
            _rect.setBottom(_fStart + _fData);

            if (!group.TopCInfo.TOPCStatus) {
                _fData = m_pConfigure->DefectVPAPos(m_nGroup, &_fStart, i);
            } else {
                _fData = m_pConfigure->DefectWidthPos(m_nGroup, &_fStart, i);
            }
            _rect.setLeft(_fStart);
            _rect.setRight(_fStart + _fData);

            _pItemGroup->SetDefect(i, _rect);
        }
    }
	if(group.bShowCursor)
	{
		_pItemGroup->EnableItems(OVERLAYS_CURSOR);
        if(group.TopCInfo.TOPCStatus){
            _pItemGroup->SetCursorPos(2 , group.afCursor[setup_CURSOR_I_REF]);
            _pItemGroup->SetCursorPos(3 , group.afCursor[setup_CURSOR_I_MES]);
            _pItemGroup->SetCursorId(2 , setup_CURSOR_I_REF);
            _pItemGroup->SetCursorId(3 , setup_CURSOR_I_MES);
        }else{
            _pItemGroup->SetCursorPos(2 , group.afCursor[setup_CURSOR_VPA_REF]);
            _pItemGroup->SetCursorPos(3 , group.afCursor[setup_CURSOR_VPA_MES]);
            _pItemGroup->SetCursorId(2 , setup_CURSOR_VPA_REF);
            _pItemGroup->SetCursorId(3 , setup_CURSOR_VPA_MES);
        }
		_pItemGroup->SetCursorPos(0 , group.afCursor[setup_CURSOR_S_REF]);
        _pItemGroup->SetCursorPos(1 , group.afCursor[setup_CURSOR_S_MES]);				
		_pItemGroup->SetCursorId(0 , setup_CURSOR_S_REF);
		_pItemGroup->SetCursorId(1 , setup_CURSOR_S_MES);

        if(bHideCursor)
        {
            HideMode = 2;
        }
	}
    if(m_pConfigure->common.scanner.eScanType == setup_SCAN_TYPE_ONE_LINE){
        _pItemGroup->SetCursorPos(4 , group.afCursor[setup_CURSOR_C_ANGLE]);
    }else{
        float indexPos = m_pConfigure->common.scanner.fIndexPos;
        float coverlength = _process->GetRasterCoveredLength(m_nGroup);
        int beamQty = _process->GetGroupLawQty(m_nGroup);
        int curLaw = group.afCursor[setup_CURSOR_LAW];
        float curPos = curLaw * coverlength / beamQty;
        _pItemGroup->SetCursorPos( 4, indexPos + curPos);
    }
    //_pItemGroup->SetCursorPos(4 , group.afCursor[setup_CURSOR_C_ANGLE]);
    _pItemGroup->SetCursorId(4 , setup_CURSOR_C_ANGLE);
	_pItemGroup->EnableItems(OVERLAYS_SCAN_MARKER);
	_pItemGroup->SetScanMarkerDirectionHorizental(true);

//	_pItemGroup->SetScanMarkerPos(m_pConfigure->common.scanner.fScanPos);
    if(m_pConfigure->common.scanner.fScanStart2 > m_pConfigure->common.scanner.fScanPos) {
       _pItemGroup->SetScanMarkerPos(m_pConfigure->common.scanner.fScanStart2);
    } else {
        _pItemGroup->SetScanMarkerPos(m_pConfigure->common.scanner.fScanPos);
    }
    if(!group.TopCInfo.TOPCStatus){
        _pItemGroup->EnableItems(OVERLAYS_LAW_MARKER_C_SCAN);
    }
    if(group.TopCInfo.TOPCValid){
        _pItemGroup->EnableItems( OVERLAYS_C_WELD_BORDER);
        _pItemGroup->SetWeldBorderDirection(false);
    }
    //_pItemGroup->UpdateItems();
	_pItemGroup->UpdateItems();
}

void DopplerOverlays::CreateOverlaysSS()
{
	GROUP_CONFIG&            group = m_pConfigure->group[m_nGroup];
	DopplerViewItems* _pItemGroup  = m_pView->GetItemGroup() ;
    if(group.eGroupMode != setup_GROUP_MODE_PA){
        _pItemGroup->EnableItems(OVERLAYS_NONE);
        return;
    }

	if(group.bShowDefect)
	{
		_pItemGroup->EnableItems(OVERLAYS_DEFECT);

		QRectF _rect;
		int _iNO = m_pConfigure->GetDefectCnt(m_nGroup);
		float _fStart, _fData;
		_pItemGroup->SetDefectIndex(m_pConfigure->m_dfParam[m_nGroup].index);
		_pItemGroup->ClearDefect();
        if (group.bShowCurrentDefect) {
            _fData = m_pConfigure->DefectWidthPos(m_nGroup, &_fStart, m_pConfigure->m_dfParam[m_nGroup].index);
            _rect.setLeft(_fStart);
            _rect.setRight(_fStart + _fData);

            _fData = m_pConfigure->DefectHeightPos(m_nGroup, &_fStart, m_pConfigure->m_dfParam[m_nGroup].index);
            _rect.setTop(_fStart);
            _rect.setBottom(_fStart + _fData);

            _pItemGroup->SetDefect(m_pConfigure->m_dfParam[m_nGroup].index, _rect);
        } else {
            for(int i = 0; i < _iNO; i++)
            {
                _fData = m_pConfigure->DefectWidthPos(m_nGroup, &_fStart, i);
                _rect.setLeft(_fStart);
                _rect.setRight(_fStart + _fData);

                _fData = m_pConfigure->DefectHeightPos(m_nGroup, &_fStart, i);
                _rect.setTop(_fStart);
                _rect.setBottom(_fStart + _fData);

                _pItemGroup->SetDefect(i, _rect);
            }
        }
	}
	//-------------------------------------------------------------------
//	if(group.bShowGate)
//	{
		_pItemGroup->EnableItems(OVERLAYS_GATE);
        _pItemGroup->SetGateDrawMode(GATE_MODE_S_SOUNDPATH);
        //_pItemGroup->SetGateDrawMode(GATE_MODE_LINE_HORIZENTAL);
        int _nScanPos = m_pProcess->GetScanIndexPos();
		PEAK_CONFIG _info[setup_GATE_MAX];
        m_pProcess->GetGatePeakInfos(m_nGroup, _nScanPos, m_nLaw, _info);
        //m_pProcess->GetGateRangeInfos(m_nGroup, m_nLaw, _info);
		_pItemGroup->SetGatePos(0 , _info[setup_GATE_A].fGs, _info[setup_GATE_A].fGw, _info[setup_GATE_A].fGh) ;
		_pItemGroup->SetGatePos(1 , _info[setup_GATE_B].fGs, _info[setup_GATE_B].fGw, _info[setup_GATE_B].fGh) ;
		_pItemGroup->SetGatePos(2 , _info[setup_GATE_I].fGs, _info[setup_GATE_I].fGw, _info[setup_GATE_I].fGh) ;
    //}

	if(group.bShowCursor)
	{
		_pItemGroup->EnableItems(OVERLAYS_CURSOR);
		_pItemGroup->SetCursorPos(2 , group.afCursor[setup_CURSOR_U_REF]);
		_pItemGroup->SetCursorPos(3 , group.afCursor[setup_CURSOR_U_MES]);
		_pItemGroup->SetCursorPos(0 , group.afCursor[setup_CURSOR_S_REF]);
		_pItemGroup->SetCursorPos(1 , group.afCursor[setup_CURSOR_S_MES]);
		_pItemGroup->SetCursorId(0 , setup_CURSOR_S_REF);
		_pItemGroup->SetCursorId(1 , setup_CURSOR_S_MES);
		_pItemGroup->SetCursorId(2 , setup_CURSOR_U_REF);
		_pItemGroup->SetCursorId(3 , setup_CURSOR_U_MES);
	}

	if(group.bShowThickness)
	{
		_pItemGroup->EnableItems(OVERLAYS_THICKNESS);
		_pItemGroup->SetThicknessDirection(true);
		_pItemGroup->SetThicknessInterval(group.part.afSize[0]);
	}

	_pItemGroup->EnableItems(OVERLAYS_LAW_MARKER);
	_pItemGroup->EnableMarkerQty(m_pView->GetLawIdentify() + 1);

    _pItemGroup->EnableItems(OVERLAYS_NEWDEFECT);

	QVector<QLineF> _line ;
	GetCurrentLawMarkerPos(&_line);
	_pItemGroup->SetupMarkersVector(&_line);
	QVector<QString> _str ;
	GetLawMarkers(&_str) ;
	_pItemGroup->SetupLawMarkerString(&_str);
	_pItemGroup->UpdateItems();
}


void DopplerOverlays::CreateOverlaysSA()
{
	GROUP_CONFIG&            group = m_pConfigure->group[m_nGroup];
	DopplerViewItems* _pItemGroup  = m_pView->GetItemGroup() ;
    if(group.eGroupMode != setup_GROUP_MODE_PA){
        _pItemGroup->EnableItems(OVERLAYS_NONE);
        return;
    }

	if(group.bShowDefect)
	{
		_pItemGroup->EnableItems(OVERLAYS_DEFECT);

		QRectF _rect;
		int _iNO = m_pConfigure->GetDefectCnt(m_nGroup);
		float _fStart, _fData;
		_pItemGroup->SetDefectIndex(m_pConfigure->m_dfParam[m_nGroup].index);
        _pItemGroup->ClearDefect();
        if (group.bShowCurrentDefect && _iNO > 0) {
            _fData = m_pConfigure->DefectWidthPos(m_nGroup, &_fStart, m_pConfigure->m_dfParam[m_nGroup].index);
            _rect.setLeft(_fStart);
            _rect.setRight(_fStart + _fData);

            _fData = m_pConfigure->DefectHeightPos(m_nGroup, &_fStart, m_pConfigure->m_dfParam[m_nGroup].index);
            _rect.setTop(_fStart);
            _rect.setBottom(_fStart + _fData);

            _pItemGroup->SetDefect(m_pConfigure->m_dfParam[m_nGroup].index, _rect);
        } else {
            for(int i = 0; i < _iNO; i++)
            {
                _fData = m_pConfigure->DefectWidthPos(m_nGroup, &_fStart, i);
                _rect.setLeft(_fStart);
                _rect.setRight(_fStart + _fData);

                _fData = m_pConfigure->DefectHeightPos(m_nGroup, &_fStart, i);
                _rect.setTop(_fStart);
                _rect.setBottom(_fStart + _fData);

                _pItemGroup->SetDefect(i, _rect);
            }
        }
	}
	//-------------------------------------------------------------------
//	if(group.bShowGate)
//	{
		_pItemGroup->EnableItems(OVERLAYS_GATE);
        _pItemGroup->SetGateDrawMode(GATE_MODE_S_TRUEDEPTH);
        //_pItemGroup->SetGateDrawMode(GATE_MODE_LINE_VERTICAL);
        int _nScanPos = m_pProcess->GetScanIndexPos();
		PEAK_CONFIG _info[setup_GATE_MAX];
        m_pProcess->GetGatePeakInfos(m_nGroup, _nScanPos, m_nLaw, _info);
        //m_pProcess->GetGateRangeInfos(m_nGroup, m_nLaw, _info);
		_pItemGroup->SetGatePos(0 , _info[setup_GATE_A].fGs, _info[setup_GATE_A].fGw, _info[setup_GATE_A].fGh) ;
		_pItemGroup->SetGatePos(1 , _info[setup_GATE_B].fGs, _info[setup_GATE_B].fGw, _info[setup_GATE_B].fGh) ;
		_pItemGroup->SetGatePos(2 , _info[setup_GATE_I].fGs, _info[setup_GATE_I].fGw, _info[setup_GATE_I].fGh) ;
    //}

	if(group.bShowCursor)
	{
		_pItemGroup->EnableItems(OVERLAYS_CURSOR);
		_pItemGroup->SetCursorPos(0 , group.afCursor[setup_CURSOR_U_REF]);
		_pItemGroup->SetCursorPos(1 , group.afCursor[setup_CURSOR_U_MES]);
		_pItemGroup->SetCursorPos(2 , group.afCursor[setup_CURSOR_I_REF]);
		_pItemGroup->SetCursorPos(3 , group.afCursor[setup_CURSOR_I_MES]);

		_pItemGroup->SetCursorId(0 , setup_CURSOR_U_REF);
		_pItemGroup->SetCursorId(1 , setup_CURSOR_U_MES);
		_pItemGroup->SetCursorId(2 , setup_CURSOR_I_REF);
		_pItemGroup->SetCursorId(3 , setup_CURSOR_I_MES);
        if(bHideCursor)
        {
            HideMode = 2;
        }
	}
	if(group.bShowThickness)
	{
		_pItemGroup->EnableItems(OVERLAYS_THICKNESS);
		_pItemGroup->SetThicknessDirection(false);
	}
	_pItemGroup->SetThicknessInterval(group.part.afSize[0]);
    _pItemGroup->EnableItems(OVERLAYS_LAW_MARKER);
	_pItemGroup->EnableMarkerQty(m_pView->GetLawIdentify() + 1);
	QVector<QLineF> _line ;
	GetCurrentLawMarkerPos(&_line);
	_pItemGroup->SetupMarkersVector(&_line);
	QVector<QString> _str ;
	GetLawMarkers(&_str) ;
	_pItemGroup->SetupLawMarkerString(&_str);
	if(group.bShowWeldPart)
	{
		_pItemGroup->EnableItems(OVERLAYS_WELD );
		//_pItemGroup->SetWeldInfo(&group.part.weld);
		_pItemGroup->SetPartInfo(&group.part);
	}
    if(group.TopCInfo.TOPCValid){
        _pItemGroup->EnableItems( OVERLAYS_TOPC_WIDTH);
    }
	_pItemGroup->UpdateItems();
}

void DopplerOverlays::CreateOverlaysSL()
{
	GROUP_CONFIG&            group = m_pConfigure->group[m_nGroup];
	DopplerViewItems* _pItemGroup  = m_pView->GetItemGroup() ;
    if(group.eGroupMode != setup_GROUP_MODE_PA){
        _pItemGroup->EnableItems(OVERLAYS_NONE);
        return;
    }

	if(group.bShowDefect)
	{
		_pItemGroup->EnableItems(OVERLAYS_DEFECT);

		QRectF _rect;
		int _iNO = m_pConfigure->GetDefectCnt(m_nGroup);
		float _fStart, _fData;
		_pItemGroup->SetDefectIndex(m_pConfigure->m_dfParam[m_nGroup].index);
		_pItemGroup->ClearDefect();
        if (group.bShowCurrentDefect) {
            _fData = m_pConfigure->DefectWidthPos(m_nGroup, &_fStart, m_pConfigure->m_dfParam[m_nGroup].index);
            _rect.setLeft(_fStart);
            _rect.setRight(_fStart + _fData);

            _fData = m_pConfigure->DefectHeightPos(m_nGroup, &_fStart, m_pConfigure->m_dfParam[m_nGroup].index);
            _rect.setTop(_fStart);
            _rect.setBottom(_fStart + _fData);

            _pItemGroup->SetDefect(m_pConfigure->m_dfParam[m_nGroup].index, _rect);
        } else {
            for(int i = 0; i < _iNO; i++)
            {
                _fData = m_pConfigure->DefectWidthPos(m_nGroup, &_fStart, i);
                _rect.setLeft(_fStart);
                _rect.setRight(_fStart + _fData);

                _fData = m_pConfigure->DefectHeightPos(m_nGroup, &_fStart, i);
                _rect.setTop(_fStart);
                _rect.setBottom(_fStart + _fData);

                _pItemGroup->SetDefect(i, _rect);
            }
        }
	}
	//-------------------------------------------------------------------
//	if(group.bShowGate)
//	{
		_pItemGroup->EnableItems(OVERLAYS_GATE);
        //_pItemGroup->SetGateDrawMode(GATE_MODE_S_TRUEDEPTH);
        _pItemGroup->SetGateDrawMode(GATE_MODE_LINE_VERTICAL);
        int _nScanPos = m_pProcess->GetScanIndexPos();
		PEAK_CONFIG _info[setup_GATE_MAX];
        m_pProcess->GetGatePeakInfos(m_nGroup, _nScanPos, m_nLaw, _info);
        //m_pProcess->GetGateRangeInfos(m_nGroup, m_nLaw, _info);
		_pItemGroup->SetGatePos(0 , _info[setup_GATE_A].fGs, _info[setup_GATE_A].fGw, _info[setup_GATE_A].fGh) ;
		_pItemGroup->SetGatePos(1 , _info[setup_GATE_B].fGs, _info[setup_GATE_B].fGw, _info[setup_GATE_B].fGh) ;
		_pItemGroup->SetGatePos(2 , _info[setup_GATE_I].fGs, _info[setup_GATE_I].fGw, _info[setup_GATE_I].fGh) ;
    //}

	if(group.bShowCursor)
	{
		_pItemGroup->EnableItems(OVERLAYS_CURSOR);
		_pItemGroup->SetCursorPos(0 , group.afCursor[setup_CURSOR_U_REF]);
		_pItemGroup->SetCursorPos(1 , group.afCursor[setup_CURSOR_U_MES]);
		_pItemGroup->SetCursorPos(2 , group.afCursor[setup_CURSOR_I_REF]);
		_pItemGroup->SetCursorPos(3 , group.afCursor[setup_CURSOR_I_MES]);

		_pItemGroup->SetCursorId(0 , setup_CURSOR_U_REF);
		_pItemGroup->SetCursorId(1 , setup_CURSOR_U_MES);
		_pItemGroup->SetCursorId(2 , setup_CURSOR_I_REF);
		_pItemGroup->SetCursorId(3 , setup_CURSOR_I_MES);
        if(bHideCursor)
        {
            HideMode = 2;
        }
	}

	if(group.bShowThickness)
	{
		_pItemGroup->EnableItems(OVERLAYS_THICKNESS);
		_pItemGroup->SetThicknessDirection(false);
	}
	_pItemGroup->SetThicknessInterval(group.part.afSize[0]);

	_pItemGroup->EnableItems(OVERLAYS_LAW_MARKER);
	_pItemGroup->EnableItems(OVERLAYS_LAW_MARKER);
	_pItemGroup->EnableMarkerQty(m_pView->GetLawIdentify() + 1);
	QVector<QLineF> _line ;
	GetCurrentLawMarkerPos(&_line);
	_pItemGroup->SetupMarkersVector(&_line);
	QVector<QString> _str ;
	GetLawMarkers(&_str) ;
	_pItemGroup->SetupLawMarkerString(&_str);

	if(group.bShowWeldPart)
	{
		_pItemGroup->EnableItems(OVERLAYS_WELD );
		//_pItemGroup->SetWeldInfo(&group.part.weld);
		_pItemGroup->SetPartInfo(&group.part);
	}
    if(group.TopCInfo.TOPCValid){
        _pItemGroup->EnableItems( OVERLAYS_TOPC_WIDTH);
    }

	_pItemGroup->UpdateItems();
}

void DopplerOverlays::UpdateOverlays()
{
    DopplerViewItems* _pItemGroup  = m_pView->GetItemGroup();
	_pItemGroup->EnableItems(OVERLAYS_NONE);
	CreateOverlays();
	m_pView->UpdateScene();
}

void DopplerOverlays::UpdateGate()
{
	DopplerViewItems* _pItemGroup  = m_pView->GetItemGroup() ;
	_pItemGroup->EnableItems(OVERLAYS_NONE);
	CreateOverlays();
	m_pView->UpdateScene();
}

void DopplerOverlays::UpdateCursor()
{
	DopplerViewItems* _pItemGroup  = m_pView->GetItemGroup() ;
	_pItemGroup->EnableItems(OVERLAYS_NONE);
	CreateOverlays();
	m_pView->UpdateScene();
}

#include <gHeader.h>
void DopplerOverlays::GetCurrentLawMarkerPos(QVector<QLineF>* _pVector)
{

	setup_DISPLAY_MODE _eMode  = (setup_DISPLAY_MODE)m_eDisp;
	switch(_eMode)
	{
	case setup_DISPLAY_MODE_S_SOUNDPATH:
		{
			int _nLawQty = m_pProcess->GetGroupLawQty(m_nGroup) ;
			for(int i = 0; i< _nLawQty ; i++)
			{
				QLineF _line( 0 , i+1 , 30 , i+1);
				_pVector->append(_line);
			}
		}
		break;
	case setup_DISPLAY_MODE_S_ATHUMIZ:
		{
			GROUP_CONFIG& _group = m_pConfigure->group[m_nGroup];
			LAW_CONFIG& _law = _group.law ;
            float _fAngleStart = DEGREE_TO_ARCH(_law.nAngleStartRefract/10.0) ;
            float  _fAngleStep = DEGREE_TO_ARCH(_law.nAngleStepRefract/10.0) ;
			float      _fStart = _group.fSampleStart	 ;

            float       _fStop = _group.fSampleRange + _fStart ;
			float*   _pBeamPos = _group.afBeamPos	   ;
			int       _nLawQty = m_pProcess->GetGroupLawQty(m_nGroup) ;

            float thickness=_group.part.afSize[0];


			float _fAngleTmp ;
            float _fPos1 , _fPos2 , _fPos3 , _fPos4 , _fTmp1,_fPos5,_fPos6;
			setup_PROBE_ANGLE _eAngle = m_pProcess->GetProbeAngle(m_nGroup);

			if(_eAngle == setup_PROBE_PART_SKEW_0 )
            {
               float _fIndexOffset = _group.fScanOffset ;

               if(!_group.m_Retype)
               {
                for(int i = 0 ; i < _nLawQty ; i++)
                {
                    _fTmp1 = _fIndexOffset + _pBeamPos[i] ;
                    _fAngleTmp = _fAngleStart + i * _fAngleStep;

                    _fPos1 = _fTmp1+sin(_fAngleTmp)*_fStart;
                    _fPos3 =_fTmp1 + sin(_fAngleTmp)* _fStop;

                    _fPos2 = cos(_fAngleTmp) * _fStart ;
                    _fPos4 = cos(_fAngleTmp) * _fStop  ;
                    QLineF _line( _fPos1 , _fPos2 , _fPos3 , _fPos4);
                    _pVector->append(_line);
                }
               }else{

                   for(int j=0; j<2; j++)
                   {
                   for(int i = 0 ; i < _nLawQty ; i++)
                   {
                       _fTmp1 = _fIndexOffset + _pBeamPos[i] ;
                       _fAngleTmp = _fAngleStart + i * _fAngleStep  ;
                        //-x
//                       _fPos1 = _fTmp1 + sin(_fAngleTmp) * _fStart; // 起点横坐标
                       _fPos1 = _fTmp1+sin(_fAngleTmp)*_fStart;
                       _fPos3 = _fTmp1 + tan(_fAngleTmp) * thickness;// 中间点横坐标
                       _fPos5 = _fTmp1 + sin(_fAngleTmp) * _fStop;// 终点横坐标
                        //-y
                        _fPos2 = cos(_fAngleTmp) * _fStart ;// 起点纵坐标
                        _fPos4 = thickness ;//中间点纵坐标
                        _fPos6 = -((cos(_fAngleTmp) * _fStop)-2*thickness);// 终点纵坐标 mm(关于厚度对称)
                       if(j==0)
                       {
                       /***********扫查轴前半段*************/
                       QLineF _line( _fPos1 , _fPos2 , _fPos3 , _fPos4);
                       _pVector->append(_line);
                       }else{

                      /***********扫查轴后半段*************/
                      QLineF _line2( _fPos3 , _fPos4 , _fPos5 , _fPos6);
                     _pVector->append(_line2);
                            }
                   }

                  }

                  }
            }
			else if(_eAngle == setup_PROBE_PART_SKEW_90 )
			{

               float _fIndexOffset = _group.fIndexOffset ; //步进偏置

               if(!_group.m_Retype)
                {
                for(int i = 0 ; i < _nLawQty ; i++)
                {

                    _fTmp1 = _fIndexOffset + _pBeamPos[i] ;
                    _fAngleTmp = _fAngleStart + i * _fAngleStep  ;
                    _fPos1 = _fTmp1+sin(_fAngleTmp)*_fStart;
                    _fPos3 =_fTmp1 + sin(_fAngleTmp)* _fStop;

                    _fPos2 = cos(_fAngleTmp) * _fStart ;
                    _fPos4 = cos(_fAngleTmp) * _fStop  ;
					QLineF _line( _fPos1 , _fPos2 , _fPos3 , _fPos4);
					_pVector->append(_line);

				}
               }else{

                   for(int j=0; j<2; j++)
                   {
                   for(int i = 0 ; i < _nLawQty ; i++)
                   {
                       _fTmp1 = _fIndexOffset + _pBeamPos[i] ;
                       _fAngleTmp = _fAngleStart + i * _fAngleStep  ;

                        //-x
//                       _fPos1 = _fTmp1 + sin(_fAngleTmp) * _fStart; // 起点横坐标
                       _fPos1 = _fTmp1+sin(_fAngleTmp)*_fStart;
                       _fPos3 = _fTmp1 + tan(_fAngleTmp) * thickness;// 中间点横坐标
                       _fPos5 = _fTmp1 + sin(_fAngleTmp) * _fStop;// 终点横坐标         
                        //-y
                        _fPos2 = cos(_fAngleTmp) * _fStart ;// 起点纵坐标
                        _fPos4 = thickness ;//中间点纵坐标
                        _fPos6 = -((cos(_fAngleTmp) * _fStop)-2*thickness);// 终点纵坐标 mm(关于厚度对称)
                       if(j==0)
                       {
                       /***********扫查轴前半段*************/
                       QLineF _line( _fPos1 , _fPos2 , _fPos3 , _fPos4);
                       _pVector->append(_line);
                       }else{
                      /***********扫查轴后半段*************/
                      QLineF _line2( _fPos3 , _fPos4 , _fPos5 , _fPos6);
                     _pVector->append(_line2);

                            }
                   }
                  }

                 }
			}
			else if(_eAngle == setup_PROBE_PART_SKEW_180 )
            {
               float _fIndexOffset = _group.fScanOffset ;

               if(!_group.m_Retype)
               {
                for(int i = 0 ; i < _nLawQty ; i++)
                {
                    _fTmp1 = _fIndexOffset - _pBeamPos[i] ;
                    _fAngleTmp = _fAngleStart + i * _fAngleStep ;                   
                    _fPos1 = _fTmp1-sin(_fAngleTmp)*_fStart;
                    _fPos3 =_fTmp1 - sin(_fAngleTmp)* _fStop;                    
                    _fPos2 = cos(_fAngleTmp) * _fStart ;
                    _fPos4 = cos(_fAngleTmp) * _fStop  ;
                    QLineF _line( _fPos1 , _fPos2 , _fPos3 , _fPos4);
                    _pVector->append(_line);
                }
               }else{

                   for(int j=0; j<2; j++)
                   {
                   for(int i = 0 ; i < _nLawQty ; i++)
                   {
                       _fTmp1 = _fIndexOffset - _pBeamPos[i] ;
                       _fAngleTmp = _fAngleStart + i * _fAngleStep  ;

                        //-x
//                       _fPos1 = _fTmp1 + sin(_fAngleTmp) * _fStart; // 起点横坐标
                       _fPos1 = _fTmp1-sin(_fAngleTmp)*_fStart;
                       _fPos3 = _fTmp1 - tan(_fAngleTmp) * thickness;// 中间点横坐标
                       _fPos5 = _fTmp1 - sin(_fAngleTmp) * _fStop;// 终点横坐标
                        //-y
                        _fPos2 = cos(_fAngleTmp) * _fStart ;// 起点纵坐标
                        _fPos4 = thickness ;//中间点纵坐标
                        _fPos6 = -((cos(_fAngleTmp) * _fStop)-2*thickness);// 终点纵坐标 mm(关于厚度对称)
                       if(j==0)
                       {
                       /***********扫查轴前半段*************/
                       QLineF _line( _fPos1 , _fPos2 , _fPos3 , _fPos4);
                       _pVector->append(_line);
                       }else{

                      /***********扫查轴后半段*************/
                      QLineF _line2( _fPos3 , _fPos4 , _fPos5 , _fPos6);
                     _pVector->append(_line2);

                            }
                   }

                  }

                  }
            }
			else if(_eAngle == setup_PROBE_PART_SKEW_270 )
            {
               float _fIndexOffset = _group.fIndexOffset ;

               if(!_group.m_Retype)
               {
                for(int i = 0 ; i < _nLawQty ; i++)
                {
                    _fTmp1 = _fIndexOffset - _pBeamPos[i] ;
                    _fAngleTmp = _fAngleStart+ i * _fAngleStep ;

                    _fPos1 = _fTmp1-sin(_fAngleTmp)*_fStart;
                    _fPos3 =_fTmp1 - sin(_fAngleTmp)* _fStop;

                    _fPos2 = cos(_fAngleTmp) * _fStart ;
                    _fPos4 = cos(_fAngleTmp) * _fStop  ;
                    QLineF _line( _fPos1 , _fPos2 , _fPos3 , _fPos4);
                    _pVector->append(_line);
                }
               }else{

                   for(int j=0; j<2; j++)
                   {
                   for(int i = 0 ; i < _nLawQty ; i++)
                   {
                       _fTmp1 = _fIndexOffset - _pBeamPos[i] ;
                       _fAngleTmp = _fAngleStart + i * _fAngleStep  ;

                        //-x
//                       _fPos1 = _fTmp1 + sin(_fAngleTmp) * _fStart; // 起点横坐标

                       _fPos1 = _fTmp1-sin(_fAngleTmp)*_fStart;
                       _fPos3 = _fTmp1 - tan(_fAngleTmp) * thickness;// 中间点横坐标
                       _fPos5 = _fTmp1 - sin(_fAngleTmp) * _fStop;// 终点横坐标
                        //-y
                        _fPos2 = cos(_fAngleTmp) * _fStart ;// 起点纵坐标
                        _fPos4 = thickness ;//中间点纵坐标
                        _fPos6 = -((cos(_fAngleTmp) * _fStop)-2*thickness);// 终点纵坐标 mm(关于厚度对称)
                       if(j==0)
                       {
                       /***********扫查轴前半段*************/
                       QLineF _line( _fPos1 , _fPos2 , _fPos3 , _fPos4);
                       _pVector->append(_line);
                       }else{

                      /***********扫查轴后半段*************/
                      QLineF _line2( _fPos3 , _fPos4 , _fPos5 , _fPos6);
                     _pVector->append(_line2);

                           }
                   }
                  }

                  }
            }
		}
		break;
	case setup_DISPLAY_MODE_S_LINEAR:
		{
			GROUP_CONFIG& _group = m_pConfigure->group[m_nGroup];
			LAW_CONFIG& _law = _group.law ;
			float _fAngleStart = DEGREE_TO_ARCH(_law.nAngleStartRefract / 10.0) ;
			float      _fStart = _group.fSampleStart	 ;
			float       _fStop = _group.fSampleRange + _fStart ;
			float*   _pBeamPos = _group.afBeamPos	   ;
			int       _nLawQty = m_pProcess->GetGroupLawQty(m_nGroup) ;

			float _fPos1 , _fPos2 , _fPos3 , _fPos4 , _fTmp1;

			_fPos2 = cos(_fAngleStart) * _fStart  ;
			_fPos4 = cos(_fAngleStart) * _fStop   ;
			setup_PROBE_ANGLE _eAngle = m_pProcess->GetProbeAngle(m_nGroup);
			if(_eAngle == setup_PROBE_PART_SKEW_0 )
			{
				float _fScanOffset = _group.fScanOffset ;
				for(int i = 0 ; i < _nLawQty ; i++)
				{
					_fTmp1 = _fScanOffset + _pBeamPos[i]  ;
					_fPos1 = _fTmp1 + sin(_fAngleStart) * _fStart;
					_fPos3 = _fTmp1 + sin(_fAngleStart) * _fStop;
					QLineF _line( _fPos1 , _fPos2 , _fPos3 , _fPos4);
					_pVector->append(_line);
				}
			}
			else if(_eAngle == setup_PROBE_PART_SKEW_90 )
			{
				float _fIndexOffset = _group.fIndexOffset ;
				for(int i = 0 ; i < _nLawQty ; i++)
				{
					_fTmp1 = _fIndexOffset + _pBeamPos[i]  ;
					_fPos1 = _fTmp1 + sin(_fAngleStart) * _fStart;
					_fPos3 = _fTmp1 + sin(_fAngleStart) * _fStop;
					QLineF _line( _fPos1 , _fPos2 , _fPos3 , _fPos4);
					_pVector->append(_line);
				}
			}
			else if(_eAngle == setup_PROBE_PART_SKEW_180 )
			{
				float _fScanOffset = _group.fScanOffset ;
				for(int i = 0 ; i < _nLawQty ; i++)
				{
					_fTmp1 = _fScanOffset - _pBeamPos[i]  ;
					_fPos1 = _fTmp1 - sin(_fAngleStart) * _fStart;
					_fPos3 = _fTmp1 - sin(_fAngleStart) * _fStop;
					QLineF _line( _fPos1 , _fPos2 , _fPos3 , _fPos4);
					_pVector->append(_line);
				}
			}
			else if(_eAngle == setup_PROBE_PART_SKEW_270 )
			{
				float _fIndexOffset = _group.fIndexOffset ;
				for(int i = 0 ; i < _nLawQty ; i++)
				{
					_fTmp1 = _fIndexOffset - _pBeamPos[i]  ;
					_fPos1 = _fTmp1 - sin(_fAngleStart) * _fStart;
					_fPos3 = _fTmp1 - sin(_fAngleStart) * _fStop;
					QLineF _line( _fPos1 , _fPos2 , _fPos3 , _fPos4);
					_pVector->append(_line);
				}
			}
		}
		break;
	default:
//        QLineF _line( 0 , 1, 30 , 1);
//        _pVector->append(_line);
		break;
	};



}

void DopplerOverlays::GetLawMarkers(QVector<QString>* pVector_)
{
	GROUP_CONFIG& _group = m_pConfigure->group[m_nGroup];
	LAW_CONFIG& _law = _group.law ;
	int _nLawQty = m_pProcess->GetGroupLawQty(m_nGroup) ;
	if(_law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
	{
		float _fAngleStart = _law.nAngleStartRefract/10.0 ;
		float _fAngleStep  = _law.nAngleStepRefract/10.0  ;
		float _fAngleTmp ;
		for(int i = 0 ; i < _nLawQty ; i++)
		{
			_fAngleTmp = _fAngleStart + _fAngleStep * i ;
			QString _str ;
			_str.sprintf("%2.1f", _fAngleTmp) ;
			pVector_->append(_str);
		}
	}
	else
	{
		for(int i = 0 ; i < _nLawQty ; i++)
		{
			QString _str ;
			_str.sprintf("%d", i+1) ;
			pVector_->append(_str);
		}
	}
}

