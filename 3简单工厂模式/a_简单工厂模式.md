```c++
#include <cstdio>
//图表基类
class Chart 
{
    public:
        Chart(){}
        virtual ~Chart(){}
        virtual void getChart()=0;
};

//饼状图
class Pie:public Chart 
{
    private:
        float range;
    public:
        Pie()
        {
            range = 0.0f;
        }
        ~Pie(){}
        void getChart()
        {
            printf("this is pie chart!----range:%f\n",range);
        }
};

//折线图
class Line:public Chart 
{
    private:
        int high;
    public:
        Line(){
            high = 1;
        }
        ~Line(){}
        void getChart()
        {
            printf("this is line chart!----high=%d\n",high);
        }
};

//图表工厂
class ChartFactory 
{
    public:
        static Chart* createChart(int arg) 
        {
            switch (arg) {
                case 1:
                    return new Pie();
                    break;
                case 2:
                    return new Line();
                    break;
                default:
                    return nullptr;
                    break;
            }
        }
};

class UseChart 
{
    private:
        Chart* chart;
    public:
        UseChart()
        {
            chart = ChartFactory::createChart(1);
        }
        ~UseChart(){}
        void setChart(int arg)
        {
            if(chart!=nullptr)
                delete chart;
            chart = ChartFactory::createChart(arg);
        }
        void getDes()
        {
            chart->getChart();
        }
};

int main(int argc,char *argv[])
{
    UseChart example;
    example.getDes();
    example.setChart(2);
    example.getDes();
    return 0;
}
```
