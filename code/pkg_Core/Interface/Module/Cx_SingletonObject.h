/*! \file Cx_SingletonObject.h
 *  \brief Define single instance implement template class: Cx_SingletonObject<cls>
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.19
 */
#ifndef X3_CX_SINGLETONOBJECT_H_
#define X3_CX_SINGLETONOBJECT_H_

#include "Ix_Object.h"
#include "XModuleItem.h"
#include <typeinfo>

HMODULE x3GetModuleHandle();

/*! \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief Single instance implement template class used by XDEFINE_CLASSMAP_ENTRY_Singleton.
 *  \brief The template parameter is a class which implement a interface.
 *  \internal
 *  \see   Cx_Object, XDEFINE_CLASSMAP_ENTRY_Singleton
 */
template <class ClsType>
class Cx_SingletonObject
    : public ClsType
    , public Ix_Object
    , public Cx_ModuleItem
{
protected:
    Cx_SingletonObject(bool bRef = true) : m_refcount(bRef ? 1 : 0)
    {
    }

    virtual ~Cx_SingletonObject()
    {
        if (Instance() == this)
        {
            Instance() = NULL;
        }
    }

protected:
    virtual void AddRef(HMODULE fromdll)
    {
        if (fromdll != x3GetModuleHandle())
        {
            InterlockedIncrement(&RefCountByOthers());
        }
        InterlockedIncrement(&m_refcount);
    }

    virtual void Release(HMODULE fromdll)
    {
        if (fromdll != x3GetModuleHandle())
        {
            InterlockedDecrement(&RefCountByOthers());
        }
        InterlockedDecrement(&m_refcount);
    }

    virtual const char* GetClassName() const
    {
        return typeid(*this).name();
    }

public:
    static Ix_Object* CreateObject(HMODULE fromdll)
    {
        if (NULL == Instance())
        {
            Cx_SingletonObject<ClsType>* p = new Cx_SingletonObject<ClsType>(false);

            if (1 == InterlockedIncrement(&Locker()))
            {
                Instance() = p;
                p->AddRef(fromdll);
                p->AddModuleItem();
            }
            else
            {
                delete p;   // has created by another thread
            }
            InterlockedDecrement(&Locker());
        }

        return Instance();
    }

    static long GetObjectCount()
    {
        return (Instance() && Instance()->m_refcount > 0) ? 1 : 0;
    }

    static long GetRefCountByOthers()
    {
        return RefCountByOthers();
    }

private:
    Cx_SingletonObject(const Cx_SingletonObject&);
    void operator=(const Cx_SingletonObject&);

    long        m_refcount;

    static Cx_SingletonObject<ClsType>*& Instance()
    {
        static Cx_SingletonObject<ClsType>* s_obj = NULL;
        return s_obj;
    }

    static long& RefCountByOthers()
    {
        static long s_refcount = 0;
        return s_refcount;
    }

    static long& Locker()
    {
        static long s_locker = 0;
        return s_locker;
    }
};

#endif // X3_CX_SINGLETONOBJECT_H_
