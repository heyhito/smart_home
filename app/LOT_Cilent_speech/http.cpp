#include "http.h"

http::http(QObject *parent) : QObject(parent)
{

}


bool http::post_sync(QString url, QMap<QString, QString> header, QByteArray requestData, QByteArray &replayData)
{
    //定义执行发送请求的对象
    QNetworkAccessManager manager;

    //定义要发送的数据对象
    QNetworkRequest request;

    /*  配置请求参数  */
    //设置请求的URL
    request.setUrl(url);

    //利用迭代器获取QMap的键值
    QMapIterator<QString,QString> it(header);
    while (it.hasNext()) {
        it.next();
        //.toLatin1()将QString 转换成 QByteArry
        //设置Head
        request.setRawHeader(it.key().toLatin1(),it.value().toLatin1());
    }

    //发送request请求 一旦服务器返回，replay会发出信号,需要捕获该信号
    QNetworkReply *replay = manager.post(request,requestData);

    //利用循环来捕获该信号 捕获成功才推出
    QEventLoop l;

    connect(replay,&QNetworkReply::finished,&l,&QEventLoop::quit);

    //执行死循环,收到inished信号才停止循环
    l.exec();

    if(replay != nullptr && replay->error() == QNetworkReply::NoError)
    {
            //读取服务器返回的数据
            replayData = replay->readAll();
            //第一次返回的数据是Access_token，且是Json格式

            return true;
    }
    else
    {
        qDebug() << "请求失败";
        return false;
    }
}
