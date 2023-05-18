#include "Paint.h"
#include"Graph.h"
#include "ui_GuideWindow.h"
// 大量涉及到qt的ui界面设置
//声明一下别的文件里面有graph的定义，自己去找？怎么让他找外部的类？
class my_GuideWindow:public Ui_GuideWindow
{
public:
  Graph g;
  Widget *w;//这两个都是功能性质的
  //下面是ui_h文件里面的图面布局、按钮等等
 
  // setupUi
  // retranslateUi
  // 设定左侧切换事件
  void setLeftEvents();
  // 设定导游系统事件
  void setMainEvents();
  // 设定范例地图
  void setupDemo();
  // 设定最短路径动态演示
  void setPaint();
};
