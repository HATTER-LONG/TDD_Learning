#include "CurlHttp.h"
#include "HttpFactory.h"

#include <memory>

using namespace std;

HttpFactory::HttpFactory()
{
    reset();
}

shared_ptr<Http> HttpFactory::get()
{
    return m_instance;
}

void HttpFactory::reset()
{
    m_instance = make_shared<CurlHttp>();
}

void HttpFactory::setInstance(shared_ptr<Http> NewInstance)
{
    m_instance = NewInstance;
}
