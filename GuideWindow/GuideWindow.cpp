#include"Headers\GuideWindow.h"
//这里包含了所有的头文件，有层层叠加之效,到这里
//，已经用完了所有的定义文件
//本质上是这个文件定义了ui界面，这个cpp行为不改，ui不变

const enum QFont::Weight bold = QFont::Weight::Bold;
const enum QFont::Weight normal = QFont::Weight::Normal;

int v[PLACES];//在这里定义了一个全局变量，项目会出错
// 设定最短路径动态演示
void my_GuideWindow::setPaint()
{
    w = new Widget();
    w->setParent(page_3);
    w->setGeometry(QRect(20, 400, 760, 260));
    for (int i = 0; i < 12; i++)
    {
        w->addVertex(i + 1);
    }
}

// 设定左侧切换事件
void my_GuideWindow::setLeftEvents()
{
    QObject::connect(button_left_1, &QAbstractButton::clicked, [=]() mutable
                     { stackedWidget->setCurrentIndex(0); });
    QObject::connect(button_left_2, &QAbstractButton::clicked, [=]() mutable
                     { stackedWidget->setCurrentIndex(1); });
    QObject::connect(button_left_3, &QAbstractButton::clicked, [=]() mutable
                     { stackedWidget->setCurrentIndex(2); });
    QObject::connect(button_left_4, &QAbstractButton::clicked, [=]() mutable
                     { stackedWidget->setCurrentIndex(3); });
    QObject::connect(button_left_5, &QAbstractButton::clicked, [=]() mutable
                     { stackedWidget->setCurrentIndex(4); });
    QObject::connect(button_left_6, &QAbstractButton::clicked, [=]() mutable
                     { stackedWidget->setCurrentIndex(5); });
    QObject::connect(button_left_7, &QAbstractButton::clicked, [=]() mutable
                     { stackedWidget->setCurrentIndex(6); });
}

// 设定导游系统事件
void my_GuideWindow::setMainEvents()
{
    // 信息录入
    QObject::connect(info_button_1, &QAbstractButton::clicked, [=]() mutable
                     {
        int num = info_text_1->toPlainText().toInt();
        string name = info_text_2->toPlainText().toStdString();
        string info = info_text_3->toPlainText().toStdString();
        g.setInfo(num, name, info); });
    // 道路录入
    QObject::connect(info_button_2, &QAbstractButton::clicked, [=]() mutable
                     {
        int num1 = info_text_4->toPlainText().toInt();
        int num2 = info_text_5->toPlainText().toInt();
        int dis = info_text_6->toPlainText().toInt();
        g.setPath(num1, num2, dis);
        w->addEdge(num1, num2); });
    // 删除景点
    QObject::connect(info_button_3, &QAbstractButton::clicked, [=]() mutable
                     {
        int num = info_text_1->toPlainText().toInt();
        g.delInfo(num);
        for (int i = 0; i < PLACES; i++)
            w->delEdge(i + 1, num);
        for (int j = 0; j < PLACES; j++)
            w->delEdge(num, j + 1); });
    // 删除道路
    QObject::connect(info_button_4, &QAbstractButton::clicked, [=]() mutable
                     {
        int num1 = info_text_4->toPlainText().toInt();
        int num2 = info_text_5->toPlainText().toInt();
        g.delPath(num1, num2);
        w->delEdge(num1, num2); });
    // 查询景点信息
    QObject::connect(search_button_1, &QAbstractButton::clicked, [=]() mutable
                     {
        int num = search_text_1->toPlainText().toInt();
        string result = g.getInfo(num);
        search_text_2->setPlainText(QString::fromStdString(result)); });
    // 查询道路信息
    QObject::connect(search_button_2, &QAbstractButton::clicked, [=]() mutable
                     {
        int num1 = search_text_3->toPlainText().toInt();
        int num2 = search_text_4->toPlainText().toInt();
        string result = g.getPathInfo(num1, num2);
        search_text_5->setPlainText(QString::fromStdString(result)); });
    // 查询最短路径
    QObject::connect(road_button_1, &QAbstractButton::clicked, [=]() mutable
                     {
        int x = road_text_1->toPlainText().toInt();
        int y = road_text_2->toPlainText().toInt();
        string result = "";
        int sum = 0;
        for (int i = 0; i < PLACES; i++)
        {
            if (v[i] != 0 && v[i + 1] != 0)
                w->addEdge(v[i], v[i + 1]);
        }
        for (int i = 0; i < PLACES; i++)
            v[i] = 0;
        g.getPath(x, y, result, sum, v);
        result = "从 " + g.vertex[x].place + " 到 " + g.vertex[y].place + " 的最短路径为：" + result + "\n路径长度：" + to_string(sum);
        road_text_3->setPlainText(QString::fromStdString(result));
        for (int i = 0; i < PLACES; i++)
        {
            if (v[i] != 0 && v[i + 1] != 0)
                w->addActiveEdge(v[i], v[i + 1]);
        } });
    // 查询所有路径
    QObject::connect(multi_button_1, &QAbstractButton::clicked, [=]() mutable
                     {
        int x = multi_text_1->toPlainText().toInt();
        int y = multi_text_2->toPlainText().toInt();
        string result = "";
        g.getAllPath(x, y, true, result);
        result = "从 " + g.vertex[x].place + " 到 " + g.vertex[y].place + " 的所有路径为：\n" + result;
        multi_text_3->setPlainText(QString::fromStdString(result)); });
    // 多景点
    QObject::connect(plenty_button_1, &QAbstractButton::clicked, [=]() mutable
                     {
        int x = plenty_text_1->toPlainText().toInt();
        int y = plenty_text_2->toPlainText().toInt();
        int z = plenty_text_3->toPlainText().toInt();
        string result = "";
        g.multiPath(x, y, z, result);
        result = "从 " + g.vertex[x].place + " 经过 " + g.vertex[y].place + " 到 " + g.vertex[z].place + " 的最短路径为：" + result;
        plenty_text_4->setPlainText(QString::fromStdString(result)); });
    // 范例
    QObject::connect(demo_button_1, &QAbstractButton::clicked, [=]() mutable
                     { setupDemo(); });
}

