# ImageRegistration

## 图像配准类：

文件：

ImageRegistration.h

ImageRegistration.cpp

```
class ImageRegistration {
    Mat src1;
    Mat src2;
    void getRegistrationMat();
    Mat transMatrix;
public:
    void init(Mat,Mat);
    Point2f getXY(int,int);
    ~ImageRegistration();
};
```

其中src1为原图像，src2为待匹配图像。

## 使用

初始化：
```
Mat src1 = imread("test-1.png", 1);
Mat src2 = imread("test-2.png", 1); 
ImageRegistration llll;
llll.init(src1, src2);
```

调用getXY函数即可得到原图中的点在src2中的坐标

```
Point2f temp = llll.getXY(i, j);
```

## 实际演示： 

比如我们将src1中的（100，100）起的50*50的块涂黑，对应的src2中也在相应位置涂黑

![](https://github.com/team79/ImageRegistration/blob/master/test.png)
