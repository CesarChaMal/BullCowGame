/*
The game logic
The game is a simple guess the word game based on Mastermind
*/

#pragma once
#include <string>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {

public:

	// constructor
	FBullCowGame();

	int32 getMaxTries() const;
	int32 getCurrentTry() const;
	int32 getHiddenWordLength() const;
	bool isGameWon() const;
	EGuessStatus checkGuessValidity(FString) const;

	void reset();
	FBullCowCount submitValidGuess(FString);

private:
	int32 myCurrentTry;
	bool bGameIsWon;
	FString myHiddenWord;
	bool isIsogram(FString guess) const;
	bool isLowercase(FString guess) const;
	bool isWrongLength(FString guess) const;
};
