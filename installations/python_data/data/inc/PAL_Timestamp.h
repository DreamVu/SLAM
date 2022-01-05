#ifndef PAL_TIMESTAMP_H
#define PAL_TIMESTAMP_H
  

#define MILLIS_IN_SEC 1000
#define MICROS_IN_MILLI 1000
#define NANOS_IN_MICRO 1000



timeval timespec2timeval(timespec time_spec);

timeval convertToEpoch(timeval boot_time);

#endif 
