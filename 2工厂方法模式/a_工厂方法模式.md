```c++
#include <cstdio>

//抽象产品类
class Picture {
public:
  Picture() {}
  ~Picture() {}
  virtual void getMessage() = 0;
};

//具体产品类
class JpegPicture : public Picture {
public:
  JpegPicture() {}
  ~JpegPicture() {}
  void getMessage() { printf("operate JPEG\n"); }
};

//具体产品类
class GifPicture : public Picture {
public:
  GifPicture() {}
  ~GifPicture() {}
  void getMessage() { printf("operate GIF\n"); }
};

//抽象工厂类
class PictureFactory {
public:
  PictureFactory() {}
  ~PictureFactory() {}
  void getMessage() {
    Picture *picture = this->createPicture();
    picture->getMessage();
  }
  virtual Picture *createPicture() = 0;
};

//具体工厂类
class JpegPictureFactory : public PictureFactory {
public:
  JpegPictureFactory() {}
  ~JpegPictureFactory() {}
  Picture *createPicture() { return new JpegPicture(); }
};

// 具体工厂类
class GifPictureFactory : public PictureFactory {
public:
  GifPictureFactory() {}
  ~GifPictureFactory() {}
  Picture *createPicture() { return new GifPicture(); }
};

//主函数
int main(int argc, char *argv[]) {
  PictureFactory *pf[2] = {new JpegPictureFactory(), new GifPictureFactory()};
  for (int i = 0; i < 2; i++) {
    pf[i]->getMessage();
  }
  return 0;
}

/*从上述实例可以看出：使用工厂方法模式设计，在进行扩展时不需要修改源代码，
 * 但要要新增两个类(一个是具体产品类，另一个时具体工厂类)
 * 虽说完美地符合了开闭原则，但是随着类的显著增加，又是一种弊端*/
 ```
