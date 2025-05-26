#include "importhandler.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QTextStream>
#include <QFile>
#include <QIODevice>
#include <QCoreApplication>
#include <QDir>
#include <QByteArray>

ImportHandler::ImportHandler(Ui::MainWindow *ui_m){
    ui = ui_m;
    connect(ui->btn_add_csv,&QPushButton::clicked,this,&ImportHandler::on_btn_add_csv_clicked);
    connect(ui->nvr_testBtn,&QPushButton::clicked,this,&ImportHandler::on_nvr_testBtn_clicked);
    connect(ui->camera_testBtn,&QPushButton::clicked,this,&ImportHandler::on_camera_testBtn_clicked);
    connect(ui->video_save_path_browseBtn,&QPushButton::clicked,this,&ImportHandler::on_video_save_path_browseBtn_clicked);
    connect(ui->video_collectBtn,&QPushButton::clicked,this,&ImportHandler::on_video_collectBtn_clicked);

    connect(ui->db_save_path_browseBtn,&QPushButton::clicked,this,&ImportHandler::on_db_save_path_browseBtn_clicked);
    connect(ui->generate_database_btn,&QPushButton::clicked,this,&ImportHandler::on_generate_database_btn_clicked);
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

    if (!ui->nvr_lineEdit->styleSheet().contains("background-color: green")) {
        QMessageBox::warning(nullptr, "错误", "NVR读取尚未有效确认");
        return;
    }
    if (!ui->camera_lineEdit->styleSheet().contains("background-color: green")) {
        QMessageBox::warning(nullptr, "错误", "高速摄像机读取尚未有效确认");
        return;
    }
    qDebug()<< ui->video_save_path_lineEdit->styleSheet();
    if (!ui->video_save_path_lineEdit->styleSheet().contains("green")) {
        QMessageBox::warning(nullptr, "错误", "视频保存路径未有效设置");
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

void ImportHandler::on_db_save_path_browseBtn_clicked(){
    dbSavePath = QFileDialog::getSaveFileName(nullptr, "选择数据库保存位置", "", "数据库文件 (*.db)");
    ui->db_save_path_lineEdit->setText(dbSavePath);
    if (!dbSavePath.isEmpty()){
        ui->db_save_path_lineEdit->setStyleSheet("background-color:green;color:white");
    }
}

void ImportHandler::on_generate_database_btn_clicked(){
    if (dbSavePath.isEmpty()) {
        QMessageBox::warning(nullptr, "错误", "请先选择数据库保存路径");
        return;
    }

    if (csvInfoList.isEmpty()) {
        QMessageBox::warning(nullptr, "错误", "请先选择CSV文件夹");
        return;
    }

    // 创建数据库并打包文件
    createDatabase();
}
void ImportHandler::createDatabase(){
    // 清空日志和重置进度条
    ui->db_generate_log->clear();
    ui->db_generate_progress->setValue(0);

    ui->db_generate_log->append("开始创建数据库文件...");

    // 计算总任务数
    int totalTasks = 3 + csvInfoList.size() + nvrInfoList.size() + cameraInfoList.size(); // 3个表创建 + 所有文件
    int currentTask = 0;

    // 创建SQLite数据库连接
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbSavePath);

    if (!db.open()) {
        QMessageBox::critical(nullptr, "数据库错误", "无法创建数据库文件: " + db.lastError().text());
        ui->db_generate_log->append("错误：无法创建数据库文件");
        return;
    }

    QSqlQuery query(db);

    // 创建CSV数据表
    ui->db_generate_log->append("创建CSV数据表...");
    if (!query.exec("CREATE TABLE csv_data ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "filename TEXT NOT NULL, "
                    "content TEXT NOT NULL, "
                    "file_size INTEGER, "
                    "created_at DATETIME DEFAULT CURRENT_TIMESTAMP)")) {
        QMessageBox::critical(nullptr, "数据库错误", "创建CSV表失败: " + query.lastError().text());
        ui->db_generate_log->append("错误：创建CSV表失败");
        db.close();
        return;
    }
    currentTask++;
    ui->db_generate_progress->setValue((currentTask * 100) / totalTasks);
    QCoreApplication::processEvents();

    // 创建视频文件表
    ui->db_generate_log->append("创建视频文件表...");
    if (!query.exec("CREATE TABLE video_files ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "filename TEXT NOT NULL, "
                    "file_data BLOB, "
                    "file_size INTEGER, "
                    "file_type TEXT, "
                    "created_at DATETIME DEFAULT CURRENT_TIMESTAMP)")) {
        QMessageBox::critical(nullptr, "数据库错误", "创建视频表失败: " + query.lastError().text());
        ui->db_generate_log->append("错误：创建视频表失败");
        db.close();
        return;
    }
    currentTask++;
    ui->db_generate_progress->setValue((currentTask * 100) / totalTasks);
    QCoreApplication::processEvents();

    // 创建元数据表
    ui->db_generate_log->append("创建元数据表...");
    if (!query.exec("CREATE TABLE metadata ("
                    "key TEXT PRIMARY KEY, "
                    "value TEXT NOT NULL)")) {
        QMessageBox::critical(nullptr, "数据库错误", "创建元数据表失败: " + query.lastError().text());
        ui->db_generate_log->append("错误：创建元数据表失败");
        db.close();
        return;
    }
    currentTask++;
    ui->db_generate_progress->setValue((currentTask * 100) / totalTasks);
    QCoreApplication::processEvents();

    // 插入CSV文件数据
    ui->db_generate_log->append(QString("开始导入 %1 个CSV文件...").arg(csvInfoList.size()));
    query.prepare("INSERT INTO csv_data (filename, content, file_size) VALUES (?, ?, ?)");
    for (const QFileInfo &fileInfo : csvInfoList) {
        ui->db_generate_log->append(QString("正在处理CSV文件: %1").arg(fileInfo.fileName()));

        QFile file(fileInfo.absoluteFilePath());
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString content = in.readAll();

            query.addBindValue(fileInfo.fileName());
            query.addBindValue(content);
            query.addBindValue(fileInfo.size());

            if (!query.exec()) {
                ui->db_generate_log->append(QString("失败: %1 - %2").arg(fileInfo.fileName(), query.lastError().text()));
            } else {
                ui->db_generate_log->append(QString("成功: %1 (%2)").arg(fileInfo.fileName(), formatFileSize(fileInfo.size())));
            }
            file.close();
        } else {
            ui->db_generate_log->append(QString("无法读取文件: %1").arg(fileInfo.fileName()));
        }

        currentTask++;
        ui->db_generate_progress->setValue((currentTask * 100) / totalTasks);
        QCoreApplication::processEvents();
    }

    // 插入NVR视频文件数据
    ui->db_generate_log->append(QString("开始导入 %1 个NVR视频文件...").arg(nvrInfoList.size()));
    query.prepare("INSERT INTO video_files (filename, file_data, file_size, file_type) VALUES (?, ?, ?, ?)");
    for (const QFileInfo &fileInfo : nvrInfoList) {
        ui->db_generate_log->append(QString("正在处理NVR视频: %1").arg(fileInfo.fileName()));

        QFile videoFile(fileInfo.absoluteFilePath());
        if (videoFile.open(QIODevice::ReadOnly)) {
            QByteArray videoData = videoFile.readAll();

            query.addBindValue(fileInfo.fileName());
            query.addBindValue(videoData);
            query.addBindValue(fileInfo.size());
            query.addBindValue("NVR");

            if (!query.exec()) {
                ui->db_generate_log->append(QString("失败: %1 - %2").arg(fileInfo.fileName(), query.lastError().text()));
            } else {
                ui->db_generate_log->append(QString("成功: %1 (%2)").arg(fileInfo.fileName(), formatFileSize(fileInfo.size())));
            }
            videoFile.close();
        } else {
            ui->db_generate_log->append(QString("无法读取视频文件: %1").arg(fileInfo.fileName()));
        }

        currentTask++;
        ui->db_generate_progress->setValue((currentTask * 100) / totalTasks);
        QCoreApplication::processEvents();
    }

    // 插入Camera视频文件数据
    ui->db_generate_log->append(QString("开始导入 %1 个Camera视频文件...").arg(cameraInfoList.size()));
    for (const QFileInfo &fileInfo : cameraInfoList) {
        ui->db_generate_log->append(QString("正在处理Camera视频: %1").arg(fileInfo.fileName()));

        QFile videoFile(fileInfo.absoluteFilePath());
        if (videoFile.open(QIODevice::ReadOnly)) {
            QByteArray videoData = videoFile.readAll();

            query.addBindValue(fileInfo.fileName());
            query.addBindValue(videoData);
            query.addBindValue(fileInfo.size());
            query.addBindValue("Camera");

            if (!query.exec()) {
                ui->db_generate_log->append(QString("失败: %1 - %2").arg(fileInfo.fileName(), query.lastError().text()));
            } else {
                ui->db_generate_log->append(QString("成功: %1 (%2)").arg(fileInfo.fileName(), formatFileSize(fileInfo.size())));
            }
            videoFile.close();
        } else {
            ui->db_generate_log->append(QString("无法读取视频文件: %1").arg(fileInfo.fileName()));
        }

        currentTask++;
        ui->db_generate_progress->setValue((currentTask * 100) / totalTasks);
        QCoreApplication::processEvents();
    }

    // 插入元数据
    ui->db_generate_log->append("写入元数据...");
    query.prepare("INSERT INTO metadata (key, value) VALUES (?, ?)");

    // 记录打包时间
    query.addBindValue("pack_time");
    query.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.exec();

    // 记录文件统计
    query.addBindValue("csv_count");
    query.addBindValue(QString::number(csvInfoList.size()));
    query.exec();

    query.addBindValue("nvr_video_count");
    query.addBindValue(QString::number(nvrInfoList.size()));
    query.exec();

    query.addBindValue("camera_video_count");
    query.addBindValue(QString::number(cameraInfoList.size()));
    query.exec();

    db.close();

    // 完成
    ui->db_generate_progress->setValue(100);
    ui->db_generate_log->append("数据库文件生成完成！");
    ui->db_generate_log->append(QString("文件位置: %1").arg(dbSavePath));
    ui->db_generate_log->append(QString("总计: CSV文件 %1 个, NVR视频 %2 个, Camera视频 %3 个")
                                    .arg(csvInfoList.size())
                                    .arg(nvrInfoList.size())
                                    .arg(cameraInfoList.size()));

    // 显示成功消息
    QString successMsg = QString("数据库文件生成完成!\n\n")
                         + QString("文件位置: %1\n").arg(dbSavePath)
                         + QString("CSV文件: %1 个\n").arg(csvInfoList.size())
                         + QString("NVR视频: %2 个\n").arg(nvrInfoList.size())
                         + QString("Camera视频: %3 个").arg(cameraInfoList.size());

    QMessageBox::information(nullptr, "成功", successMsg);
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
