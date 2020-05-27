//
// Created by BinyBrion on 2019-09-13.
//

#ifndef TEXTUREATLASCREATOR_TESTSUITE_H
#define TEXTUREATLASCREATOR_TESTSUITE_H

#include <QtCore/QObject>

namespace Tests
{
    /**
     *  Creates a test suite to simplify the execution of tests. Any time a class derived
     *  from this class is created, it will be added to the (static) vector of this class.
     *  Once all the appropriate test classes are created (which are derived from this class),
     *  loop through the (static) vector of this class and execute each test.
     *
     *  Idea is from: https://alexhuszagh.github.io/2016/using-qttest-effectively/
     *
     *  Example Usage:
     *
     *  class TestSomeComponent : public TestSuite { *Some Tests to execute* };
     *
     *  auto tests = TestSuite::suite();
     *
     *  for(const auto i : tests)
     *  {
     *      QTest::qExec(i, argc, argv);
     *  }
     */

    class TestSuite : public QObject
    {
        public:

            /**
             *  Initializes this Test Class with the given name, allowing it to be controlled
             *  when it is run based off of program arguments.
             *
             * @param testClassName name of the test class
             */
            explicit TestSuite(const QString &testClassName);

            /**
             * Get the references to all of the test classes registered with this suite.
             *
             * @return vector of registered test classes; ie test classes to run
             */
            static std::vector<std::pair<QString, QObject*>>& suite();

        protected:

            /**
             * Gets the location of the root folder holding the test files for all of the test class.
             *
             * @return location of root folder holding the test files
             */
            virtual QString getTestAssetFolder() const;

            /**
             * Reads the contents of the given file, and returns it.
             *
             * @param fileLocation location of the file to read
             * @return contents of the file associated with the passed in location
             */
            std::string readFile(const QString &fileLocation) const;
    };
}

#endif //TEXTUREATLASCREATOR_TESTSUITE_H
