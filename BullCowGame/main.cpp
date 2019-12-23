/* 
This is the console executable, thats makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void printIntro();
void playGame();
FText getValidGuess();
void printBack(FBullCowCount guess);
bool askToPlayAgain();
void printGameSummary();
// Instantiate a new game
FBullCowGame BCGame;

// the entry point of our application
int main()
{
	do {
		printIntro();
		playGame();
	} while (askToPlayAgain());

	std::cout << std::endl << std::endl;
	return 0;
}

// introduce the game
void printIntro()
{
	std::cout << "\n\nWelcome to Bulls and Cows Game in C++!\n\r" << std::endl;
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.getHiddenWordLength() << " letter isogram I'm thinking of?\n\r";
	std::cout << std::endl;
	return;
}

void playGame()
{
	BCGame.reset();
	int32 MaxTries = BCGame.getMaxTries();
	//std::cout << MaxTries << std::endl;

	// loop for the  number of turns asking of guesses
/*
	constexpr int NUMBER_OF_TURNS = 5;
	for (int i = 1; i <= NUMBER_OF_TURNS; i++)
	{
		FText Guess = GetGuess();
		PrintBack(Guess);
		std::cout << std::endl;
	}
*/
	// loop for the  number of turns asking of guesses
	while (!BCGame.isGameWon() && BCGame.getCurrentTry() <= MaxTries) {
		FText guess = getValidGuess();

		//Submit valid guess to the game
		FBullCowCount bullCowCount = BCGame.submitValidGuess(guess);

		printBack(bullCowCount);
		std::cout << std::endl;
	}

	printGameSummary();
	return;
}

// get a guess from the player
FText getValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText guess = "";
	do
	{
		int32 CurrentTry = BCGame.getCurrentTry();
		//std::cout << "Tries left: " << (BCGame.getMaxTries()+1 - CurrentTry) << std::endl;

		std::cout << "Try " << CurrentTry << " of " << BCGame.getMaxTries() << ". Enter your guess: ";
		//cin >> Guess;
		std::getline(std::cin, guess);

		Status = BCGame.checkGuessValidity(guess);
		switch (Status)
		{
			case EGuessStatus::Not_Isogram:
				std::cout << "Please enter a word without repeating letters.\n\r";
				std::cout << std::endl;
				break;
			case EGuessStatus::Not_Lowercase:
				std::cout << "Please enter all lowercase letters.\n\r";
				std::cout << std::endl;
				break;
			case EGuessStatus::Wrong_Length:
				std::cout << "Please enter a " << BCGame.getHiddenWordLength() << " letter word.\n\r";
				std::cout << std::endl;
				break;
			default:
				// Assume the guess is valid
				break;
		}
	} while (Status != EGuessStatus::OK);
	return guess;
}

// repeat the guess back to them
void printBack(FBullCowCount guess)
{
	//std::cout << "Your guess was: " << guess << std::endl;
	std::cout << "Bulls = " << guess.Bulls << "\t";
	std::cout << "Cows = " << guess.Cows;
	std::cout << std::endl;
}

bool askToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);

	//cout << "Is is y? " << (Response[0] == 'y');

	return (Response[0] == 'y' || Response[0] == 'Y');
}

void printGameSummary()
{
	if (BCGame.isGameWon()) {
		std::cout << "WELL DONE - YOU WIN!\n\r";
	} else {
		std::cout << "Better luck next time\n\r";
	}
}


