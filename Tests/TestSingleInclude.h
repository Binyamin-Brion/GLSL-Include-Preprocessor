//
// Created by BinyBrion on 2020-05-26.
//

#ifndef GLSL_INCLUDE_PREPROCESSOR_TESTSINGLEINCLUDE_H
#define GLSL_INCLUDE_PREPROCESSOR_TESTSINGLEINCLUDE_H

#include "TestSuite.h"

namespace Tests
{
    /**
     * Tests the preprocessor with files that have only a single include statement, and the include file does not have
     * any include statement itself.
     */

    class TestSingleInclude : public TestSuite
    {
            Q_OBJECT

        public:

            /**
             *  Initializes this Test Class with the given name, allowing it to be controlled
             *  when it is run based off of program arguments.
             *
             * @param testClassName name of the test class
             */
            explicit TestSingleInclude(const QString &testClassName);

        private slots:

            /**
             * Tests the preprocessor on a file with an include statement on the very first line.
             */
            void testIncludeFirstLine();

            /**
             * Tests the preprocessor on a file with an include statement in the middle of the file.
             */
            void testIncludeMiddleLine();

            /**
             * Tests the preprocessor on a file with an include statement on the very first line, but the included
             * file is in a parent directory.
             */
            void testIncludeRelative();

        private:

            /**
             * Gets the location of the folder holding the test files for this test class.
             *
             * @return location of folder holding the test files
             */
            QString getTestAssetFolder() const override;
    };
}

#endif //GLSL_INCLUDE_PREPROCESSOR_TESTSINGLEINCLUDE_H
