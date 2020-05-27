//
// Created by BinyBrion on 2020-05-26.
//

#include "TestRecursiveInclude.h"
#include "../PreprocessorInclude/RecursiveInclude.h"
#include <QtTest/qtestcase.h>

static Tests::TestRecursiveInclude testRecursiveInclude{"Test_Recursive_Include"};

using namespace PreprocessorInclude;

namespace Tests
{
    TestRecursiveInclude::TestRecursiveInclude(const QString &testClassName)
                            :
                                TestSuite(testClassName)
    {

    }

    void TestRecursiveInclude::testSingleRecursiveInclude()
    {
        auto includeResult = RecursiveInclude::execute(getTestAssetFolder() + "/includeFirstLineRecursive.txt", true);

        const QString errorMessage = "This many lines were received: " + QString::number(includeResult.size());

        QVERIFY(!includeResult.empty());
        QVERIFY2(includeResult.size() == 39, qPrintable(errorMessage)); // This is how many files there are in the asset file.

        QVERIFY(!RecursiveInclude::mergeExecutionResults(includeResult).empty());
        QVERIFY(RecursiveInclude::mergeExecutionResults(includeResult) == readFile(getTestAssetFolder() + "/ExpectedResult/includeFirstLineRecursive.txt"));
    }

    void TestRecursiveInclude::testRelativeRecursive()
    {
       auto includeResult = RecursiveInclude::execute(getTestAssetFolder() + "/includeRelativeRecursive.txt", true);

        const QString errorMessage = "This many lines were received: " + QString::number(includeResult.size());

        QVERIFY(!includeResult.empty());
        QVERIFY2(includeResult.size() == 39, qPrintable(errorMessage)); // This is how many files there are in the asset file.

        QVERIFY(!RecursiveInclude::mergeExecutionResults(includeResult).empty());
        QVERIFY(RecursiveInclude::mergeExecutionResults(includeResult) == readFile(getTestAssetFolder() + "/ExpectedResult/includeRelativeRecursive.txt"));
    }

    void TestRecursiveInclude::testRelativeExtraRecursive()
    {
        auto includeResult = RecursiveInclude::execute(getTestAssetFolder() + "/includeRelativeRecursive.txt", true);

        const QString errorMessage = "This many lines were received: " + QString::number(includeResult.size());

        QVERIFY(!includeResult.empty());
        QVERIFY2(includeResult.size() == 39, qPrintable(errorMessage)); // This is how many files there are in the asset file.

        QVERIFY(!RecursiveInclude::mergeExecutionResults(includeResult).empty());
        QVERIFY(RecursiveInclude::mergeExecutionResults(includeResult) == readFile(getTestAssetFolder() + "/ExpectedResult/includeRelativeRecursive.txt"));
    }

    QString TestRecursiveInclude::getTestAssetFolder() const
    {
        return TestSuite::getTestAssetFolder() + "/RecursiveInclude";
    }
}
