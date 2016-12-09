#include "DopplerGroupTab.h"
#include "ui_DopplerGroupTab.h"
#include <QPushButton>
#include <configure/DopplerConfigure.h>
#include <process/ParameterProcess.h>
#include <configure/const.h>
#include <gHeader.h>
#include <QtGui>

const int MAX_ITEM_QTY = 50 ;

//  Description: ������ʾ��������
static const char* g_strDisplayMode[] =
{
	//**************************	HEADER
	"3D Display" ,
	"2D Display" ,
	//**************************	DISPLAY GROUP
	"All" , "Part" , "Probe and Wedge" , "Weld" , "Sonic Beams" ,
	"A SCAN" , "A-B SCAN" , "A-B SCAN" ,
	"S SCAN" , "S-A SCAN" , "S-A SCAN" , "S-A-A-A SCAN" , "S-A-A-A-C SCAN" ,
	"S-A-B SCAN" , "S-A-B SCAN" ,"S-A-B SCAN" ,
	"S-A-B-C SCAN" , "S-A-B-C SCAN" , "S-A-B-C SCAN" ,
	"S-A-C SCAN"  , "S-A-C SCAN"  ,
	"S-A-C-C SCAN"  , "S-A-C-C SCAN"
}  ;

DopplerGroupTab::DopplerGroupTab(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DopplerGroupTab)
{
	ui->setupUi(this);

	m_nGroupId = 0 ;
	m_pConfig = DopplerConfigure::Instance()  ;
	m_pGroup  = &m_pConfig->group[m_nGroupId]  ;
	ui->toolBox->setMinimumHeight(400);

    for(int i = 0; i < setup_DAC_POINT_QTY; i++){
        m_pSizingCurveName[i] = findChild<QLabel*>("LabelSizingCure" + QString::number(i + 1));
    }

    for(int i = 0; i < setup_DAC_POINT_QTY; i++){
        m_pSizingCurveValue[i] = findChild<QDoubleSpinBox*>("ValueSizingCurve" + QString::number(i + 1));
    }

    for(int i = 0; i < setup_DAC_POINT_QTY; i++){
        m_pSizingCurveUnit[i] = findChild<QLabel*>("LabelSizingCureUnit" + QString::number(i + 1));
    }

	int _iLang = m_pConfig->AppEvn.eLanguage;
	ui->ComLanguage->clear();
	for(int i = 0; i < 2; i++) {
		ui->ComLanguage->addItem(g_strLanguageName[i]);
	}

	ui->ComLanguage->setCurrentIndex(_iLang);

    SetWndName();

	UpdateGroupConfig ();
	ui->toolBox->setCurrentIndex(0);
	CreateSettingView ();
	// ʹ���ڲ�ʹ��  ֻ��������ʾ��
	SetWidgetInvalide() ;
}

DopplerGroupTab::~DopplerGroupTab ()
{
	delete ui;
}

void DopplerGroupTab::retranslateUi()
{
    ui->retranslateUi(this);
}

void DopplerGroupTab::SetGroupId(int nGroupId_)
{
	m_nGroupId = nGroupId_ ;
	m_pGroup  = &m_pConfig->group[m_nGroupId]  ;
	UpdateGroupConfig ();
}

QToolBox* DopplerGroupTab::GetToolBox() const
{
	if(ui->toolBox)
	  return ui->toolBox ;
	else return NULL;
}

/****************************************************************************
  Description: ��������ѡ��
*****************************************************************************/
void DopplerGroupTab::UpdateVelocitySelection()
{
	MATERIAL& _material = m_pGroup->part.material ;
	ui->ComVelocitySelection->clear();

	QString _strTmp[3];
	DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
	int _iLang = _pConfig->AppEvn.eLanguage;
	_strTmp[0] = _material.strName[_iLang] ;

	_strTmp[1].sprintf("[L]%.0f" , _material.fVelocityLon) ;
	_strTmp[2].sprintf("[T]%.0f" , _material.fVelocityTran) ;

	ui->ComVelocitySelection->addItem(_strTmp[0]);
	ui->ComVelocitySelection->addItem(_strTmp[1]);
	ui->ComVelocitySelection->addItem(_strTmp[2]);
}

void DopplerGroupTab::InitComBoxMaterialSelection()
{
	QList<MATERIAL*>* _list = m_pConfig->m_listMaterial ;
	ui->ComMaterial->clear();
	QStringList _strList;

	DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
	int _iLang = _pConfig->AppEvn.eLanguage;

	int _nIndex = 0;
	for(int i = 0 ; i< _list->count() ; i++)
	{
		MATERIAL* _pMaterial = _list->at(i) ;
		QString _str ;
		_str.sprintf("[%s][L:%.0f][T:%.0f]" , QString(tr(_pMaterial->strName[_iLang])).toUtf8().data(), _pMaterial->fVelocityLon , _pMaterial->fVelocityTran ) ;
		_strList.append(_str);
		if(!strcmp( _pMaterial->strName[0] , m_pGroup->part.material.strName[0]) )
			_nIndex= i ;
		//-------------------------------------------------------------
	}
	ui->ComMaterial->addItems(_strList);
	ui->ComMaterial->setCurrentIndex(_nIndex);
}
/****************************************************************************
  Description: ̽ͷ����
*****************************************************************************/
void DopplerGroupTab::UpdateProbeConfig(int bIsRx_)
{
	PROBE_CONFIG& _probe = m_pGroup->probe[bIsRx_ ? 1 : 0] ;

	QString _str[4] ;

    _str[0].sprintf("Element Qty  :     Pri[%3d]     Sec[%3d] ", _probe.nElementPri ,	_probe.nElementSec ) ;
    _str[1].sprintf("Element Size :     Pri[%2.1f]   Sec[%2.1f]  mm", _probe.fSizePri ,  _probe.fSizeSec)	;
    _str[2].sprintf("Element Pitch:     Pri[%2.1f]   Sec[%2.1f]  mm" , _probe.fPitchPri, _probe.fPitchSec) ;
    _str[3].sprintf("Element Frequency: %.1f MHz" , _probe.fFrequency);

	if(bIsRx_)
	{
		ui->BtnProbeSelection_2->setText(_probe.strName);
		ui->LabelProbeT_Line1_2->setText(_str[0]);
		ui->LabelProbeT_Line2_2->setText(_str[1]);
		ui->LabelProbeT_Line3_2->setText(_str[2]);
		ui->LabelProbeT_Line4_2->setText(_str[3]);
	}
	else
	{
		ui->BtnProbeSelection->setText(_probe.strName);
		ui->LabelProbeT_Line1->setText(_str[0]);
		ui->LabelProbeT_Line2->setText(_str[1]);
		ui->LabelProbeT_Line3->setText(_str[2]);
		ui->LabelProbeT_Line4->setText(_str[3]);
	}
}

/****************************************************************************
  Description: Ш�����
*****************************************************************************/
void DopplerGroupTab::UpdateWedgeConfig(int bIsRx_)
{
	WEDGE_CONFIG& _wedge = m_pGroup->wedge[bIsRx_ ? 1 : 0] ;

    QString _str[4] ;

    _str[0].sprintf("Wedge Angle:         %2.1f   Roof Angle:      %2.1f" , _wedge.fWedgeAngle , _wedge.fRoofAngle ) ;
    _str[1].sprintf("Velocity Longtitude: %.0f    Transmmit:       %.0f" , _wedge.fVelocityLon , _wedge.fVelocityTra ) ;
    _str[2].sprintf("Wedge Type:          %s      Wedge Direction: %s",
                    _wedge.eType ? "UT" : "PA" , _wedge.eDirection ? "NORMAL" : "INVERSE");
    if(_wedge.eType)
    {
        _str[3].sprintf("Reference Point:     %.1f mm Wedge Delay:     %.2f us",
                        _wedge.fRefPoint , _wedge.nWedgeDelay /1000.0) ;
    }
    else
    {
        _str[3].sprintf("First Height:        %.1f    Offset Fir:      %.1f    Sec: %.1f" ,
                       _wedge.fHeigtFirst , _wedge.fOffsetFir , _wedge.fOffsetSec) ;
    }

	if(bIsRx_)
	{
        ui->BtnWedgeSelection_2->setText(_wedge.strName);
		ui->LabelWedgeT_Line1_2->setText(_str[0]);
		ui->LabelWedgeT_Line2_2->setText(_str[1]);
		ui->LabelWedgeT_Line3_2->setText(_str[2]);
		ui->LabelWedgeT_Line4_2->setText(_str[3]);
	}
	else
	{
		ui->BtnWedgeSelection->setText(_wedge.strName);
		ui->LabelWedgeT_Line1->setText(_str[0]);
		ui->LabelWedgeT_Line2->setText(_str[1]);
		ui->LabelWedgeT_Line3->setText(_str[2]);
		ui->LabelWedgeT_Line4->setText(_str[3]);
	}

}
/****************************************************************************
  Description: �۽��������
*****************************************************************************/
void DopplerGroupTab::UpdateLawConfig()
{
	LAW_CONFIG& _law = m_pGroup->law ;
	ui->ComLawType->setCurrentIndex(_law.eLawType);
	//************  angle  setting ***************
	ui->ValueRefractStart->setValue(_law.nAngleStartRefract / 10.0);
	ui->ValueRefractStep->setValue(_law.nAngleStepRefract / 10.0);
	ui->ValueRefractStop->setValue(_law.nAngleStopRefract / 10.0);
	//************************************************
	//************ focal point
	ui->ComFocalType->setCurrentIndex(_law.eFocalType);
	ui->ValueFocusPositionStart->setValue(_law.fPositionStart);
	ui->ValueFocusPositionStop->setValue(_law.fPositionStop);
	ui->ValueFocusPositionStep->setValue(_law.fPositionStep);
	ui->ValueFocusOffsetStart->setValue(_law.fOffsetStart);
	ui->ValueFocusOffsetStop->setValue(_law.fOffsetStop);
	ui->ValueFocusDepthStart->setValue(_law.fDepthStart);
	ui->ValueFocusDepthStop->setValue(_law.fDepthStop);
	//***********************************************
	//************ element selection
	ui->ValueElementQtyPri->setValue(_law.nElemQtyFir);
	ui->ValueElementStartPri->setValue(_law.nFirstElemFir);
	ui->ValueElementStopPri->setValue(_law.nLastElemFir);
	ui->ValueElementStepPri->setValue(_law.nElemStepFir);
	ui->ValueElementQtySec->setValue(_law.nElemQtySec);
	ui->ValueElementStartSec->setValue(_law.nFirstElemSec);
	ui->ValueElementStopSec->setValue(_law.nLastElemSec);
	ui->ValueElementStepSec->setValue(_law.nElemStepSec);

	UpdateFocallawState();
}

