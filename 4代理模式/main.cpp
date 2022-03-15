//---------------------------------
//File Name    : main.cpp
//Author       : aico
//Mail         : 2237616014@qq.com
//Github       : https://github.com/TBBtianbaoboy
//Site         : https://www.lengyangyu520.cn
//Create Time  : 2022-03-11 12:14:18
//Description  : 
//----------------------------------
//@Function: 为其他类对象提供一个代理类，以控制对这个类对象的访问
//@WhenUse: 想在访问一些类时做一些控制
//@Good: 职责清晰，高扩展性，智能化
//@Bad: 因为增加了代理对象，因此有可能会造成请求的处理速度变慢。实现代理模式需要额外的工作。
//@Compare: 和适配器模式的区别：适配器模式主要改变所考虑对象的接口，代理模式则不可以。
//          和装饰器模式的区别：装饰器模式是为了增强功能，而代理模式是为了加以控制。
//----------------------------------

#include <iostream>
using std::cout;
using std::endl;
using std::string;

//@Func: 图片抽象类
class Image {
    public:
        Image(){
            cout << "Image Con" << endl;
        }
        virtual ~Image(){};
        virtual void display()=0;
};

//@Func: 现实图片类
class RealImage: public Image {
    private:
        string filename;
    public:
        RealImage(const string&);
        void display();
        void loadDisk();
};

RealImage::RealImage(const string& path):filename(path){
    cout <<"RealImage Con" << endl;
    loadDisk();
}

void RealImage::loadDisk(){
    cout << "Loading"+filename << endl;
}

void RealImage::display(){
    cout << "Displaying"+filename << endl;
}

//@Func: 代理模式类
class Proxy:public Image {
    private:
        RealImage *image;
        string filename;
    public:
        Proxy(const string&);
        ~Proxy();
        void display();
};

Proxy::Proxy(const string& path):image(nullptr),filename(path){
    cout << "Proxy Con" << endl;
}
Proxy::~Proxy(){if(image) delete image;}
void Proxy::display(){
    if(!image){
        image = new RealImage(filename);
    }
    image->display();
}

//@Func: 主函数
int main(){
    Proxy a("abc");
    a.display();
    a.display();
    return 0;
}
