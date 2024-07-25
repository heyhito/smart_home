#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtMqtt/qmqttclient.h>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:

    //槽函数处理
    void connect_success_slot();
    void connect_error_slot();

    void on_connectButton_clicked();

    //消息接收,保存在ba数组里
    void messageRecvSlot(const QByteArray &ba,const QMqttTopicName &topic);



    void on_kitchbutton_clicked();

    void on_alermbutton_clicked();


private:
    Ui::Widget *ui;
    //创建客户端对象指针
    QMqttClient *client;

    //记录led状态
    int kitchen_flag;

    //记录报警器状态
    int alerm_flag;


};

#endif // WIDGET_H
