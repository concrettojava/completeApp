#ifndef IMPORTTABHANDLER_H
#define IMPORTTABHANDLER_H

#include <QObject>
#include "qfileinfo.h"
#include "ui_mainwindow.h"

class ImportHandler:public QObject
{
    Q_OBJECT
public:
    explicit ImportHandler(Ui::MainWindow *ui_m = nullptr);
    // ~ImportHandler();

private slots:
    void on_btn_add_csv_clicked();
    void on_nvr_testBtn_clicked();
    void on_camera_testBtn_clicked();
    void on_video_save_path_browseBtn_clicked();
    void on_video_collectBtn_clicked();

private:
    Ui::MainWindow *ui;

    void displayCsvFileInfo(const QString &folderPath);
    QString formatFileSize(qint64 size);

    QFileInfoList csvInfoList;
    QFileInfoList nvrInfoList;
    QFileInfoList cameraInfoList;
    // bool nvr_checked = false;
    // bool camera_checked = false;
    // bool video_path_ready = false;
    QString videoSavePath;
};

#endif // IMPORTTABHANDLER_H
