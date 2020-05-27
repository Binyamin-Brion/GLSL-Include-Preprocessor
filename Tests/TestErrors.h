//
// Created by BinyBrion on 2020-05-27.
//

#ifndef GLSL_INCLUDE_PREPROCESSOR_TESTERRORS_H
#define GLSL_INCLUDE_PREPROCESSOR_TESTERRORS_H

#include "TestSuite.h"

namespace Tests
{
    /**
     * Tests that the appropriate error messages are thrown if an issue occurs during the execution of the preprocessor.
     */

    class TestErrors : public TestSuite
    {
            Q_OBJECT

        public:
            explicit TestErrors(const QString &testClassName);

        private slots:

            /**
             * Tests that an error message is thrown if an invalid file name is specified in an include statement.
             */
            void testIllFormedIncludeFileName();

            /**
             * Checks that an error message is thrown if an include statement does not contain two tokens.
             * ("#include" followed by white space, then "someFileName")
             */
            void testIllFormedIncludeLine();

            /**
             * Checks that an error message is thrown if an include statement refers to a parent directory that does not exist.
             */
            void testInvalidDirectory();

            /**
             * Tests that an error message is thrown if the pre-processor encounters a file that does not exist.
             */
            void testInvalidFile();

            /**
             * Tests than error message is thrown if the pre-processor comes across a file line starting with a '#',
             * but is neither a "#include" nor a GLSL pre-processor directive.
             */
            void testInvalidPreprocessorDirective();

        private:

            /**
             * Gets the location of the folder holding the test files for this test class.
             *
             * @return location of folder holding the test files
             */
            QString getTestAssetFolder() const override;

    };
}

#endif //GLSL_INCLUDE_PREPROCESSOR_TESTERRORS_H
