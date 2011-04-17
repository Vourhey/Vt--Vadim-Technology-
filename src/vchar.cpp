#include "vchar.h"

#include "private/vunicodetables_p.h"

#include "vunicodetables.cpp"

#define FLAG(x) (1 << (x))

VChar::VChar(char ch)
{
    ucs = uchar(ch);
}

VChar::VChar(uchar ch)
{
    ucs = ch;
}

bool VChar::isPrint() const
{
    const int test = FLAG(Other_Control) |
                     FLAG(Other_NotAssigned);
    return !(FLAG(qGetProp(ucs)->category) & test);
}

bool VChar::isSpace() const
{
    if(ucs >= 9 && ucs <=13)
        return true;
    const int test = FLAG(Separator_Space) |
                     FLAG(Separator_Line) |
                     FLAG(Separator_Paragraph);
    return FLAG(qGetProp(ucs)->category) & test;
}

bool VChar::isMark() const
{
    const int test = FLAG(Mark_NonSpacing) |
                     FLAG(Mark_SpacingCombining) |
                     FLAG(Mark_Enclosing);
    return FLAG(qGetProp(ucs)->category) & test;
}

bool VChar::isPunct() const
{
    const int test = FLAG(Punctuation_Connector) |
                     FLAG(Punctuation_Dash) |
                     FLAG(Punctuation_Open) |
                     FLAG(Punctuation_Close) |
                     FLAG(Punctuation_InitialQuote) |
                     FLAG(Punctuation_FinalQuote) |
                     FLAG(Punctuation_Other);
    return FLAG(qGetProp(ucs)->category) & test;
}

bool VChar::isLetter() const
{
    const int test = FLAG(Letter_Uppercase) |
                     FLAG(Letter_Lowercase) |
                     FLAG(Letter_Titlecase) |
                     FLAG(Letter_Modifier) |
                     FLAG(Letter_Other);
    return FLAG(qGetProp(ucs)->category) & test;
}

bool VChar::isNumber() const
{
    const int test = FLAG(Number_DecimalDigit) |
                     FLAG(Number_Letter) |
                     FLAG(Number_Other);
    return FLAG(qGetProp(ucs)->category) & test;
}

bool VChar::isLetterOrNumber() const
{
    const int test = FLAG(Letter_Uppercase) |
                     FLAG(Letter_Lowercase) |
                     FLAG(Letter_Titlecase) |
                     FLAG(Letter_Modifier) |
                     FLAG(Letter_Other) |
                     FLAG(Number_DecimalDigit) |
                     FLAG(Number_Letter) |
                     FLAG(Number_Other);
    return FLAG(qGetProp(ucs)->category) & test;
}

/*! Возвращает \c true, если символ - числовой */ 
bool VChar::isDigit() const
{
    return (qGetProp(ucs)->category == Number_DecimalDigit);
}


bool VChar::isSymbol() const
{
    const int test = FLAG(Symbol_Math) |
                     FLAG(Symbol_Currency) |
                     FLAG(Symbol_Modifier) |
                     FLAG(Symbol_Other);
    return FLAG(qGetProp(ucs)->category) & test;
}

int VChar::digitValue() const
{
    return qGetProp(ucs)->digitValue;
}

int VChar::digitValue(ushort ucs2)
{
    return qGetProp(ucs2)->digitValue;
}

int VChar::digitValue(uint ucs4)
{
    if (ucs4 > UNICODE_LAST_CODEPOINT)
        return 0;
    return qGetProp(ucs4)->digitValue;
}

VChar::Category VChar::category() const
{
    return (VChar::Category) qGetProp(ucs)->category;
}

VChar::Category VChar::category(uint ucs4)
{
    if (ucs4 > UNICODE_LAST_CODEPOINT)
        return VChar::NoCategory;
    return (VChar::Category) qGetProp(ucs4)->category;
}

VChar::Category VChar::category(ushort ucs2)
{
    return (VChar::Category) qGetProp(ucs2)->category;
}

