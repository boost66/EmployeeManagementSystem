#include "workerManagerSystem.h"
#include <iostream>
#include <fstream>
//*********************************************
//定义构造函数
WorkerManager::WorkerManager()
{

    //文件不存在
    ifstream ifs;
    ifs.open(FILENAME, ifstream::in);
    if (!ifs.is_open())
    { //文件未创建，并且进行初始化
        cout << "文件不存在！" << endl;
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    // //文件存在但为空
    char ch;

    ifs >> ch;
    if (ifs.eof())
    {
        cout << "文件为空！" << endl;
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    //文件存在且含有数据,获取记录的在职人数
    int num = this->GetEmpNum();
    this->m_EmpNum = num; //返回人数，并初始化职工信息
    this->m_EmpArray = new Worker *[this->m_EmpNum];
    this->Init_Emp();

    // ifs.close();
    // cout << this->m_EmpArray[0]->m_Id << "  " << this->m_EmpArray[0]->m_Name << "  " << this->m_EmpArray[0]->m_DepId << endl;
}
// 定义菜单显示函数
void WorkerManager::ShowMenu()
{
    cout << "***************************************" << endl;
    cout << "**********欢迎使用职工管理系统**********" << endl;
    cout << "**********1、退出职工管理系统***********" << endl;
    cout << "************2、增加职工信息*************" << endl;
    cout << "************3、显示职工信息*************" << endl;
    cout << "************4、删除职工信息*************" << endl;
    cout << "************5、修改职工信息*************" << endl;
    cout << "************6、查找职工信息*************" << endl;
    cout << "************7、按照编号排序*************" << endl;
    cout << "************8、清空所有文档*************" << endl;
    cout << "***************************************" << endl;
}
//保存文件函数
void WorkerManager::saveFile()
{
    ofstream file;
    file.open(FILENAME, ofstream::out); //输出的方式打开文件
    //写入信息
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        file << this->m_EmpArray[i]->m_Id << "  " << this->m_EmpArray[i]->m_Name << "  " << this->m_EmpArray[i]->m_DepId << endl;
        // cout << "名字：" << this->m_EmpArray[i]->m_Name << endl;
        // file << "你好" << endl;
    }
    file.close();
}
//确定职工数量
int WorkerManager::GetEmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ifstream::in);
    int id;
    string name;
    int depId;
    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> depId)
    {
        num++;
    }
    ifs.close();
    return num;
}
//初始化职工信息
void WorkerManager::Init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ifstream::in);
    int id;
    string name;
    int depId;
    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> depId)
    {
        Worker *worker = NULL;
        //根据不同部门id创建不同对象
        if (depId == 1)
        {
            worker = new Employee(id, name, depId);
        }
        else if (depId == 2)
        {
            worker = new Manager(id, name, depId);
        }
        else
        {
            worker = new Boss(id, name, depId);
        }
        //存放在数组
        this->m_EmpArray[num] = worker;
        num++;
    }
}
//判断员工id判断是否存在,存在则为true
bool WorkerManager::ExpIsExist(int id)
{

    for (int i = 0; i < this->m_EmpNum; i++)
    {
        if (id == this->m_EmpArray[i]->m_Id)
        {
            return true;
        }
    }
    // cout << "员工不存在！" << endl;
    return false;
}
// bool WorkerManager::SysIsExist(id){//判断在系统中是否已经存在
//     for(int i=0;i<this->m_EmpNum;i++){
//     if(id=this->m_EmpArray[i]->m_Id){
//         cout << "该员工编号已经存在，请重新输入员工编号：" << endl;
//         cin >> id;
//     }
// }
// }
//添加职工信息
void WorkerManager::AddInfo()
{

    cout << "请输入添加职工数量：" << endl;
    int addNum = 0;
    int id;
    string name;
    int depId; //部门编号
    bool IsExist = false;
    cin >> addNum;
    if (addNum > 0)
    {
        int newSize = addNum + this->m_EmpNum;     //计算新空间的大小
        Worker **newSpace = new Worker *[newSize]; //开辟新空间数组，存的的是每一个对象的指针
        //将原空间下内容拷贝到新空间
        if (this->m_EmpArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }

        //输入新的数据
        for (int i = 0; i < addNum; i++)
        {
            cout << "请输入第" << i + 1 << "个员工编号：" << endl;
            cin >> id;
            for (int j = m_EmpNum; j < this->m_EmpNum + i; j++)
            { //判断新加入的员工编号是否重复
                // cout << newSpace[i]->m_Id << endl;
                if (id == newSpace[j]->m_Id)
                {
                    IsExist = true;
                    break;
                }
                else
                {
                    IsExist = false;
                }
            }
            while (this->ExpIsExist(id) || IsExist) //判断员工编号是否已经存在
            {
                cout << "该员工编号已经存在，请重新输入员工编号：" << endl;
                cin >> id;
                for (int j = m_EmpNum; j < this->m_EmpNum + i; j++)
                { //判断新加入的员工编号是否重复
                    // cout << newSpace[i]->m_Id << endl;
                    if (id == newSpace[j]->m_Id)
                    {
                        IsExist = true;
                        break;
                    }
                    else
                    {
                        IsExist = false;
                    }
                }
            }
            cout << "请输入第" << i + 1 << "个员工姓名：" << endl;
            cin >> name;
            cout << "请输入该员工的岗位：" << endl;
            cout << "1、普通员工"
                 << "\t"
                 << "2、经理"
                 << "\t\t"
                 << "3、总裁" << endl;
            cin >> depId;
            Worker *worker = NULL; //worker是一个指向Worker对象的指针，并且是父类指针指向每一个子类对象（利用了多态）
            switch (depId)
            {
            case 1: //普通员工
                // Employee  worker(id,name,depId);
                worker = new Employee(id, name, depId); //返回的是指针
                break;
            case 2: //经理
                worker = new Manager(id, name, depId);
                break;
            case 3: //总裁
                worker = new Boss(id, name, depId);
                break;
            default:
                cout << "没有该选项" << endl;
                break;
            }
            //将创建的职工职责，保存到数组中
            newSpace[this->m_EmpNum + i] = worker;
        }
        delete[] this->m_EmpArray; //删除原来数据
        //更改新空间的指向
        this->m_EmpArray = newSpace;
        //更新新的职工人数
        this->m_EmpNum = newSize;
        //更新职工不为空标志
        this->m_FileIsEmpty = false;
        this->saveFile();
        cout << "成功添加" << addNum << "名新职工" << endl;
    }
    else
    {
        cout << "输入有误,请重新输入!" << endl;
        cin.clear();
        cin.ignore();
    }
}
//显示职工信息
void WorkerManager::ShowInfo()
{
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        this->m_EmpArray[i]->ShowInfo();
    }
}
void WorkerManager::ExitManager()
{
    cout << "欢迎下次使用!" << endl;
    system("pause");
    exit(0);
}
//删除员工信息
void WorkerManager::DelInfo()
{
    cout << "请输入要删除员工的编号：" << endl;
    int id;
    cin >> id;
    bool isExist;
    isExist = this->ExpIsExist(id);
    if (isExist)
    { //删除
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            if (id == this->m_EmpArray[i]->m_Id)
            {
                this->m_EmpArray[i] = this->m_EmpArray[i + 1];
            }
        }
        this->m_EmpNum--;
        this->saveFile();
    }
    else
    {
        cout << "删除失败，因为没有该员工信息！" << endl;
    }
}
//修改员工信息
void WorkerManager::ModifyInf()
{
    cout << "请输入要修改员工的编号：" << endl;
    int id;
    cin >> id;
    bool isExist;
    isExist = this->ExpIsExist(id);
    if (isExist)
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            if (id == this->m_EmpArray[i]->m_Id)
            {
                int newId;      //新的编号
                string newName; //新的名字
                int newDepId;   //新的部门id

                cout << "请重新输入该员工编号：" << endl;
                cin >> newId;
                while (this->ExpIsExist(newId))
                {
                    if (newId == this->m_EmpArray[i]->m_Id)
                    {
                        break;
                    }
                    cout << "该员工编号已经存在，请重新输入新的员工编号:" << endl;
                    cin >> newId;
                }
                cout << "请重新输入该员工姓名：" << endl;
                cin >> newName;
                cout << "请输入该员工的岗位：" << endl;
                cout << "1、普通员工"
                     << "\t"
                     << "2、经理"
                     << "\t\t"
                     << "3、总裁" << endl;
                cin >> newDepId;
                //更新修改的信息
                this->m_EmpArray[i]->m_Id = newId;
                this->m_EmpArray[i]->m_Name = newName;
                this->m_EmpArray[i]->m_DepId = newDepId;
                this->saveFile();
                break;
            }
        }
    }
    else
    {
        cout << "无法修改该员工信息，因为没有此员工！" << endl;
    }
}
//查找员工
void WorkerManager::SeekInfo()
{
    cout << "请输入要查找员工的编号：" << endl;
    int id;
    cin >> id;
    bool isExist;
    isExist = this->ExpIsExist(id);
    if (isExist)
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            if (id == this->m_EmpArray[i]->m_Id)
            {
                this->m_EmpArray[i]->ShowInfo();
                break;
            }
        }
    }
}
//按照员工编号排序
void WorkerManager::SortInfo()
{
    cout << "请问按照升序还是降序：" << endl;
    cout << "1、按照升序"
         << "\t2、按照降序" << endl;
    int select;
    cin >> select;
    int temId;
    string temName;
    int temDepId;
    switch (select)
    {
    case 1: //升序
        for (int i = 0; i < this->m_EmpNum - 1; i++)
        {
            for (int j = 0; j < this->m_EmpNum - 1 - i; j++)
            {
                if (this->m_EmpArray[j]->m_Id > this->m_EmpArray[j + 1]->m_Id)
                {
                    cout << m_EmpArray[j]->m_Id << endl;
                    temId = this->m_EmpArray[j]->m_Id;
                    temName = this->m_EmpArray[j]->m_Name;
                    temDepId = this->m_EmpArray[j]->m_DepId;
                    this->m_EmpArray[j]->m_Id = this->m_EmpArray[j + 1]->m_Id;
                    this->m_EmpArray[j]->m_Name = this->m_EmpArray[j + 1]->m_Name;
                    this->m_EmpArray[j]->m_DepId = this->m_EmpArray[j + 1]->m_DepId;
                    this->m_EmpArray[j + 1]->m_Id = temId;
                    this->m_EmpArray[j + 1]->m_Name = temName;
                    this->m_EmpArray[j + 1]->m_DepId = temDepId;
                    cout << m_EmpArray[j]->m_Id << endl;
                }
            }
        }
        this->saveFile();
        break;
    case 2: //降序
        for (int i = 0; i < this->m_EmpNum - 1; i++)
        {
            for (int j = 0; j < this->m_EmpNum - 1 - i; j++)
            {
                if (this->m_EmpArray[j]->m_Id < this->m_EmpArray[j + 1]->m_Id)
                {
                    temId = this->m_EmpArray[j]->m_Id;
                    temName = this->m_EmpArray[j]->m_Name;
                    temDepId = this->m_EmpArray[j]->m_DepId;
                    this->m_EmpArray[j]->m_Id = this->m_EmpArray[j + 1]->m_Id;
                    this->m_EmpArray[j]->m_Name = this->m_EmpArray[j + 1]->m_Name;
                    this->m_EmpArray[j]->m_DepId = this->m_EmpArray[j + 1]->m_DepId;
                    this->m_EmpArray[j + 1]->m_Id = temId;
                    this->m_EmpArray[j + 1]->m_Name = temName;
                    this->m_EmpArray[j + 1]->m_DepId = temDepId;
                }
            }
        }
        this->saveFile();
        break;
    default: //不排序
        break;
    }
}
//清空
void WorkerManager::ClearInfo()
{
    cout << "您确定要删除所有员工信息吗？" << endl;
    cout << "1、确定删除\t2、取消删除" << endl;
    int select;
    cin >> select;
    if (select == 1)
    { //确定清空
        delete this->m_EmpArray;
        this->m_EmpNum = 0;
        this->saveFile();
    }
}
WorkerManager::~WorkerManager()
{
}
//职工类信息
//*********************************************
Employee::Employee(int id, string name, int depId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DepId = depId; //部门编号
};
//显示个人信息
void Employee::ShowInfo()
{
    cout << "职工编号：" << this->m_Id << "\t职工姓名:" << this->m_Name << "\t\t职工岗位：" << this->GetDeptName() << "\t\t职工职责：完成经理交给的任务" << endl;
}
//获取岗位名称:普通员工、经理、总裁
string Employee::GetDeptName()
{
    return string("员工");
}
Employee::~Employee(){

};
//经理类信息
//*********************************************
Manager::Manager(int id, string name, int depId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DepId = depId; //部门编号
};
//显示个人信息
void Manager::ShowInfo()
{
    cout << "职工编号：" << this->m_Id << "\t职工姓名:" << this->m_Name << "\t\t职工岗位：" << this->GetDeptName() << "\t\t职工职责：完成老板交给的任务，并下发给员工" << endl;
}
//获取岗位名称:普通员工、经理、总裁
string Manager::GetDeptName()
{
    return string("经理");
}
Manager::~Manager(){

};
//总裁类信息
//*********************************************
Boss::Boss(int id, string name, int depId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DepId = depId; //部门编号
};
//显示个人信息
void Boss::ShowInfo()
{
    cout << "职工编号：" << this->m_Id << "\t职工姓名:" << this->m_Name << "\t\t职工岗位：" << this->GetDeptName() << "\t\t职工职责：管理公司全部任务" << endl;
}
//获取岗位名称:普通员工、经理、总裁
string Boss::GetDeptName()
{
    return string("总裁");
}
Boss::~Boss(){

};