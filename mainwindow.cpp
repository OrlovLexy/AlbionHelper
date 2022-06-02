#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QLibraryInfo>
#include <QEvent>
#include <QComboBox>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItems(QStringList() << "ru_RU" << "en_US");
    connect(ui->comboBox, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            [=](const QString &str) {
        qtLanguageTranslator.load(QString("QtLanguage_") + str);
        qApp->installTranslator(&qtLanguageTranslator);
    });
    qtLanguageTranslator.load(QString("QtLanguage_") + QString("ru_RU"));
    qApp->installTranslator(&qtLanguageTranslator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

