//
// Created by BinyBrion on 2019-09-13.
//

#include <QtCore/QDir>
#include "TestSuite.h"
#include <fstream>

namespace Tests
{
    /*
     *  When a class is derived from this class and constructed, this default constructor will run.
     *  When that does, the instance of the class to be constructed will be added to the test suite.
     *
     *  A class derived from this can be created using a static object. For example"
     *
     *  class SomeTest : public TestSuite { *Some Tests* };
     *
     *  In SomeTest.cpp:
     *
     *  static SomeTest someTest;
     */

    TestSuite::TestSuite(const QString &testClassName)
    {
        suite().push_back({testClassName, this});
    }

    std::vector<std::pair<QString, QObject*>>& TestSuite::suite()
    {
        static std::vector<std::pair<QString, QObject*>> testObjects;

        return testObjects;
    }

    QString TestSuite::getTestAssetFolder() const
    {
        QDir currentPath = QDir::current();

        if(!(currentPath.cdUp() && currentPath.cd("TestAssets")))
        {
            throw std::runtime_error{"Unable to find test asset folder, located at: projectRootDirectory/TestAssets"};
        }

        return currentPath.path();
    }

    std::string TestSuite::readFile(const QString &fileLocation) const
    {
        std::fstream fileReader{fileLocation.toStdString()};

        if(!fileReader.is_open())
        {
            throw std::runtime_error{"Unable to open the file: " + fileLocation.toStdString()};
        }

        std::string currentLine;
        std::string fileContents;

        while(std::getline(fileReader, currentLine))
        {
            fileContents += currentLine + '\n';
        }

        return fileContents;
    }
}