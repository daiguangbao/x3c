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

#ifndef _X3_CONFIGXML_CONFIGXML_H
#define _X3_CONFIGXML_CONFIGXML_H

#include <Ix_ConfigData.h>
#include <Ix_ConfigXml.h>
#include <Ix_ConfigTransaction.h>

struct ConfigXmlImpl;

class Cx_ConfigXml
    : public Ix_ConfigData
    , public Ix_ConfigXml
    , public Ix_ConfigTransaction
{
protected:
    Cx_ConfigXml();
    virtual ~Cx_ConfigXml();

protected:
    // From Ix_ConfigXml
    //
    virtual Ix_ConfigData* GetData();
    virtual std::wstring GetFileName() const;
    virtual void SetFileName(const wchar_t* filename);
    virtual std::wstring GetRootName() const;
    virtual void SetRootName(const wchar_t* rootName = L"root", 
        const wchar_t* encoding = L"UTF-8", 
        const wchar_t* nmspace = L"");
    virtual void SetSchemaLocation(const wchar_t* location);
    virtual bool Reload();
    virtual bool Save(const wchar_t* filename = L"") const;
    virtual bool GetXmlContent(std::wstring& content) const;
    virtual bool SetXmlContent(const std::wstring& content);
    virtual bool GetXmlContent(std::wstring& content, Ix_ConfigSection* node) const;
    virtual IFileCryptHandler* SetCryptHandler(IFileCryptHandler* handler);

    // From Ix_ConfigTransaction
    //
    virtual void BeginTransaction();
    virtual bool EndTransaction();
    virtual ULONG GetModifiedCount();

    // From Ix_ConfigData
    //
    virtual ConfigIOSection GetSection(
        const wchar_t* name, bool autoCreate = true);
    virtual ConfigIOSection GetSection(
        Ix_ConfigSection* parent, const wchar_t* name, 
        const wchar_t* attrName, ULONG attrValue, 
        bool autoCreate = true);
    virtual ConfigIOSection GetSection(
        Ix_ConfigSection* parent, const wchar_t* name, 
        const wchar_t* attrName, const wchar_t* attrValue, 
        bool autoCreate = true);
    virtual ConfigIOSection GetSection(
        Ix_ConfigSection* parent, const wchar_t* name, 
        const wchar_t* attrName, const wchar_t* attrValue, 
        const wchar_t* attrName2, const wchar_t* attrValue2, 
        bool autoCreate = true);
    virtual ConfigIOSection GetSection(
        Ix_ConfigSection* parent, const wchar_t* name, 
        const wchar_t* attrName, ULONG attrValue, 
        const wchar_t* attrName2, ULONG attrValue2, 
        bool autoCreate = true);
    virtual long GetSectionCount(
        Ix_ConfigSection* parent, const wchar_t* name);
    virtual ConfigIOSection GetSectionByIndex(
        Ix_ConfigSection* parent, const wchar_t* name, long index);
    virtual ConfigIOSection AddSection(
        Ix_ConfigSection* parent, const wchar_t* name);
    virtual bool RemoveSection(Ix_ConfigSection* sec);
    virtual long RemoveChildren(Ix_ConfigSection* parent, const wchar_t* name, 
        const wchar_t* attrName = L"", const wchar_t* attrValue = L"");
    virtual long RemoveChildren(Ix_ConfigSection* parent, const wchar_t* name, 
        const wchar_t* attrName, ULONG attrValue);
    virtual ConfigIOSection GetParentSection(Ix_ConfigSection* sec);

private:
    ConfigXmlImpl*  m_pImpl;
};

#endif // _X3_CONFIGXML_CONFIGXML_H