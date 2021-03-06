#include <fstream>
#include "Tests/TestSuite.h"
#include <QTest>
#include "PreprocessorInclude/RecursiveInclude.h"

int main(int argc, char *argv[])
{
    auto testSuite = Tests::TestSuite::suite();

    // Only run the tests if they were specified in the program arguments.
    // Note: index 0 is the program name; it is not checked if it corresponds to a test.
    // The tests will only work if the project structure is the same as development, so that the
    // test asset folder can be found.
    for(int i = 1; i < argc; ++i)
    {
        for(auto &test: testSuite)
        {
            if(test.first == argv[i])
            {
                QTest::qExec(test.second);
            }
        }
    }

    /*
     * The three expected arguments are as follows:
     *
     * #1 - The program name (convention is that this is the first program argument, even if not specified- it is unused here).
     * #2 - The file containing the contents to perform the include operation
     * #3 - The location in which to store the execution result (as after this program ends, the execution result is freed from memory).
     * #4 - boolean specifying whether or not to abort execution on reading an unknown file line starting with a '#'.
     */
    const unsigned int EXPECTED_NUMBER_ARGUMENTS = 4;

    if(argc < EXPECTED_NUMBER_ARGUMENTS)
    {
        printf("Wrong number of program arguments- expected at least four, received: %d \n", argc);

        return -1;
    }

    // No particular reason to create the file before running the preprocessor; code seems to look cleaner, but this
    // is a personal decision. If the main function was bigger, then no so that the scope of the stream is smaller.
    std::ofstream writeContents{argv[2]};

    if(!writeContents.is_open())
    {
        printf("Unable to create a file at: %s for writing! \n", argv[2]);

        return -2;
    }

    try
    {
        auto preprocessorResult = PreprocessorInclude::RecursiveInclude::execute(argv[1], std::string{argv[3]} == "false");

        writeContents << PreprocessorInclude::RecursiveInclude::mergeExecutionResults(preprocessorResult);
    }
    catch(std::exception &e)
    {
        // Remove the file created as there is no result to output to a file. If this delete file operation fails,
        // it is not critical as this program will overwrite the (not deleted) file the next time it runs.
        std::remove(argv[2]);

        printf("Error running include preprocessor: %s \n", e.what());

        return -3;
    }

    return 0;
}
