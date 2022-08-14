#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    QStringList serialPortName;

    ui->setupUi(this);

    ui->receiveTextEdit->setReadOnly(true);

    serialPort = new QSerialPort(this);

    connect(serialPort, SIGNAL(readyRead()), this, SLOT(serialPortReadyRead()));

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        serialPortName << info.portName();
    }

    ui->serialNumberComboBox->addItems(serialPortName);

    file.setFileName("config.txt");
    file.open(QIODevice::ReadWrite);

    QByteArray configByteArray;
    for(int i = 0; i < 7 && file.atEnd() == false; i++)
    {
        configByteArray = file.readLine();
        switch(i)
        {
        case 0:
            QCommand = configByteArray;
            QCommand = QCommand.left(QCommand.length() - 1);
            break;
        case 1:
            WCommand = configByteArray;
            WCommand = WCommand.left(WCommand.length() - 1);
            break;
        case 2:
            ECommand = configByteArray;
            ECommand = ECommand.left(ECommand.length() - 1);
            break;
        case 3:
            ACommand = configByteArray;
            ACommand = ACommand.left(ACommand.length() - 1);
            break;
        case 4:
            SCommand = configByteArray;
            SCommand = SCommand.left(SCommand.length() - 1);
            break;
        case 5:
            DCommand = configByteArray;
            DCommand = DCommand.left(DCommand.length() - 1);
            break;
        case 6:
            emergencyStopCommand = configByteArray;
            //emergencyStopCommand = emergencyStopCommand.left(emergencyStopCommand.length() - 1);
            break;
        }
    }
    file.close();
}

Widget::~Widget()
{
    if(serialPort->isOpen())
    {
        serialPort->clear();
        serialPort->close();
    }
    delete ui;
}

void Widget::on_SwitchOnSerialPortPushButton_clicked()
{
    //如果串口已经打开了，就先关闭
    if(serialPort->isOpen())
    {
        serialPort->clear();
        serialPort->close();
        ui->serialNumberComboBox->setEnabled(true);
        ui->SwitchOnSerialPortPushButton->setText("打开串口");
        return;
    }


    serialPort->setPortName(ui->serialNumberComboBox->currentText());
    serialPort->setBaudRate(ui->BaudRateComboBox->currentText().toInt());
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setParity(QSerialPort::NoParity);

    if(serialPort->isOpen() == false && serialPort->open(QIODevice::ReadWrite) == false)
    {
        QMessageBox::critical(this, "提示", "串口打开失败");
    }
    else
    {
        ui->serialNumberComboBox->setEnabled(false);
        ui->SwitchOnSerialPortPushButton->setText("关闭串口");
    }
}


void Widget::on_scanSerialPortPushButton_clicked()
{
    QStringList serialPortName;

    ui->serialNumberComboBox->clear();

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        serialPortName << info.portName();
    }

    ui->serialNumberComboBox->addItems(serialPortName);
}

void Widget::serialPortReadyRead()
{
    QByteArray receiveData = serialPort->readAll();
    QString receiveText = QString::fromStdString(receiveData.toStdString());

    ui->receiveTextEdit->insertPlainText(receiveText);
}

void Widget::on_sendMessagePushButton_clicked()
{
    QByteArray sendData;
    QString sendText;

    if(ui->sendTextLineEdit->text().isEmpty() == false)
    {
        sendText = ui->sendTextLineEdit->text();

        if(ui->addEnterComboBox->currentText() == "是")
        {
            sendText += '\n';
        }

        sendData = sendText.toLatin1();

        serialPort->write(sendData);
    }
}


void Widget::on_clearReceiveTextPushButton_clicked()
{
    ui->receiveTextEdit->clear();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_W:
        serialPort->write(WCommand.toLatin1());
        break;
    case Qt::Key_A:
        serialPort->write(ACommand.toLatin1());
        break;
    case Qt::Key_S:
        serialPort->write(SCommand.toLatin1());
        break;
    case Qt::Key_D:
        serialPort->write(DCommand.toLatin1());
        break;
    case Qt::Key_Q:
        serialPort->write(QCommand.toLatin1());
        break;
    case Qt::Key_E:
        serialPort->write(ECommand.toLatin1());
        break;
    default:
        serialPort->write(emergencyStopCommand.toLatin1());
        break;
    }
    if(ui->addEnterComboBox->currentIndex() == 0)
    {
        serialPort->write(QString('\n').toLatin1());
    }
}

void Widget::on_WCommandPushButton_clicked()
{
    bool ok;
    QString command = QInputDialog::getText(this, "按键命令", "输入按键控制发送的命令", QLineEdit::Normal, WCommand, &ok);
    if(ok && command.isEmpty() == false)
    {
        WCommand = command;
    }
}


