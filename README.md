Trivial Pursuit C++ Game
Welcome to the Trivial Pursuit C++ project! This is a complete, multi-part application that brings the classic trivia game to your desktop, built with C++ and managed through a Visual Studio solution.

About The Project
This project is a fully-featured trivia game application separated into three distinct components:

TrivialPursuit (GUI Application): The main, playable game with a graphical user interface. Players can enjoy a polished trivia experience.

TrivialPursuitCore (Logic Library): The brains of the operation. This is a static library containing all the backend logic, including file management for questions, game rules, and state tracking.

TrivialPursuitTests (Console Test Suite): A console-based application that allows for interactive testing of all the core logic, ensuring that every function works as expected.

Features
Graphical User Interface: A user-friendly interface for seamless gameplay.

Dynamic Question Database: All questions and answers are loaded from external .csv files, making it easy to add, remove, or modify categories.

Comprehensive Test Suite: An interactive console application to run tests on all core functionalities, from file I/O to game logic.

Complete Game Loop: Includes dice rolling, question picking, answer checking, and score tracking.

How to Play (Recommended)
The easiest way to play the game is by downloading a pre-compiled version from the Releases page.

Navigate to the Releases section of this repository.

Download the latest .zip file for the GUI application (e.g., TrivialPursuit_GUI_v1.0.0.zip).

Unzip the file.

Run the TrivialPursuit.exe application. All necessary .csv files are included in the download.

How to Build from Source (For Developers)
If you wish to compile the project yourself:

Clone the repository: git clone https://github.com/YourUsername/TrivialPursuitGame.git

Open the TrivialPursuit.sln file in Visual Studio.

Set the desired project (TrivialPursuit or TrivialPursuitTests) as the "Startup Project".

Build the solution (usually by pressing F5 or Ctrl+Shift+B). The executables will be located in the x64/Debug or x64/Release folder.
