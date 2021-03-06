//! \file ChainObserver.h
//! \brief 定义职责链观察者类 ChainObserver

#ifndef EXAMPLE_CHAIN_OBSERVER_H_
#define EXAMPLE_CHAIN_OBSERVER_H_

#include <ChangeObserver/Cx_ChangeObserver.h>

//! 作为例子的职责链观察者类
/*! 本例子用于让多个派生类都能处理同一个调用
    \note 建议派生类从本类私有继承
    \ingroup _GROUP_CHANGE_OBSERVER_
*/
class ChainObserver : public Cx_ChangeObserver
{
public:
    //! ChainObserver 观察者的通知数据类
    class Data : public ChangeNotifyData
    {
    public:
        Data(int* _sum) : ChangeNotifyData("ChainObserver"), sum(_sum)
        {
        }

        int*    sum;
        NOCOPY_CONSTRUCTOR(Data);
    };

protected:
    ChainObserver() : Cx_ChangeObserver("ChainObserver")
    {
    }

    //! 让派生类响应职责链通知
    virtual void OnChain(int& sum)
    {
        sum;
    }

private:
    void DoUpdate(ChangeNotifyData* data)
    {
        Data* mydata = static_cast<Data*>(data);
        ASSERT(mydata && mydata->sum);
        OnChain(*(mydata->sum));
    }
    NOCOPY_CONSTRUCTOR(ChainObserver);
};

#endif // EXAMPLE_CHAIN_OBSERVER_H_