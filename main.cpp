#include <iostream>
#include <string>
#include "workerManagerSystem.h"
using namespace std;
int main()
{
    WorkerManager Manager;
    Manager.ShowMenu();
    int userChoice = 9;
    while (true)
    {
        cout << "请输入您的选择：" << endl;
        cin >> userChoice;

        switch (userChoice)
        {
        case 1: //退出系统
            Manager.ExitManager();
            Manager.ShowMenu();
            break;
        case 2: //增加职工
            Manager.AddInfo();
            system("clr");
            Manager.ShowMenu();
            break;
        case 3: //显示职工
            Manager.ShowInfo();
            break;
        case 4: //删除职工
            Manager.DelInfo();
            system("clr");
            Manager.ShowMenu();
            break;
        case 5: //修改职工
            Manager.ModifyInf();
            system("clr");
            Manager.ShowMenu();
            break;
        case 6: //查找职工
            Manager.SeekInfo();
            break;
        case 7: //按照编号进行排序
            Manager.SortInfo();
            break;
        case 8: //清空所有文档
            Manager.ClearInfo();
            system("clr");
            Manager.ShowMenu();
            break;
        default: //退出系统
            // system("cls");
            cout << "没有此选项，请重新输入！" << endl;
            cin.clear();
            cin.ignore(); //防止输入错误造成死循环
            break;
        }
    }

    // Manager.ShowMenu();
}