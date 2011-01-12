// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*! \file RelToAbs.h
 *  \brief ��������ļ���ת���������ļ����ĺ��� RelToAbsWithPlugin, FileNameRelToAbs
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef UTILFUNC_RELTOABS_H_
#define UTILFUNC_RELTOABS_H_

#include "XComPtr.h"
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

//! �õ��������ģ������ͨ��ΪEXE�����������ز����ģ��
inline HMODULE GetMainModuleHandle()
{
    HMODULE hModule = GetModuleHandleW(L"PluginManagerX3.dll");
    typedef HMODULE (*FUNC_GET)();
    FUNC_GET fn = (FUNC_GET)GetProcAddress(hModule, "xGetMainModuleHandle");
    return fn ? (*fn)() : NULL;
}

//! ����ļ���ת���������ļ���������ڵ�ǰ����ļ�
/*!
    \ingroup _GROUP_UTILFUNC
    \param relname Ҫת�������·��
    \param isfile ���·�����ļ�������·����
    \return ת����ľ���·�������isfileΪfalse�����·��ĩβ��б��
    \see FileNameRelToAbs
*/
inline std::wstring RelToAbsWithPlugin(const wchar_t* relname, bool isfile = true)
{
    wchar_t path[MAX_PATH] = { 0 };
    
    GetModuleFileNameW(xGetModuleHandle(), path, MAX_PATH);
    PathRemoveFileSpecW(path);
    PathAppendW(path, relname);
    
    PathRemoveBackslashW(path);
    if (!isfile)
    {
        PathAddBackslashW(path);
    }
    
    return path;
}

//! ����ļ���ת���������ļ���
/*! �������ģ���ļ���ͨ��ΪEXE�����������ز����ģ�飩
    \ingroup _GROUP_UTILFUNC
    \param relname Ҫת�������·��
    \param isfile ���·�����ļ�������·����
    \return ת����ľ���·�������isfileΪfalse�����·��ĩβ��б��
    \see GetMainModuleHandle
*/
inline std::wstring FileNameRelToAbs(const wchar_t* relname, bool isfile = true)
{
    wchar_t path[MAX_PATH] = { 0 };
    
    GetModuleFileNameW(GetMainModuleHandle(), path, MAX_PATH);
    PathRemoveFileSpecW(path);
    PathAppendW(path, relname);
    
    PathRemoveBackslashW(path);
    if (!isfile)
    {
        PathAddBackslashW(path);
    }
    
    return path;
}

//! ������ʱ�ļ�ȫ��
/*! �������ģ���ļ���ͨ��ΪEXE�����������ز����ģ�飩
    \ingroup _GROUP_UTILFUNC
    \param relname Ҫת�������·�������԰�����Ŀ¼�������硰Log.txt��
    \param isfile ���·�����ļ�������·����
    \return ת����ľ���·�������isfileΪfalse�����·��ĩβ��б��
    \see GetMainModuleHandle
*/
inline std::wstring MakeTempFileName(const wchar_t* relname = L"", bool isfile = true)
{
    wchar_t path[MAX_PATH] = { 0 };
    wchar_t exename[MAX_PATH] = { 0 };
    
    GetModuleFileNameW(GetMainModuleHandle(), exename, MAX_PATH);
    PathStripPath(exename);
    PathRemoveExtension(exename);

    GetTempPathW(MAX_PATH - 1, path);
    PathAppendW(path, exename);
    if (relname && *relname)
    {
        PathAppendW(path, relname);
    }
    
    PathRemoveBackslashW(path);
    if ( !(isfile && relname && *relname) )
    {
        PathAddBackslashW(path);
    }
    
    return path;
}

//! ȷ��·��ĩβ�з�б��
/*!
    \ingroup _GROUP_UTILFUNC
    \param[in,out] wstrPath ·���ļ�ȫ��
    \return ��wstrPath��ͬ
*/
inline std::wstring EnsurePathHasSlash(std::wstring& wstrPath)
{
    if (!wstrPath.empty())
    {
        wchar_t c = wstrPath[wstrPath.size() - 1];
        if (c != '\\' && c != '/')
        {
            wstrPath += '\\';
        }
    }
    return wstrPath;
}

#endif // UTILFUNC_RELTOABS_H_