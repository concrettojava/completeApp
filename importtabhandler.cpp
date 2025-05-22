#include "importtabhandler.h"
#include <QDebug>
#include <QFileDialog>

ImportHandler::ImportHandler(Ui::MainWindow *ui_m){
    ui = ui_m;
    connect(ui->btn_add_csv,&QPushButton::clicked,this,&ImportHandler::on_btn_add_csv_clicked);
}

void ImportHandler::on_btn_add_csv_clicked(){
    QString csv_path = QFileDialog::getExistingDirectory(nullptr,"选择文件夹","");
    // QFileDialog::getOpenFileNames(nullptr,"选择多个 CSV 文件","","CSV 文件 (*.csv);;所有文件 (*.*)");
    ui->csv_path_line->setText(csv_path);

    //显示文件列表
    displayCsvFileInfo(csv_path);
}

void ImportHandler::displayCsvFileInfo(const QString &folderPath){
    //获取地址对应文件夹下的csv文件信息
    QDir csv_dir(folderPath);
    QStringList csv_filter;
    csv_filter <<"*.csv";
    csv_dir.setNameFilters(csv_filter);
    QFileInfoList csvInfoList = csv_dir.entryInfoList(QDir::Files);

    //显示在log中
    QString logContent;
    // logContent += QString("<b><span style='color:blue; font-size:18px'>共找到 %1 个数据文件</span></b><br><br>")
    //                   .arg(csvInfoList.size());
    logContent += QString("共找到 %1 个数据文件\n\n").arg(csvInfoList.size());

    if (csvInfoList.isEmpty()) {
        logContent += "该文件夹中没有找到CSV文件";
    } else {
        // 表头
        logContent += QString("%-30s %-10s %s\n").arg("名称", "类型", "大小");
        logContent += QString("%1\n").arg(QString("-").repeated(60));

        // 遍历文件列表
        for (const QFileInfo &fileInfo : csvInfoList) {
            QString fileName = fileInfo.fileName();
            QString fileType = "CSV文件";
            QString fileSize = formatFileSize(fileInfo.size());

            logContent += QString("%-30s %-10s %s\n")
                               .arg(fileName.length() > 30 ? fileName.left(27) + "..." : fileName)
                               .arg(fileType)
                               .arg(fileSize);
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
