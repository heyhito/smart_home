#include "speech.h"

speech::speech(QObject *parent) : QObject(parent)
{

}


QString speech::speechIdentify(QString fileName)
{
    //拼接请求URL 获取Access_token
    QString tokenUrl = QString(baiduUrl).arg(client_id).arg(client_key);

    //设置请求头
    QMap<QString,QString> header;
    header.insert(QString("Content-Type"),QString("audio/pcm;rate=16000"));

    //发送的音频数据
    QByteArray requestData;
    //服务器返回的内容
    QByteArray replayData;

    //获取accessToken
    http my_http;
    QString accessToken;
    bool result = my_http.post_sync(tokenUrl,header,requestData,replayData);

    if(result)
    {
        QString key = "access_token";
        accessToken = getJsonValue(replayData,key);

        //qDebug() << accessToken;
    }
    else
    {

    }

    //添加以下代码：

    /*  向服务器发送第二次请求 */
    //组成请求URL
    QString speechUrl = QString(baiduSpeechUrl).arg(QHostInfo::localHostName()).arg(accessToken);

    //将文件转换成QByteArray
    QFile file;
    file.setFileName(fileName);
    //读取到的数据放在requestData；
    file.open(QIODevice::ReadOnly);
    requestData = file.readAll();
    file.close();

    //清楚上一次获取的数据
    replayData.clear();


    //再次发起请求，获取识别的结果
    bool result2 = my_http.post_sync(speechUrl,header,requestData,replayData);
    if(result2)
    {
        /*
        识别成功返回 case：

    {"err_no":0,"err_msg":"success.","corpus_no":"15984125203285346378",
    "sn":"481D633F-73BA-726F-49EF-8659ACCC2F3D","result":["北京天气"]}

    */
        qDebug() << "replay:" + replayData;
        QString key = "result";
        QString text = getJsonValue(replayData,key);
        qDebug() << "text:"+text;
        return text;
    }
    else
    {
        QMessageBox::warning(NULL,"识别提示","识别失败");
    }
    return "";


}


QString speech::getJsonValue(QByteArray ba, QString key)
{
    //用于接收转换的错误信息
    QJsonParseError paraseError;
    //将QByteArray类型解析成jsonDocument类型
    QJsonDocument jsonDocument = QJsonDocument::fromJson(ba,&paraseError);
    if(paraseError.error == QJsonParseError::NoError)
    {
        //确保是jsonDocument对象
        if(jsonDocument.isObject())
        {
            //进一步将jsonDocument对象转换成json对象
            QJsonObject jsonObject = jsonDocument.object();
            //进一步判断json数据中是否有需要获取的键值
            if(jsonObject.contains(key))
            {
                //根据键获取值
                QJsonValue jsonvalue = jsonObject.value(key);

                //判断获取到的值是哪种类型
                //因为第一次获取access_token是字符串类型
                //第二次获取语音识别的结果，是数组类型
                //因此需要进行区分
                if(jsonvalue.isString()) //字符串
                {

                    return jsonvalue.toString();//返回QString类型
                }
                else if(jsonvalue.isArray()) //数组 获取数组的第一个元素
                {
                    QJsonArray jsonArray =  jsonvalue.toArray();//转换成JsonArray
                    //获取第一个元素
                    QJsonValue jv = jsonArray.at(0);
                    qDebug() << jv;
                    return jv.toString();

                }
            }
        }
    }
    return "没有";
}
