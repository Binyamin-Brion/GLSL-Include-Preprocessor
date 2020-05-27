//
// Created by BinyBrion on 2020-05-26.
//

#ifndef GLSL_INCLUDE_PREPROCESSOR_TESTRECURSIVEINCLUDE_H
#define GLSL_INCLUDE_PREPROCESSOR_TESTRECURSIVEINCLUDE_H

#include "TestSuite.h"

namespace Tests
{
    /**
     * Tests the preprocessor with test files that include files that themselves have includes files.
     */

    class TestRecursiveInclude : public TestSuite
    {
            Q_OBJECT

        public:

            /**
             *  Initializes this Test Class with the given name, allowing it to be controlled
             *  when it is run based off of program arguments.
             *
             * @param testClassName name of the test class
             */
            explicit TestRecursiveInclude(const QString &testClassName);

        private slots:

            /**
             * Tests the preprocessor with a file that has an include statement, and the included file itself has a
             * include statement. This test also has two include statements, though the second one is not recursive.
             */
            void testSingleRecursiveInclude();

            /**
             * Same as the above test, but the file to be included in the first include statement is in a parent directory.
             */
            void testRelativeRecursive();

            /**
             * Same as the above test (testRelativeRecursive), but the first include statement is in the parent's parent directory
             * (so two of "../").
             */
            void testRelativeExtraRecursive();

        private:

            /**
             * Gets the location of the folder holding the test files for this test class.
             *
             * @return location of folder holding the test files
             */
            QString getTestAssetFolder() const override;
    };
}

#endif //GLSL_INCLUDE_PREPROCESSOR_TESTRECURSIVEINCLUDE_H
