#ifndef VSTRINGLIST_H
#define VSTRINGLIST_H

#include "vlist.h"
#include "vstring.h"

class VStringList : public VList<VString>
{
public:
    inline VStringList() {}
    inline VStringList(const VString &str) { append(str); }
    inline VStringList(const VStringList &other) : VList<VString>(other) {}
    inline VStringList(const VList<VString> &other) : VList<VString>(other) {}

    bool contains(const VString &str, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;

    VStringList filter(const VString &str, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;

    int indexOf(const VString &value, int from = 0) const;
    int lastIndexOf(const VString &value, int from = -1) const;
    VStringList &replaceInStrings(const VString &before, const VString &after, Vt::CaseSensitivity cs = Vt::CaseSensitive);

    VString join(const VString &separator) const;
    int removeDuplicates();

    // operators
    inline VStringList &operator<<(const VString &str) { append(str); return *this; }
    inline VStringList &operator<<(const VStringList &other) { append(other); return *this; }
    VStringList operator+(const VStringList &other) const { return VList<VString>::operator+(other); }
};

typedef VListIterator<VString> VStringListIterator;
typedef VMutableListIterator<VString> VMutableStringListIterator;

#endif
