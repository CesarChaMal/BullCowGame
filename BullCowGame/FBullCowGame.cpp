#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame()
{
	reset();
}

void FBullCowGame::reset()
{
	// this must be an isogram
	const FString HIDDEN_WORD = "planet";

	myHiddenWord = HIDDEN_WORD;
	myCurrentTry = 1;
	bGameIsWon = false;

	return;
}

int FBullCowGame::getMaxTries() const
{
	//return myMaxTries;
	TMap<int32, int32> WordLengthToMaxTries{ { 3,4 }, { 4,7 }, { 5,10 }, { 6,16 }, { 7,20 } };
	return WordLengthToMaxTries[myHiddenWord.length()];
}

int32 FBullCowGame::getCurrentTry() const
{
	return myCurrentTry;
}

int32 FBullCowGame::getHiddenWordLength() const
{
	return myHiddenWord.length();
}

bool FBullCowGame::isGameWon() const
{
	return bGameIsWon;
}

bool FBullCowGame::isIsogram(FString guess) const
{
	// treat 0 and 1 letter words as isograms
	if (guess.length() <= 1) {
		return true;
	}

	TMap <char, bool> letterSeen;

	//for (char letter : guess)
	for (auto letter : guess)
	{
		letter = tolower(letter);
		if (letterSeen[letter]) {
			return false;
		} else {
			letterSeen[letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::isLowercase(FString guess) const
{
	//for (char letter : guess)
	for (auto letter : guess)
	{
		if (!islower(letter)) {
			return false;
		}
	}
	return true;
}

bool FBullCowGame::isWrongLength(FString guess) const
{
	return guess.length() == getHiddenWordLength();
}

EGuessStatus FBullCowGame::checkGuessValidity(FString guess) const
{
	//if (false) {
	if (!isIsogram(guess)) {
		return EGuessStatus::Not_Isogram;
	} else if (!isLowercase(guess)) {
	//} else if (false) {
		return EGuessStatus::Not_Lowercase;
	} else if (!isWrongLength(guess)) {
		return EGuessStatus::Wrong_Length;
	} else {
		return EGuessStatus::OK;
	}

}

// receives a VALID guess, increments turn, and return count
FBullCowCount FBullCowGame::submitValidGuess(FString guess)
{
	// increment the turn number
	myCurrentTry++;

	// setup a return variable
	FBullCowCount bullCowCount;
	int32 hiddenWordLength = myHiddenWord.length();
	int32 guessWordLength = guess.length();

	// loop through all the letters in the hidden word
	for (int32 i = 0; i < hiddenWordLength; i++) {
		for (int32 j = 0; j < guessWordLength; j++) {
			if (guess[i] == myHiddenWord[j]) {
				if (i == j) {
					bullCowCount.Bulls++;
				} else {
					bullCowCount.Cows++;
				}
			}
		}
	}

	if (bullCowCount.Bulls == hiddenWordLength) {
		bGameIsWon = true;
	} else {
		bGameIsWon = false;
	}

	return bullCowCount;
}
