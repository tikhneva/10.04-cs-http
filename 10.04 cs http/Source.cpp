#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#pragma comment(lib, "urlmon.lib")
using namespace std;

void findTemperature(const string& srcURL, const char* city)
{
    const char* destFile = "weather.txt";

    // Clear the contents of the file
    ofstream clearFile(destFile);
    clearFile.close();

    if (S_OK != URLDownloadToFileA(NULL, srcURL.c_str(), destFile, 0, NULL))
    {
        return;
    }

    FILE* f;
    fopen_s(&f, destFile, "r");

    char text[200];

    while (fgets(text, 199, f))
    {
        AnsiToOem(text, text);
        string line(text);
        int span = line.find("data-temperature-f=\"");
        if (span != string::npos) {
            int start = line.find("+",span);
            int end = line.find("&", start);
            if (end != string::npos) {
                string temperature = line.substr(start, end - start);
                cout << "Temperature in " << city << ": " << temperature << endl;
                break;
            }
        }
    }

    fclose(f);
}



int main()
{
    const char* srcOdessa = "https://www.gismeteo.ua/weather-odessa-4982/";
    const char* srcKyiv = "https://meteofor.com.ua/ru/weather-kyiv-4944/";
    const char* srcLviv = "https://meteofor.com.ua/ru/weather-lviv-4949";
    const char* srcKharkiv = "https://meteofor.com.ua/ru/weather-kharkiv-5053/";
    const char* srcSumy = "https://meteofor.com.ua/ru/weather-sumy-4936/";
    const char* srcDnipro = "https://meteofor.com.ua/ru/weather-dnipro-5077/";
    const char* srcZaporizhzhia = "https://meteofor.com.ua/ru/weather-zaporizhia-5093/";
    const char* srcKryviyRig = "https://meteofor.com.ua/ru/weather-kryvyi-rih-4978/";
    const char* srcVinnytsia = "https://meteofor.com.ua/ru/weather-vinnytsia-4962/";
    const char* srcPoltava = "https://meteofor.com.ua/ru/weather-poltava-4957/";
    const char* srcChernihiv = "https://meteofor.com.ua/ru/weather-chernihiv-4923/";

    findTemperature(srcOdessa, "Odessa");
    findTemperature(srcKyiv, "Kyiv");
    findTemperature(srcLviv, "Lviv");
    findTemperature(srcKharkiv, "Kharkiv");
    findTemperature(srcSumy, "Sumy");
    findTemperature(srcDnipro, "Dnipro");
    findTemperature(srcZaporizhzhia, "Zaporizhzhia");
    findTemperature(srcKryviyRig, "Donetsk");
    findTemperature(srcVinnytsia, "Mariupol");
    findTemperature(srcPoltava, "Kherson");
    findTemperature(srcChernihiv, "Mykolaiv");

    return 0;
}

