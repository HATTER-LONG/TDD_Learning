#include "CurlHttp.h"

#include <string>

using namespace std;

string CurlHttp::response_;

CurlHttp::CurlHttp()
        : Curl(NULL)
{
}

CurlHttp::~CurlHttp()
{
    curl_global_cleanup();
}

void CurlHttp::initialize()
{
    curl_global_init(CURL_GLOBAL_ALL);
    Curl = curl_easy_init();
    curl_easy_setopt(Curl, CURLOPT_WRITEFUNCTION, &CurlHttp::writeCallback);
}

string CurlHttp::get(const string& Url) const
{
    response_ = "invalid request";   // TODO test
    curl_easy_setopt(Curl, CURLOPT_URL, Url.c_str());
    curl_easy_perform(Curl);
    curl_easy_cleanup(Curl);

    return CurlHttp::response();
}

string CurlHttp::response()
{
    return response_;
}

size_t CurlHttp::writeCallback(const char* Buf, size_t Size, size_t NMemb, void*)
{
    for (auto i = 0u; i < Size * NMemb; i++)
        response_.push_back(Buf[i]);
    return Size * NMemb;
}
