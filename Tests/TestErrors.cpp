//
// Created by BinyBrion on 2020-05-27.
//

#include <QtTest/QtTest>
#include "TestErrors.h"
#include "PreprocessorInclude/RecursiveInclude.h"

static Tests::TestErrors testErrors{"Test_Errors"};

using namespace PreprocessorInclude;

namespace Tests
{
    TestErrors::TestErrors(const QString &testClassName)
            :
                TestSuite{testClassName}
    {

    }

    void TestErrors::testIllFormedIncludeFileName()
    {
        try
        {
            RecursiveInclude::execute(getTestAssetFolder() + "/illFormedIncludeFileName.txt");
        }
        catch(std::exception &e)
        {
            const std::string expectedErrorMessage = "Ill-formed include file in file";
            const std::string errorMessage = "Expected message with words: \"" + expectedErrorMessage + "\" but got: " + e.what();

            QVERIFY2(std::string{e.what()}.find(expectedErrorMessage) != std::string::npos, errorMessage.c_str());

            goto success;
        }

        QVERIFY(false);

        success:;
    }

    void TestErrors::testIllFormedIncludeLine()
    {
        try
        {
            RecursiveInclude::execute(getTestAssetFolder() + "/illFormedIncludeLine.txt");
        }
        catch(std::exception &e)
        {
            const std::string expectedErrorMessage = "expected two sequences of text separated by whitespace";
            const std::string errorMessage = "Expected message with words: \"" + expectedErrorMessage + "\" but got: " + e.what();

            QVERIFY2(std::string{e.what()}.find(expectedErrorMessage) != std::string::npos, errorMessage.c_str());

            goto success;
        }

        QVERIFY(false);

        success:;
    }

    void TestErrors::testInvalidDirectory()
    {
        try
        {
            // See the testAsset file for a note about this test- in some instances this test could fail even if the program
            // correctly works due to the location of where the test asset folder is located.
            RecursiveInclude::execute(getTestAssetFolder() + "/invalidDirectory.txt");
        }
        catch(std::exception &e)
        {
            const std::string expectedErrorMessage = "Could not cd-up from the directory";
            const std::string errorMessage = "Expected message with words: \"" + expectedErrorMessage + "\" but got: " + e.what();

            QVERIFY2(std::string{e.what()}.find(expectedErrorMessage) != std::string::npos, errorMessage.c_str());

            goto success;
        }

        QVERIFY(false);

        success:;
    }

    void TestErrors::testInvalidFile()
    {
        try
        {
            RecursiveInclude::execute(getTestAssetFolder() + "/aNonExistentFile.txt");
        }
        catch(std::exception &e)
        {
            const std::string expectedErrorMessage = " does not represent a file!";
            const std::string errorMessage = "Expected message with words: \"" + expectedErrorMessage + "\" but got: " + e.what();

            QVERIFY2(std::string{e.what()}.find(expectedErrorMessage) != std::string::npos, errorMessage.c_str());

            goto success;
        }

        QVERIFY(false);

        success:;
    }

    void TestErrors::testInvalidPreprocessorDirective()
    {
        try
        {
            RecursiveInclude::execute(getTestAssetFolder() + "/invalidPreprocessorDirective.txt");
        }
        catch(std::exception &e)
        {
            const std::string expectedErrorMessage = "Unexpected command starting with a '#'";
            const std::string errorMessage = "Expected message with words: \"" + expectedErrorMessage + "\" but got: " + e.what();

            QVERIFY2(std::string{e.what()}.find(expectedErrorMessage) != std::string::npos, errorMessage.c_str());

            goto success;
        }

        QVERIFY(false);

        success:;
    }

    QString TestErrors::getTestAssetFolder() const
    {
        return TestSuite::getTestAssetFolder() + "/InvalidIncludes";
    }
}