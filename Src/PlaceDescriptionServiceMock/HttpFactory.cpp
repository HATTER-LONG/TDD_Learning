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
    return Instance;
}

void HttpFactory::reset()
{
    Instance = make_shared<CurlHttp>();
}

void HttpFactory::setInstance(shared_ptr<Http> NewInstance)
{
    Instance = NewInstance;
}
