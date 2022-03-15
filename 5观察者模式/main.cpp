//---------------------------------
// File Name    : main.cpp
// Author       : aico
// Mail         : 2237616014@qq.com
// Github       : https://github.com/TBBtianbaoboy
// Site         : https://www.lengyangyu520.cn
// Create Time  : 2022-03-11 13:06:25
// Description  :
//----------------------------------
//@Function:
//定义对象间一对多的依赖关系，当一个对象状态发生改变时，所有依赖它的对象都得到通知并被自动更新
//@WhenUse: 一个对象的状态发生改变，所有依赖的对象都将得到通知，进行广播通知
//@KeyCode: 在一个类里有一个ArrayList存放观察者们
//@Good: 观察者和被观察者是抽象耦合的关系
//       建立一套触发机制
//@Bad: 如果一个被观察者有很多观察者，那么将所有观察者都通知会花费很多时间
//      如果存在循环依赖的话，会触发循环调用，可能导致系统崩溃
//      没有相应的机制知道观察者是如何发生变化的，仅仅只知道其发生了变化
//@Care: 避免循环依赖
//       一般采用异步的方式来通知观察者，这样可以避免某一观察者出错导致系统卡壳

#include <iostream>
#include <list>
#include <bitset>

using std::cout;
using std::endl;
using std::list;

class Subject;
//@Func: 观察者类
class Observer {
protected:
  Subject *subject;
public:
  virtual ~Observer(){}
  virtual void update() = 0;
};
//@Func: 最终操作类
class Subject final {
private:
  list<Observer *> observers;
  int state;

public:
  Subject() : state(0) {}
  ~Subject(){

  };
  int getState() const;
  void setState(const int &);
  void attach(Observer *);
  void notifyAllObservers();
  void Delete();
};

//@Func: 子观察者类1
class BinaryObserver final : public Observer {
public:
    BinaryObserver(Subject*);
  virtual void update() override;
};

BinaryObserver::BinaryObserver(Subject* sub){
    subject = sub;
    if (subject)
        sub->attach(this);
}

void BinaryObserver::update(){
    cout << std::bitset<sizeof(int)*8>(subject->getState()) << endl;
}

//@Func: 子观察类2
class HexObserver final : public Observer {
public:
    HexObserver(Subject*);
  virtual void update() override;
};

HexObserver::HexObserver(Subject* sub){
    subject = sub;
    if (subject)
        sub->attach(this);
}

void HexObserver::update(){
    cout << std::hex << subject->getState() << endl;
}


int Subject::getState() const { return state; }

void Subject::setState(const int &value) {
  state = value;
  notifyAllObservers();
}

void Subject::attach(Observer *target) { observers.push_back(target); }

void Subject::notifyAllObservers() {
  for (Observer *obj : observers) {
    obj->update();
  }
}

void Subject::Delete(){
    cout << observers.size() << endl;
    for (Observer *obj :observers) {
        delete obj;
    }
    cout << observers.size() << endl;
}

int main(){
    Subject a;
    new BinaryObserver(&a);
    new HexObserver(&a);
    a.setState(3);
    a.setState(10);
    a.Delete();
    return 0;
}