VChar::Direction VChar::direction() const
{
    return (VChar::Direction) qGetProp(ucs)->direction;
}

VChar::Direction VChar::direction(uint ucs4)
{
    if (ucs4 > UNICODE_LAST_CODEPOINT)
        return VChar::DirL;
    return (VChar::Direction) qGetProp(ucs4)->direction;
}

VChar::Direction VChar::direction(ushort ucs2)
{
    return (VChar::Direction) qGetProp(ucs2)->direction;
}

VChar::Joining VChar::joining() const
{
    return (VChar::Joining) qGetProp(ucs)->joining;
}

VChar::Joining VChar::joining(uint ucs4)
{
    if (ucs4 > UNICODE_LAST_CODEPOINT)
        return VChar::OtherJoining;
    return (VChar::Joining) qGetProp(ucs4)->joining;
}

VChar::Joining VChar::joining(ushort ucs2)
{
    return (VChar::Joining) qGetProp(ucs2)->joining;
}


bool VChar::hasMirrored() const
{
    return qGetProp(ucs)->mirrorDiff != 0;
}

VChar VChar::mirroredChar() const
{
    return ucs + qGetProp(ucs)->mirrorDiff;
}

uint VChar::mirroredChar(uint ucs4)
{
    if (ucs4 > UNICODE_LAST_CODEPOINT)
        return ucs4;
    return ucs4 + qGetProp(ucs4)->mirrorDiff;
}

ushort VChar::mirroredChar(ushort ucs2)
{
    return ucs2 + qGetProp(ucs2)->mirrorDiff;
}


enum {
    Hangul_SBase = 0xac00,
    Hangul_LBase = 0x1100,
    Hangul_VBase = 0x1161,
    Hangul_TBase = 0x11a7,
    Hangul_SCount = 11172,
    Hangul_LCount = 19,
    Hangul_VCount = 21,
    Hangul_TCount = 28,
    Hangul_NCount = 21*28
};

/*
// buffer has to have a length of 3. It's needed for Hangul decomposition
static const unsigned short *  decompositionHelper
    (uint ucs4, int *length, int *tag, unsigned short *buffer)
{
    *length = 0;
    if (ucs4 > UNICODE_LAST_CODEPOINT)
        return 0;
    if (ucs4 >= Hangul_SBase && ucs4 < Hangul_SBase + Hangul_SCount) {
        int SIndex = ucs4 - Hangul_SBase;
        buffer[0] = Hangul_LBase + SIndex / Hangul_NCount; // L
        buffer[1] = Hangul_VBase + (SIndex % Hangul_NCount) / Hangul_TCount; // V
        buffer[2] = Hangul_TBase + SIndex % Hangul_TCount; // T
        *length = buffer[2] == Hangul_TBase ? 2 : 3;
        *tag = VChar::Canonical;
        return buffer;
    }

    const unsigned short index = GET_DECOMPOSITION_INDEX(ucs4);
    if (index == 0xffff)
        return 0;
    const unsigned short *decomposition = uc_decomposition_map+index;
    *tag = (*decomposition) & 0xff;
    *length = (*decomposition) >> 8;
    return decomposition+1;
} */

/*!
    Decomposes a character into its parts. Returns an empty string if
    no decomposition exists.
*/ /*
QString VChar::decomposition() const
{
    return decomposition(ucs);
} */

/*!
    \overload
    Decomposes the UCS-4-encoded character specified by \a ucs4 into its
    constituent parts. Returns an empty string if no decomposition exists.
*/ /*
QString VChar::decomposition(uint ucs4)
{
    unsigned short buffer[3];
    int length;
    int tag;
    const unsigned short *d = decompositionHelper(ucs4, &length, &tag, buffer);
    return QString::fromUtf16(d, length);
}
*/
VChar::Decomposition VChar::decompositionTag() const
{
    return decompositionTag(ucs);
}

