//
// Created by BinyBrion on 2020-05-27.
//

#include <c++/stdexcept>
#include <fstream>
#include <regex>
#include "RecursiveInclude.h"
#include <QtCore/QTextStream>

namespace PreprocessorInclude
{
    bool RecursiveInclude::ignoreUnidentifiedDirective;

    // Beginning of public functions

    std::vector<std::string> RecursiveInclude::execute(const QString &fileLocation, bool ignoreUnknownDirective)
    {
        ignoreUnidentifiedDirective = ignoreUnknownDirective;

        auto includedFiles = processFile(fileLocation);

        // Convert the result of the preprocessor to C++ standard strings as it is expected that this program will be integrated
        // into another program if this class files are used directly into another project. The chances are that the program
        // already used standard strings instead of QStrings is considered high.
        std::vector<std::string> returnResult;

        for(const auto &i : includedFiles)
        {
            returnResult.push_back(i.toStdString());
        }

        return returnResult;
    }

    std::string RecursiveInclude::mergeExecutionResults(const std::vector<std::string> &executionResult)
    {
        std::string mergedResult;

        for(const auto &i : executionResult)
        {
            mergedResult += i + '\n';
        }

        return mergedResult;
    }

    // Beginning of private functions

    std::vector<unsigned int> RecursiveInclude::findIncludeLineNumbers(const std::vector<QString> &fileContents)
    {
        std::vector<unsigned int> lineNumbers;

        for(unsigned int i = 0; i < fileContents.size(); ++i)
        {
            // It is assumed that include statements are referenced by the "#include" sequence of characters, as this
            // is what is seen in the C preprocessor.
            if(fileContents[i].contains("#include"))
            {
                lineNumbers.push_back(i);
            }
            else if(!ignoreUnidentifiedDirective &&
                    !fileContents[i].isEmpty() && // Check to make sure string isn't empty before checking first
                                                  // character, to avoid undefined behaviour.
                    fileContents[i].startsWith('#') &&
                    !checkGLSLDirective(fileContents[i]))
            {
                throw std::runtime_error{"Unexpected command starting with a '#' : " + fileContents[i].toStdString()};
            }
        }

        return lineNumbers;
    }

    void RecursiveInclude::findParentDirectory(QDir &currentDirectory, QString &includeStatement)
    {
        // Keep going to the parent directory while "../" are found at the beginning of
        // the include statement. If this fails, an exception is thrown as the include
        // statement may be referring to a non-existent directory.
        while(includeStatement.startsWith("../"))
        {
            if(!currentDirectory.cdUp())
            {
                throw std::runtime_error{"Could not cd-up from the directory: " + currentDirectory.path().toStdString()};
            }

            // As "../" is three characters long.
            includeStatement.remove(0, 3);
        }
    }

    QString RecursiveInclude::getIncludeFileStatement(const QString &fileName, const QString &currentFileLine, unsigned int lineNumber)
    {
        QStringList lineWords = currentFileLine.split(QRegExp{"\\s+"});

        const unsigned int EXPECTED_NUMBER_WORDS = 2;

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

        if(lineWords.size() != EXPECTED_NUMBER_WORDS)
        {
            std::string errorMessage = "Error: At line number: " + std::to_string(lineNumber);
            errorMessage += " expected two sequences of text separated by whitespace, but got " + std::to_string(lineWords.size());
            errorMessage += " sequences of tokens.";

            throw std::runtime_error{errorMessage};
        }

        // Due to the above assertion that each include line is two words, then the file to include is the second
        // work of the include line.
        return lineWords[1];
    }

    std::vector<QString> RecursiveInclude::processFile(const QString &fileLocation)
    {
        QFileInfo fileInfo{fileLocation};

        if(!fileInfo.isFile())
        {
            throw std::runtime_error{"The location " + fileLocation.toStdString() + " does not represent a file!"};
        }

        auto fileContents = readFile(fileLocation);

        auto includeLines = findIncludeLineNumbers(fileContents);

        // For-range loop not used due to inner loop executed at the end of this loop.
        for(unsigned int includeIndex = 0; includeIndex < includeLines.size(); ++includeIndex)
        {
            // Simply an alias to make this number more readable.
            unsigned int lineOffset = includeLines[includeIndex];

            QString includeFileName = getIncludeFileStatement(fileLocation, fileContents[lineOffset], lineOffset);

            checkValidIncludeFile(fileLocation, includeFileName);

            includeFileName.remove("\"");

            // Find the parent directory that the include statements is referring to, if any.
            // Action will be taken if the include statement contains "../"

            QDir currentDirectory = fileInfo.dir();
            findParentDirectory(currentDirectory, includeFileName);

            // What is left of the include file statement now refers to a child directory and can now be appended to the
            // found parent directory.
            QString toReadFileLocation = currentDirectory.path() + "/" + includeFileName;

            auto readContents = processFile(toReadFileLocation);

            // Erased before the include operation as the lineOffset changes after the
            // include statement if more than one line is included; easier to erase now as the lineOffset value is still valid.
            fileContents.erase(fileContents.begin() + lineOffset);

            fileContents.insert(fileContents.begin() + lineOffset, readContents.begin(), readContents.end());

            unsigned int numberLinesAdded = readContents.size() - 1; // '-1' because the original include statement is removed.

            // Update the remaining offset values to take into account that the lines they reference have moved within the file,
            // due to content being added before them.
            for(unsigned int i = includeIndex + 1; i < includeLines.size(); ++i)
            {
                includeLines[i] += numberLinesAdded;
            }
        }

        return fileContents;
    }

    std::vector<QString> RecursiveInclude::readFile(const QString &fileLocation)
    {
        QFile file{fileLocation};

        if(!file.open(QFile::ReadOnly | QFile::Text))
        {
            throw std::runtime_error{"Unable to open the file: " + fileLocation.toStdString()};
        }

        QTextStream inputStream{&file};

        std::vector<QString> readContents;

        while(!inputStream.atEnd())
        {
            readContents.push_back(inputStream.readLine());
        }

        return readContents;
    }

    bool RecursiveInclude::checkGLSLDirective(const QString &fileLine)
    {
        const std::vector<QString> glslDirectives =
                {
                        // These are specific to GLSL, and have no C alternative, as described here:
                        // https://www.khronos.org/opengl/wiki/Core_Language_(GLSL)#Compilation_settings
                        "#version",
                        "#extension",
                        "#line",

                        // In the above link, it is said other than the above directives,
                        // GLSL has the directives same as C. The following list lists those directives.
                        "#define",
                        "#undef",
                        "#if",
                        "#ifdef",
                        "#ifndef",
                        "#else",
                        "#endif",
                        "#line",
                        "#elif",
                        "#error",
                };

        for(const auto &i : glslDirectives)
        {
            if(fileLine.contains(i))
            {
                return true;
            }
        }

        return false;
    }

    void RecursiveInclude::checkValidIncludeFile(const QString &file, const QString &includeFileText)
    {
        QRegExp validIncludeFileRegex{R"("(../)*(/|[a-z]|[A-Z]|[0-9]|\.)+")"};

        // There should only one word after the "#include" that matches the above regular expression.
        if(includeFileText.count(validIncludeFileRegex) != 1)
        {
            throw std::runtime_error{"Ill-formed include file in file" + file.toStdString() + ", expected form \"nameOfFile\" , got: " + includeFileText.toStdString()};
        }
    }
}