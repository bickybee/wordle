//
//  Game.h
//  Wordle
//
//  Created by Vicky on 2024-04-01.
//

#ifndef Game_h
#define Game_h

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct LetterGuess {
    enum Evaluation {
        Incorrect,
        CorrectLetterIncorrectLocation,
        Correct
    };
    
    char character;
    Evaluation eval;
    
    static const map<Evaluation, string> evalSymbols;
    
    inline string toString() const;
};

struct WordGuess {
    vector<LetterGuess> letters;
    inline string toString() const;
};

struct GameParams {
    string solutionStr;
    int solutionLen;
    int tries;
};

struct GameState {
    bool solutionFound;
    int guessesRemaining;
    vector<WordGuess> guesses;
};

class GameIO {
public:
    static string promptSolutionWord();
    static string promptGuess(int length, int guessesRemaining);
    static void renderGameState(const GameState& state);
};

class Game {
private:
    GameParams m_params;
    GameState m_state;
    
public:
    Game() {};
    void start();
    
private:
    void gameLoop();
    bool guess(string input);
    bool isComplete() const;
    LetterGuess::Evaluation evaluateChar(char ch, int index) const;
};

#endif /* Game_h */
