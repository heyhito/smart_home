#ifndef SPEECH_H
#define SPEECH_H

#include <QObject>
#include "http.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
//获取主机名
#include <QHostInfo>
#include <QFile>
#include <QIODevice>
#include <QMessageBox>

//获取Access_token相关参数
const QString baiduUrl = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2&";
//访问百度语音的token_id
const QString client_id = "MJzBJ24R49daHpEv3c9MvKHV";
//访问百度语音的token_key
const QString client_key = "SDCrvjZqKz4mRGaOb5ZbuLCzT046cTtE";

//获取语音识别
//1537:普通话 cuid:主机名
const QString baiduSpeechUrl = "http://vop.baidu.com/server_api?dev_pid=1537&cuid=%1&token=%2";

class speech : public QObject
{
    Q_OBJECT
public:
    explicit speech(QObject *parent = 0);

    //传入需要识别的文件，返回识别内容QString类型
    QString speechIdentify(QString fileName);

    //解析Json数据
    QString getJsonValue(QByteArray ba,QString key);

signals:

private:

    //定义Http类
    http my_http;

public slots:
};

#endif // SPEECH_H
