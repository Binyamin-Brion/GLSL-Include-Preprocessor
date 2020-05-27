//
// Created by BinyBrion on 2020-05-26.
//

#ifndef GLSL_INCLUDE_PREPROCESSOR_TESTNOINCLUDES_H
#define GLSL_INCLUDE_PREPROCESSOR_TESTNOINCLUDES_H

#include "TestSuite.h"

namespace Tests
{
    /**
     * Holds tests that test the preprocessor on files that have no include statements.
     */

    class TestNoIncludes : public TestSuite
    {
            Q_OBJECT

        public:

            /**
             *  Initializes this Test Class with the given name, allowing it to be controlled
             *  when it is run based off of program arguments.
             *
             * @param testClassName name of the test class
             */
            explicit TestNoIncludes(const QString &testClassName);

        private slots:

            /**
             *  Tests the preprocessor on an empty file.
             */
            void testEmptyFile();

            /**
             * Tests the preprocessor on a file with content, but there are no include statements in that file.
             */
            void testFileNoIncludes();

        private:

            /**
             * Gets the location of the folder holding the test files for this test class.
             *
             * @return location of folder holding the test files
             */
            QString getTestAssetFolder() const override;
    };
}

#endif //GLSL_INCLUDE_PREPROCESSOR_TESTNOINCLUDES_H
