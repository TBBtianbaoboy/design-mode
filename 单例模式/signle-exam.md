```c++
#include <iostream>
#include <mutex>

using std::cout;
using std::endl;

class SinExam {
private:
  static SinExam *example;
  SinExam();
public:
  static SinExam *getExam();
  void test();
};

// 延迟加载-(懒汉式) 单例模式 
// SinExam *SinExam::example = nullptr;

// -(饿汉式) 单例模式 
SinExam *SinExam::example = new SinExam();

SinExam *SinExam::getExam() {
// 延迟加载-(懒汉式) 单例模式 
  //   if (example==nullptr)
  // {
  //     std::mutex a;
  //     a.lock();
  //     if (example==nullptr){
  //         example = new SinExam();
  //     }
  //     a.unlock();
  // }
  return example;
}
SinExam::SinExam() {}

void SinExam::test() { cout << " ok " << endl; }

int main(int argc, char *argv[]) {
  SinExam *examplt = SinExam::getExam();
  examplt->test();
  delete examplt;
  return 0;
}
```