/****************************************************************************
  Description:  ̽ͷ�������
*****************************************************************************/
void DopplerGroupTab::UpdateProbeWedge()
{
	ui->ComGroupMode->setCurrentIndex(m_pGroup->eGroupMode);
	UpdateProbeConfig(0);
	UpdateProbeConfig(1);
	UpdateWedgeConfig(0);
	UpdateWedgeConfig(1);
}
#include <QToolTip>
#include <process/CalcMeasurement.h>
void DopplerGroupTab::slotMeasureBoxTipInfo(int nIndex_)
{
	QToolTip::hideText();
	QToolTip::showText(QCursor::pos() , QString(CalcMeasurement::GetMeasureContentString(m_nGroupId , (FEILD_VALUE_INDEX)nIndex_ ))) ;
}


/****************************************************************************
  Description: ��������ѡ��
*****************************************************************************/
void DopplerGroupTab::UpdateMeasureBox()
{
	QComboBox* _field[5] ;
	_field[0] = ui->ComField1 ;
	_field[1] = ui->ComField2 ;
	_field[2] = ui->ComField3 ;
	_field[3] = ui->ComField4 ;
	_field[4] = ui->ComField5 ;

	for(int i = 0 ; i < 5 ; i ++)
	{
		_field[i]->clear();

		for(int j = 0 ; j < FEILD_VALUE_INDEX_MAX ; j++)
		{
			_field[i]->addItem( CalcMeasurement::GetMeasureNameString(m_nGroupId , (FEILD_VALUE_INDEX)j ));
		}
		_field[i]->setCurrentIndex(m_pGroup->aeMeasureType[i]);

		connect(_field[i] , SIGNAL(highlighted(int)) , SLOT(slotMeasureBoxTipInfo(int))) ;
	}
}

