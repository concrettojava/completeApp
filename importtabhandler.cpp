#include "importtabhandler.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

ImportHandler::ImportHandler(Ui::MainWindow *ui_m){
    ui = ui_m;
    connect(ui->btn_add_csv,&QPushButton::clicked,this,&ImportHandler::on_btn_add_csv_clicked);
    connect(ui->nvr_testBtn,&QPushButton::clicked,this,&ImportHandler::on_nvr_testBtn_clicked);
    connect(ui->camera_testBtn,&QPushButton::clicked,this,&ImportHandler::on_camera_testBtn_clicked);
    connect(ui->video_save_path_browseBtn,&QPushButton::clicked,this,&ImportHandler::on_video_save_path_browseBtn_clicked);
    connect(ui->video_collectBtn,&QPushButton::clicked,this,&ImportHandler::on_video_collectBtn_clicked);
}

void ImportHandler::on_btn_add_csv_clicked(){
    QString csv_path = QFileDialog::getExistingDirectory(nullptr,"选择文件夹","");
    // QFileDialog::getOpenFileNames(nullptr,"选择多个 CSV 文件","","CSV 文件 (*.csv);;所有文件 (*.*)");
    ui->csv_path_line->setText(csv_path);

    //显示文件列表
    displayCsvFileInfo(csv_path);
}

//***模拟的nvr视频读取测试
void ImportHandler::on_nvr_testBtn_clicked()
{
    QString nvr_path = ui->nvr_lineEdit->text().trimmed();

    //读取路径下的所有视频文件
    if (nvr_path.isEmpty()){
        QMessageBox::warning(nullptr,"NVR路径为空", "请输入有效路径");
        ui->nvr_lineEdit->setStyleSheet("");
        return;
    }

    QDir nvr_Dir(nvr_path);
    if(!nvr_Dir.exists()){
        QMessageBox::warning(nullptr, "NVR路径错误", "路径不存在");
        ui->nvr_lineEdit->setStyleSheet("");
        return;
    }

    QStringList fileFilters;
    fileFilters << "*.mp4" << "*.avi" << "*.mov" << "*.mkv" << "*.flv";
    nvrInfoList = nvr_Dir.entryInfoList(fileFilters, QDir::Files | QDir::NoDotAndDotDot);

    if (nvrInfoList.isEmpty()) {
        QMessageBox::warning(nullptr, "文件为空", "该路径下不存在有效的视频文件");
        ui->nvr_lineEdit->setStyleSheet("");
        return;
    }

    // 构造视频文件信息
    QString info = QString("找到 %1 个视频文件:\n\n").arg(nvrInfoList.size());
    for (const QFileInfo &fileInfo : nvrInfoList) {
        QString fileName = fileInfo.fileName();
        qint64 fileSize = fileInfo.size();
        QString sizeStr;

        // 格式化文件大小为 MB 或 KB
        if (fileSize >= 1024 * 1024)
            sizeStr = QString::number(fileSize / (1024.0 * 1024.0), 'f', 2) + " MB";
        else
            sizeStr = QString::number(fileSize / 1024.0, 'f', 2) + " KB";

        info += QString("• %1 \t\t (%2)\n").arg(fileName, sizeStr);
    }

    QMessageBox::information(nullptr, "NVR Video Files", info);

    // 设置按钮颜色为绿色（表示成功）
    ui->nvr_lineEdit->setStyleSheet("background-color: green; color: white;");
}
void ImportHandler::on_camera_testBtn_clicked()
{
    QString nvr_path = ui->camera_lineEdit->text().trimmed();

    //读取路径下的所有视频文件
    if (nvr_path.isEmpty()){
        QMessageBox::warning(nullptr,"路径为空", "请输入有效路径");
        ui->camera_lineEdit->setStyleSheet("");
        return;
    }

    QDir nvr_Dir(nvr_path);
    if(!nvr_Dir.exists()){
        QMessageBox::warning(nullptr, "NVR路径错误", "路径不存在");
        ui->camera_lineEdit->setStyleSheet("");
        return;
    }

    QStringList fileFilters;
    fileFilters << "*.mp4" << "*.avi" << "*.mov" << "*.mkv" << "*.flv";
    cameraInfoList = nvr_Dir.entryInfoList(fileFilters, QDir::Files | QDir::NoDotAndDotDot);

    if (cameraInfoList.isEmpty()) {
        QMessageBox::warning(nullptr, "文件为空", "该路径下不存在有效的视频文件");
        ui->camera_lineEdit->setStyleSheet("");
        return;
    }

    // 构造视频文件信息
    QString info = QString("找到 %1 个视频文件:\n\n").arg(cameraInfoList.size());
    for (const QFileInfo &fileInfo : cameraInfoList) {
        QString fileName = fileInfo.fileName();
        qint64 fileSize = fileInfo.size();
        QString sizeStr;

        // 格式化文件大小为 MB 或 KB
        if (fileSize >= 1024 * 1024)
            sizeStr = QString::number(fileSize / (1024.0 * 1024.0), 'f', 2) + " MB";
        else
            sizeStr = QString::number(fileSize / 1024.0, 'f', 2) + " KB";

        info += QString("• %1 \t\t (%2)\n").arg(fileName, sizeStr);
    }

    QMessageBox::information(nullptr, "NVR Video Files", info);

    // 设置按钮颜色为绿色（表示成功）
    ui->camera_lineEdit->setStyleSheet("background-color: green; color: white;");
}
void ImportHandler::on_video_save_path_browseBtn_clicked(){
    videoSavePath = QFileDialog::getExistingDirectory();
    ui->video_save_path_lineEdit->setText(videoSavePath);
    if (!videoSavePath.isEmpty()){
        ui->video_save_path_lineEdit->setStyleSheet("background-color:green;color:white");
    }
}
void ImportHandler::on_video_collectBtn_clicked() {
    ui->video_save_log->clear();

    QString nvrPath = ui->nvr_lineEdit->text().trimmed();
    QString cameraPath = ui->camera_lineEdit->text().trimmed();
    QString savePath = ui->video_save_path_lineEdit->text().trimmed();

    if (ui->nvr_lineEdit->styleSheet().contains("background-color: green", Qt::CaseInsensitive)) {
        QMessageBox::warning(nullptr, "错误", "NVR读取尚未确认");
        return;
    }
    if (ui->camera_lineEdit->styleSheet().contains("background-color: green", Qt::CaseInsensitive)) {
        QMessageBox::warning(nullptr, "错误", "高速摄像机读取尚未确认");
        return;
    }
    if (ui->video_save_path_lineEdit->styleSheet().contains("background-color: green", Qt::CaseInsensitive)) {
        QMessageBox::warning(nullptr, "错误", "视频保存路径未设置");
        return;
    }

    QDir().mkpath(savePath + "/NVR");
    QDir().mkpath(savePath + "/Camera");

    QStringList nvrFiles = QDir(nvrPath).entryList(QDir::Files);
    QStringList cameraFiles = QDir(cameraPath).entryList(QDir::Files);

    int totalFiles = nvrFiles.size() + cameraFiles.size();
    if (totalFiles == 0) {
        QMessageBox::information(nullptr, "提示", "没有可导入的视频文件");
        return;
    }

    int copied = 0;
    ui->video_collect_progressBar->setValue(0);

    auto copyAndLog = [&](const QStringList &files, const QString &srcPath, const QString &dstPath) {
        for (const QString &file : files) {
            QString srcFile = srcPath + "/" + file;
            QString dstFile = dstPath + "/" + file;

            if (QFile::copy(srcFile, dstFile)) {
                ui->video_save_log->append(QString("已复制：%1").arg(file));
            } else {
                ui->video_save_log->append(QString("复制失败：%1").arg(file));
            }

            copied++;
            int progress = static_cast<int>((copied * 100.0) / totalFiles);
            ui->video_collect_progressBar->setValue(progress);
            QCoreApplication::processEvents(); // 确保UI更新
        }
    };

    ui->video_save_log->append("开始导入NVR视频...");
    copyAndLog(nvrFiles, nvrPath, savePath + "/NVR");

    ui->video_save_log->append("开始导入Camera视频...");
    copyAndLog(cameraFiles, cameraPath, savePath + "/Camera");

    ui->video_save_log->append("视频导入完成！");
    ui->video_collect_progressBar->setValue(100);
}


