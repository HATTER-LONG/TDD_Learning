#pragma once

#include "Http.h"

#include <string>

class CurlHttp : public Http
{
public:
    CurlHttp();
    virtual ~CurlHttp();

    void initialize();
    virtual std::string get(const std::string& Url) const;
    static std::string response();
    static size_t writeCallback(const char* Buf, size_t Size, size_t NMemb, void*);

private:
    // CURL* m_curl;

    static std::string sResponse;
};
