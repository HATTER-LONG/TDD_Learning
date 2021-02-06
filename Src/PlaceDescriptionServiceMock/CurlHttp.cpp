#include "CurlHttp.h"

#include <string>

using namespace std;

string CurlHttp::sResponse;

CurlHttp::CurlHttp() { }

CurlHttp::~CurlHttp()
{
    // curl_global_cleanup();
}

void CurlHttp::initialize()
{
    // curl_global_init(CURL_GLOBAL_ALL);
    // m_curl = curl_easy_init();
    // curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &CurlHttp::writeCallback);
}

string CurlHttp::get(const string& Url) const
{
    sResponse = "invalid request";   // TODO test
    // curl_easy_setopt(m_curl, CURLOPT_URL, Url.c_str());
    // curl_easy_perform(m_curl);
    // curl_easy_cleanup(m_curl);

    return CurlHttp::response();
}

string CurlHttp::response()
{
    return sResponse;
}

size_t CurlHttp::writeCallback(const char* Buf, size_t Size, size_t NMemb, void*)
{
    for (auto i = 0u; i < Size * NMemb; i++)
        sResponse.push_back(Buf[i]);
    return Size * NMemb;
}