void Widget::on_SCommandPushButton_clicked()
{
    bool ok;
    QString command = QInputDialog::getText(this, "按键命令", "输入按键控制发送的命令", QLineEdit::Normal, SCommand, &ok);
    if(ok && command.isEmpty() == false)
    {
        SCommand = command;
    }
}


void Widget::on_ACommandPushButton_clicked()
{
    bool ok;
    QString command = QInputDialog::getText(this, "按键命令", "输入按键控制发送的命令", QLineEdit::Normal, ACommand, &ok);
    if(ok && command.isEmpty() == false)
    {
        ACommand = command;
    }
}


void Widget::on_DCommandPushButton_clicked()
{
    bool ok;
    QString command = QInputDialog::getText(this, "按键命令", "输入按键控制发送的命令", QLineEdit::Normal, DCommand, &ok);
    if(ok && command.isEmpty() == false)
    {
        DCommand = command;
    }
}


void Widget::on_QCommandPushButton_clicked()
{
    bool ok;
    QString command = QInputDialog::getText(this, "按键命令", "输入按键控制发送的命令", QLineEdit::Normal, QCommand, &ok);
    if(ok && command.isEmpty() == false)
    {
        QCommand = command;
    }
}


void Widget::on_ECommandPushButton_clicked()
{
    bool ok;
    QString command = QInputDialog::getText(this, "按键命令", "输入按键控制发送的命令", QLineEdit::Normal, ECommand, &ok);
    if(ok && command.isEmpty() == false)
    {
        ECommand = command;
    }
}


void Widget::on_emergencyStopCommandPushButton_clicked()
{
    bool ok;
    QString command = QInputDialog::getText(this, "按键命令", "输入按键控制发送的命令", QLineEdit::Normal,
                                            emergencyStopCommand, &ok);
    if(ok && command.isEmpty() == false)
    {
        emergencyStopCommand = command;
    }
}

void Widget::on_lockerPushButton_toggled(bool checked)
{
    if(checked)
    {
        ui->lockerPushButton->setText("解锁");
        ui->clearReceiveTextPushButton->setEnabled(false);
        ui->ACommandPushButton->setEnabled(false);
        ui->DCommandPushButton->setEnabled(false);
        ui->ECommandPushButton->setEnabled(false);
        ui->QCommandPushButton->setEnabled(false);
        ui->SCommandPushButton->setEnabled(false);
        ui->WCommandPushButton->setEnabled(false);
        ui->emergencyStopCommandPushButton->setEnabled(false);
        ui->SwitchOnSerialPortPushButton->setEnabled(false);
        ui->sendMessagePushButton->setEnabled(false);
        ui->sendTextLineEdit->setEnabled(false);
        ui->scanSerialPortPushButton->setEnabled(false);
        //ui->serialNumberComboBox->setEnabled(false);
        ui->BaudRateComboBox->setEnabled(false);
        ui->addEnterComboBox->setEnabled(false);
        ui->saveConfigPushButton->setEnabled(false);
        ui->receiveTextEdit->setFocusPolicy(Qt::NoFocus);
    }
    else
    {
        ui->lockerPushButton->setText("锁定");
        ui->clearReceiveTextPushButton->setEnabled(true);
        ui->ACommandPushButton->setEnabled(true);
        ui->DCommandPushButton->setEnabled(true);
        ui->ECommandPushButton->setEnabled(true);
        ui->QCommandPushButton->setEnabled(true);
        ui->SCommandPushButton->setEnabled(true);
        ui->WCommandPushButton->setEnabled(true);
        ui->emergencyStopCommandPushButton->setEnabled(true);
        ui->SwitchOnSerialPortPushButton->setEnabled(true);
        ui->sendMessagePushButton->setEnabled(true);
        ui->sendTextLineEdit->setEnabled(true);
        ui->scanSerialPortPushButton->setEnabled(true);
        //ui->serialNumberComboBox->setEnabled(true);
        ui->BaudRateComboBox->setEnabled(true);
        ui->saveConfigPushButton->setEnabled(true);
        ui->addEnterComboBox->setEnabled(true);
    }
}


void Widget::on_saveConfigPushButton_clicked()
{
    file.open(QIODevice::ReadWrite);
    file.write((QCommand + '\n').toLatin1());
    file.write((WCommand + '\n').toLatin1());
    file.write((ECommand + '\n').toLatin1());
    file.write((ACommand + '\n').toLatin1());
    file.write((SCommand + '\n').toLatin1());
    file.write((DCommand + '\n').toLatin1());
    file.write((emergencyStopCommand).toLatin1());
    file.close();
}