void ImportHandler::displayCsvFileInfo(const QString &folderPath){
    //获取地址对应文件夹下的csv文件信息
    QDir csv_dir(folderPath);
    QStringList csv_filter;
    csv_filter <<"*.csv";
    csv_dir.setNameFilters(csv_filter);
    csvInfoList = csv_dir.entryInfoList(QDir::Files);

    QString logContent;
    logContent += QString("共找到 %1 个数据文件\n\n").arg(csvInfoList.size());

    if (csvInfoList.isEmpty()) {
        logContent += "该文件夹中没有找到CSV文件";
    } else {
        // 表头 - 使用制表符
        logContent += QString("名称\t\t\t大小\n");
        logContent += QString("-").repeated(60) + "\n";

        // 遍历文件列表
        for (const QFileInfo &fileInfo : csvInfoList) {
            QString fileName = fileInfo.fileName();
            QString truncatedFileName = (fileName.length() > 35) ? fileName.left(32) + "..." : fileName;
            QString fileSize = formatFileSize(fileInfo.size());

            logContent += truncatedFileName + QString("\t\t") + fileSize + "\n";
        }
    }
    ui->csv_log->setText(logContent);
}

QString ImportHandler::formatFileSize(qint64 size) {
    const qint64 KB = 1024;
    const qint64 MB = KB * 1024;
    const qint64 GB = MB * 1024;

    if (size >= GB) {
        return QString::number(size / (double)GB, 'f', 2) + " GB";
    } else if (size >= MB) {
        return QString::number(size / (double)MB, 'f', 2) + " MB";
    } else if (size >= KB) {
        return QString::number(size / (double)KB, 'f', 2) + " KB";
    } else {
        return QString::number(size) + " B";
    }
}
