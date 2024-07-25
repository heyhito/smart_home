#include "audio.h"

Audio::Audio(QObject *parent) : QObject(parent)
{

}


//按下按钮开始录音
void Audio::startAudio(QString fileName)
{
    //判断是否有录音设备
    QAudioDeviceInfo device = QAudioDeviceInfo::defaultInputDevice();
    if(device.isNull())
    {
        //录音设备不存在
        QMessageBox::warning(NULL,"QAudioDeviceInfo","录音设备不存在");
    }
    else
    {
        //音频编码要求 根据文档要求设置https://ai.baidu.com/ai-doc/SPEECH/Jlbxdezuf
        QAudioFormat my_format;
        //设置采样频率
        my_format.setSampleRate(16000);
        //设置通道数
        my_format.setChannelCount(1);
        //设置位深
        my_format.setSampleSize(16);
        //设置编码
        my_format.setCodec("audio/pcm");

        //判断设备是否支持该格式
        if(!device.isFormatSupported(my_format))
        {
            //如果不支持，找到相近的格式
            my_format=device.nearestFormat(my_format);
        }

        //打开文件
        my_file = new QFile;
        //设置文件名
        my_file->setFileName(fileName);
        //打开文件 录音即往文件写数据 以只写的方式打开
        my_file->open(QIODevice::WriteOnly);

        //创建录音对象
        my_audio = new QAudioInput(my_format,this);
        my_audio->start(my_file);//开始录音

    }

}

//松开按钮结束录音
void Audio::stopAudio()
{
    //停止录音
    my_audio->stop();
    //关闭文件 释放内存
    my_file->close();
    //删除文件对象
    delete my_file;
    //防止出现野指针
    my_file = NULL;
}
