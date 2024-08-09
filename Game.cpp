//
//  Game.cpp
//  Wordle
//
//  Created by Vicky on 2024-04-01.
//

#include "Game.h"

using namespace std;

const map<LetterGuess::Evaluation, string> LetterGuess::evalSymbols = {
    {LetterGuess::Evaluation::Correct, "🟩"},
    {LetterGuess::Evaluation::CorrectLetterIncorrectLocation, "🟨"},
    {LetterGuess::Evaluation::Incorrect, "⬜"}
};

inline string LetterGuess::toString() const {
    string evalSymbol = evalSymbols.at(eval);
    return evalSymbol + character + evalSymbol;
}

inline string WordGuess::toString() const {
    string guessStr = "";
    for (LetterGuess charResult : letters) {
        guessStr += charResult.toString();
    }
    return guessStr;
}

string GameIO::promptGuess(int length, int guessesRemaining) {
    cout << "Guess a " << length << "-letter word (" << guessesRemaining << " guesses remaining): \n";
    string result;
    getline(cin, result);
    // TODO: validate guess (is it a real 6 letter word), reprompt if necessary until valid guess is provided
    return result;
}

void GameIO::renderGameState(const GameState &state) {
    for (WordGuess guess : state.guesses) {
        cout << guess.toString() << "\n";
    }
}

string GameIO::promptSolutionWord() {
    cout << "Type in a word to be guessed by the other player:\n";
    string result;
    getline(cin, result);
    
    // silly way to hide what the other player wrote...!
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    
    return result;
}

void Game::start() {
    // set up game params
    m_params.solutionStr = GameIO::promptSolutionWord();
    m_params.tries = 6; // TODO: make configurable
    m_params.solutionLen = m_params.solutionStr.length();

    // force uppercase for everything
    for (int i = 0; i < m_params.solutionLen; i++) {
        m_params.solutionStr[i] = toupper(m_params.solutionStr[i]);
    }
    
    // set up game state
    m_state.solutionFound = false;
    m_state.guessesRemaining = m_params.tries;
    m_state.guesses.reserve(m_params.tries);
    
    while (!isComplete()) {
        gameLoop();
    }
    
    if (m_state.solutionFound) {
        cout << "Congrats! You solved it! \n";
    } else {
        cout << "Ran out of guesses. Try again! \n";
    }
}

void Game::gameLoop() {
    m_state.solutionFound = guess(GameIO::promptGuess(m_params.solutionLen, m_state.guessesRemaining));
    GameIO::renderGameState(m_state);
}

bool Game::isComplete() const {
    return m_state.solutionFound || m_state.guessesRemaining < 1;
}

bool Game::guess(string input) {
    WordGuess guessResult;
    bool allCorrect = true;
    for (int i = 0; i < m_params.solutionLen; i++) {
        char ch = toupper(input[i]); // force uppercase
        LetterGuess result;
        result.character = ch;
        result.eval = evaluateChar(ch, i);
        guessResult.letters.push_back(result);
        allCorrect = allCorrect && (result.eval == LetterGuess::Evaluation::Correct);
    }
    m_state.guesses.push_back(guessResult);
    m_state.guessesRemaining--;
    return allCorrect;
}

LetterGuess::Evaluation Game::evaluateChar(char ch, int index) const {
    if (m_params.solutionStr[index] == ch) {
        return LetterGuess::Evaluation::Correct;
    } else if (m_params.solutionStr.find(ch) != std::string::npos) {
        return LetterGuess::Evaluation::CorrectLetterIncorrectLocation;
    } else {
        return LetterGuess::Evaluation::Incorrect;
    }
}
