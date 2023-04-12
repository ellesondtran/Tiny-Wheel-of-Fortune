//Elleson Tran
//Roberts
//Tiny Wheel of Fortune 3.0
//FINAL


#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;


//function that creates a string that are blanks of the original string
//returns the new string
string hideanswer(string &tempString, string word){
  for(int x = 0; x < word.length(); x++){//for each letter
    if(word.at(x) != ' '){//if the letter is a letter
      tempString.at(x) = '_';//make it a dash
    }
    if(word.at(x) == ' '){//if the letter is a space
      tempString.at(x) = ' ';//keep it a space
    }

  }
  return tempString;
}

//checks if the letter the user guesses is in the string
//returns true if it is, false if it isnt
bool vannaWhite(string word,string hiddenWord, char letter, bool &answer){
  for(int x = 0; x < word.length(); x++){//for each Letter
    if(word.at(x) == letter){//if any of the letters is the same as the users guess
      answer = true;//returns true
      return answer;
    }
  }
  answer = false;//if none, return false
  return answer;
}

//displays the hidden blanks with spaces in between and the category
void showHidden(string hiddenWord, string category){
  cout<<endl;
  for(int x = 0; x < hiddenWord.length(); x++){
    cout<<hiddenWord.at(x)<<" ";//adds a space after each character
  }
  cout<<endl<<"Category: "<<category;
}


//asks the user what letter
//returns the user's answer as a capital letter
char makeGuess(char letter){
  cout<<endl<<"Letter: ";
  cin>>letter;
  letter = toupper(letter);//capitalizes the letter
  return letter;
}


//function that chooses a random word and the corresponding category with it
const vector<string> words = {"ELEPHANT", "MONSTER TRUCK", "APPLE PIE", "OVERALLS", "PLAYSTATION"};
const vector<string> categories = {"ANIMALS", "VEHICLES", "FOOD", "CLOTHING", "GAMES"};

void setanswerAndCategory(string &word, string &category){
  int randomNum = rand()%6;
  word = words[randomNum];
  category = categories[randomNum];

}

//function that checks if the user has already guessed this
bool previousGuesse(char letter, vector<char> previousLetters, bool previousGuess, int guesses){
  if(guesses == 1){//skips the first guess
    previousGuess = false;
    return previousGuess;
  }
  for(int x = 0; x < previousLetters.size() - 1; x++){
    if(previousLetters[x] == letter){//returns true if any of the previous guesses equal the current guess
      previousGuess = true;
      return previousGuess;
    }
  }
  previousGuess = false;//returns false if its a new guess
  return previousGuess;
}


int main() {
  srand(time(0));
  string word = "";
  string category = "";
  bool answer;
  bool previousGuess;
  int guesses = 0;
  vector<char> previousLetters;

  //generates the random word and corresponding category
  setanswerAndCategory(word, category);

  //generates the blank version of the word
  string tempString = word; //temporary copy of the word
  string hiddenWord = hideanswer(tempString, word); //makes the temporary copy into blanks

  int mistake = 5;

  while(mistake > 0){
    cout<<endl<<"-=-==-=-=-=-=-=-=-=-=-=-=-=-";
    cout<<endl<<"Mistakes remaining: "<<mistake;
    showHidden(hiddenWord, category);//displays the hidden work, blanks and category

    char tempLetter;
    char letter = makeGuess(tempLetter);//asks the user for the letter
    previousLetters.push_back(letter);

    guesses = guesses + 1;//only for the first guess


    if(previousGuesse(letter, previousLetters, previousGuess, guesses) == true){//if the current guess is the same as any of the previous guesses
      while(previousGuesse(letter, previousLetters, previousGuess, guesses) == true){//keeps going if it is the same, stays in this block of code
        cout<<endl<<"Already guessed that one!";
        letter = makeGuess(tempLetter);//asks the user for the letter
      }
      //only adds the letter to the vector once its not a duplicate
      previousLetters.push_back(letter);//adds the letter into the vector
    }



    if(vannaWhite(word, hiddenWord, letter, answer) == true){//if the user guessed right
      for(int x = 0; x < hiddenWord.length(); x++){//for each Letter
        if(word.at(x) == letter){//if the letter of the word is the same as the user's guess, it will change the hidden word
          hiddenWord.at(x) = letter;
        }
      }
    }
    if(vannaWhite(word, hiddenWord, letter, answer) == false){//if the user guessed wrong
      cout<<"Letter "<<letter<<" was not found!"<<endl;
      mistake = mistake - 1;//subtracts a mistake
    }

    if(hiddenWord == word){//if the user wins!
      showHidden(hiddenWord, category);
      cout<<endl<<"Great Job!";
      mistake = -1;//automaticaly stops the game (its -1, so the "the puzzle was..." part doesnt get printed)
    }
  
  }
  if(mistake == 0){//if the user lost
    cout<<endl<<"The puzzle was: "<<word;
  }
  

}