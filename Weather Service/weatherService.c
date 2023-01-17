#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>

int main() {
    CURL *curl;
    CURLcode res;
    char weather[256];

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://api.openweathermap.org/data/2.5/weather?q=your_city&appid=your_api_key");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, weather);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        printf("Current weather: %s\n", weather);
    }
    return 0;
}
