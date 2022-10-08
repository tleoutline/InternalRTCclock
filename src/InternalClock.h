#ifndef TIME_PARSER
#define TIME_PARSER

#include <Arduino.h>
#include <Time.h>

class InternalRTCTimer {
public:
    InternalRTCTimer(char const* date, char const* time);
    void updateTime(unsigned long updateTime);
    String getDateTimeFormated();
    uint8_t day, mon, hr, min, sec;
    uint16_t year;


private:
    unsigned long ms = 0;
    unsigned long lastUpdateTime;
    bool leapYear;

};

time_t cvt_date(char const* date);


#endif //TIME_PARSER