VChar::Decomposition VChar::decompositionTag(uint ucs4)
{
    if (ucs4 > UNICODE_LAST_CODEPOINT)
        return VChar::NoDecomposition;
    const unsigned short index = GET_DECOMPOSITION_INDEX(ucs4);
    if (index == 0xffff)
        return VChar::NoDecomposition;
    return (VChar::Decomposition)(uc_decomposition_map[index] & 0xff);
}

unsigned char VChar::combiningClass() const
{
    return (unsigned char) qGetProp(ucs)->combiningClass;
}

unsigned char VChar::combiningClass(uint ucs4)
{
    if (ucs4 > UNICODE_LAST_CODEPOINT)
        return 0;
    return (unsigned char) qGetProp(ucs4)->combiningClass;
}

unsigned char VChar::combiningClass(ushort ucs2)
{
    return (unsigned char) qGetProp(ucs2)->combiningClass;
}

VChar::UnicodeVersion VChar::unicodeVersion() const
{
    return (VChar::UnicodeVersion) qGetProp(ucs)->unicodeVersion;
}

VChar::UnicodeVersion VChar::unicodeVersion(uint ucs4)
{
    if (ucs4 > UNICODE_LAST_CODEPOINT)
        return VChar::Unicode_Unassigned;
    return (VChar::UnicodeVersion) qGetProp(ucs4)->unicodeVersion;
}

VChar::UnicodeVersion VChar::unicodeVersion(ushort ucs2)
{
    return (VChar::UnicodeVersion) qGetProp(ucs2)->unicodeVersion;
}

VChar VChar::toLower() const
{
    const VUnicodeTables::Properties *p = qGetProp(ucs);
    if (!p->lowerCaseSpecial)
        return ucs + p->lowerCaseDiff;
    return ucs;
}

uint VChar::toLower(uint ucs4)
{
    if (ucs4 > UNICODE_LAST_CODEPOINT)
        return ucs4;
    const VUnicodeTables::Properties *p = qGetProp(ucs4);
    if (!p->lowerCaseSpecial)
        return ucs4 + p->lowerCaseDiff;
    return ucs4;
}

ushort VChar::toLower(ushort ucs2)
{
    const VUnicodeTables::Properties *p = qGetProp(ucs2);
    if (!p->lowerCaseSpecial)
        return ucs2 + p->lowerCaseDiff;
    return ucs2;
}

VChar VChar::toUpper() const
{
    const VUnicodeTables::Properties *p = qGetProp(ucs);
    if (!p->upperCaseSpecial)
        return ucs + p->upperCaseDiff;
    return ucs;
}

uint VChar::toUpper(uint ucs4)
{
    if (ucs4 > UNICODE_LAST_CODEPOINT)
        return ucs4;
    const VUnicodeTables::Properties *p = qGetProp(ucs4);
    if (!p->upperCaseSpecial)
        return ucs4 + p->upperCaseDiff;
    return ucs4;
}

ushort VChar::toUpper(ushort ucs2)
{
    const VUnicodeTables::Properties *p = qGetProp(ucs2);
    if (!p->upperCaseSpecial)
        return ucs2 + p->upperCaseDiff;
    return ucs2;
}

VChar VChar::toTitleCase() const
{
    const VUnicodeTables::Properties *p = qGetProp(ucs);
    if (!p->titleCaseSpecial)
        return ucs + p->titleCaseDiff;
    return ucs;
}

uint VChar::toTitleCase(uint ucs4)
{
    if (ucs4 > UNICODE_LAST_CODEPOINT)
        return ucs4;
    const VUnicodeTables::Properties *p = qGetProp(ucs4);
    if (!p->titleCaseSpecial)
        return ucs4 + p->titleCaseDiff;
    return ucs4;
}

ushort VChar::toTitleCase(ushort ucs2)
{
    const VUnicodeTables::Properties *p = qGetProp(ucs2);
    if (!p->titleCaseSpecial)
        return ucs2 + p->titleCaseDiff;
    return ucs2;
}


