#include <fstream>
#include "PreprocessorInclude/IncludeImplementation.h"

int main(int argc, char *argv[])
{
    /*
     * The three expected arguments are as follows:
     *
     * #1 - The program name (convention is that this is the first program argument, even if not specified- it is unused here).
     * #2 - The file containing the contents to perform the include operation
     * #3 - The location in which to store the execution result (as after this program ends, the execution result is freed from memory).
     */
    const unsigned int EXPECTED_NUMBER_ARGUMENTS = 3;

    if(argc > EXPECTED_NUMBER_ARGUMENTS)
    {
        printf("Wrong number of program arguments- expected two, received: %d \n", argc);

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
        auto preprocessorResult = PreprocessorInclude::IncludeImplementation::execute(argv[1]);

        for(const auto &line : preprocessorResult)
        {
            writeContents << line;
        }
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