/****************************************************************************
  Description: ��ǰ�Ƕ�ѡ��ؼ�����
*****************************************************************************/
void DopplerGroupTab::UpdateCurrentAngleCom()
{
	ui->ComCurrentAngle->clear();
	QString _str ;
	int _nCurrentAngle = m_pGroup->law.nAngleStartRefract;
	if(m_pGroup->eGroupMode == setup_GROUP_MODE_PA && m_pGroup->law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
	{

		while(_nCurrentAngle <= m_pGroup->law.nAngleStopRefract)
		{
			_str.clear();
			_str.sprintf("%2.1f" , _nCurrentAngle / 10.0) ;
			_nCurrentAngle += m_pGroup->law.nAngleStepRefract  ;
			ui->ComCurrentAngle->addItem(_str);
		}
	}
	else
	{
		_str.sprintf("%2.1f" , _nCurrentAngle / 10.0) ;
		ui->ComCurrentAngle->addItem(_str);
	}
	int _nCurrentId  = (int)m_pGroup->afCursor[setup_CURSOR_LAW]  ;
	if(_nCurrentId > ui->ComCurrentAngle->count() - 1)
	{
		_nCurrentId  = 0  ;
		m_pGroup->afCursor[setup_CURSOR_LAW] = 0;
	}
	ui->ComCurrentAngle->setCurrentIndex(_nCurrentId);
}
/****************************************************************************
  Description: ������Χ
*****************************************************************************/
void DopplerGroupTab::UpdateSampleRange()
{
	ParameterProcess* _process = ParameterProcess::Instance();
	int _nLawId = ui->ComCurrentAngle->currentIndex() ;
	ui->ValueStart->setValue(_process->GetSampleStart(m_nGroupId , _nLawId));
	ui->ValueRange->setValue(_process->GetSampleRange(m_nGroupId , _nLawId));
}

void DopplerGroupTab::SetWndName()
{
	if(m_pGroup->eTxRxMode == setup_TX_RX_MODE_TOFD ) {
		ui->labelDefectOffset->hide();
		ui->labelDefectWidth->hide();
		ui->ValueDefectWStart->hide();
		ui->ValueDefectWidth->hide();
		ui->LabelCursorUnit3_11->hide();
		ui->LabelCursorUnit3_12->hide();
	} else {
		ui->labelDefectOffset->show();
		ui->labelDefectWidth->show();
		ui->ValueDefectWStart->show();
		ui->ValueDefectWidth->show();
		ui->LabelCursorUnit3_11->show();
		ui->LabelCursorUnit3_12->show();
	}

	QComboBox* _comboxTab[4];
	_comboxTab[0] = ui->ComComDisp1;
	_comboxTab[1] = ui->ComComDisp2;
	_comboxTab[2] = ui->ComComDisp3;
	_comboxTab[3] = ui->ComComDisp4;

	QString _str;
	int _nQty = m_pConfig->common.nGroupQty;
	U8* _pComDisp = m_pConfig->GetComDisplayPoint();
	for(int k = 0; k < 4; k++) {
		_comboxTab[k]->clear();
		for(int i = 0; i < _nQty; i++) {
			_str.sprintf("Group%d", i+1) ;
			_comboxTab[k]->addItem(_str);
		}
		_comboxTab[k]->setCurrentIndex(_pComDisp[k]);
	}

	if(_nQty < 5 && _nQty > 1) {
		ui->groupBoxComDisp->show();
		ui->BtnRefurbishComDisp->setEnabled(false);
		for(int i = 0; i < 4; i++)	{
			_comboxTab[i]->hide();
			_comboxTab[i]->setEnabled(false);
		}

		for(int i = 0; i < _nQty; i++)	{
			_comboxTab[i]->show();
		}
	} else if(_nQty == 1) {
		ui->groupBoxComDisp->hide();
	} else {
		ui->groupBoxComDisp->show();
		ui->BtnRefurbishComDisp->setEnabled(true);
		for(int i = 0; i < 4; i++)	{
			_comboxTab[i]->show();
			_comboxTab[i]->setEnabled(true);
		}
	}
}

/****************************************************************************
  Description: ���ڲ��ɱ༭
*****************************************************************************/
void DopplerGroupTab::SetWidgetInvalide()
{
    ui->ValueGain->setDisabled(true);
    ui->ValueStart->setDisabled(true);
    ui->ValueRange->setDisabled(true);
    ui->ValueWedgeDelay->setDisabled(true);
    ui->ValueVelocity->setDisabled(true);
    ui->ComCurrentAngle->setDisabled(true);
    ui->ComVelocitySelection->setDisabled(true);
    ui->ComTravelMode->setDisabled(true);
    ui->BoxPulserReceiver->setDisabled(true);
    ui->groupBox_2->setDisabled(true);

    ui->ProbWedge->setDisabled(true);
    ui->FocalLaw->setDisabled(true);

    ui->ComGateSync->setDisabled(true);
    ui->ComGateMeasure->setDisabled(true);
    ui->groupBox_curves->setDisabled(true);

    ui->ComGeometry->setDisabled(true);
    ui->ComMaterial->setDisabled(true);
    ui->ValuePartSize2->setDisabled(true);
    ui->ValuePartSize3->setDisabled(true);
    ui->CheckUnifiedPartSetting->setDisabled(true);

    ui->ValueDefectLStart->setDisabled(true);
    ui->ValueDefectLength->setDisabled(true);
    ui->ValueDefectHStart->setDisabled(true);
    ui->ValueDefectHeight->setDisabled(true);
    ui->ValueDefectWStart->setDisabled(true);
    ui->ValueDefectWidth->setDisabled(true);

    ui->ComColorLineColor->setDisabled(true);
    ui->ComColorLineSelection->setDisabled(true);
}

#include <QStandardItemModel>
#include <QMimeData>
#include <QDrag>

/****************************************************************************
  Description: ��ʾ���ʹ��ڴ���
*****************************************************************************/
void DopplerGroupTab::CreateSettingView()
{
	model = new QStandardItemModel(2,1);
	model->setHeaderData(0, Qt::Horizontal, tr("Display Mode"));
	QStandardItem* _pItems[MAX_ITEM_QTY]  ;
	int i;
	int _nQty = sizeof(g_strDisplayMode) / sizeof(int) ;
	for( i = 0 ; i < _nQty; i++)
	{
		_pItems[i] = new QStandardItem(tr(g_strDisplayMode[i]));
		QString str = QString(":/icon/display/resource/Display/0-");
		QString tmp; tmp.sprintf("%02d.png", i+1) ;
		str += tmp ;
		QByteArray array = str.toLatin1() ;
		_pItems[i]->setIcon(QIcon(array.data()));
		_pItems[i]->setData(i , Qt::UserRole);
	}

	model->setItem(0, 0, _pItems[0]);
	model->setItem(1, 0, _pItems[1]);

	for(i = 2 ; i< 3 ; i++)
	{
		_pItems[0]->appendRow(_pItems[i]);
	}
	//----------------------------------------
	for(i = 7 ; i< _nQty ; i++)
	{
		_pItems[1]->appendRow(_pItems[i]);
	}


	QTreeView *tree = ui->treeView;
	tree->setModel (model);
	tree->expandAll();
	tree->viewport()->setAttribute(Qt::WA_StaticContents);
	connect(tree , SIGNAL(pressed(QModelIndex)) , SLOT(StartDrags(QModelIndex)))  ;
}
/****************************************************************************
  Description: ��ʾ���ʹ���  ��ק��Ӧ����
*****************************************************************************/
void DopplerGroupTab::StartDrags(QModelIndex index)
{
	// Get item string and id
	const QAbstractItemModel* model = index.model() ;
	QString _str1  = model->data(index , Qt::DisplayRole).toString()  ;
	int _nId = model->data(index , Qt::UserRole).toInt() ;
	QVariant icon = model->data(index , Qt::DecorationRole);
	QPixmap pixmap =  (icon.value<QIcon>()).pixmap(48 , 48);

	// setup MimeData
	QByteArray itemData;
	QDataStream dataStream(&itemData, QIODevice::WriteOnly);
	dataStream << _str1 << _nId << m_nGroupId;

	QMimeData *mimeData = new QMimeData;
	mimeData->setData("DOPPLER_DISPLAY_ITEM", itemData);

	QDrag *drag = new QDrag(this);
	drag->setMimeData(mimeData);

	drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
	drag->setPixmap(pixmap);
	drag->exec() ; //(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
}

void DopplerGroupTab::UpdateColorSetting()
{
	ParameterProcess* _process = ParameterProcess::Instance();
	void* _pColor = _process->GetPalete(m_nGroupId , PALETTE_AMP) ;
	ui->BtnColorAmp->SetColorIndex(_pColor);
	_pColor = _process->GetPalete(m_nGroupId , PALETTE_RECTIFY) ;
	ui->BtnColorRf->SetColorIndex(_pColor);
	_pColor = _process->GetPalete(m_nGroupId , PALETTE_THICKNESS) ;
	ui->BtnColorThickness->SetColorIndex(_pColor);
}

/****************************************************************************
  Description: ������ͬ��
*****************************************************************************/
void DopplerGroupTab::UpdateCursorValue()
{
	ui->ValueARef->setValue(m_pGroup->afCursor[setup_CURSOR_A_REF]);
	ui->ValueAMes->setValue(m_pGroup->afCursor[setup_CURSOR_A_MES]);
	ui->ValueURef->setValue(m_pGroup->afCursor[setup_CURSOR_U_REF]);
	ui->ValueUMes->setValue(m_pGroup->afCursor[setup_CURSOR_U_MES]);
	ui->ValueSRef->setValue(m_pGroup->afCursor[setup_CURSOR_S_REF]);
	ui->ValueSMes->setValue(m_pGroup->afCursor[setup_CURSOR_S_MES]);
	ui->ValueIRef->setValue(m_pGroup->afCursor[setup_CURSOR_I_REF]);
	ui->ValueIMes->setValue(m_pGroup->afCursor[setup_CURSOR_I_MES]);

	SCANNER& _scanner = m_pConfig->common.scanner ;
	if(_scanner.eEncoderType == setup_ENCODER_TYPE_TIMER) {
		ui->LabelCursorUnit5->setText("sec");
		ui->LabelCursorUnit6->setText("sec");
	} else {
		ui->LabelCursorUnit5->setText("mm");
		ui->LabelCursorUnit6->setText("mm");
	}

	ui->ValueARef->setEnabled(false);
	ui->ValueAMes->setEnabled(false);

	ParameterProcess* _process = ParameterProcess::Instance() ;
	TOFD_PARA* _tofd = m_pConfig->GetTofdConfig(m_nGroupId);
	_process->GetTofdDepth(m_nGroupId , 1 , &_tofd->fDepthCal);
	ui->SpinBoxDepthCal->setValue(_tofd->fDepthCal);
}
void DopplerGroupTab::UpdateDefectBox()
{
	DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
	int _iCnt = _pConfig->GetDefectCnt(m_nGroupId);

	QComboBox* _pBox = ui->ComDefectIndex;
	_pBox->clear();
	if(_iCnt == 0)
	{
		_pBox->addItem(QString("NULL"));
		_pBox->setEnabled(false);
	}
	else
	{
		QString _str;
		int _index = _pConfig->m_dfParam[m_nGroupId].index;
		for(int i = 0 ; i < _iCnt ; i ++)
		{
			_str.sprintf("%d", i+1);
			_pBox->addItem(_str);
		}
		_pBox->setCurrentIndex(_index);
		_pBox->setEnabled(true);
	}

	ui->CheckDefectShow->setChecked(m_pGroup->bShowDefect ? Qt::Checked : Qt::Unchecked);
}

void DopplerGroupTab::UpdateDefectValue()
{
	DopplerConfigure* _pConfig = DopplerConfigure::Instance();

	ui->lineEditReMark->setText(QString(tr("")));
	ui->lineEditReMark->setEnabled(false);
	ui->ValueDefectLStart->setValue(0);
	ui->ValueDefectLength->setValue(0);
	ui->ValueDefectHStart->setValue(0);
	ui->ValueDefectHeight->setValue(0);
	ui->ValueDefectWStart->setValue(0);
	ui->ValueDefectWidth->setValue(0);

	int _iCnt = _pConfig->GetDefectCnt(m_nGroupId);
	if(_iCnt > 0)
	{
		int   _index = _pConfig->m_dfParam[m_nGroupId].index;
		if(_index < 0)		_index = 0;
		if(_index >= _iCnt) _index = _iCnt - 1;

		char *_pInfo = _pConfig->GetDefectInfo(m_nGroupId, _index);
		ui->lineEditReMark->setText(QString(tr(_pInfo)));
		ui->lineEditReMark->setEnabled(true);

		float _fStart = 0;
		float  _fData = 0;

		_fData = _pConfig->DefectLengthValue(m_nGroupId, &_fStart, _index);
		if(_fData >= 0)
		{
			ui->ValueDefectLStart->setValue(_fStart);
			ui->ValueDefectLength->setValue(_fData);
		}

		_fData = _pConfig->DefectHeightValue(m_nGroupId, &_fStart, _index);
		if(_fData >= 0)
		{
			float _fDepth = _pConfig->DefectDepthValue(m_nGroupId, _index);
			if(_fDepth >= 0) {
				_fStart = _fDepth;
			}
			ui->ValueDefectHStart->setValue(_fStart);
			ui->ValueDefectHeight->setValue(_fData);
		}

		_fData = _pConfig->DefectWidthValue(m_nGroupId, &_fStart, _index);
		if(_fData >= 0)
		{
			ui->ValueDefectWStart->setValue(_fStart);
			ui->ValueDefectWidth->setValue(_fData);
		}
	}
	else
	{
		ui->ValueDefectLStart->setValue(0);
		ui->ValueDefectLength->setValue(0);
		ui->ValueDefectHStart->setValue(0);
		ui->ValueDefectHeight->setValue(0);
		ui->ValueDefectWStart->setValue(0);
		ui->ValueDefectWidth->setValue(0);
	}
}

/****************************************************************************
  Description: �����ͬ��
*****************************************************************************/
void DopplerGroupTab::UpdateGroupConfig ()
{
	ParameterProcess* _process = ParameterProcess::Instance();

	ui->ValueGain->setValue(m_pGroup->fGain) ;
	ui->ValueRefGain->setValue(m_pGroup->fRefGain);
	UpdateCurrentAngleCom();
	UpdateSampleRange();
	ui->ValueWedgeDelay->setValue(m_pGroup->nWedgeDelay / 1000.0);
	ui->ValueVelocity->setValue(m_pGroup->fVelocity);
	ui->ComTravelMode->setCurrentIndex(m_pGroup->eTravelMode);
	ui->ComTxRxMode->setCurrentIndex(m_pGroup->eTxRxMode);

	UpdateVelocitySelection() ;
	ui->ValuePulser->setValue(m_pGroup->nTrigeStart);
	ui->ValueReceiver->setValue(m_pGroup->nReceiveStart);
	ui->ComFilter->setCurrentIndex(m_pGroup->eFileter);
	ui->ComRectifier->setCurrentIndex(m_pGroup->eRectifier);
	ui->CheckVideoFilter->setCheckState(m_pGroup->bVedioFilter?Qt::Checked :Qt::Unchecked);
	ui->ValuePointQty->setValue(m_pGroup->nPointQty);
	//ui->ValuePointQty->setEnabled(!m_pGroup->bPointQtyAuto);
	ui->CheckPointQtyAuto->setCheckState(m_pGroup->bPointQtyAuto ? Qt::Checked : Qt::Unchecked);
	ui->ValueSumGain->setValue(m_pGroup->fSumGain);
	//ui->ValueSumGain->setEnabled(!m_pGroup->bSumGainAuto);
	ui->CheckSumGainAuto->setCheckState(m_pGroup->bSumGainAuto ?Qt::Checked :Qt::Unchecked );
	ui->ComAverage->setCurrentIndex(m_pGroup->eAveraging);

	//********** Probe and Wedge **********//
	UpdateProbeWedge() ;

	//**********	Focallaw	***************//
	UpdateLawConfig();

	//**********   Gate and Sizeing curves
	int _nGate = ui->ComGateSelect->currentIndex() ;
	GATE_CONFIG& gate = m_pGroup->gate[_nGate] ;
	ui->CheckGateShow->setCheckState(m_pGroup->bShowGate ? Qt::Checked : Qt::Unchecked);
	ui->ValueGateStart->setValue(gate.fStart);
	ui->ValueGateWidth->setValue(gate.fWidth);
	ui->ValueGateHeight->setValue(gate.nThreshold);
	ui->ComGateSync->setCurrentIndex(gate.eSynChro);
	ui->ComGateMeasure->setCurrentIndex(gate.eMeasure);
	UpdateSizeingCurves();

    //  ********** geometry  ***************//
	InitComBoxMaterialSelection() ;
	ui->ComGeometry->setCurrentIndex(m_pGroup->part.eGeometry);
	UpdateGeometryState();
	ui->CheckShowThickness->setCheckState(m_pGroup->bShowThickness ? Qt::Checked : Qt::Unchecked );
	ui->CheckUnifiedPartSetting->setCheckState(m_pConfig->common.bUnifiedPart ? Qt::Checked : Qt::Unchecked);
	//if(m_nGroupId && m_pConfig->common.bUnifiedPart)   ui->BoxPart->setEnabled(false);

	ui->ValueScanOffset->setValue(m_pGroup->fScanOffset);
	ui->ValueIndexOffset->setValue(m_pGroup->fIndexOffset);
	ui->ComSkewAngle->setCurrentIndex(m_pGroup->eSkew);
	ui->CheckPartFileShow->setChecked(_process->GetShowWeldPart(m_nGroupId));

	SCANNER& _scanner = m_pConfig->common.scanner ;
	if(_scanner.eEncoderType == setup_ENCODER_TYPE_TIMER) {
		ui->LabelScanOffsetUnit->setText("sec");
	} else {
		ui->LabelScanOffsetUnit->setText("mm");
	}

	UpdateTofdParam();

	//*********** measure
	ui->CheckMeasureShow->setCheckState(m_pGroup->bShowMeasure ? Qt::Checked : Qt::Unchecked );
	//ui->CheckBackShow->setCheckState(g_pMainWnd->ParamBackMode() ? Qt::Checked : Qt::Unchecked );
	//ui->CheckBackShow->setChecked(g_pMainWnd->ParamBackMode()); //�ſ��������
	ui->ComField1->setCurrentIndex(m_pGroup->aeMeasureType[0]);
	ui->ComField2->setCurrentIndex(m_pGroup->aeMeasureType[1]);
	ui->ComField3->setCurrentIndex(m_pGroup->aeMeasureType[2]);
	ui->ComField4->setCurrentIndex(m_pGroup->aeMeasureType[3]);
	ui->ComField5->setCurrentIndex(m_pGroup->aeMeasureType[4]);

	//*********** measure
	ui->CheckCursorShow->setCheckState(m_pGroup->bShowCursor ? Qt::Checked : Qt::Unchecked );
	ui->CheckCursorSync->setCheckState(m_pConfig->AppEvn.bSAxisCursorSync ? Qt::Checked : Qt::Unchecked );
	UpdateCursorValue() ;
	UpdateDefectValue() ;

	ui->ComColorLineSelection->setCurrentIndex(0);
	ui->ComColorLineColor->setCurrentIndex(m_pGroup->color.anColor[0]);
	ui->ComCScanSource1->setCurrentIndex(m_pGroup->eCScanSource[0]);
	ui->ComCScanSource2->setCurrentIndex(m_pGroup->eCScanSource[1]);
	ui->ValueCScanThicknessMin->setValue(m_pGroup->fMinThickness);
	ui->ValueCScanThicknessMax->setValue(m_pGroup->fMaxThickness);

	UpdateColorSetting();
	UpdateMeasureBox();
	UpdateDefectBox();
	UpdateParameterLimit();

}
void DopplerGroupTab::UpdateTofdParam()
{
	ui->LabelTofdPcsCal->hide();
	ui->SpinBoxCalPCS->hide();
	ui->LabelCalPCSUnit->hide();
	if(m_pGroup->eTxRxMode != setup_TX_RX_MODE_TOFD )
	{
		ui->BoxPartTofd->hide();
	}
	else
	{
		ui->BoxPartTofd->show();
		ui->CheckLwBwShow->setChecked(m_pGroup->bShowLwBw);

		SCANNER& _scaner = m_pConfig->common.scanner ;
		ui->ComBoxScanMode->setCurrentIndex(_scaner.eScanMode);
		ui->ComBoxProMode->setCurrentIndex(m_pConfig->AppEvn.iTofdDataProMode);

		TOFD_PARA* _tofd = m_pConfig->GetTofdConfig(m_nGroupId);
		ui->SpinBoxWedgeSeperation->setValue(_tofd->fWedgeSep);
		ui->SpinBoxPCS->setValue(_tofd->fPCS);
		ui->SpinBoxCalPCS->setValue(_tofd->fPcs);
		ui->SpinBoxZeroOff->setValue(_tofd->fZeroOff);
		ui->SpinBoxDepthStart->setValue(_tofd->fLayerStart);
		ui->SpinBoxDepthEnd->setValue(_tofd->fLayerEnd);
	}
}

void DopplerGroupTab::UpdateSizeingCurves()
{
	ParameterProcess* _process = ParameterProcess::Instance();

	ui->ComSizingCurve->setEnabled(false);
	ui->ComCurvePointId->setEnabled(false);

	ui->BtnAddPoint->setEnabled(false);
	ui->BtnDelPoint->setEnabled(false);

	for(int i = 0; i < setup_DAC_POINT_QTY; i++) {
		m_pSizingCurveValue[i]->setEnabled(false);

		m_pSizingCurveName[i]->hide();
		m_pSizingCurveValue[i]->hide();
		m_pSizingCurveUnit[i]->hide();
	}

	CURVES& _curve = m_pGroup->curve;

    if(_curve.eType == setup_CURVE_TYPE_LINEAR_DAC) {
        m_pSizingCurveName[0]->setText(QString(tr("Mat. Atten:")));
        m_pSizingCurveName[1]->setText(QString(tr("Delay:")));
    } else {
        m_pSizingCurveName[0]->setText(QString(tr("RefAmplitude:")));
        m_pSizingCurveName[1]->setText(QString(tr("RefAmplitude:")));
    }

	int _nLawId  = (int)m_pGroup->afCursor[setup_CURSOR_LAW]  ;
	switch(_curve.eType)
	{
	case setup_CURVE_TYPE_DAC:
		for(int i = 0; i < _curve.nPointQty; i++)
		{
			m_pSizingCurveName[i]->show();
			m_pSizingCurveValue[i]->show();
			m_pSizingCurveUnit[i]->show();

			m_pSizingCurveValue[i]->setDecimals(1);
			m_pSizingCurveValue[i]->setValue(_process->GetSizingCurveRefAmp(m_nGroupId, _nLawId,  i+1));
			m_pSizingCurveUnit[i]->setText(QString(tr("%")));
		}
		break;
	case setup_CURVE_TYPE_LINEAR_DAC:
		for(int i = 0; i < 2; i++)
		{
			m_pSizingCurveName[i]->show();
			m_pSizingCurveValue[i]->show();
			m_pSizingCurveUnit[i]->show();

			m_pSizingCurveValue[i]->setDecimals(2);
			m_pSizingCurveValue[i]->setValue(_process->GetSizingCurveRefAmp(m_nGroupId, _nLawId,  i));
		}

		m_pSizingCurveUnit[0]->setText(QString(tr("dB/mm")));
		m_pSizingCurveUnit[1]->setText(QString(tr("mm")));
		break;
	case setup_CURVE_TYPE_TCG:
		for(int i = 0; i < _curve.nPointQty; i++)
		{
			m_pSizingCurveName[i]->show();
			m_pSizingCurveValue[i]->show();
			m_pSizingCurveUnit[i]->show();

			m_pSizingCurveValue[i]->setDecimals(1);
			m_pSizingCurveValue[i]->setValue(_process->GetSizingCurveRefAmp(m_nGroupId, _nLawId,  i+1));
			m_pSizingCurveUnit[i]->setText(QString(tr("dB")));
		}
		break;
	default:
		break;
	}
	ui->ComSizingCurve->setCurrentIndex((int)_curve.eType);
	ui->ComCurvePointId->clear();
	char strBuf[256];
	for(int i = 0; i < _curve.nPointQty; i++) {
		sprintf(strBuf, "%d", i+1);
		ui->ComCurvePointId->addItem(QString(QObject::tr(strBuf)));
	}
    ui->ComCurvePointId->setCurrentIndex(_curve.nPointPos);
}

/****************************************************************************
  Description: �������޸���
*****************************************************************************/
#include <process/Limitation.h>
void DopplerGroupTab::UpdateParameterLimit()
{
	Limitation _limit ;

	// Gain
	ui->ValueGain->setMaximum(_limit.GetGroupGainMax(m_nGroupId));
	ui->ValueGain->setMinimum(_limit.GetGroupGainMin(m_nGroupId));
	// Start & Range
	ui->ValueStart->setMaximum(_limit.GetGroupSampleRangeMax(m_nGroupId));
	ui->ValueRange->setMaximum(_limit.GetGroupSampleRangeMax(m_nGroupId) - ui->ValueStart->value());
}


/****************************************************************************
  Description: �۽���������
*****************************************************************************/
void DopplerGroupTab::UpdateFocallawState()
{
    ui->ComAngleType->setCurrentIndex(0);

	if(ui->ComLawType->currentIndex() == 0) // angle
	{ // angle
		ui->ValueElementStopPri->setValue(ui->ValueElementQtyPri->value() + ui->ValueElementStartPri->value() - 1 );
    }
}

/****************************************************************************
  Description: �������� ����
*****************************************************************************/
void DopplerGroupTab::UpdateGeometryState()
{
	setup_PART_GEOMETRY _eGeometry =  (setup_PART_GEOMETRY)ui->ComGeometry->currentIndex();
	if(_eGeometry == setup_PART_GEOMETRY_FLAT)
	{
        ui->LabelPartSize1->setText(QString(tr("Thickness:")));
        ui->LabelPartSize2->setText(QString(tr("Length:")));
        ui->LabelPartSize3->setText(QString(tr("Width:")));
    }else{
        ui->LabelPartSize1->setText(QString(tr("Inner Diameter:")));
        ui->LabelPartSize2->setText(QString(tr("Outer Diameter:")));
        ui->LabelPartSize3->setText(QString(tr("Length:")));
	}

	ui->ValuePartSize1->setValue(m_pGroup->part.afSize[0]);
	ui->ValuePartSize2->setValue(m_pGroup->part.afSize[1]);
	ui->ValuePartSize3->setValue(m_pGroup->part.afSize[2]);
}

void DopplerGroupTab::on_ValueGain_editingFinished()
{
	double _fValue = ui->ValueGain->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupGain(m_nGroupId , _fValue) ;
}

#include "ProcessDisplay.h"
void DopplerGroupTab::on_ValueRefGain_valueChanged(double)
{
	if(!ui->ValueRefGain->hasFocus())  return ;
	double _fValue = ui->ValueRefGain->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupRefGain(m_nGroupId , _fValue) ;
	ProcessDisplay _display ;
	_display.UpdateAllViewCursorOfGroup(m_nGroupId);
	g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ValueStart_editingFinished()
{
	double _fValue = ui->ValueStart->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();

	if(ui->ComTravelMode->currentIndex() == 0)
	{
		int _nLawId = ui->ComCurrentAngle->currentIndex() ;
		float _fAngle = _process->GetLawAngle(m_nGroupId , _nLawId) ;
		_fValue = _fValue / cos(DEGREE_TO_ARCH(_fAngle))  ;
	}

	_process->SetupSampleStart(m_nGroupId , _fValue) ;
	ProcessDisplay _display ;
	_display.UpdateAllViewOfGroup(m_nGroupId);
}

void DopplerGroupTab::on_ValueRange_editingFinished()
{
	double _fValue = ui->ValueRange->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();

	if(ui->ComTravelMode->currentIndex() == 0)
	{
		int _nLawId = ui->ComCurrentAngle->currentIndex() ;
		float _fAngle = _process->GetLawAngle(m_nGroupId , _nLawId) ;
		_fValue = _fValue / cos(DEGREE_TO_ARCH(_fAngle))  ;
	}
	_process->SetupSampleRange(m_nGroupId , _fValue ) ;

	ProcessDisplay _display ;
	_display.UpdateAllViewOfGroup(m_nGroupId);
}

void DopplerGroupTab::on_ComCurrentAngle_currentIndexChanged(int index)
{
	if(!ui->ComCurrentAngle->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupCurrentLawCursor(m_nGroupId , index) ;
	UpdateSampleRange();
}

void DopplerGroupTab::on_ComTravelMode_currentIndexChanged(int index)
{
	if(!ui->ComTravelMode->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupTravelMode(m_nGroupId , index) ;
	UpdateSampleRange();
}

void DopplerGroupTab::on_ValueVelocity_editingFinished()
{
	double _fValue = ui->ValueVelocity->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupVelocity(m_nGroupId , _fValue) ;
}

void DopplerGroupTab::on_ValueWedgeDelay_editingFinished()
{
	double _fValue = ui->ValueWedgeDelay->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupVelocity(m_nGroupId , _fValue) ;
}

void DopplerGroupTab::on_ComVelocitySelection_currentIndexChanged(int index)
{
	if(!ui->ComVelocitySelection->hasFocus())  return ;
	if(!index)  return  ;

	ParameterProcess* _process = ParameterProcess::Instance();
	float _fValue  = _process->GetMaterialVelocity(m_nGroupId , index - 1 ) ;
	ui->ValueVelocity->setValue(_fValue);
	_process->SetupVelocity(m_nGroupId , _fValue) ;
	ui->ComVelocitySelection->setCurrentIndex(0);
}

void DopplerGroupTab::on_ValuePulser_editingFinished()
{
	int _nValue = ui->ValuePulser->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupTxElementStart(m_nGroupId , _nValue) ;
}

void DopplerGroupTab::on_ValueReceiver_editingFinished()
{
	int _nValue = ui->ValuePulser->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupRxElementStart(m_nGroupId , _nValue) ;
}

void DopplerGroupTab::on_ComFilter_currentIndexChanged(int)
{
	if(!ui->ComFilter->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	int _nValue = ui->ComFilter->currentIndex() ;
	_process->SetupFilter(m_nGroupId , _nValue) ;
}

void DopplerGroupTab::on_ComRectifier_currentIndexChanged(int)
{
	if(!ui->ComRectifier->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	int _nValue = ui->ComRectifier->currentIndex() ;
	_process->SetupRectifier(m_nGroupId , _nValue) ;
}

void DopplerGroupTab::on_CheckVideoFilter_clicked(bool checked)
{
	if(!ui->CheckVideoFilter->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupRectifier(m_nGroupId , checked) ;
}

void DopplerGroupTab::on_ValuePointQty_editingFinished()
{
	ParameterProcess* _process = ParameterProcess::Instance();
	int _nValue = ui->ValuePointQty->value() ;
	_process->SetupPointQty(m_nGroupId , _nValue) ;
}

void DopplerGroupTab::on_ValueSumGain_editingFinished()
{
	double _fValue = ui->ValueSumGain->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupSumGain(m_nGroupId , _fValue) ;
}

void DopplerGroupTab::on_ComAverage_currentIndexChanged(int index)
{
	if(!ui->ComAverage->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupAverage(m_nGroupId , index) ;
}

void DopplerGroupTab::on_ComGroupMode_currentIndexChanged(int index)
{
	if(!ui->ComGroupMode->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupGroupMode(m_nGroupId , index) ;
	UpdateGroupConfig();
}

void DopplerGroupTab::on_CheckPointQtyAuto_toggled(bool checked)
{
	if(!ui->CheckPointQtyAuto->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupPointQtyAutoMode(m_nGroupId , checked) ;
	ui->ValuePointQty->setEnabled(!checked);
}

void DopplerGroupTab::on_CheckSumGainAuto_toggled(bool checked)
{
	if(!ui->CheckSumGainAuto->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupSumGainAutoMode(m_nGroupId , checked) ;
	ui->ValueSumGain->setEnabled(!checked);
}

void DopplerGroupTab::on_ComLawType_currentIndexChanged(int)
{
	if(!ui->ComLawType->hasFocus())  return ;
	UpdateFocallawState() ;
}

void DopplerGroupTab::on_BtnProcessLaw_clicked()
{
	//qDebug("on_BtnProcessLaw_clicked");

	LAW_CONFIG _law ;
	_law.eLawType = (setup_LAW_TYPE)ui->ComLawType->currentIndex();
	//************  angle  setting ***************
	_law.nAngleStartRefract = ui->ValueRefractStart->value() * 10 ;
	_law.nAngleStepRefract = ui->ValueRefractStep->value() * 10 ;
	_law.nAngleStopRefract = ui->ValueRefractStop->value() * 10 ;
	//************************************************
	//************ focal point
	_law.eFocalType	 = (setup_FOCAL_TYPE)ui->ComFocalType->currentIndex() ;
	_law.fPositionStart = ui->ValueFocusPositionStart->value() ;
	_law.fPositionStop  = ui->ValueFocusPositionStop->value() ;
	_law.fPositionStep  = ui->ValueFocusPositionStep->value() ;
	_law.fOffsetStart   = ui->ValueFocusOffsetStart->value() ;
	_law.fOffsetStop	= ui->ValueFocusOffsetStop->value() ;
	_law.fDepthStart	= ui->ValueFocusDepthStart->value() ;
	_law.fDepthStop	 = ui->ValueFocusDepthStop->value() ;
	//***********************************************
	//************ element selection
	_law.nElemQtyFir   = ui->ValueElementQtyPri->value() ;
	_law.nFirstElemFir = ui->ValueElementStartPri->value() ;
	_law.nLastElemFir  = ui->ValueElementStopPri->value() ;
	_law.nElemStepFir  = ui->ValueElementStepPri->value() ;

	_law.nElemQtySec   = ui->ValueElementQtySec->value() ;
	_law.nFirstElemSec = ui->ValueElementStartSec->value() ;
	_law.nLastElemSec  = ui->ValueElementStopSec->value() ;
	_law.nElemStepSec  = ui->ValueElementStepSec->value() ;

	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupFocalLaw(m_nGroupId , &_law);

	UpdateCurrentAngleCom();
	UpdateSampleRange();

}

void DopplerGroupTab::on_ComAngleType_currentIndexChanged(int)
{
	if(!ui->ComAngleType->hasFocus())  return ;
	UpdateFocallawState();
}

void DopplerGroupTab::AngleAlign()
{
	int _nStart = ui->ValueRefractStart->value() * 10 ;
	int _nStop  = ui->ValueRefractStop->value()  * 10 ;
	int _nStep  = ui->ValueRefractStep->value()  * 10 ;
	int _nSteps = (_nStop - _nStart) / _nStep  ;
	_nStop = _nStart + _nStep * _nSteps ;
	ui->ValueRefractStop->setValue(_nStop / 10.0);
}

void DopplerGroupTab::FocusPositionAlign()
{
	int _nStart = ui->ValueFocusPositionStart->value() * 10 ;
	int _nStop  = ui->ValueFocusPositionStop->value()  * 10 ;
	int _nStep  = ui->ValueFocusPositionStep->value()  * 10 ;
	int _nSteps = (_nStop - _nStart) / _nStep  ;
	_nStop = _nStart + _nStep * _nSteps ;
	ui->ValueFocusPositionStop->setValue(_nStop / 10.0);
}

void DopplerGroupTab::ElementAlign()
{
	int _nQty   = ui->ValueElementQtyPri->value()  ;
	int _nStart = ui->ValueElementStartPri->value() ;
	int _nStop  = ui->ValueElementStopPri->value() ;
	int _nStep  = ui->ValueElementStepPri->value() ;
	int _nSteps = (_nStop - _nQty - _nStart + 1) / _nStep ;
	_nStop = _nStart + _nStep * _nSteps + _nQty - 1;
	ui->ValueElementStopPri->setValue(_nStop );
}

void DopplerGroupTab::on_ValueRefractStart_editingFinished()
{
	AngleAlign() ;
}

void DopplerGroupTab::on_ValueRefractStop_editingFinished()
{
	AngleAlign();
}

void DopplerGroupTab::on_ValueRefractStep_editingFinished()
{
	AngleAlign();
}

void DopplerGroupTab::on_ComFocalType_currentIndexChanged(int)
{
	if(!ui->ComFocalType->hasFocus())  return ;
	UpdateFocallawState() ;
}

void DopplerGroupTab::on_ValueFocusPositionStart_editingFinished()
{
	FocusPositionAlign() ;
}

void DopplerGroupTab::on_ValueFocusPositionStop_editingFinished()
{
	FocusPositionAlign() ;
}

void DopplerGroupTab::on_ValueFocusPositionStep_editingFinished()
{
	FocusPositionAlign() ;
}

void DopplerGroupTab::on_ValueElementQtyPri_editingFinished()
{
	ElementAlign() ;
}

void DopplerGroupTab::on_ValueElementStartPri_editingFinished()
{
	ElementAlign() ;
}

void DopplerGroupTab::on_ValueElementStopPri_editingFinished()
{
	ElementAlign() ;
}

void DopplerGroupTab::on_ValueElementStepPri_editingFinished()
{
	ElementAlign() ;
}

// gate
void DopplerGroupTab::on_ComGateSelect_currentIndexChanged(int index)
{
	if(!ui->ComGateSelect->hasFocus())  return ;
	GROUP_CONFIG& group = m_pConfig->group[m_nGroupId] ;
	GATE_CONFIG& _gate = group.gate[index] ;
	ui->ValueGateStart->setValue(_gate.fStart);
	ui->ValueGateWidth->setValue(_gate.fWidth);
	ui->ValueGateHeight->setValue(_gate.nThreshold);

	if(index == 2) //gate i
	{
		ui->ComGateSync->setCurrentIndex(0);
		ui->ComGateMeasure->setCurrentIndex(0);
		ui->ComGateMeasure->setEnabled(false);
		ui->ComGateSync->setEnabled(false);
    }else{
		ui->ComGateMeasure->setEnabled(true);
		ui->ComGateSync->setEnabled(true);
		ui->ComGateSync->setCurrentIndex(_gate.eSynChro);
		ui->ComGateMeasure->setCurrentIndex(_gate.eMeasure);
	}
}

#include "ProcessDisplay.h"
void DopplerGroupTab::on_CheckGateShow_clicked(bool checked)
{
	m_pGroup->bShowGate = checked ;
	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
}

void DopplerGroupTab::GatePro()
{
	GATE_CONFIG _gate ;
	_gate.fStart = ui->ValueGateStart->value() ;
	_gate.fWidth = ui->ValueGateWidth->value() ;
	_gate.nThreshold = ui->ValueGateHeight->value();
	_gate.eMeasure   = ui->ComGateMeasure->currentIndex() ;
	_gate.eSynChro   = (setup_GATE_AYNC_TYPE)ui->ComGateSync->currentIndex() ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupGateInfo(m_nGroupId , (setup_GATE_NAME)ui->ComGateSelect->currentIndex() , &_gate) ;

	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
	g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ValueGateStart_valueChanged(double)
{
	if(!ui->ValueGateStart->hasFocus())  return ;
	GatePro();
}

void DopplerGroupTab::on_ValueGateWidth_valueChanged(double)
{
	if(!ui->ValueGateWidth->hasFocus())  return ;
	GatePro();
}

void DopplerGroupTab::on_ValueGateHeight_valueChanged(double)
{
	if(!ui->ValueGateHeight->hasFocus())  return ;
	GatePro();
}
void DopplerGroupTab::on_ComGateSync_currentIndexChanged(int )
{
	if(!ui->ComGateSync->hasFocus())  return ;
	GatePro();
}

void DopplerGroupTab::on_ComGateMeasure_currentIndexChanged(int)
{
	if(!ui->ComGateMeasure->hasFocus())  return ;
	GatePro();
	UpdateMeasureBox();
}

void DopplerGroupTab::on_CheckShowThickness_clicked(bool checked)
{
	m_pGroup->bShowThickness = checked  ;

	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
}

void DopplerGroupTab::on_ComGeometry_currentIndexChanged(int)
{
	if(!ui->ComGeometry->hasFocus())  return ;
	UpdateGeometryState() ;
	PartPro();
}

void DopplerGroupTab::PartPro()
{
	PART_CONFIG _part ;
	_part.eGeometry = (setup_PART_GEOMETRY)ui->ComGeometry->currentIndex() ;
	_part.afSize[0] = ui->ValuePartSize1->value() ;
	_part.afSize[1] = ui->ValuePartSize2->value() ;
	_part.afSize[2] = ui->ValuePartSize3->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupPartGeometry (m_nGroupId , &_part) ;
	ProcessDisplay _display ;
	_display.UpdateAllView();
	g_pMainWnd->RunDrawThreadOnce(true);
	UpdateDefectValue();
}

void DopplerGroupTab::on_ValuePartSize1_valueChanged(double)
{
	if(!ui->ValuePartSize1->hasFocus())  return ;
	PartPro();
}

void DopplerGroupTab::on_ValuePartSize2_valueChanged(double)
{
	if(!ui->ValuePartSize2->hasFocus())  return ;
	PartPro();
}

void DopplerGroupTab::on_ValuePartSize3_valueChanged(double)
{
	if(!ui->ValuePartSize3->hasFocus())  return ;
	PartPro();
}

void DopplerGroupTab::on_ComMaterial_currentIndexChanged(int index)
{
	if(!ui->ComMaterial->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupPartMaterial(m_nGroupId ,  index) ;
	ui->ValueVelocity->setValue(m_pGroup->fVelocity);
	UpdateVelocitySelection() ;
}

void DopplerGroupTab::on_ValueScanOffset_editingFinished()
{
	if(!ui->ValueScanOffset->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	double _fValue1 = ui->ValueScanOffset->value()  ;
	double _fValue2 = ui->ValueIndexOffset->value() ;
	_process->SetupWedgePosition(m_nGroupId ,  _fValue1 , _fValue2) ;

	DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
	_pConfig->ResetShadowData();

	g_pMainWnd->RunDrawThreadOnce(true);
	ProcessDisplay _display ;
	//_display.UpdateAllViewOfGroup(m_nGroupId);
	_display.UpdateAllView();
	sleep(20);
	_display.UpdateAllView();
	g_pMainWnd->RunDrawThreadOnce(true);
	sleep(20);
}

void DopplerGroupTab::on_ValueIndexOffset_editingFinished()
{
	if(!ui->ValueIndexOffset->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	double _fValue1 = ui->ValueScanOffset->value()  ;
	double _fValue2 = ui->ValueIndexOffset->value() ;
	_process->SetupWedgePosition(m_nGroupId ,  _fValue1 , _fValue2) ;

	ProcessDisplay _display ;
	_display.UpdateAllViewOfGroup(m_nGroupId);
	g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ComSkewAngle_currentIndexChanged(int index)
{
	if(!ui->ComSkewAngle->hasFocus())  return  ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupWedgeSkewAngle(m_nGroupId , (setup_PROBE_ANGLE)index)  ;

	ProcessDisplay _display ;
	_display.UpdateAllView();
	_display.UpdateAllViewOfGroup(m_nGroupId);
	g_pMainWnd->RunDrawThreadOnce(true);
}

#include "dialog/DialogWeldPartLoad.h"
void DopplerGroupTab::on_BtnLoadPartFile_clicked()
{
	DialogWeldPartLoad _dialog(this);
	int _nRet = _dialog.exec();

	if(_nRet)
	{
		ParameterProcess* _process = ParameterProcess::Instance();
		_process->SetupPart(m_nGroupId,  _dialog.GetPart());
	}

	ProcessDisplay _display ;
	_display.UpdateAllViewOfGroup(m_nGroupId);
}
void DopplerGroupTab::on_CheckLwBwShow_clicked(bool checked)
{
	m_pGroup->bShowLwBw = checked;
	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
}

void DopplerGroupTab::on_ComBoxProMode_currentIndexChanged(int index_)
{
	if(!ui->ComBoxProMode->hasFocus())  return  ;

	if(m_pConfig->TOFD[m_nGroupId].eProingST == 0) {
		m_pConfig->AppEvn.iTofdDataProMode = index_;
	} else {
		ui->ComBoxProMode->setCurrentIndex(m_pConfig->AppEvn.iTofdDataProMode);
	}
}
void DopplerGroupTab::on_SpinBoxWedgeSeperation_valueChanged(double arg1)
{
	if(!ui->SpinBoxWedgeSeperation->hasFocus())  return  ;

	TOFD_PARA* _tofd = m_pConfig->GetTofdConfig(m_nGroupId);
	_tofd->fWedgeSep = arg1  ;
	_tofd->fPCS	  = arg1 + 2 * _tofd->fRefPoint ;
	ui->SpinBoxPCS->setValue(_tofd->fPCS);

	ParameterProcess* _process = ParameterProcess::Instance() ;
	_process->TofdCursorCalibration(m_nGroupId);

	ProcessDisplay _display ;
	_display.UpdateAllViewOfGroup(m_nGroupId);
	g_pMainWnd->RunDrawThreadOnce(true);
}
void DopplerGroupTab::on_SpinBoxZeroOff_valueChanged(double)
{
	if(!ui->SpinBoxZeroOff->hasFocus()) return ;

	TOFD_PARA* _tofd = m_pConfig->GetTofdConfig(m_nGroupId);
	_tofd->fZeroOff = ui->SpinBoxZeroOff->value() ;

	ParameterProcess* _process = ParameterProcess::Instance() ;
	_process->TofdCursorCalibration(m_nGroupId);

	ProcessDisplay _display ;
	_display.UpdateAllViewOfGroup(m_nGroupId);
	g_pMainWnd->RunDrawThreadOnce(true);

	_process->GetTofdDepth(m_nGroupId , 1 , &_tofd->fDepthCal);
	ui->SpinBoxDepthCal->setValue(_tofd->fDepthCal);
}
void DopplerGroupTab::on_SpinBoxDepthStart_valueChanged(double)
{
	if(!ui->SpinBoxDepthStart->hasFocus()) return ;

	TOFD_PARA* _tofd = m_pConfig->GetTofdConfig(m_nGroupId);
	_tofd->fLayerStart = ui->SpinBoxDepthStart->value() ;

	ParameterProcess* _process = ParameterProcess::Instance() ;
	_process->TofdCursorCalibration(m_nGroupId);

	ProcessDisplay _display ;
	_display.UpdateAllViewOfGroup(m_nGroupId);
	g_pMainWnd->RunDrawThreadOnce(true);
}
void DopplerGroupTab::on_SpinBoxDepthEnd_valueChanged(double)
{
	if(!ui->SpinBoxDepthEnd->hasFocus()) return ;

	TOFD_PARA* _tofd = m_pConfig->GetTofdConfig(m_nGroupId);
	_tofd->fLayerEnd = ui->SpinBoxDepthEnd->value() ;

	ParameterProcess* _process = ParameterProcess::Instance() ;
	_process->TofdCursorCalibration(m_nGroupId);

	ProcessDisplay _display ;
	_display.UpdateAllViewOfGroup(m_nGroupId);
	g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_SpinBoxDepthCal_valueChanged(double)
{
	if(!ui->SpinBoxDepthCal->hasFocus()) return ;
	TOFD_PARA* _tofd = m_pConfig->GetTofdConfig(m_nGroupId);
	_tofd->fDepthCal = ui->SpinBoxDepthCal->value();
}

void DopplerGroupTab::on_BtnDepthCal_clicked()
{
	TOFD_PARA* _tofd = m_pConfig->GetTofdConfig(m_nGroupId);
	_tofd->fDepthCal = ui->SpinBoxDepthCal->value();

	ParameterProcess* _process = ParameterProcess::Instance();
	_process->TofdDepthCalibration(m_nGroupId);

	ProcessDisplay _display ;
	_display.UpdateAllViewOfGroup(m_nGroupId);
	g_pMainWnd->RunDrawThreadOnce(true);

	_process->GetTofdDepth(m_nGroupId, 2, &_tofd->fDepthCal);
	ui->SpinBoxDepthCal->setValue(_tofd->fDepthCal);

	ui->SpinBoxZeroOff->setValue(_tofd->fZeroOff);
}

void DopplerGroupTab::on_CheckPartFileShow_clicked(bool checked)
{
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupShowWeldPart(m_nGroupId , checked)  ;

	ProcessDisplay _display ;
	_display.UpdateAllViewOfGroup(m_nGroupId);
}

void DopplerGroupTab::on_CheckMeasureShow_clicked(bool checked)
{
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupShowMeasure(m_nGroupId , checked)  ;
	g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_CheckBackShow_clicked(bool checked)
{
	if(!ui->CheckBackShow->hasFocus()) return ;
	g_pMainWnd->SetParamBackMode(checked) ;
	g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ComField1_currentIndexChanged(int index)
{
	if(!ui->ComField1->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupMeasureData(m_nGroupId , 0 , index)  ;

	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
}

void DopplerGroupTab::on_ComField2_currentIndexChanged(int index)
{
	if(!ui->ComField2->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupMeasureData(m_nGroupId , 1 , index)  ;

	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
}

void DopplerGroupTab::on_ComField3_currentIndexChanged(int index)
{
	if(!ui->ComField3->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupMeasureData(m_nGroupId , 2 , index)  ;

	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
}

void DopplerGroupTab::on_ComField4_currentIndexChanged(int index)
{
	if(!ui->ComField4->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupMeasureData(m_nGroupId , 3 , index)  ;

	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
}

void DopplerGroupTab::on_ComField5_currentIndexChanged(int index)
{
	if(!ui->ComField5->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupMeasureData(m_nGroupId , 4 , index)  ;

	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
}

void DopplerGroupTab::on_CheckCursorShow_clicked(bool checked)
{
	m_pGroup->bShowCursor = checked ;
	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
}

void DopplerGroupTab::on_CheckCursorSync_clicked(bool checked)
{
	m_pConfig->AppEvn.bSAxisCursorSync = checked ;
	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
}

void DopplerGroupTab::on_ValueARef_valueChanged(double)
{
	if(!ui->ValueARef->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	double _fValue = ui->ValueARef->value() ;
	_process->SetupCursor(m_nGroupId , setup_CURSOR_A_REF , _fValue)  ;

	if(ui->CheckCursorShow->checkState())
	{
		ProcessDisplay _display ;
		_display.UpdateAllViewOverlay();
	}
	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
}
void DopplerGroupTab::on_ValueAMes_valueChanged(double)
{
	if(!ui->ValueAMes->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	double _fValue = ui->ValueAMes->value() ;
	_process->SetupCursor(m_nGroupId , setup_CURSOR_A_MES , _fValue)  ;

	if(ui->CheckCursorShow->checkState())
	{
		ProcessDisplay _display ;
		_display.UpdateAllViewOverlay();
	}
	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
}
void DopplerGroupTab::on_ValueURef_valueChanged(double)
{
	if(!ui->ValueURef->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	double _fValue = ui->ValueURef->value() ;
	_process->SetupCursor(m_nGroupId , setup_CURSOR_U_REF , _fValue)  ;

	if(ui->CheckCursorShow->checkState())
	{
		ProcessDisplay _display ;
		_display.UpdateAllViewOverlay();
	}
	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
	ui->ValueARef->setValue(m_pGroup->afCursor[setup_CURSOR_A_REF]);
}
void DopplerGroupTab::on_ValueUMes_valueChanged(double)
{
	if(!ui->ValueUMes->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	double _fValue = ui->ValueUMes->value() ;
	_process->SetupCursor(m_nGroupId , setup_CURSOR_U_MES , _fValue)  ;

	if(ui->CheckCursorShow->checkState())
	{
		ProcessDisplay _display ;
		_display.UpdateAllViewOverlay();
	}
	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
	ui->ValueAMes->setValue(m_pGroup->afCursor[setup_CURSOR_A_MES]);
}
void DopplerGroupTab::on_ValueSRef_valueChanged(double)
{
	if(!ui->ValueSRef->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	double _fValue = ui->ValueSRef->value() ;
	_process->SetupCursor(m_nGroupId , setup_CURSOR_S_REF , _fValue)  ;

	if(ui->CheckCursorShow->checkState())
	{
		ProcessDisplay _display ;
		_display.UpdateAllViewOverlay();
	}
	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
}
void DopplerGroupTab::on_ValueSMes_valueChanged(double)
{
	if(!ui->ValueSMes->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	double _fValue = ui->ValueSMes->value() ;
	_process->SetupCursor(m_nGroupId , setup_CURSOR_S_MES , _fValue)  ;

	if(ui->CheckCursorShow->checkState())
	{
		ProcessDisplay _display ;
		_display.UpdateAllViewOverlay();
	}
	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
}
void DopplerGroupTab::on_ValueIRef_valueChanged(double)
{
	if(!ui->ValueIRef->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	double _fValue = ui->ValueIRef->value() ;
	_process->SetupCursor(m_nGroupId , setup_CURSOR_I_REF , _fValue)  ;

	if(ui->CheckCursorShow->checkState())
	{
		ProcessDisplay _display ;
		_display.UpdateAllViewOverlay();
	}
	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
}
void DopplerGroupTab::on_ValueIMes_valueChanged(double)
{
	if(!ui->ValueIMes->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	double _fValue = ui->ValueIMes->value() ;
	_process->SetupCursor(m_nGroupId , setup_CURSOR_I_MES , _fValue)  ;

	if(ui->CheckCursorShow->checkState())
	{
		ProcessDisplay _display ;
		_display.UpdateAllViewOverlay();
	}
	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
}

#include "dialog/DialogColorSelect.h"
void DopplerGroupTab::on_BtnColorAmp_clicked()
{
	DialogColorSelect _dialog(this) ;
	int _nRet = _dialog.exec();
	if(_nRet)
	{
		ParameterProcess* _process = ParameterProcess::Instance();
		_process->SetupPalette(m_nGroupId , PALETTE_AMP , _dialog.GetColorIndex()) ;
	}
	UpdateColorSetting();
	g_pMainWnd->RunDrawThreadOnce();
}

void DopplerGroupTab::on_BtnColorRf_clicked()
{
	DialogColorSelect _dialog(this) ;
	int _nRet = _dialog.exec();
	if(_nRet)
	{
		ParameterProcess* _process = ParameterProcess::Instance();
		_process->SetupPalette(m_nGroupId , PALETTE_RECTIFY , _dialog.GetColorIndex()) ;
	}
	UpdateColorSetting();
	g_pMainWnd->RunDrawThreadOnce();
}

void DopplerGroupTab::on_BtnColorThickness_clicked()
{
	DialogColorSelect _dialog(this) ;
	int _nRet = _dialog.exec();
	if(_nRet)
	{
		ParameterProcess* _process = ParameterProcess::Instance();
		_process->SetupPalette(m_nGroupId , PALETTE_THICKNESS , _dialog.GetColorIndex()) ;
	}
	UpdateColorSetting();
	g_pMainWnd->RunDrawThreadOnce();
}

void DopplerGroupTab::on_ComColorLineSelection_currentIndexChanged(int index)
{
	if(!ui->ComColorLineSelection->hasFocus()) return ;
	ui->ComColorLineColor->setCurrentIndex(m_pGroup->color.anColor[index]);
}

void DopplerGroupTab::on_ComColorLineColor_currentIndexChanged(int index)
{
	if(!ui->ComColorLineColor->hasFocus()) return ;
	int _nLine = ui->ComColorLineSelection->currentIndex()  ;

	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupAScanColor(m_nGroupId , _nLine  , index);
}

void DopplerGroupTab::on_ValueCScanThicknessMin_valueChanged(double)
{
	if(!ui->ValueCScanThicknessMin->hasFocus()) return ;
	m_pGroup->fMinThickness = ui->ValueCScanThicknessMin->value() ;

	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
	g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ValueCScanThicknessMax_valueChanged(double)
{
	if(!ui->ValueCScanThicknessMax->hasFocus()) return ;
	m_pGroup->fMaxThickness = ui->ValueCScanThicknessMax->value() ;

	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
	g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ComCScanSource1_currentIndexChanged(int index)
{
	if(!ui->ComCScanSource1->hasFocus()) return ;
	m_pGroup->eCScanSource[0] = (setup_CSCAN_SOURCE_MODE)index ;
	g_pMainWnd->UpdateAllDisplay();
	g_pMainWnd->RunDrawThreadOnce();
}

void DopplerGroupTab::on_ComCScanSource2_currentIndexChanged(int index)
{
	if(!ui->ComCScanSource2->hasFocus()) return ;
	m_pGroup->eCScanSource[1] = (setup_CSCAN_SOURCE_MODE)index ;
	g_pMainWnd->UpdateAllDisplay();
	g_pMainWnd->RunDrawThreadOnce();
}

void DopplerGroupTab::ComDispPro(int index, int iGroup)
{
	QComboBox* _comboxTab[4];
	_comboxTab[0] = ui->ComComDisp1;
	_comboxTab[1] = ui->ComComDisp2;
	_comboxTab[2] = ui->ComComDisp3;
	_comboxTab[3] = ui->ComComDisp4;

	if(index > 3)  return ;
	if(!_comboxTab[index]->hasFocus()) return ;

	U8* _pComDisp = m_pConfig->GetComDisplayPoint();
	bool _bExist = false;
	for(int i = 0; i < 4; i++) {
		if(i != index) {
			if(_pComDisp[i] == iGroup) {
				_bExist = true;
			}
		}
	}
	if(_bExist) {
		_comboxTab[index]->setCurrentIndex(_pComDisp[index]);
	} else {
		_pComDisp[index] = iGroup;
	}
}

void DopplerGroupTab::on_ComComDisp1_currentIndexChanged(int index)
{
	ComDispPro(0, index);
}

void DopplerGroupTab::on_ComComDisp2_currentIndexChanged(int index)
{
	ComDispPro(1, index);
}

void DopplerGroupTab::on_ComComDisp3_currentIndexChanged(int index)
{
	ComDispPro(2, index);
}

void DopplerGroupTab::on_ComComDisp4_currentIndexChanged(int index)
{
	ComDispPro(3, index);
}

void DopplerGroupTab::on_BtnRefurbishComDisp_clicked()
{
	g_pMainWnd->UpdateCombinationDisplay();
	sleep(600);
}

void DopplerGroupTab::on_CheckDefectShow_clicked(bool checked)
{
	m_pGroup->bShowDefect = checked ;
	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
}

void DopplerGroupTab::on_ComDefectIndex_currentIndexChanged(int index)
{
	if(!ui->ComDefectIndex->hasFocus()) return ;
	DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
	_pConfig->m_dfParam[m_nGroupId].index = index;
	UpdateDefectValue() ;
	g_pMainWnd->RunDrawThreadOnce();
}

void DopplerGroupTab::on_lineEditReMark_textChanged(QString str)
{
	if(!ui->lineEditReMark->hasFocus()) return ;
	//QString str = ui->lineEditReMark->text();
	DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
	int _index = _pConfig->m_dfParam[m_nGroupId].index;
	_pConfig->SetDefectInfo(m_nGroupId, _index, (char*)(qPrintable(str)));

	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
}
void DopplerGroupTab::on_BtnDefectDelete_clicked()
{
	DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
	int _index = _pConfig->m_dfParam[m_nGroupId].index;

	_pConfig->DeleteDefect(m_nGroupId, _index);

	UpdateDefectBox();
	UpdateDefectValue() ;
//  g_pMainWnd->RunDrawThreadOnce();
	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
}

void DopplerGroupTab::on_ComLanguage_currentIndexChanged(int index_)
{
	if(!ui->ComLanguage->hasFocus()) return ;

	setup_LANG _eLang;
	switch(index_)
	{
	case 0:  _eLang = setup_LANG_ENGLISH;  break;
	case 1:  _eLang = setup_LANG_CHINESS;  break;
	case 2:  _eLang = setup_LANG_JAPEN;  break;
	case 3:  _eLang = setup_LANG_KOREA;  break;
	default: return;
	}
	m_pConfig->AppEvn.eLanguage = _eLang;
    g_pMainWnd->SetWndName();
}
