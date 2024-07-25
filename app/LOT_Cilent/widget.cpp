#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("厨房安全检测系统");

    //初始化led和报警器状态
    kitchen_flag = 0;
    alerm_flag = 0;

    //未接受到数据时控制按键不可用 连接成功后才可使用
    ui->kitchbutton->setEnabled(false);
    ui->alermbutton->setEnabled(false);

    //初始化客户端对象
    client = new QMqttClient;

    //连接信号和槽
    connect(client,&QMqttClient::connected,this,&Widget::connect_success_slot);
    connect(client,&QMqttClient::disconnected,this,&Widget::connect_error_slot);

    client->setProtocolVersion(QMqttClient::MQTT_5_0);
    //IP地址 MQTT免费的公开IP
    client->setHostname("broker.emqx.io");
    //端口号
    client->setPort(1883);
    //用户ID
    client->setClientId("Qt");
    //访问服务器的账号和密码 如果访问的是MQTT免费服务器 这两个参数无关紧要
    client->setUsername("admin");
    client->setPassword("admin");




}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_connectButton_clicked()
{
    client->connectToHost();
}

//连接成功后进行处理，
void Widget::connect_success_slot()
{
    QMessageBox::information(this,"连接提示","开始检测");

    //连接成功开启控制按键
    ui->kitchbutton->setEnabled(true);
    ui->alermbutton->setEnabled(true);

    //连接成功后关闭按钮
    ui->connectButton->setEnabled(false);

    //等待服务器推送数据
    connect(client,&QMqttClient::messageReceived,this,&Widget::messageRecvSlot);

    //订阅主题
    client->subscribe(QString("/my/devpub"));



}

void Widget::connect_error_slot()
{
    QMessageBox::information(this,"连接提示","连接失败");
}

//服务器一旦推送消息过来就会调用此函数
void Widget::messageRecvSlot(const QByteArray &ba,const QMqttTopicName &topic)
{
    if(topic.name()!="/my/devpub")
    {
        return;
    }
    //把QByteArray转化为Json对象
    QJsonObject json = QJsonDocument::fromJson(ba).object();

    // 读取温度，如果TEMP是以整数形式存储的
    int temp = json.value("TEMP").toInt();

    // 读取湿度，如果HUM是以整数形式存储的
    int hum = json.value("HUM").toInt();

    //读取亮度
    double light = json.value("LIGHT").toDouble();

    //修改数值的字体格式 微软雅黑格式
    QFont font("Mircosoft YaHei",16,75);


    //将读取到的数据显示在对应的标签上
    //将浮点型转换成字符串
    ui->templabel->setFont(font);
    ui->templabel->setText(QString::number(temp));

    ui->humlabel->setFont(font);
    ui->humlabel->setText(QString::number(hum));

    //将浮点型转换成字符串，并且保留两位小数
    ui->lightlabel->setFont(font);
    ui->lightlabel->setText(QString::number(light,'f',2));


}

void Widget::on_kitchbutton_clicked()
{
    QJsonObject json;

    //查看当前灯的状态
    if(kitchen_flag == 0)
    {
        //开灯
        json.insert("LED",1);
        json.insert("alerm",alerm_flag);

        //发布数据
        //参数：主题 具体内容（不能直接发Json格式）
        QByteArray ba = QJsonDocument(json).toJson();
        client->publish(QString("/my/devsub"),ba);

        //更新灯的状态
        kitchen_flag = 1;

    }
    else if(kitchen_flag == 1)
    {
        //关灯
        json.insert("LED",0);
        json.insert("alerm",alerm_flag);

        //发布数据
        //参数：主题 具体内容（不能直接发Json格式）
        QByteArray ba = QJsonDocument(json).toJson();
        client->publish(QString("/my/devsub"),ba);

        //更新灯的状态
        kitchen_flag = 0;
    }
}

void Widget::on_alermbutton_clicked()
{
    QJsonObject json;

    //查看当前报警器的状态
    if(alerm_flag == 0)
    {
        //开启报警器
        json.insert("alerm",1);
        json.insert("LED",kitchen_flag);

        //发布数据
        //参数：主题 具体内容（不能直接发Json格式）
        QByteArray ba = QJsonDocument(json).toJson();
        client->publish(QString("/my/devsub"),ba);

        //更新报警器状态
        alerm_flag = 1;

    }
    else if(alerm_flag == 1)
    {
        //关闭报警器
        json.insert("alerm",0);
        json.insert("LED",kitchen_flag);

        //发布数据
        //参数：主题 具体内容（不能直接发Json格式）
        QByteArray ba = QJsonDocument(json).toJson();
        client->publish(QString("/my/devsub"),ba);

        //更新报警器状态
        alerm_flag = 0;
    }
}