// 设定范例地图
void my_GuideWindow::setupDemo()
{
    g.setInfo(1, "正门", "软件学院正门");
    g.setInfo(2, "教学楼", "上课上自习的地方");
    g.setInfo(3, "科研楼", "做科研的地方");
    g.setInfo(4, "实验楼", "上机实验以及社团实验室");
    g.setInfo(5, "教研楼", "教研楼");
    g.setInfo(6, "图书馆", "借书看书自习的地方");
    g.setInfo(7, "食堂", "吃饭的地方");
    g.setInfo(8, "篮球场", "打篮球打网球的地方");
    g.setInfo(9, "足球场", "踢足球的体育场，在校外");
    g.setInfo(10, "5号学生公寓", "学生公寓");
    g.setInfo(11, "1号学生公寓", "学生公寓");
    g.setInfo(12, "3号学生公寓", "学生公寓");
    g.setPath(1, 2, 9);
    w->addEdge(1, 2);
    g.setPath(1, 3, 11);
    w->addEdge(1, 3);
    g.setPath(1, 7, 13);
    w->addEdge(1, 7);
    g.setPath(2, 3, 6);
    w->addEdge(2, 3);
    g.setPath(2, 7, 9);
    w->addEdge(2, 7);
    g.setPath(2, 10, 12);
    w->addEdge(2, 10);
    g.setPath(3, 4, 3);
    w->addEdge(3, 4);
    g.setPath(3, 6, 8);
    w->addEdge(3, 6);
    g.setPath(5, 6, 2);
    w->addEdge(5, 6);
    g.setPath(7, 9, 30);
    w->addEdge(7, 9);
    g.setPath(7, 12, 10);
    w->addEdge(7, 12);
    g.setPath(8, 12, 6);
    w->addEdge(8, 12);
    g.setPath(10, 11, 7);
    w->addEdge(10, 11);
    g.setPath(11, 12, 7);
    w->addEdge(11, 12);
}
