#include "vstringlist.h"
#include "valgorithms.h"

bool VStringList::contains(const VString &str, Vt::CaseSensitivity cs) const
{
    for(int i=0; i<size(); ++i)
    {
	if(!VString::compare(at(i), str, cs))
	    return true;
    }

    return false;
}

VStringList VStringList::filter(const VString &str, Vt::CaseSensitivity cs) const
{
    VStringList sl;
    
    for(int i=0; i<size(); ++i)
    {
	if(at(i).contains(str, cs))
	    sl << at(i);
    }

    return sl;
}

int VStringList::indexOf(const VString &value, int from) const
{
    for(int i=from; i<size(); ++i)
	if(!VString::compare(at(i), value))
	    return i;
    return -1;
}

int VStringList::lastIndexOf(const VString &value, int from) const
{
    if(from == -1) from = size() - 1;

    for(int i = from; i>-1; --i)
	if(!VString::compare(at(i), value))
	    return i;
    return -1;
}

VString VStringList::join(const VString &separator) const
{
    int l = size()-1;
    VString ret;
    // немного ускоряем работу
    ret.reserve(l * separator.size());

    for(int i=0; i<l; ++i)
    {
	ret.append(at(i));
	ret.append(separator);
    }

    if(!isEmpty())
	ret.append(at(size()-1));
    return ret;
}

VStringList &VStringList::replaceInStrings(const VString &before, const VString &after, Vt::CaseSensitivity cs)
{
    for(int i=0; i<size(); ++i)
	value(i).replace(before, after, cs);

    return *this;
}

int VStringList::removeDuplicates()
{
    int c = 0;

    /*
    for(int i=0; i<size(); ++i)
    {
	for(int j=i+1; j<size(); ++j)
	    if(!VString::compare(at(i), at(j)))
	    {
		++c;
		removeAt(j);
		--j;
	    }
    } */

    VStringList nlist;

    for(int i=0; i<size(); ++i)
    {
	if(!nlist.contains(at(i)))
	{
	    nlist << at(i);
	    ++c;
	}
    }

    int co = size() - c;

    clear();
    reserve(c);

    for(int i=0; i<nlist.size(); ++i)
	append(nlist.at(i));
    resize(nlist.size());

    return co;
}

/*
void VStringList::sort()
{
    vSort<VList<VString>::iterator, vLess<VString> >(begin(), end(), vLess<VString>());
}
*/
