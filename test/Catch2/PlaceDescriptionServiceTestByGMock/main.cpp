#define CATCH_CONFIG_RUNNER
#include "catch2/catch.hpp"

#include "gmock/gmock.h"

int main(int argc, char** argv)
{
    int gmockArgC = 1;
    ::testing::InitGoogleMock(&gmockArgC, argv);

    struct Listener : public testing::EmptyTestEventListener
    {
        void OnTestPartResult(const testing::TestPartResult& Result) override
        {
            std::string filename = "unknown";
            size_t linenumber = 0;
            std::string message = "unknown";

            if (Result.file_name() != nullptr) filename = Result.file_name();

            if (Result.line_number() != -1) linenumber = static_cast<std::size_t>(Result.line_number());

            if (Result.message() != nullptr) message = Result.message();

            ::Catch::SourceLineInfo sourceLineInfo(filename.c_str(), linenumber);

            if (Result.fatally_failed())
            {
                ::Catch::AssertionHandler assertion(
                    "GTEST", sourceLineInfo, "", ::Catch::ResultDisposition::Normal);

                assertion.handleMessage(::Catch::ResultWas::ExplicitFailure, message);

                assertion.setCompleted();
            }
            else if (Result.nonfatally_failed())
            {
                ::Catch::AssertionHandler assertion(
                    "GTEST", sourceLineInfo, "", ::Catch::ResultDisposition::ContinueOnFailure);

                assertion.handleMessage(::Catch::ResultWas::ExplicitFailure, message);

                assertion.setCompleted();
            }
        }
    };

    ::testing::UnitTest::GetInstance()->listeners().Append(new Listener);

    delete ::testing::UnitTest::GetInstance()->listeners().Release(
        ::testing::UnitTest::GetInstance()->listeners().default_result_printer());

    Catch::Session session;

    int returnCode = session.applyCommandLine(argc, argv);
    if (returnCode != 0)   // Indicates a command line error
        return returnCode;

    int result = session.run();

    return result;
}