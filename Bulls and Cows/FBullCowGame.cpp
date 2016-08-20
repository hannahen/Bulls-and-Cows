#pragma once
#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map


using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const {
    TMap<int32,int32> WordLengthToMaxTries { {3,5}, {4,5}, {5,6}, {6,7}, {7,9}, {8,10} };
    return WordLengthToMaxTries[GetHiddenWordLength()];
}

void FBullCowGame::Reset()
{
    const FString HIDDEN_WORD = "planet";
    MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
    bGameIsWon = false;
    return;
}




EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!IsIsogram(Guess)) // if the guess isn't an isogram
    {
        return EGuessStatus::Not_Isogram;
    }
    else if (!IsLowercase(Guess)) // if the guess isn't all lowercase
    {
        return EGuessStatus::Not_Lowercase;
    }
    else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
    {
        return EGuessStatus::Wrong_Length;
    }
    else
    {
        return EGuessStatus::OK;
    }
}


// receives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

    // loop through all letters in the hidden word
    for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
        // compare letters against the guess
        for (int32 GChar = 0; GChar < WordLength; GChar++) {
            // if they match then
            if (Guess[GChar] == MyHiddenWord[MHWChar]) {
                if (MHWChar == GChar) { // if they're in the same place
                    BullCowCount.Bulls++; // incriment bulls
                }
                else {
                    BullCowCount.Cows++; // must be a cow
                }
            }
        }
    }
    if (BullCowCount.Bulls == WordLength) {
        bGameIsWon = true;
    }
    else
    {
        bGameIsWon = false;
    }
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
    //treat 0 or 1 letter words as isograms
    if(Word.length() <= 1 ){ return true; }

    // set up map
    TMap<char,bool> LetterSeen;

    for (auto Letter : Word){ // loop thru every letter in the guess
        Letter = tolower(Letter); //handle mixed case

        if(LetterSeen[Letter] == true){ return false; }
        else { LetterSeen[Letter] = true; }

    }
    return true;
}

bool FBullCowGame::IsLowercase(FString Word) const {
    for(auto Letter : Word){
        if(!islower(Letter) || isspace(Letter)){
            return false;
        }
    }
    return true;
}