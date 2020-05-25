//
// Created by binybrion on 5/25/20.
//

#ifndef GLSL_INCLUDE_PREPROCESSOR_INCLUDEIMPLEMENTATION_H
#define GLSL_INCLUDE_PREPROCESSOR_INCLUDEIMPLEMENTATION_H

#include <string>
#include <vector>

namespace PreprocessorInclude
{
    /**
     * Holds the code that replaces include statements with the contents of another file. To run, use the following code:
     *
     * std::vector<std::string> preprocessorResult = PreprocessorInclude::IncludeImplementation::execute(locationToFile);
     *
     *                                          or more concisely
     *
     * auto preprocessorResult = PreprocessorInclude::IncludeImplementation::execute(locationToFile);
     *
     */

    class IncludeImplementation
    {
        public:

            /**
             * Starts the preprocessor, running until there are no more include statements in the resulting file content.
             *
             * If a file included itself has an include statement, this include statement will cause the preprocessor to
             * take action too. This will continue until no more include statements are encountered.
             *
             * @param startingFileLocation the location to the file on which to perform the include pre-processing
             * @return vector of strings of the result of running the pre-processor; every element represents a line
             *                had the result been written to a file.
             */
            static std::vector<std::string> execute(const std::string &startingFileLocation);

            /**
             * Replaces the execution result with the equivalent content stored as a string.
             *
             * This is a convenience function, not strictly required for the include operation.
             *
             * @param executionResult vector of strings to replace with one string
             * @return the string equivalent of executionResult.
             */
            static std::string mergeExecutionResults(const std::vector<std::string> &executionResult);

        private:

            /**
             * Searches the input for any include statements, and stores them.
             *
             * @param fileContents to search for include statements
             * @return vector of indexes into fileContents that contain include statements
             */
            static std::vector<unsigned int> findIncludeLineNumbers(const std::vector<std::string> &fileContents);

            /**
             * Inserts the contents of the file referenced by an include statement into the file containing the include statement.
             * The line containing the include statement does not exist after running this function.
             *
             * @param fileContents on which to perform the include operation
             * @param includeLineNumbers indexes into fileContents that contain include statements
             * @throws runtime_error if a include statement is ill-formed. See IncludeImplementation.cpp for more details.
             */
            static void insertFileContents(std::vector<std::string> &fileContents, std::vector<unsigned int> &includeLineNumbers);

            /**
             * Reads the contents of a file, representing the contents of the file as a vector of strings.
             *
             * @param fileLocation location to the file containing the contents on which to perform include operations
             * @return vector of strings representing the read file contents, where every elements represents a file line
             * @throws runtime_error if the given file could not be opened
             */
            static std::vector<std::string> readFile(const std::string &fileLocation);

            /**
             * Spits the given line by white space, returning all of the words in the line.
             *
             * @param currentLine to split by white space
             * @return vector of strings as a result of splitting the given line by whitespace
             */
            static std::vector<std::string> splitWhiteSpace(const std::string &currentLine);
    };
}

#endif //GLSL_INCLUDE_PREPROCESSOR_INCLUDEIMPLEMENTATION_H
