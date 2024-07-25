#ifndef AUDIO_H
#define AUDIO_H

#include <QObject>
#include <QAudioInput>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QIODevice>
#include <QFile>
#include <QMessageBox>

class Audio : public QObject
{
    Q_OBJECT
public:
    explicit Audio(QObject *parent = 0);

    //按下按钮开始录音
    void startAudio(QString fileName);

    //松开按钮结束录音
    void stopAudio();

signals:

public slots:

private:
    //定义录音对象，开始录音和结束录音都要对这个对象进行控制
    QAudioInput *my_audio;

    //定义文件对象
    QFile *my_file;


};

#endif // AUDIO_H
