#pragma once
#include <windows.h>
#include <string.h>
#include <vector>
#include <thread>
#include <chrono>
#include<iostream>
#include<ctime>

using namespace std;

void date()
{
    string weekday[7] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Staturday"};
    struct tm now;
    time_t tmp = time(0);
    localtime_s(&now, &tmp);

    cout << now.tm_hour << ":" << now.tm_min << ":" << now.tm_sec << endl;
    cout << weekday[now.tm_wday] << "-" << now.tm_mday << "-" << now.tm_mon + 1 << "-" << now.tm_year + 1900 << endl;;

}
