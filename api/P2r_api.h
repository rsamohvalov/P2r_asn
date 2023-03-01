#ifndef _P2R_API_H
#define _P2R_API_H

typedef enum 
{
    UNKNOWN = 0,
    PLANNED = 1,
    UNPLANNED = 2
} tReason;

typedef enum _ret
{
    Success = 0,
    NotEnoughMemory = 1,
    TransportInitError = 2,
    ServerIsUnreachable = 3,
    EncodingError = 4,
    Error = 5,
    ClientAlreadyInitialized = 6,
    ServerAlreadyInitialized = 7,
    ParameterError = 8,
    NoService = 9
} ret_val;

#endif









