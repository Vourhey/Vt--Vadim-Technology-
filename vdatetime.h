#ifndef VTIME_H
#define VTIME_H

class VTime
{
public:
    VTime();
    VTime(int h, int m, int s = 0, int ms = 0);

    VTime addMSecs(int ms) const;
    VTime addSecs(int s) const;

    int hour() const;
    int minute() const;
    int msec() const;
    int second() const;

    bool isNull() const;
    bool isValid() const;

    static bool isValid(int h, int m, int s, int ms=0);
    static VTime currentTime();

    bool setHMS(int h, int m, int s, int ms = 0);
    void start();
    int restart();

    int elapsed() const;
    int msecsTo(const VTime &t) const;
    int secsTo(const VTime &t) const;

    // operators
    bool operator!=(const VTime &t) const
	{ return t.dms != dms; }
    bool operator<(const VTime &t) const
	{ return t.dms < dms; }
    bool operator<=(const VTime &t) const
	{ return t.dms <= dms; }
    bool operator==(const VTime &t) const
	{ return t.dms == dms; }
    bool operator>(const VTime &t) const
	{ return t.dms > dms; }
    bool operator>=(const VTime &t) const
	{ return t.dms >= dms; }

private:
    int dms;
};

#endif
