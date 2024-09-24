#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// Function prototypes at the top of the file for function decomposition

/**
 * Print instructions for using the program.
 */
void printMenu();
/**
 * Returns the 0-based index in the English alphabet where `c` appears,
 * or -1 if `c` is not an uppercase letter in the alphabet.
 *
 * For example:
 *  - `findIndexInAlphabet('A')` returns 0
 *  - `findIndexInAlphabet('D')` returns 3
 *  - `findIndexInAlphabet('+')` returns -1
 *  - `findIndexInAlphabet('a')` returns -1
 */
int findIndexInAlphabet(char c);
/**
 * Returns `c` rotated by `amount` many characters forward. If we run out
 * of letters in the alphabet, wrap around back to 'A'. This method
 * assumes that `c` is an uppercase letter.
 * For example:
 *  - `rot('A', 0)` returns 'A'
 *  - `rot('A', 1)` returns 'B'
 *  - `rot('Z', 1)` returns 'A'
 *  - `rot('A', 10)` returns 'K'
 *  - `rot('J', 25)` returns 'I'
 */
char rot(char c, int amount);
/**
 * Returns a new string in which every character has been rotated by `amount`
 * letters. Lowercase letters are converted to uppercase and rotated.
 * Non-alphabetic characters are left alone.
 * For example:
 *  `rot("A", 0)` returns "A"
 *  `rot("AA", 3)` returns "DD"
 *  `rot("HELLO", 0)` returns "HELLO"
 *  `rot("HELLO", 1)` returns "IFMMP"
 *  `rot("oh HEL-LO!", 1)` returns "PI IFM-MP!"
 */
string rot( string line, int amount); 
string vigenerRot(string line, string rawKey); // initiates Task: Vigenère Cipher Encoder 
string toUpperKey(string key); // converts lowercase key to uppercase
vector<string> splitText(string text); // splits input text to words
bool isInDictionary( string word,  vector <string> dictionary); // checks if word is in dictionary

int main() {
    string command;
    string text;
    string key;
    int rotNumb;
    ifstream inFS;
    vector <string> dictionary;

    inFS.open("dictionary.txt"); // opens dictionary.txt file
    while(inFS >> key){ // reads every word form the file
        for(auto c : key){ 
            c = toupper(c); 
        }
        dictionary.push_back(key); // puts every uppercase key to dictionary string
    }
    inFS.close();

    cout << "Welcome to Ciphers!" << endl;
    cout << "-------------------" << endl;
    cout << endl;

    do {
        printMenu();
        cout << endl
             << "Enter a command (case does not matter): ";

        // Use getline for all user input to avoid needing to handle
        // input buffer issues relating to using both >> and getline
        getline(cin, command);
        cout << endl;

        if(command == "c" || command == "C"){ // according to user's input initiates the task
            cout << "Enter the text to encrypt:"<< endl;
            getline(cin,text);
            cout<<endl<<"Enter the number of characters to rotate by:"<<endl<<endl;
            cin >> rotNumb;
            cin.ignore(10000, '\n'); // clear input buffer
            string rotString = rot(text, rotNumb);
            cout<< rotString << endl;
        
        }
        else if(command == "v" || command == "V"){ // v means Vigenere cipher encryption 
            cout << "Enter text to encrypt:" << endl;
            getline(cin, text);
            cout << "Enter the Vigenère key:" << endl;
            getline(cin, key);
            string vString = vigenerRot(text,key); // Perform encryption
            cout<< vString << endl;

        }
        else if (command == "d" || command == "D") { // d means Caeser cioher decryption
            cout << "Enter the text to Caesar-cipher decrypt:" << endl;
            getline(cin, text);

            vector<string> decrypt;
            bool foundDecryption = false;

            for (int shift = 0; shift < 26; ++shift) { // checks all the possible shifts
                string decryptedWord = rot(text,26-shift);
                auto words = splitText(decryptedWord);
                int wordsCount = 0;

                for (auto word : words) { 
                    if(isInDictionary(word, dictionary)){
                        ++wordsCount; // counts number of matched words
                    }
                }

                if (wordsCount > words.size() / 2) { // if more than half of words matched, all thw words get printed
                    foundDecryption = true;
                    decrypt.push_back(decryptedWord);   
                }
            }

            if(!decrypt.empty()){
                for(auto reverse = decrypt.rbegin(); reverse != decrypt.rend(); ++reverse){ //reverse the output order
                cout<< *reverse << endl;
                }
            }

            if(!foundDecryption) { // if not decryption was found
                cout << "No good decryptions found" << endl;
            }
        }
        cout << endl;

    } while (!(command == "x" || command == "X"));//exits progaram

    return 0;
}

void printMenu() {
    cout << "Ciphers Menu" << endl;
    cout << "------------" << endl;
    // Caesar Ciphers
    cout << "C - Encrypt with Caesar Cipher" << endl;
    cout << "D - Decrypt Caesar Cipher" << endl;
    // Vigenere
    cout << "V - Encrypt with Vigenère" << endl;
    // Utility
    cout << "X - Exit Program" << endl;
}

int findIndexInAlphabet(char c) {
    if(c < 'A' || c > 'Z'){
    return -1;
}
return c - 'A';
}

char rot(char c, int amount) { // rotates single character
    if(c >= 'A' && c <= 'Z'){
        return 'A' + (c - 'A' + amount)%26; // makes rotation around 'A' tp 'Z'
    }
    return c; // returns unchanged if it is not letter
}

string rot(string line, int amount) { //rotates whole string
    string rotLine;
    for(char c : line){
        if(isalpha(c)){
            char upperC = toupper(c); // converts each char to uppercase
            rotLine += rot(upperC, amount); //applies rotation
        }
        else{
            rotLine += c;
        }
    }
    return rotLine;
}

string toUpperKey(string key){ // converts key to uppercase letters
    string result;
    for(char k : key){
        if(isalpha(k)){ // checks if it character
            result += toupper(k);
        }
    }
    return result;
}

string vigenerRot(string line, string rawKey){
    string key = toUpperKey(rawKey);
    if(key.empty()){
        return line; // returns unchanged line if key is empty
    }
    int keyIndex = 0;
    string rotLine;

        for(char c : line){
            if(isalpha(c)){
                char upperC = toupper(c);
                int shift = key[keyIndex % key.size()] - 'A'; //calculates rotation amount
                rotLine += rot(upperC, shift); //applies Vigenere rotation
                keyIndex++; //moves to the next char in key
            }
            else{
                rotLine += c;
            }
        }
    
    return rotLine;
}

vector<string> splitText(string text){
    vector <string> words;
    string word;
    for(char c : text){
        if(isalpha(c)) {
            word += toupper(c); 
        }
        else if (!word.empty()){
            words.push_back(word); // Adds the word to the list when  char is not alphabetic
            word.clear(); //resets the word fot the next one
        }
    }
    if(!word.empty()){
        words.push_back(word); // Adds the last word if there is non-aplhabetic char
    }
    return words;
}   

bool isInDictionary(string word, vector <string> dictionary){
    for(auto dictWord : dictionary){
        if(word == dictWord){
            return true; //found word in Dictionary
        }
    }
    return false; // no match
}
