#ifndef __MMA8451_H
#define __MMA8451_H

#include <sys/time.h>
#include <stdint.h>

typedef enum
{
    transient_int,
    accel_data
} accel_msg_type;

typedef struct __attribute__((__packed__))
{
    uint32_t data;
    time_t timestamp;
    accel_msg_type m_type;
} accel_msg_s;

void accel_init();
accel_msg_s read_accel();

#endif