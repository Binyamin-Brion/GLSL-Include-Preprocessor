//
// Created by BinyBrion on 2020-05-27.
//

#ifndef GLSL_INCLUDE_PREPROCESSOR_RECURSIVEINCLUDE_H
#define GLSL_INCLUDE_PREPROCESSOR_RECURSIVEINCLUDE_H

#include <string>
#include <vector>
#include <QDir>

namespace PreprocessorInclude
{
    /**
     * Holds the code that replaces include statements with the contents of another file. To run, use the following code:
     *
     * std::vector<std::string> preprocessorResult = PreprocessorInclude::RecursiveInclude::execute(locationToFile);
     *
     *                                          or more concisely
     *
     * auto preprocessorResult = PreprocessorInclude::RecursiveInclude::execute(locationToFile);
     *
     */

    class RecursiveInclude
    {
        public:

            /**
             * Starts the preprocessor, running until there are no more include statements in the resulting file content.
             *
             * If a file included itself has an include statement, this include statement will cause the preprocessor to
             * take action too. This will continue until no more include statements are encountered.
             *
             * @param startingFileLocation the location to the file on which to perform the include pre-processing
             *
             * @param ignoreUnknownDirective whether or not to consider any file line starting with a '#' that is neither
             *                               a "#include" or a GLSL preprocessor directive an error. True if to issue an error.
             *
             * @return vector of strings of the result of running the pre-processor; every element represents a line
             *                had the result been written to a file.
             */
            static std::vector<std::string> execute(const QString &fileLocation, bool ignoreUnknownDirective = false);

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
             * Checks if a line starting with a '#' is one of the GLSL preprocessor directives.
             *
             * @param fileLine the line containing statement starting with a '#'
             * @return true if the line is one of the GLSL preprocessor directives.
             */
            static bool checkGLSLDirective(const QString &fileLine);

             /**
              * Checks if a given include line is of the correct form.
              *
              * @param file that contains the include statement to check for validity
              * @param includeFileText the statement to check for a valid form
              * @throws runtime_error if the include statement does not have a valid form.
              */
             static void checkValidIncludeFile(const QString &file, const QString &includeFileText);

            /**
             * Searches the input for any include statements, and stores them.
             *
             * @param fileContents to search for include statements
             * @return vector of indexes into fileContents that contain include statements
             */
            static std::vector<unsigned int> findIncludeLineNumbers(const std::vector<QString> &fileContents);

             /**
              * Finds the parent directory of any include-statement that refers to one.
              *
              * This function modifies the directory to point to the parent directory referecned by the include statement.
              * The include statement is modified to refer to the current directory, as the parent directory will become
              * the current directory after this function.
              *
              * Such include statements have one more of "../" at the beginning of the statement.
              *
              * @param currentDirectory the directory of the file containing the include statement
              * @param includeStatement the include statement that may refer to a file in located in a parent directory
              */
             static void findParentDirectory(QDir &currentDirectory, QString &includeStatement);

             /**
              * Extracts the include statement without the preprocessor directive ("#include") from the passed in file line.
              *
              * @param fileName name of the file holding the include statement
              * @param currentFileLine the line containing the include statement
              * @param lineNumber the file number of the passed in file line
              * @return the include statement without the preprocessor directive
              * @throws runtime_exception if the include statement (the entire line) is ill-formed
              */
             static QString getIncludeFileStatement(const QString &fileName, const QString &currentFileLine, unsigned int lineNumber);

             /**
              * Reads the given file and scans for any include statements. Those include statements are replaced
              * with the contents of the file they refer to. This continues recursively until no more include statements
              * exist in all the files encountered while servicing include statements.
              *
              * @param fileLocation the location of the file to scan for include statements
              * @return a vector of strings, where every elements represents a line of the file after it has been expanded
              *         by executing the include statements contained within.
              */
             static std::vector<QString> processFile(const QString &fileLocation);

            /**
             * Reads the contents of a file, representing the contents of the file as a vector of strings.
             *
             * @param fileLocation location to the file containing the contents on which to perform include operations
             * @return vector of strings representing the read file contents, where every elements represents a file line
             * @throws runtime_error if the given file could not be opened
             */
            static std::vector<QString> readFile(const QString &fileLocation);

            // Determines whether any file lines starting with a '#' should be considered an error if it is neither
            // a "#include" or a GLSL preprocessor directive.
            static bool ignoreUnidentifiedDirective;
    };
}

#endif //GLSL_INCLUDE_PREPROCESSOR_RECURSIVEINCLUDE_H
