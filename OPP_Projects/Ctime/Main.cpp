#include <iostream>

enum Status { SUCCESS, ERROR, WARNING };

struct Time {
    int hours, minutes, seconds;
};

Status input(Time* time) {
    Status state = SUCCESS;
    char colon;
    std::cin >> time->hours >> colon
        >> time->minutes >> colon
        >> time->seconds;
    return state;
}

Status check(const Time* time) {
    if (time->hours > 24 || time->hours < 0 ||
        time->minutes > 60 || time->seconds > 60 ||
        time->minutes < 0 || time->seconds < 0)
    {
        return ERROR;
    }
    else return SUCCESS;
};

Status convert(Time* time) {
    int countS = 0, countT = 0;

    check(time);

    while (time->seconds > 60) {
        time->seconds -= 60;
        countS++;
    }
    time->minutes += countS;

    while (time->minutes > 60) {
        time->minutes -= 60;
        countT++;
    }

    if (time->hours + countT > 24) { return WARNING; }
    else { time->hours += countT; return SUCCESS; }
}

Status add_hours(Time* time, int hours) {
    if (check(time) == SUCCESS) {
        time->hours += hours;
        return convert(time);
    }
    return ERROR;
}
Status add_minutes(Time* time, int minutes) {
    if (check(time) == SUCCESS) {
        time->minutes += minutes;
        return convert(time);
    }
    return ERROR;
}
Status add_seconds(Time* time, int seconds) {
    if (check(time) == SUCCESS) {
        time->seconds += seconds;
        return convert(time);
    }
    return ERROR;
}

int compare(const Time* time1, const Time* time2) {
    int second1 = (time1->hours * 3600) + (time1->minutes * 60) + time1->seconds;
    int second2 = (time2->hours * 3600) + (time2->minutes * 60) + time2->seconds;

    if (second1 < second2) return 2;
    if (second1 > second2) return 1;
    if (second1 == second2) return 0;

}

Status assign(Time* time1, Time* time2) {
    Status state = SUCCESS;
    if (time2 == nullptr)
        state = ERROR;
    else {
        time1->hours = time2->hours;
        time1->minutes = time2->minutes;
        time1->seconds = time2->seconds;
    }
    return state;
}

Status output(const Time* time) {
    Status state = SUCCESS;
    if (time == nullptr) {
        state = ERROR;
        return state;
    }
    std::cout << time->hours << ":"
        << time->minutes << ":"
        << time->seconds << std::endl;
    return state;
}

int main() { return 0; }