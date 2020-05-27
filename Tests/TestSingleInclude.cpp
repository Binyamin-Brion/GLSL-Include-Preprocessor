//
// Created by BinyBrion on 2020-05-26.
//

#include "TestSingleInclude.h"
#include "../PreprocessorInclude/RecursiveInclude.h"
#include <QtTest/qtestcase.h>

static Tests::TestSingleInclude testSingleInclude{"Test_Single_Include"};

using namespace PreprocessorInclude;

namespace Tests
{
    TestSingleInclude::TestSingleInclude(const QString &testClassName)
                        :
                            TestSuite{testClassName}
    {

    }

    void TestSingleInclude::testIncludeFirstLine()
    {
        auto includeResult = RecursiveInclude::execute(getTestAssetFolder() + "/includeFirstLine.txt");

        const QString errorMessage = "This many lines were received: " + QString::number(includeResult.size());

        QVERIFY(!includeResult.empty());
        QVERIFY2(includeResult.size() == 27, qPrintable(errorMessage)); // This is how many files there are in the asset file.

        QVERIFY(!RecursiveInclude::mergeExecutionResults(includeResult).empty());
        QVERIFY(RecursiveInclude::mergeExecutionResults(includeResult) == readFile(getTestAssetFolder() + "/ExpectedResult/includeFirstLine.txt"));
    }

    void TestSingleInclude::testIncludeMiddleLine()
    {
        auto includeResult = RecursiveInclude::execute(getTestAssetFolder() + "/includeMiddleLine.txt");

        const QString errorMessage = "This many lines were received: " + QString::number(includeResult.size());

        QVERIFY(!includeResult.empty());
        QVERIFY2(includeResult.size() == 27, qPrintable(errorMessage)); // This is how many files there are in the asset file.

        QVERIFY(!RecursiveInclude::mergeExecutionResults(includeResult).empty());
        QVERIFY(RecursiveInclude::mergeExecutionResults(includeResult) == readFile(getTestAssetFolder() + "/ExpectedResult/includeMiddleLine.txt"));
    }

    void TestSingleInclude::testIncludeRelative()
    {
        auto includeResult = RecursiveInclude::execute(getTestAssetFolder() + "/includeFirstLineRelative.txt");

        const QString errorMessage = "This many lines were received: " + QString::number(includeResult.size());

        QVERIFY(!includeResult.empty());
        QVERIFY2(includeResult.size() == 22, qPrintable(errorMessage)); // This is how many files there are in the asset file.

        QVERIFY(!RecursiveInclude::mergeExecutionResults(includeResult).empty());
        QVERIFY(RecursiveInclude::mergeExecutionResults(includeResult) == readFile(getTestAssetFolder() + "/ExpectedResult/includeRelativeFirstLine.txt"));
    }

    QString TestSingleInclude::getTestAssetFolder() const
    {
        return TestSuite::getTestAssetFolder() + "/SingleInclude";
    }
}
