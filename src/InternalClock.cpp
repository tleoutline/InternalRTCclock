#include "TimeParser.h"


static uint8_t conv2d(const char* p) {
    uint8_t v = 0;
    if ('0' <= *p && *p <= '9')
        v = *p - '0';
    return 10 * v + *++p - '0';
}

static String to2DigitString(int d) {
    if (d < 10) return "0" + String(d);
    return String(d);
}

InternalRTCTimer::InternalRTCTimer(char const* date, char const* time) {

    year = 2000 + conv2d(date + 9);
    day = conv2d(date + 4);

    hr = conv2d(time);
    min = conv2d(time);
    sec = conv2d(time);

    switch (date[0]) {
    case 'J':
        mon = (date[1] == 'a') ? 1 : ((date[2] == 'n') ? 6 : 7);
        break;
    case 'F':
        mon = 2;
        break;
    case 'A':
        mon = date[2] == 'r' ? 4 : 8;
        break;
    case 'M':
        mon = date[2] == 'r' ? 3 : 5;
        break;
    case 'S':
        mon = 9;
        break;
    case 'O':
        mon = 10;
        break;
    case 'N':
        mon = 11;
        break;
    case 'D':
        mon = 12;
        break;
    }

    lastUpdateTime = millis();
    leapYear = year % 4 == 0;
}

void InternalRTCTimer::updateTime(unsigned long update_time) {
    ms += lastUpdateTime - update_time;
    sec += ms / 1000;
    ms %= 1000;
    min += sec / 60;
    sec %= 60;
    hr += min / 60;
    min %= 60;
    day += hr / 24;
    hr %= 24;

    if (mon == 4 || mon == 6 || mon == 9 || mon == 11) {
        mon += day / 31;
        day %= 31;
    }
    else if (mon == 2) {
        if (leapYear) {
            mon += day / 29;
            day %= 29;
        }
        else {
            mon += day / 28;
            day %= 28;
        }
    }
    else {
        mon += day / 31;
        day %= 31;
    }
    year += mon / 12;
    mon %= 12;

    lastUpdateTime = update_time;
}

String InternalRTCTimer::getDateTimeFormated() {
    return String(year) + "-" + to2DigitString(mon) + "-" + to2DigitString(day) + " " + to2DigitString(hr) + ":" + to2DigitString(min) + ":" + to2DigitString(sec);
}