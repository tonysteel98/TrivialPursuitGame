#pragma once
#include <string>
#include <vector>
#include <utility>

class GameSetup {
private:
    std::string playerName;
    int maxLives;
    int maxQuestions;
    const std::vector<std::string> categoryFiles = {
    "geography.csv",
    "history.csv",
    "science.csv",
    "sports.csv",
    "movie.csv",
    "custom.csv"
    };

    // internal state for GUI mode
    std::vector<std::vector<std::string>> categoryQuestions;
    std::vector<std::vector<std::string>> categoryAnswers;
    int lives;
    int score;
    std::string currentAnswer;
    int lastCategory;
    int lastPickedIndex;
    bool questionActive;
    std::string lastCorrectAnswer;

public:
    GameSetup(const std::string& name, int lives_, int questions_);

    // existing
    void start(bool interactive = true);

    // GUI-friendly methods
    // load data and reset internal state
    void initializeGUI();

    int getMaxQuestions() const { return maxQuestions; };
    bool hasActiveQuestion()const { return !currentAnswer.empty(); };

    // roll dice (1..N)
    int rollCategory();

    // pick question (index is 1-based roll), returns {question, answer}
    std::pair<std::string, std::string> pickQuestionFromCategory(int category);

    // submit answer typed by user; returns true if correct and updates state
    bool submitAnswerForGUI(const std::string& userInput);

    // getters
    int getLives() const { return lives; }
    int getScore() const { return score; }
    bool isGameOver() const { return (lives <= 0) || (score >= maxQuestions); }

    // convenience: gets player name
    std::string getPlayerName() const { return playerName; }

    // persist high score (append to HighScores.csv)
    bool saveHighScore();
    std::string getLastCorrectAnswer() const { return lastCorrectAnswer; }
};
