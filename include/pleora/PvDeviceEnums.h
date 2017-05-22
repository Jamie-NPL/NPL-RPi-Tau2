// *****************************************************************************
//
//     Copyright (c) 2013, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************

#ifndef __PV_DEVICE_ENUMS_H__
#define __PV_DEVICE_ENUMS_H__


typedef enum
{
    PvAccessUnknown = 0,
    PvAccessOpen,
    PvAccessControl,
    PvAccessExclusive,
    PvAccessReadOnly,

} PvAccessType;


typedef enum
{
    PvActionAckStatusOK = 0,
    PvActionAckStatusLate = 1,
    PvActionAckStatusOverflow = 2,
    PvActionAckStatusNoRefTime = 3,

} PvActionAckStatusEnum;


#endif // __PV_DEVICE_ENUMS_H__
