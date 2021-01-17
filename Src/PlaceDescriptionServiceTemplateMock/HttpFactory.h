#pragma once

#include "Http.h"

#include <memory>

class HttpFactory
{
public:
    HttpFactory();
    std::shared_ptr<Http> get();
    void setInstance(std::shared_ptr<Http>);
    void reset();

private:
    std::shared_ptr<Http> m_instance;
};