static inline uint foldCase(const ushort *ch, const ushort *start)
{
    uint c = *ch;
    if (VChar(c).isLowSurrogate() && ch > start && VChar(*(ch - 1)).isHighSurrogate())
        c = VChar::surrogateToUcs4(*(ch - 1), c);
    return *ch + qGetProp(c)->caseFoldDiff;
}

static inline uint foldCase(uint ch, uint &last)
{
    uint c = ch;
    if (VChar(c).isLowSurrogate() && VChar(last).isHighSurrogate())
        c = VChar::surrogateToUcs4(last, c);
    last = ch;
    return ch + qGetProp(c)->caseFoldDiff;
}

static inline ushort foldCase(ushort ch)
{
    return ch + qGetProp(ch)->caseFoldDiff;
}

VChar VChar::toCaseFolded() const
{
    return ucs + qGetProp(ucs)->caseFoldDiff;
}

uint VChar::toCaseFolded(uint ucs4)
{
    if (ucs4 > UNICODE_LAST_CODEPOINT)
        return ucs4;
    return ucs4 + qGetProp(ucs4)->caseFoldDiff;
}

ushort VChar::toCaseFolded(ushort ucs2)
{
    return ucs2 + qGetProp(ucs2)->caseFoldDiff;
}


char VChar::toAscii() const
{
    return ucs > 0xff ? 0 : char(ucs);
}

VChar VChar::fromAscii(char c)
{
    return VChar(ushort((uchar)c));
}


/*****************************************************************************
  Documentation of VChar related functions
 *****************************************************************************/

// ---------------------------------------------------------------------------

/*
static void decomposeHelper(QString *str, bool canonical, VChar::UnicodeVersion version, int from)
{
    unsigned short buffer[3];

    QString &s = *str;

    const unsigned short *utf16 = reinterpret_cast<unsigned short *>(s.data());
    const unsigned short *uc = utf16 + s.length();
    while (uc != utf16 + from) {
        uint ucs4 = *(--uc);
        if (VChar(ucs4).isLowSurrogate() && uc != utf16) {
            ushort high = *(uc - 1);
            if (VChar(high).isHighSurrogate()) {
                --uc;
                ucs4 = VChar::surrogateToUcs4(high, ucs4);
            }
        }
        if (VChar::unicodeVersion(ucs4) > version)
            continue;
        int length;
        int tag;
        const unsigned short *d = decompositionHelper(ucs4, &length, &tag, buffer);
        if (!d || (canonical && tag != VChar::Canonical))
            continue;

        int pos = uc - utf16;
        s.replace(pos, VChar::requiresSurrogates(ucs4) ? 2 : 1, reinterpret_cast<const VChar *>(d), length);
        // since the insert invalidates the pointers and we do decomposition recursive
        utf16 = reinterpret_cast<unsigned short *>(s.data());
        uc = utf16 + pos + length;
    }
} */

