//
// Created by BinyBrion on 2020-05-26.
//

#include <QtTest/qtestcase.h>
#include "TestNoIncludes.h"
#include "../PreprocessorInclude/RecursiveInclude.h"

static Tests::TestNoIncludes testNoIncludes{"Test_No_Includes"};

using namespace PreprocessorInclude;

namespace Tests
{
    TestNoIncludes::TestNoIncludes(const QString &testClassName)
                    :
                        TestSuite{testClassName}
    {

    }

    void TestNoIncludes::testEmptyFile()
    {
        auto includeResult = RecursiveInclude::execute(getTestAssetFolder() + "/empty.txt");

        QVERIFY(includeResult.empty());
        QVERIFY(RecursiveInclude::mergeExecutionResults(includeResult).empty());
    }

    void TestNoIncludes::testFileNoIncludes()
    {
        RecursiveInclude recursiveInclude;

        auto includeResult = recursiveInclude.execute(getTestAssetFolder() + "/contentNoIncludes.txt");

        QVERIFY(!includeResult.empty());
        QVERIFY(includeResult.size() == 16); // This is how many files there are in the asset file.

        QVERIFY(!RecursiveInclude::mergeExecutionResults(includeResult).empty());
        QVERIFY(RecursiveInclude::mergeExecutionResults(includeResult) == readFile(getTestAssetFolder() + "/contentNoIncludes.txt"));
    }

    QString TestNoIncludes::getTestAssetFolder() const
    {
        return TestSuite::getTestAssetFolder() + "/NoInclude";
    }
}