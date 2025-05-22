#ifndef IMPORTTABHANDLER_H
#define IMPORTTABHANDLER_H

#include <QObject>
#include "ui_mainwindow.h"

class ImportHandler:public QObject
{
    Q_OBJECT
public:
    explicit ImportHandler(Ui::MainWindow *ui_m = nullptr);
    // ~ImportHandler();

private slots:
    void on_btn_add_csv_clicked();

private:
    Ui::MainWindow *ui;

    void displayCsvFileInfo(const QString &folderPath);
    QString formatFileSize(qint64 size);
};

#endif // IMPORTTABHANDLER_H
