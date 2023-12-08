#include "EngineMain.h"
#include "EngineCore.h"
#include <QApplication>






int EngineMain(int argc, char *argv[])
{
    QApplication app(argc, argv);
    EngineCore w;
    w.show();

    //qDebug()<<"je";

    /*
        引擎之心
    */


    //引擎启动
        //引擎预处理
    /*
    1. 设置全局对象
    2. 配置状态机
    3. 启动各系统和组件
    4. 阶段后续处理
    */

       // 设置全局对象
       // 配置状态机






        //引擎初始化

    //进入响应循环

    //引擎退出






    return app.exec();

}