/*
static ushort ligatureHelper(ushort u1, ushort u2)
{
    // hangul L-V pair
    int LIndex = u1 - Hangul_LBase;
    if (0 <= LIndex && LIndex < Hangul_LCount) {
        int VIndex = u2 - Hangul_VBase;
        if (0 <= VIndex && VIndex < Hangul_VCount)
            return Hangul_SBase + (LIndex * Hangul_VCount + VIndex) * Hangul_TCount;
    }

    // hangul LV-T pair
    int SIndex = u1 - Hangul_SBase;
    if (0 <= SIndex && SIndex < Hangul_SCount && (SIndex % Hangul_TCount) == 0) {
        int TIndex = u2 - Hangul_TBase;
        if (0 <= TIndex && TIndex <= Hangul_TCount)
            return u1 + TIndex;
    }

    const unsigned short index = GET_LIGATURE_INDEX(u2);
    if (index == 0xffff)
        return 0;
    const unsigned short *ligatures = uc_ligature_map+index;
    ushort length = *ligatures;
    ++ligatures;
    // ### use bsearch
    for (uint i = 0; i < length; ++i)
        if (ligatures[2*i] == u1)
            return ligatures[2*i+1];
    return 0;
} */
/*
static void composeHelper(QString *str, int from)
{
    QString &s = *str;

    if (s.length() - from < 2)
        return;

    // the loop can partly ignore high Unicode as all ligatures are in the BMP
    int starter = 0;
    int lastCombining = 0;
    int pos = from;
    while (pos < s.length()) {
        uint uc = s.at(pos).unicode();
        if (VChar(uc).isHighSurrogate() && pos < s.length()-1) {
            ushort low = s.at(pos+1).unicode();
            if (VChar(low).isLowSurrogate()) {
                uc = VChar::surrogateToUcs4(uc, low);
                ++pos;
            }
        }
        int combining = VChar::combiningClass(uc);
        if (starter == pos - 1 || combining > lastCombining) {
            // allowed to form ligature with S
            VChar ligature = ligatureHelper(s.at(starter).unicode(), uc);
            if (ligature.unicode()) {
                s[starter] = ligature;
                s.remove(pos, 1);
                continue;
            }
        }
        if (!combining)
            starter = pos;
        lastCombining = combining;
        ++pos;
    }
}


static void canonicalOrderHelper(QString *str, VChar::UnicodeVersion version, int from)
{
    QString &s = *str;
    const int l = s.length()-1;
    int pos = from;
    while (pos < l) {
        int p2 = pos+1;
        uint u1 = s.at(pos).unicode();
        if (VChar(u1).isHighSurrogate()) {
            ushort low = s.at(p2).unicode();
            if (VChar(low).isLowSurrogate()) {
                u1 = VChar::surrogateToUcs4(u1, low);
                if (p2 >= l)
                    break;
                ++p2;
            }
        }
        uint u2 = s.at(p2).unicode();
        if (VChar(u2).isHighSurrogate() && p2 < l) {
            ushort low = s.at(p2+1).unicode();
            if (VChar(low).isLowSurrogate()) {
                u2 = VChar::surrogateToUcs4(u2, low);
                ++p2;
            }
        }

        ushort c2 = 0;
        {
            const VUnicodeTables::Properties *p = qGetProp(u2);
            if ((VChar::UnicodeVersion)p->unicodeVersion <= version)
                c2 = p->combiningClass;
        }
        if (c2 == 0) {
            pos = p2+1;
            continue;
        }

        ushort c1 = 0;
        {
            const VUnicodeTables::Properties *p = qGetProp(u1);
            if ((VChar::UnicodeVersion)p->unicodeVersion <= version)
                c1 = p->combiningClass;
        }

        if (c1 > c2) {
            VChar *uc = s.data();
            int p = pos;
            // exchange characters
            if (!VChar::requiresSurrogates(u2)) {
                uc[p++] = u2;
            } else {
                uc[p++] = VChar::highSurrogate(u2);
                uc[p++] = VChar::lowSurrogate(u2);
            }
            if (!VChar::requiresSurrogates(u1)) {
                uc[p++] = u1;
            } else {
                uc[p++] = VChar::highSurrogate(u1);
                uc[p++] = VChar::lowSurrogate(u1);
            }
            if (pos > 0)
                --pos;
            if (pos > 0 && s.at(pos).isLowSurrogate())
                --pos;
        } else {
            ++pos;
            if (VChar::requiresSurrogates(u1))
                ++pos;
        }
    }
} */

int  VUnicodeTables::script(unsigned int uc)
{
    if (uc > 0xffff)
        return Common;
    int script = uc_scripts[uc >> 7];
    if (script < ScriptSentinel)
        return script;
    script = (((script - ScriptSentinel) * UnicodeBlockSize) + UnicodeBlockCount);
    script = uc_scripts[script + (uc & 0x7f)];
    return script;
}

 VUnicodeTables::LineBreakClass  VUnicodeTables::lineBreakClass(uint ucs4)
{
    return (VUnicodeTables::LineBreakClass) qGetProp(ucs4)->line_break_class;
}

