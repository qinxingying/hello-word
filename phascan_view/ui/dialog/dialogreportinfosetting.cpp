#include "dialogreportinfosetting.h"
#include "ui_dialogreportinfosetting.h"

DialogReportInfoSetting::DialogReportInfoSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogReportInfoSetting)
{
    ui->setupUi(this);
    ui->spaceLine->hide();


}

DialogReportInfoSetting::~DialogReportInfoSetting()
{
    delete ui;
}

void DialogReportInfoSetting::SetReportInfo2(ReportInfo2 &pInfo)
{
    m_cInfo = pInfo;

    ui->ProjectNameLine->setText(m_cInfo.projectName);
    ui->ClientLine->setText(m_cInfo.client);
    ui->SpecimenNameLine->setText(m_cInfo.specimenName);
    ui->ReportNumLine->setText(m_cInfo.reportNum);
    ui->SpecimenNumLine->setText(m_cInfo.specimenNum);
    ui->InspectionQuantityLine->setText(m_cInfo.inspectionQuantity);
    ui->InspectionScaleLine->setText(m_cInfo.inspectionScale);
    ui->ConstructionOrganizationLine->setText(m_cInfo.constructionOrganization);
    ui->SpecificationsLine->setText(m_cInfo.specifications);
    ui->WeldingMethodLine->setText(m_cInfo.weldingMethod);
    ui->SlopeTypeLine->setText(m_cInfo.slopeType);
    ui->HotDealingConditionLine->setText(m_cInfo.hotDealingCondition);
    ui->TestSurfaceLine->setText(m_cInfo.testSurface);
    ui->DetectionTimeLine->setText(m_cInfo.detectionTime);
    ui->OperationInstructionNumLine->setText(m_cInfo.operationInstructionNum);
    ui->TestStandardLine->setText(m_cInfo.testStandard);
    ui->AcceptanceStandardLine->setText(m_cInfo.acceptanceStandard);
    ui->DetectionLevelLine->setText(m_cInfo.detectionLevel);
    ui->AcceptanceLevelLine->setText(m_cInfo.acceptanceLevel);
    ui->SurfaceConditionLine->setText(m_cInfo.surfaceCondition);
    ui->CalibrationBlockLine->setText(m_cInfo.calibrationBlock);
}

ReportInfo2& DialogReportInfoSetting::GetRePortInfo2()
{
    return m_cInfo ;
}

void DialogReportInfoSetting::on_buttonBox_accepted()
{
    m_cInfo.projectName = ui->ProjectNameLine->text();
    m_cInfo.client      = ui->ClientLine->text();
    m_cInfo.specimenName = ui->SpecimenNameLine->text();
    m_cInfo.reportNum = ui->ReportNumLine->text();
    m_cInfo.specimenNum = ui->SpecimenNumLine->text();
    m_cInfo.inspectionQuantity = ui->InspectionQuantityLine->text();
    m_cInfo.inspectionScale = ui->InspectionScaleLine->text();
    m_cInfo.constructionOrganization = ui->ConstructionOrganizationLine->text();
    m_cInfo.specifications = ui->SpecificationsLine->text();
    m_cInfo.weldingMethod = ui->WeldingMethodLine->text();
    m_cInfo.slopeType = ui->SlopeTypeLine->text();
    m_cInfo.hotDealingCondition = ui->HotDealingConditionLine->text();
    m_cInfo.testSurface = ui->TestSurfaceLine->text();
    m_cInfo.detectionTime = ui->DetectionTimeLine->text();

    m_cInfo.operationInstructionNum = ui->OperationInstructionNumLine->text();
    m_cInfo.testStandard = ui->TestStandardLine->text();
    m_cInfo.acceptanceStandard = ui->AcceptanceStandardLine->text();
    m_cInfo.detectionLevel = ui->DetectionLevelLine->text();
    m_cInfo.acceptanceLevel = ui->AcceptanceLevelLine->text();
    m_cInfo.surfaceCondition = ui->SurfaceConditionLine->text();
    m_cInfo.calibrationBlock = ui->CalibrationBlockLine->text();
}
