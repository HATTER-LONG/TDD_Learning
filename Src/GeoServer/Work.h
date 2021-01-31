#pragma once
#include <functional>

class Work
{
public:
    static const int DefaultId { 0 };
    Work(int id = DefaultId)
            : m_id { id }
            , m_executeFunction { [] {} }
    {
    }

    Work(std::function<void()> executeFunction, int id = DefaultId)
            : m_id { id }
            , m_executeFunction { executeFunction }
    {
    }
    void execute() { m_executeFunction(); }
    int id() const { return m_id; }

private:
    int m_id;
    std::function<void()> m_executeFunction;
};