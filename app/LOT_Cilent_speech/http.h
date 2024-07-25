#ifndef HTTP_H
#define HTTP_H

#include <QObject>
#include <QMap>
//发送请求需要用到的类
#include <QNetworkAccessManager>
#include <QNetworkRequest>
//接收服务器返回的信息
#include <QNetworkReply>
//死循环
#include <QEventLoop>
#include <qDebug>

class http : public QObject
{
    Q_OBJECT
public:
    explicit http(QObject *parent = 0);

    /*
    para:
    QString url:向哪个链接发送请求
    QMap<QString,QString> header:HTTP请求头 Content-Type: audio/pcm;rate=16000
    QByteArray requestData:音频文件，第二次发送请求时同时也要把音频文件发送过去
    QByteArray &replayData:接收信息存放的数组
    */

    bool post_sync(QString url,QMap<QString,QString> header,QByteArray requestData,QByteArray &replayData);

signals:

public slots:
};

#endif // HTTP_H
