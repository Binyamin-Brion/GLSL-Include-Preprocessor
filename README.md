# GLSL-Include-Preprocessor

## Overview

GLSL, the OpenGL Shading Langauge, does not contain a "#include" preprocessor directive.
As a result, there are two possible solutions when trying to split a long GLSL file:

* Have everything in one file.
* Implement a "#include" equivalent that merges all sources files into one source file,
   before the GLSL compiler sees it.
   
The problem with the first alternative is that the source file can become very long, to the
point of being unmanaegable.

This program provides the second alternative.

## Usage

There are two ways to use this program:

* Use the provided executable. Then, the program would be used like the following:

  system(_locationToTheExecutable_, _locationToFileToRunPreprocessorOn_, _locationOutput_, _true_)
  
  **_The value of 'true' means abort execution if a file line contains a line starting with a '#' that is neither a "#include" nor a GLSL preprocessor directive. If no action should be taken, pass in false._**
  
  **Using the _system_ call may not be the best choice due to security reasons. If there is an alternative way to invoke an executable from a program available, it may be worth considering.**

* Include the files located in the "PreprocessorInclude" folder into the project source. However, this relies on the Qt framework being installed on the developement machine. See compilation note. The following code is required for usage:

  _// This stores the resulting file as a vector of strings, where each elements represents a single file line._
  
  auto preprocessorResult = PreprocessorInclude::RecursiveInclude::execute(_locationToFile_, true);
  
  _// This stores the above result as a single string._
  
  std::string executionResult = PreprocessorInclude::RecursiveInclude::mergeExecutionResults(preprocessorResult);
  
## Compilation Note:

If the source files are being included in the project, then the Qt framework needs to be installed on the developement machine. The version of the Qt framework used was 5.9.9.

Additionally, the CMake file will need to be updated to point to the location of the Qt framework on the developement machine.

## Sample Preprocessor Result

**File 1:** 

  #include "File2"
  
  This is some text in the first program
  
**File 2:**

  This is some text from the second program
  
**system("GLSL-Include-Preprocessor", "File1.txt", "Output.txt", true)**

**Output.txt:**

  This is some text from the second program
  
  This is some test in the first program
