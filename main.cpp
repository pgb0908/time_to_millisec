#include <iostream>
#include <chrono>
#include <ctime>
#include <unistd.h>
#include <thread>
using namespace std;

std::chrono::milliseconds::rep tmConvert_t(int YYYY, int MM, int DD, int hh, int mm, int ss)
{
    std::tm t{};

    t.tm_year = YYYY - 1900;
    t.tm_mon = MM - 1;
    t.tm_mday = DD;
    t.tm_hour = hh;
    t.tm_min = mm;
    t.tm_sec = ss;
    time_t orig = std::mktime(&t);

    // ask for the duration since the epoch
    auto dur = std::chrono::system_clock::from_time_t(orig).time_since_epoch();

    // cast to whole milliseconds
    auto dur_in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur);

    // return the tick count in milliseconds
    return dur_in_ms.count();
}

int main() {

    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
    cout <<"chrono-origin : " << tp.time_since_epoch().count() << endl;

    auto millisec_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(
                                        std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "milliseconds since epoch: " << millisec_since_epoch << endl;


    time_t now = time(nullptr);
    time_t mnow = now * 1000;

    auto lt = localtime(&now);

    unsigned long long current_millis = tmConvert_t((lt->tm_year+ 1900),(lt->tm_mon+1),
                                                    lt->tm_mday,lt->tm_hour,(lt->tm_min+1),0);

    cout << lt->tm_year + 1900 << endl;
    cout << lt->tm_mon+1 << endl;
    cout << lt->tm_hour << endl;
    cout << lt->tm_min+1 << endl;

    std::cout << current_millis << std::endl;

    return 0;
}
