// pch.h: This is a pre-compiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// Standard library headers
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits> // Required for clearing input buffer
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <ctime>

// Include headers from the Core project
// The path assumes the Core project is in a sibling directory.
// Update the path if your project structure is different.
#include "../TrivialPursuitCore/DeleteManager.h"
#include "../TrivialPursuitCore/FileReader.h"
#include "../TrivialPursuitCore/FileWriter.h"
#include "../TrivialPursuitCore/GameFunctions.h"
#include "../TrivialPursuitCore/GameSetup.h"

// Test-specific headers
#include "TestHelpers.h"

#endif //PCH_H
