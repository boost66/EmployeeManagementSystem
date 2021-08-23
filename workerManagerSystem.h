#pragma once //防止头文件重复
#include <string>
#define FILENAME "empFile.txt"
using namespace std;
//定义职工抽象基类,无法实例化
//*********************************************
class Worker
{
public:
    //显示个人信息
    virtual void ShowInfo() = 0; //纯虚函数
    //获取岗位名称:普通员工、经理、总裁
    virtual string GetDeptName() = 0;
    int m_Id;
    string m_Name;
    int m_DepId; //部门编号
};
//定义员工管理类
class WorkerManager
{
public:
    //记录职工人数
    int m_EmpNum;
    //判断文件是否为空
    bool m_FileIsEmpty;
    Worker **m_EmpArray;
    //确定现有职工的人数
    int GetEmpNum();
    //职工信息初始化
    void Init_Emp();
    WorkerManager();
    void saveFile(); //保存文件信息
    //展示菜单函数
    void ShowMenu();
    //添加个人信息,不用容器
    void AddInfo();
    bool ExpIsExist(int id);
    //显示职工信息
    void ShowInfo();
    void DelInfo();   //删除员工信息
    void ModifyInf(); //修改员工信息
    void SeekInfo();  //查找员工
    void SortInfo();  //按照编号进行排序
    void ClearInfo(); //清空
    void ExitManager();
    ~WorkerManager();
};

//定义普通员工类
//*********************************************
class Employee : public Worker
{
public:
    Employee(int id, string name, int depId);
    //显示个人信息
    virtual void ShowInfo();
    //获取岗位名称:普通员工、经理、总裁
    virtual string GetDeptName();
    ~Employee();
};
//定义经理员工类
//*********************************************
class Manager : public Worker
{
public:
    Manager(int id, string name, int depId);
    //显示个人信息
    virtual void ShowInfo();

    //获取岗位名称:普通员工、经理、总裁
    virtual string GetDeptName();
    ~Manager();
};
//定义总裁员工类
//*********************************************
class Boss : public Worker
{
public:
    Boss(int id, string name, int depId);
    //显示个人信息
    virtual void ShowInfo();
    //获取岗位名称:普通员工、经理、总裁
    virtual string GetDeptName();
    ~Boss();
};