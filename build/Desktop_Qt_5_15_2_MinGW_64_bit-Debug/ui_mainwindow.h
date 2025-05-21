/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_open;
    QAction *action_save;
    QAction *action_exit;
    QAction *action_about;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_import;
    QVBoxLayout *import_layout;
    QGroupBox *csv_group;
    QVBoxLayout *csv_layout;
    QHBoxLayout *csv_select_layout;
    QPushButton *btn_add_csv;
    QPushButton *btn_remove_csv;
    QSpacerItem *csv_spacer;
    QListWidget *list_csv_files;
    QGroupBox *video_group;
    QVBoxLayout *video_layout;
    QHBoxLayout *video_select_layout;
    QPushButton *btn_select_video_folder;
    QSpacerItem *horizontalSpacer;
    QTextEdit *textEdit;
    QGroupBox *output_group;
    QVBoxLayout *output_layout;
    QHBoxLayout *output_select_layout;
    QLineEdit *edit_output_path;
    QPushButton *btn_select_output;
    QPushButton *pushButton;
    QProgressBar *progress_import;
    QTextEdit *text_import_log;
    QWidget *tab_display;
    QVBoxLayout *display_layout;
    QHBoxLayout *main_content_layout;
    QVBoxLayout *video_layout1;
    QScrollArea *scroll_video;
    QWidget *scroll_video_content;
    QVBoxLayout *data_panel_layout;
    QTabWidget *tab_data_panel;
    QWidget *tab_status_data;
    QVBoxLayout *status_layout;
    QTableWidget *table_status_data;
    QWidget *tab_experiment_data;
    QVBoxLayout *experiment_layout;
    QTableWidget *table_experiment_data;
    QWidget *tab_annotations;
    QVBoxLayout *annotations_layout;
    QTableWidget *table_annotations;
    QHBoxLayout *annotation_buttons;
    QPushButton *btn_edit_annotation;
    QPushButton *btn_delete_annotation;
    QSpacerItem *annotation_spacer;
    QVBoxLayout *controls_layout;
    QHBoxLayout *playback_controls;
    QPushButton *btn_play_pause;
    QSlider *slider_position;
    QLabel *label_time;
    QDoubleSpinBox *playSpeedControl;
    QSpacerItem *speed_spacer;
    QWidget *tab_export;
    QVBoxLayout *export_layout;
    QLabel *label_export_placeholder;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 630);
        action_open = new QAction(MainWindow);
        action_open->setObjectName(QString::fromUtf8("action_open"));
        action_save = new QAction(MainWindow);
        action_save->setObjectName(QString::fromUtf8("action_save"));
        action_exit = new QAction(MainWindow);
        action_exit->setObjectName(QString::fromUtf8("action_exit"));
        action_about = new QAction(MainWindow);
        action_about->setObjectName(QString::fromUtf8("action_about"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_import = new QWidget();
        tab_import->setObjectName(QString::fromUtf8("tab_import"));
        import_layout = new QVBoxLayout(tab_import);
        import_layout->setObjectName(QString::fromUtf8("import_layout"));
        csv_group = new QGroupBox(tab_import);
        csv_group->setObjectName(QString::fromUtf8("csv_group"));
        csv_layout = new QVBoxLayout(csv_group);
        csv_layout->setObjectName(QString::fromUtf8("csv_layout"));
        csv_select_layout = new QHBoxLayout();
        csv_select_layout->setObjectName(QString::fromUtf8("csv_select_layout"));
        btn_add_csv = new QPushButton(csv_group);
        btn_add_csv->setObjectName(QString::fromUtf8("btn_add_csv"));

        csv_select_layout->addWidget(btn_add_csv);

        btn_remove_csv = new QPushButton(csv_group);
        btn_remove_csv->setObjectName(QString::fromUtf8("btn_remove_csv"));

        csv_select_layout->addWidget(btn_remove_csv);

        csv_spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        csv_select_layout->addItem(csv_spacer);


        csv_layout->addLayout(csv_select_layout);

        list_csv_files = new QListWidget(csv_group);
        list_csv_files->setObjectName(QString::fromUtf8("list_csv_files"));

        csv_layout->addWidget(list_csv_files);


        import_layout->addWidget(csv_group);

        video_group = new QGroupBox(tab_import);
        video_group->setObjectName(QString::fromUtf8("video_group"));
        video_layout = new QVBoxLayout(video_group);
        video_layout->setObjectName(QString::fromUtf8("video_layout"));
        video_select_layout = new QHBoxLayout();
        video_select_layout->setObjectName(QString::fromUtf8("video_select_layout"));
        btn_select_video_folder = new QPushButton(video_group);
        btn_select_video_folder->setObjectName(QString::fromUtf8("btn_select_video_folder"));

        video_select_layout->addWidget(btn_select_video_folder);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        video_select_layout->addItem(horizontalSpacer);


        video_layout->addLayout(video_select_layout);

        textEdit = new QTextEdit(video_group);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        video_layout->addWidget(textEdit);


        import_layout->addWidget(video_group);

        output_group = new QGroupBox(tab_import);
        output_group->setObjectName(QString::fromUtf8("output_group"));
        output_layout = new QVBoxLayout(output_group);
        output_layout->setObjectName(QString::fromUtf8("output_layout"));
        output_select_layout = new QHBoxLayout();
        output_select_layout->setObjectName(QString::fromUtf8("output_select_layout"));
        edit_output_path = new QLineEdit(output_group);
        edit_output_path->setObjectName(QString::fromUtf8("edit_output_path"));

        output_select_layout->addWidget(edit_output_path);

        btn_select_output = new QPushButton(output_group);
        btn_select_output->setObjectName(QString::fromUtf8("btn_select_output"));

        output_select_layout->addWidget(btn_select_output);

        pushButton = new QPushButton(output_group);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        output_select_layout->addWidget(pushButton);


        output_layout->addLayout(output_select_layout);


        import_layout->addWidget(output_group);

        progress_import = new QProgressBar(tab_import);
        progress_import->setObjectName(QString::fromUtf8("progress_import"));
        progress_import->setValue(0);

        import_layout->addWidget(progress_import);

        text_import_log = new QTextEdit(tab_import);
        text_import_log->setObjectName(QString::fromUtf8("text_import_log"));
        text_import_log->setReadOnly(true);

        import_layout->addWidget(text_import_log);

        tabWidget->addTab(tab_import, QString());
        tab_display = new QWidget();
        tab_display->setObjectName(QString::fromUtf8("tab_display"));
        display_layout = new QVBoxLayout(tab_display);
        display_layout->setObjectName(QString::fromUtf8("display_layout"));
        main_content_layout = new QHBoxLayout();
        main_content_layout->setObjectName(QString::fromUtf8("main_content_layout"));
        video_layout1 = new QVBoxLayout();
        video_layout1->setSpacing(5);
        video_layout1->setObjectName(QString::fromUtf8("video_layout1"));
        scroll_video = new QScrollArea(tab_display);
        scroll_video->setObjectName(QString::fromUtf8("scroll_video"));
        scroll_video->setWidgetResizable(true);
        scroll_video_content = new QWidget();
        scroll_video_content->setObjectName(QString::fromUtf8("scroll_video_content"));
        scroll_video_content->setGeometry(QRect(0, 0, 466, 491));
        scroll_video->setWidget(scroll_video_content);

        video_layout1->addWidget(scroll_video);


        main_content_layout->addLayout(video_layout1);

        data_panel_layout = new QVBoxLayout();
        data_panel_layout->setObjectName(QString::fromUtf8("data_panel_layout"));
        tab_data_panel = new QTabWidget(tab_display);
        tab_data_panel->setObjectName(QString::fromUtf8("tab_data_panel"));
        tab_status_data = new QWidget();
        tab_status_data->setObjectName(QString::fromUtf8("tab_status_data"));
        status_layout = new QVBoxLayout(tab_status_data);
        status_layout->setObjectName(QString::fromUtf8("status_layout"));
        table_status_data = new QTableWidget(tab_status_data);
        table_status_data->setObjectName(QString::fromUtf8("table_status_data"));
        table_status_data->setAlternatingRowColors(true);

        status_layout->addWidget(table_status_data);

        tab_data_panel->addTab(tab_status_data, QString());
        tab_experiment_data = new QWidget();
        tab_experiment_data->setObjectName(QString::fromUtf8("tab_experiment_data"));
        experiment_layout = new QVBoxLayout(tab_experiment_data);
        experiment_layout->setObjectName(QString::fromUtf8("experiment_layout"));
        table_experiment_data = new QTableWidget(tab_experiment_data);
        table_experiment_data->setObjectName(QString::fromUtf8("table_experiment_data"));
        table_experiment_data->setAlternatingRowColors(true);

        experiment_layout->addWidget(table_experiment_data);

        tab_data_panel->addTab(tab_experiment_data, QString());
        tab_annotations = new QWidget();
        tab_annotations->setObjectName(QString::fromUtf8("tab_annotations"));
        annotations_layout = new QVBoxLayout(tab_annotations);
        annotations_layout->setObjectName(QString::fromUtf8("annotations_layout"));
        table_annotations = new QTableWidget(tab_annotations);
        table_annotations->setObjectName(QString::fromUtf8("table_annotations"));
        table_annotations->setAlternatingRowColors(true);

        annotations_layout->addWidget(table_annotations);

        annotation_buttons = new QHBoxLayout();
        annotation_buttons->setObjectName(QString::fromUtf8("annotation_buttons"));
        btn_edit_annotation = new QPushButton(tab_annotations);
        btn_edit_annotation->setObjectName(QString::fromUtf8("btn_edit_annotation"));

        annotation_buttons->addWidget(btn_edit_annotation);

        btn_delete_annotation = new QPushButton(tab_annotations);
        btn_delete_annotation->setObjectName(QString::fromUtf8("btn_delete_annotation"));

        annotation_buttons->addWidget(btn_delete_annotation);

        annotation_spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        annotation_buttons->addItem(annotation_spacer);


        annotations_layout->addLayout(annotation_buttons);

        tab_data_panel->addTab(tab_annotations, QString());

        data_panel_layout->addWidget(tab_data_panel);


        main_content_layout->addLayout(data_panel_layout);


        display_layout->addLayout(main_content_layout);

        controls_layout = new QVBoxLayout();
        controls_layout->setObjectName(QString::fromUtf8("controls_layout"));
        playback_controls = new QHBoxLayout();
        playback_controls->setObjectName(QString::fromUtf8("playback_controls"));
        btn_play_pause = new QPushButton(tab_display);
        btn_play_pause->setObjectName(QString::fromUtf8("btn_play_pause"));

        playback_controls->addWidget(btn_play_pause);

        slider_position = new QSlider(tab_display);
        slider_position->setObjectName(QString::fromUtf8("slider_position"));
        slider_position->setMinimum(0);
        slider_position->setMaximum(100);
        slider_position->setOrientation(Qt::Horizontal);

        playback_controls->addWidget(slider_position);

        label_time = new QLabel(tab_display);
        label_time->setObjectName(QString::fromUtf8("label_time"));

        playback_controls->addWidget(label_time);

        playSpeedControl = new QDoubleSpinBox(tab_display);
        playSpeedControl->setObjectName(QString::fromUtf8("playSpeedControl"));

        playback_controls->addWidget(playSpeedControl);

        speed_spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        playback_controls->addItem(speed_spacer);


        controls_layout->addLayout(playback_controls);


        display_layout->addLayout(controls_layout);

        tabWidget->addTab(tab_display, QString());
        tab_export = new QWidget();
        tab_export->setObjectName(QString::fromUtf8("tab_export"));
        export_layout = new QVBoxLayout(tab_export);
        export_layout->setObjectName(QString::fromUtf8("export_layout"));
        label_export_placeholder = new QLabel(tab_export);
        label_export_placeholder->setObjectName(QString::fromUtf8("label_export_placeholder"));
        label_export_placeholder->setAlignment(Qt::AlignCenter);

        export_layout->addWidget(label_export_placeholder);

        tabWidget->addTab(tab_export, QString());

        horizontalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);
        tab_data_panel->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\345\256\236\351\252\214\345\233\236\346\272\257\347\263\273\347\273\237", nullptr));
        action_open->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
        action_save->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        action_exit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        action_about->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
        csv_group->setTitle(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\346\226\207\344\273\266\350\257\273\345\217\226", nullptr));
        btn_add_csv->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\346\216\247\345\210\266\346\226\207\344\273\266", nullptr));
        btn_remove_csv->setText(QCoreApplication::translate("MainWindow", "\347\247\273\351\231\244\351\200\211\344\270\255", nullptr));
        video_group->setTitle(QCoreApplication::translate("MainWindow", "\351\253\230\351\200\237\347\233\270\346\234\272\344\270\216NVR\350\257\273\345\217\226", nullptr));
        btn_select_video_folder->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\350\247\206\351\242\221\346\226\207\344\273\266\345\244\271", nullptr));
        output_group->setTitle(QCoreApplication::translate("MainWindow", "\350\276\223\345\207\272\350\256\276\347\275\256", nullptr));
        edit_output_path->setPlaceholderText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\225\260\346\215\256\345\272\223\344\277\235\345\255\230\350\267\257\345\276\204", nullptr));
        btn_select_output->setText(QCoreApplication::translate("MainWindow", "\346\265\217\350\247\210...", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220\346\225\260\346\215\256\345\272\223\346\226\207\344\273\266", nullptr));
        text_import_log->setPlaceholderText(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245\346\227\245\345\277\227\345\260\206\345\234\250\346\255\244\346\230\276\347\244\272...", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_import), QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\345\257\274\345\205\245", nullptr));
        tab_data_panel->setTabText(tab_data_panel->indexOf(tab_status_data), QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201\346\225\260\346\215\256", nullptr));
        tab_data_panel->setTabText(tab_data_panel->indexOf(tab_experiment_data), QCoreApplication::translate("MainWindow", "\345\256\236\351\252\214\346\225\260\346\215\256", nullptr));
        btn_edit_annotation->setText(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221", nullptr));
        btn_delete_annotation->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        tab_data_panel->setTabText(tab_data_panel->indexOf(tab_annotations), QCoreApplication::translate("MainWindow", "\346\240\207\346\263\250\345\210\227\350\241\250", nullptr));
        btn_play_pause->setText(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276/\346\232\202\345\201\234", nullptr));
        label_time->setText(QCoreApplication::translate("MainWindow", "00:00 / 00:00", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_display), QCoreApplication::translate("MainWindow", "\345\256\236\351\252\214\345\233\236\346\224\276", nullptr));
        label_export_placeholder->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\345\212\237\350\203\275\345\274\200\345\217\221\344\270\255...", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_export), QCoreApplication::translate("MainWindow", "\345\256\236\351\252\214\345\257\274\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
