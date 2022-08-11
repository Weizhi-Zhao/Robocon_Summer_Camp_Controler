#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <QKeyEvent>
#include <qinputdialog.h>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_SwitchOnSerialPortPushButton_clicked();

    void on_scanSerialPortPushButton_clicked();

    void serialPortReadyRead();

    void on_sendMessagePushButton_clicked();

    void on_clearReceiveTextPushButton_clicked();

    void on_WCommandPushButton_clicked();

    void on_SCommandPushButton_clicked();

    void on_ACommandPushButton_clicked();

    void on_DCommandPushButton_clicked();

    void on_QCommandPushButton_clicked();

    void on_ECommandPushButton_clicked();

    void on_emergencyStopCommandPushButton_clicked();

    void on_lockerPushButton_toggled(bool checked);

    void on_saveConfigPushButton_clicked();

private:
    Ui::Widget *ui;

    QSerialPort *serialPort;

    QString WCommand, ACommand, SCommand, DCommand, QCommand, ECommand, emergencyStopCommand;

    QFile file;

    void keyPressEvent(QKeyEvent *event);
};
#endif // WIDGET_H
