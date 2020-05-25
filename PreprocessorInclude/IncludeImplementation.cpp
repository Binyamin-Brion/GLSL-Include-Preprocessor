//
// Created by binybrion on 5/25/20.
//

#include "IncludeImplementation.h"

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iterator>

namespace PreprocessorInclude
{
    std::vector<std::string> IncludeImplementation::execute(const std::string &startingFileLocation)
    {
        std::vector<std::string> startingFile = readFile(startingFileLocation);

        while(true)
        {
            // Find the lines with include statements and then replace those include statements with the contents of the
            // files those include statements reference.
            auto includeLineNumbers = findIncludeLineNumbers(startingFile);

            insertFileContents(startingFile, includeLineNumbers);

            // The included file contents may themselves contain include statements. This means that even after a particular
            // run, there may still be include statements in the returned execution result. Thus, this loop will only break
            // after all include statements are removed.
            if(findIncludeLineNumbers(startingFile).empty())
            {
                break;
            }
        }

        return startingFile;
    }

    std::vector<unsigned int> IncludeImplementation::findIncludeLineNumbers(const std::vector<std::string> &fileContents)
    {
        std::vector<unsigned int> lineNumbers;

        for(unsigned int i = 0; i < fileContents.size(); ++i)
        {
            // It is assumed that include statements are referenced by the '#include' sequence of characters, as this
            // is what is seen in the C preprocessor.
            if(fileContents[i].find("#include") != std::string::npos)
            {
                lineNumbers.push_back(i);
            }
        }

        return lineNumbers;
    }

    void IncludeImplementation::insertFileContents(std::vector<std::string> &fileContents, std::vector<unsigned int> &includeLineNumbers)
    {
        for(unsigned int index = 0; index < includeLineNumbers.size(); ++index)
        {
            unsigned int lineOffset = includeLineNumbers[index];

            auto lineWords = splitWhiteSpace(fileContents[lineOffset]);

            /*
             * An include statements should contains two words- the '#include' keyword itself and the file it references, like so:
             *
             *  Line x: #include someFileToInclude
             *             ^        ^
             *            Word 1   Word 2   (number of whitespaces between words is irrelevant)
             *
             *  If there is less than two words, then the file to include is not specified; if there are more, than it is
             *  unclear how to process the include (is the third word the file to include for example?) and so an error is issued.
             */
            const unsigned int EXPECTED_NUMBER_WORDS = 2;

            if(lineWords.size() != EXPECTED_NUMBER_WORDS)
            {
                std::string errorMessage = "Error: At line number: " + std::to_string(lineOffset);
                errorMessage += " expected two sequences of text separated by whitespace, but got " + std::to_string(lineWords.size());
                errorMessage += " sequences of tokens.";

                throw std::runtime_error{errorMessage};
            }

            // Due to the above assertion that each include line is two words, then the file to include is the second
            // work of the include line.
            const unsigned int INCLUDE_FILE_INDEX = 1;

            auto includedFileContents = readFile(lineWords[INCLUDE_FILE_INDEX]);

            // Erased before the include operation as the lineOffset changes after the
            // include statement if more than one line is included; easier to erase now as the lineOffset value is still valid.
            fileContents.erase(fileContents.begin() + lineOffset);

            fileContents.insert(includedFileContents.begin(), includedFileContents.end(), fileContents.begin() + lineOffset);

            unsigned int numberLinesAdded = includedFileContents.size() - 1; // '-1' because the original include statement is removed.

            // Update the remaining offset values to take into account that the lines they reference have moved within the file,
            // due to content being added before them.
            for(unsigned int i = index + 1; i < includedFileContents.size(); ++i)
            {
                includeLineNumbers[i] += numberLinesAdded;
            }
        }
    }

    std::vector<std::string> IncludeImplementation::readFile(const std::string &fileLocation)
    {
        std::ifstream fileReader{fileLocation};

        if(!fileReader.is_open())
        {
            throw std::runtime_error{"Unable to find the file: " + fileLocation};
        }

        std::string currentLine;
        std::vector<std::string> fileContents;

        // Note: all empty lines are preserved so that the only modifications present in the file read (when the user views
        // execution result) are the include operations.
        while(std::getline(fileReader, currentLine))
        {
            fileContents.push_back(currentLine);
        }

        return fileContents;
    }

    std::vector<std::string> IncludeImplementation::splitWhiteSpace(const std::string &currentLine)
    {
        std::istringstream inputStringStream(currentLine);

        return std::vector<std::string> {std::istream_iterator<std::string>{inputStringStream},std::istream_iterator<std::string>{}};
    }

    std::string IncludeImplementation::mergeExecutionResults(const std::vector<std::string> &executionResult)
    {
        std::string mergedResult;

        for(const auto &i : executionResult)
        {
            mergedResult += i;
        }

        return mergedResult;
    }
}
