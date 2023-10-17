#pragma once
#include <time.h>
#include <Arduino.h>

#define TIME_FORMAT_DEFAULT "%a %b %d %H:%M:%S %Y"
#define TIME_FORMAT_ISO8601_FULL "%Y-%m-%dT%H:%M:%S%z"

class MyTime {
private:

public:
    MyTime() {
        configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    }

    int32_t now() {
        return ::time(nullptr);
    }

    int32_t local() {
        time_t rawTime = now();
        struct tm *timeInfo = localtime(&rawTime);
        return mktime(timeInfo);
    }

    void zone(float hoursOffset) {
        long secondsOffset = hoursOffset * 3600;
        setenv("TZ", createTzFormat(secondsOffset).c_str(), 1);
        tzset();
    }

    void setTime(time_t timeVal) {
        struct timeval tv;
        tv.tv_sec = timeVal;
        tv.tv_usec = 0;
        settimeofday(&tv, nullptr);
    }

    String timeStr() {
        return format(TIME_FORMAT_DEFAULT);
    }

    String format(time_t timeVal, const char *strFormat) {
        char buffer[100];
        strftime(buffer, sizeof(buffer), strFormat, localtime(&timeVal));
        return String(buffer);
    }

    String format(const char *strFormat) {
        return format(now(), strFormat);
    }

    String format(time_t timeVal) {
        return format(timeVal, TIME_FORMAT_DEFAULT);
    }

    String format() {
        return format(now(), TIME_FORMAT_DEFAULT);
    }

private:
    String createTzFormat(long seconds) {
        int absolute = abs(seconds);
        int hours = absolute / 3600;
        int minutes = (absolute % 3600) / 60;
        char tzFormat[10];
        snprintf(tzFormat, sizeof(tzFormat), "GMT%c%02d%02d", (seconds < 0 ? '-' : '+'), hours, minutes);
        return String(tzFormat);
    }
};