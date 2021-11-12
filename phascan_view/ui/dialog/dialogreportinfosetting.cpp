#include "dialogreportinfosetting.h"
#include "ui_dialogreportinfosetting.h"
#include <QFileDialog>

DialogReportInfoSetting::DialogReportInfoSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogReportInfoSetting)
{
    ui->setupUi(this);

    m_model = new QFileSystemModel(this);
    QDir *tmp = new QDir;
    m_infoFilePath = QCoreApplication::applicationDirPath() + "/data/ReportInfo";
    if(!tmp->exists(m_infoFilePath)) {
        tmp->mkdir(m_infoFilePath);
    }
    QStringList nameFilter;
    nameFilter << "*.info";
    m_model->setNameFilterDisables(false);
    m_model->setNameFilters(nameFilter);
    m_model->setRootPath(m_infoFilePath);

    QModelIndex index = m_model->index(m_infoFilePath);
    ui->listView->setModel(m_model);
    ui->listView->setRootIndex(index);
}

DialogReportInfoSetting::~DialogReportInfoSetting()
{
    delete ui;
}

void DialogReportInfoSetting::SetReportInfo2(ReportInfo2 &pInfo, bool flush)
{
    if (flush) {
        m_cInfo = pInfo;
    }

    ui->ProjectNameLine->setText(pInfo.projectName);
    ui->ClientLine->setText(pInfo.client);
    ui->SpecimenNameLine->setText(pInfo.specimenName);
    ui->ReportNumLine->setText(pInfo.reportNum);
    ui->SpecimenNumLine->setText(pInfo.specimenNum);
    ui->InspectionQuantityLine->setText(pInfo.inspectionQuantity);
    ui->InspectionScaleLine->setText(pInfo.inspectionScale);
    ui->ConstructionOrganizationLine->setText(pInfo.constructionOrganization);
    ui->SpecificationsLine->setText(pInfo.specifications);
    ui->WeldingMethodLine->setText(pInfo.weldingMethod);
    ui->SlopeTypeLine->setText(pInfo.slopeType);
    ui->HotDealingConditionLine->setText(pInfo.hotDealingCondition);
    ui->TestSurfaceLine->setText(pInfo.testSurface);
    ui->DetectionTimeLine->setText(pInfo.detectionTime);
    ui->OperationInstructionNumLine->setText(pInfo.operationInstructionNum);
    ui->TestStandardLine->setText(pInfo.testStandard);
    ui->AcceptanceStandardLine->setText(pInfo.acceptanceStandard);
    ui->DetectionLevelLine->setText(pInfo.detectionLevel);
    ui->AcceptanceLevelLine->setText(pInfo.acceptanceLevel);
    ui->SurfaceConditionLine->setText(pInfo.surfaceCondition);
    ui->CalibrationBlockLine->setText(pInfo.calibrationBlock);
    ui->CouplantLine->setText(pInfo.couplant);
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
    m_cInfo.couplant = ui->CouplantLine->text();
}

void DialogReportInfoSetting::on_saveBtn_clicked()
{
    on_buttonBox_accepted();

    QFile file(m_infoFileName);
    file.open (QIODevice::ReadWrite | QIODevice::Truncate);
    QDataStream write(&file);
    write << m_cInfo.projectName;
    write << m_cInfo.client;
    write << m_cInfo.specimenName;
    write << m_cInfo.reportNum;
    write << m_cInfo.specimenNum;
    write << m_cInfo.inspectionQuantity;
    write << m_cInfo.inspectionScale;
    write << m_cInfo.constructionOrganization;
    write << m_cInfo.specifications;
    write << m_cInfo.weldingMethod;
    write << m_cInfo.slopeType;
    write << m_cInfo.hotDealingCondition;
    write << m_cInfo.testSurface;
    write << m_cInfo.detectionTime;
    write << m_cInfo.operationInstructionNum;
    write << m_cInfo.testStandard;
    write << m_cInfo.acceptanceStandard;
    write << m_cInfo.detectionLevel;
    write << m_cInfo.acceptanceLevel;
    write << m_cInfo.surfaceCondition;
    write << m_cInfo.calibrationBlock;
    write << m_cInfo.couplant;

    file.close();
}

void DialogReportInfoSetting::on_deleteBtn_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    if (m_model->fileInfo(index).isFile()) {
        m_model->remove(index);
    }
}

void DialogReportInfoSetting::on_newBtn_clicked()
{
    QDialog *dlg = new QDialog(this);
    dlg->setMinimumSize(220, 50);

    QLabel    *label = new QLabel(tr("File name: "));
    QLineEdit *edit = new QLineEdit();

    QPushButton *okbtn = new QPushButton(tr("Ok"));
    QPushButton *cancelbtn = new QPushButton(tr("Cancel"));

    QHBoxLayout *hlay1 = new QHBoxLayout();
    hlay1->addWidget(okbtn);
    hlay1->addWidget(cancelbtn);

    QHBoxLayout *hlay2 = new QHBoxLayout();
    hlay2->addWidget(label);
    hlay2->addWidget(edit);

    QVBoxLayout *vlay = new QVBoxLayout();
    vlay->addLayout(hlay2);
    vlay->addLayout(hlay1);
    dlg->setLayout(vlay);
    dlg->setModal(true);

    connect(okbtn, &QPushButton::clicked, dlg, [=] {
        dlg->accept();
    });
    connect(cancelbtn, &QPushButton::clicked, dlg, [=] {
        dlg->reject();
    });
    int ret = dlg->exec();
    if (ret == 1) {
        QString name = edit->text();
        if (!name.isNull()) {
            m_infoFileName = m_infoFilePath + "/" + name + ".info";
            on_saveBtn_clicked();
        }
    }

}

void DialogReportInfoSetting::on_clearBtn_clicked()
{
    ReportInfo2 reportInfo;
    SetReportInfo2(reportInfo, false);
}

void DialogReportInfoSetting::on_listView_clicked(const QModelIndex &index)
{
    m_infoFileName = m_model->fileInfo(index).filePath();
    QFile file(m_infoFileName);
    if(!file.open (QIODevice::ReadOnly)){
        return;
    }
    QDataStream reader(&file);
    ReportInfo2 reportInfo;

    reader >> reportInfo.projectName;
    reader >> reportInfo.client;
    reader >> reportInfo.specimenName;
    reader >> reportInfo.reportNum;
    reader >> reportInfo.specimenNum;
    reader >> reportInfo.inspectionQuantity;
    reader >> reportInfo.inspectionScale;
    reader >> reportInfo.constructionOrganization;
    reader >> reportInfo.specifications;
    reader >> reportInfo.weldingMethod;
    reader >> reportInfo.slopeType;
    reader >> reportInfo.hotDealingCondition;
    reader >> reportInfo.testSurface;
    reader >> reportInfo.detectionTime;
    reader >> reportInfo.operationInstructionNum;
    reader >> reportInfo.testStandard;
    reader >> reportInfo.acceptanceStandard;
    reader >> reportInfo.detectionLevel;
    reader >> reportInfo.acceptanceLevel;
    reader >> reportInfo.surfaceCondition;
    reader >> reportInfo.calibrationBlock;
    reader >> reportInfo.couplant;

    SetReportInfo2(reportInfo, false);
    file.close();
}
