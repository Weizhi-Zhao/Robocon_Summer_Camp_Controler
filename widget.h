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

    void on_ZCommandPushButton_clicked();

    void on_XCommandPushButton_clicked();

    void on_CCommandPushButton_clicked();

    void on_UPCommandPushButton_clicked();

    void on_DOWNCommandPushButton_clicked();

    void on_LEFTCommandPushButton_clicked();

    void on_RIGHTCommandPushButton_clicked();

private:
    Ui::Widget *ui;

    QSerialPort *serialPort;

    //0 1 2 3 4 5 6 7 8 9  10   11   12
    //q w e a s d z x c up down left right
    //0:press, 1:release
    QString command[13][2];
    QString emergencyStopCommand;

    QFile file;

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};
#endif // WIDGET_H
