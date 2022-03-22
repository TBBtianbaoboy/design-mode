//---------------------------------
//File Name    : main.cpp
//Author       : aico
//Mail         : 2237616014@qq.com
//Github       : https://github.com/TBBtianbaoboy
//Site         : https://www.lengyangyu520.cn
//Create Time  : 2022-03-15 15:32:24
//Description  : 
//----------------------------------
//@Function: 做为两个不兼容的接口之间的桥梁，用于结合两个独立接口的功能
//@KeyCode: 适配器继承和使用已有的对象，同时，已有的对象使用适配器对象
//@Good: 可以让任何两个没有关联的类一起运行；
//       提高了类的复用
//       增加了类的透明度
//       灵活性好
//@Bad: 过多使用适配器会让系统非常零乱，不易整体进行把握;
//      因此，如非必要，可以不使用适配器，而是直接对系统进行重构

#include <iostream>
using std::cout;
using std::endl;
using std::string;

//@Function: 这是专门用来播放除mp3的类
class AdvancedMediaPlayer {
    public:
        virtual ~AdvancedMediaPlayer(){};
        virtual void playMp4()=0;
        virtual void playVlc()=0;
};

class VlcPlayer final : public AdvancedMediaPlayer {
    public:
        virtual void playVlc() override {
            cout << "vlc playing" << endl;
        }
        virtual void playMp4() override {
        }
};

class Mp4Player final : public AdvancedMediaPlayer {
    public:
        virtual void playVlc() override {
        }
        virtual void playMp4() override {
            cout << "mp4 playing" << endl;
        }
};

//统一合并使用类
class MediaPlayer {
    public:
        virtual ~MediaPlayer(){};
        virtual void play(const string&)=0;
};

//@Function: 适配器，用于统一合并使用类的另一个对象使用
class MediaAdapter final : public MediaPlayer {
    private:
        AdvancedMediaPlayer *advancedMediaPlayer;

    public:
        MediaAdapter(const string&name){
            if(name=="mp4")
                advancedMediaPlayer = new Mp4Player();
            else if(name=="vlc")
                advancedMediaPlayer = new VlcPlayer();
        }
        ~MediaAdapter(){
            if(advancedMediaPlayer!=nullptr)
                delete advancedMediaPlayer;
        }

        virtual void play(const string &name) override {
            if(name=="mp4")
                advancedMediaPlayer->playMp4();
            else if(name=="vlc")
                advancedMediaPlayer->playVlc();
        }
};

//@Function: 统一供外部使用的对象
class AudioPlayer final : public MediaPlayer {
    private:
        MediaAdapter *mediaAdapter;
    public:
        AudioPlayer():mediaAdapter(nullptr){}
        virtual ~AudioPlayer(){
            if (mediaAdapter != nullptr) {
                delete mediaAdapter;
            }
        }
        virtual void play(const string& name)override {
            if(name=="mp4" || name=="vlc"){
                if(mediaAdapter!=nullptr)
                    delete mediaAdapter;
                mediaAdapter = new MediaAdapter(name);
                mediaAdapter->play(name);
            }
            else if(name=="mp3"){
                cout << "mp3 playing" <<endl;
            }else{
                cout << "unknow" << endl;
            }
        }
};

int main(){
    AudioPlayer a;
    a.play("mp3");
    a.play("asd");
    a.play("mp4");
    a.play("vlc");
    return 0;
}

