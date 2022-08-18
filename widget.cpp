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
    for(int i = 0; i < 13 && file.atEnd() == false; i++)
    {
        configByteArray = file.readLine();
        command[i][0] = configByteArray;
        command[i][0] = command[i][0].left(command[i][0].length() - 1);

        configByteArray = file.readLine();
        command[i][1] = configByteArray;
        command[i][1] = command[i][1].left(command[i][1].length() - 1);
    }

    if(file.atEnd() == false)
    {
        configByteArray = file.readLine();
        emergencyStopCommand = configByteArray;
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

    ui->receiveTextEdit->moveCursor(QTextCursor::End);
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
    case Qt::Key_Q:
        serialPort->write(command[0][0].toLatin1());
        break;
    case Qt::Key_W:
        serialPort->write(command[1][0].toLatin1());
        break;
    case Qt::Key_E:
        serialPort->write(command[2][0].toLatin1());
        break;
    case Qt::Key_A:
        serialPort->write(command[3][0].toLatin1());
        break;
    case Qt::Key_S:
        serialPort->write(command[4][0].toLatin1());
        break;
    case Qt::Key_D:
        serialPort->write(command[5][0].toLatin1());
        break;
    case Qt::Key_Z:
        serialPort->write(command[6][0].toLatin1());
        break;
    case Qt::Key_X:
        serialPort->write(command[7][0].toLatin1());
        break;
    case Qt::Key_C:
        serialPort->write(command[8][0].toLatin1());
        break;
    case Qt::Key_Up:
        serialPort->write(command[9][0].toLatin1());
        break;
    case Qt::Key_Down:
        serialPort->write(command[10][0].toLatin1());
        break;
    case Qt::Key_Left:
        serialPort->write(command[11][0].toLatin1());
        break;
    case Qt::Key_Right:
        serialPort->write(command[12][0].toLatin1());
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

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Q:
        serialPort->write(command[0][1].toLatin1());
        break;
    case Qt::Key_W:
        serialPort->write(command[1][1].toLatin1());
        break;
    case Qt::Key_E:
        serialPort->write(command[2][1].toLatin1());
        break;
    case Qt::Key_A:
        serialPort->write(command[3][1].toLatin1());
        break;
    case Qt::Key_S:
        serialPort->write(command[4][1].toLatin1());
        break;
    case Qt::Key_D:
        serialPort->write(command[5][1].toLatin1());
        break;
    case Qt::Key_Z:
        serialPort->write(command[6][1].toLatin1());
        break;
    case Qt::Key_X:
        serialPort->write(command[7][1].toLatin1());
        break;
    case Qt::Key_C:
        serialPort->write(command[8][1].toLatin1());
        break;
    case Qt::Key_Up:
        serialPort->write(command[9][1].toLatin1());
        break;
    case Qt::Key_Down:
        serialPort->write(command[10][1].toLatin1());
        break;
    case Qt::Key_Left:
        serialPort->write(command[11][1].toLatin1());
        break;
    case Qt::Key_Right:
        serialPort->write(command[12][1].toLatin1());
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

void Widget::on_QCommandPushButton_clicked()
{
    bool ok;

    QString input = QInputDialog::getText(this, "按键命令", "按下", QLineEdit::Normal, command[0][0], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[0][0] = input;
    }

    input = QInputDialog::getText(this, "按键命令", "松开", QLineEdit::Normal, command[0][1], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[0][1] = input;
    }
}

void Widget::on_WCommandPushButton_clicked()
{
    bool ok;

    QString input = QInputDialog::getText(this, "按键命令", "按下", QLineEdit::Normal, command[1][0], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[1][0] = input;
    }

    input = QInputDialog::getText(this, "按键命令", "松开", QLineEdit::Normal, command[1][1], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[1][1] = input;
    }
}

void Widget::on_ECommandPushButton_clicked()
{
    bool ok;

    QString input = QInputDialog::getText(this, "按键命令", "按下", QLineEdit::Normal, command[2][0], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[2][0] = input;
    }

    input = QInputDialog::getText(this, "按键命令", "松开", QLineEdit::Normal, command[2][1], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[2][1] = input;
    }
}

void Widget::on_ACommandPushButton_clicked()
{
    bool ok;

    QString input = QInputDialog::getText(this, "按键命令", "按下", QLineEdit::Normal, command[3][0], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[3][0] = input;
    }

    input = QInputDialog::getText(this, "按键命令", "松开", QLineEdit::Normal, command[3][1], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[3][1] = input;
    }
}

void Widget::on_SCommandPushButton_clicked()
{
    bool ok;

    QString input = QInputDialog::getText(this, "按键命令", "按下", QLineEdit::Normal, command[4][0], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[4][0] = input;
    }

    input = QInputDialog::getText(this, "按键命令", "松开", QLineEdit::Normal, command[4][1], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[4][1] = input;
    }
}

void Widget::on_DCommandPushButton_clicked()
{
    bool ok;

    QString input = QInputDialog::getText(this, "按键命令", "按下", QLineEdit::Normal, command[5][0], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[5][0] = input;
    }

    input = QInputDialog::getText(this, "按键命令", "松开", QLineEdit::Normal, command[5][1], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[5][1] = input;
    }
}

void Widget::on_ZCommandPushButton_clicked()
{
    bool ok;

    QString input = QInputDialog::getText(this, "按键命令", "按下", QLineEdit::Normal, command[6][0], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[6][0] = input;
    }

    input = QInputDialog::getText(this, "按键命令", "松开", QLineEdit::Normal, command[6][1], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[6][1] = input;
    }
}

void Widget::on_XCommandPushButton_clicked()
{
    bool ok;

    QString input = QInputDialog::getText(this, "按键命令", "按下", QLineEdit::Normal, command[7][0], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[7][0] = input;
    }

    input = QInputDialog::getText(this, "按键命令", "松开", QLineEdit::Normal, command[7][1], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[7][1] = input;
    }
}

void Widget::on_CCommandPushButton_clicked()
{
    bool ok;

    QString input = QInputDialog::getText(this, "按键命令", "按下", QLineEdit::Normal, command[8][0], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[8][0] = input;
    }

    input = QInputDialog::getText(this, "按键命令", "松开", QLineEdit::Normal, command[8][1], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[8][1] = input;
    }
}

void Widget::on_UPCommandPushButton_clicked()
{
    bool ok;

    QString input = QInputDialog::getText(this, "按键命令", "按下", QLineEdit::Normal, command[9][0], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[9][0] = input;
    }

    input = QInputDialog::getText(this, "按键命令", "松开", QLineEdit::Normal, command[9][1], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[9][1] = input;
    }
}

void Widget::on_DOWNCommandPushButton_clicked()
{
    bool ok;

    QString input = QInputDialog::getText(this, "按键命令", "按下", QLineEdit::Normal, command[10][0], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[10][0] = input;
    }

    input = QInputDialog::getText(this, "按键命令", "松开", QLineEdit::Normal, command[10][1], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[10][1] = input;
    }
}

void Widget::on_LEFTCommandPushButton_clicked()
{
    bool ok;

    QString input = QInputDialog::getText(this, "按键命令", "按下", QLineEdit::Normal, command[11][0], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[11][0] = input;
    }

    input = QInputDialog::getText(this, "按键命令", "松开", QLineEdit::Normal, command[11][1], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[11][1] = input;
    }
}

void Widget::on_RIGHTCommandPushButton_clicked()
{
    bool ok;

    QString input = QInputDialog::getText(this, "按键命令", "按下", QLineEdit::Normal, command[12][0], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[12][0] = input;
    }

    input = QInputDialog::getText(this, "按键命令", "松开", QLineEdit::Normal, command[12][1], &ok);
    if(ok && input.isEmpty() == false)
    {
        command[12][1] = input;
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
        ui->ZCommandPushButton->setEnabled(false);
        ui->XCommandPushButton->setEnabled(false);
        ui->CCommandPushButton->setEnabled(false);
        ui->UPCommandPushButton->setEnabled(false);
        ui->DOWNCommandPushButton->setEnabled(false);
        ui->LEFTCommandPushButton->setEnabled(false);
        ui->RIGHTCommandPushButton->setEnabled(false);
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
        ui->ZCommandPushButton->setEnabled(true);
        ui->XCommandPushButton->setEnabled(true);
        ui->CCommandPushButton->setEnabled(true);
        ui->UPCommandPushButton->setEnabled(true);
        ui->DOWNCommandPushButton->setEnabled(true);
        ui->LEFTCommandPushButton->setEnabled(true);
        ui->RIGHTCommandPushButton->setEnabled(true);
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
    for(int i = 0; i < 13; i++)
    {
        file.write((command[i][0] + '\n').toLatin1());
        file.write((command[i][1] + '\n').toLatin1());
    }
    file.write((emergencyStopCommand).toLatin1());
    file.close();
}
