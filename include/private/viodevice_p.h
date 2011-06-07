#ifndef VIODEVICE_P_H
#define VIODEVICE_P_H

#include "vbytearray.h"
#include "viodevice.h"

class VIODevicePrivate
{
public:
    VIODevicePrivate(VIODevice *dev);
    virtual ~VIODevicePrivate();

    VByteArray errorString;

    VIODevice::OpenMode openMode;

    vint64 pos;

    VIODevice *v_ptr;
};

#endif
