#include <iostream>
#include <fstream>
#include <sstream>


bool is_empty(std::ifstream& file);
bool is_decimal_literal(const std::string& word, int line);
bool is_octal_literal(const std::string& word, int line);
bool is_hex_literal(const std::string& word, int line);
bool is_binary_literal(const std::string& word, int line);

int main(int argc, char *argv[]) {

    //Check for file with specific name
    if (argc < 2) {
        std::cout << "NO SPECIFIED INPUT FILE NAME." << std::endl;
        return 1;
    }

    //Check if you can open the file
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "CANNOT OPEN THE FILE myfile" << std::endl;
        return 1;
    }

    //Check if the file is empty
    if (is_empty(inputFile)) {
        std::cout << "File is empty." << std::endl;
        inputFile.close();
        return 0;
    }

    //Reset file to the beginning
    inputFile.clear();
    inputFile.seekg(0);

    //variables
    int totalLines = 0;
    int numWords = 0;
    int decLiterals = 0;
    int hexLiterals = 0;
    int octLiterals = 0;
    int binLiterals = 0;
    std::string line;

    //Read the file line by line
    while (getline(inputFile, line)) {
        totalLines++; //add 1 every time a new line is read

        //Create string stream to extract words
        std::stringstream iss(line);
        std::string word;
        //extract each word in the stream
        while (iss >> word) {
            numWords++; //increment each word

            //Check if the each word is a decimal, octcal, hexadecimal, or binary literal
            if (is_decimal_literal(word, totalLines)) {
                decLiterals++;
            } else if (is_octal_literal(word, totalLines)) {
                octLiterals++;
            } else if (is_hex_literal(word, totalLines)) {
                hexLiterals++;
            } else if (is_binary_literal(word, totalLines)) {
                binLiterals++;
            }
        }
    }

    //Print the results
    std::cout << "Total Number of Lines: " << totalLines << std::endl;
    std::cout << "Number of Words: " << numWords << std::endl;
    std::cout << "Number of Decimal Literals: " << decLiterals << std::endl;
    std::cout << "Number of Hexadecimal Literals: " << hexLiterals << std::endl;
    std::cout << "Number of Octal Literals: " << octLiterals << std::endl;
    std::cout << "Number of Binary Literals: " << binLiterals << std::endl;

    return 0;
}

//Function to check if file is empty. It peeks for the first letter
bool is_empty(std::ifstream& file) {
    return file.peek() == std::ifstream::traits_type::eof();
}

//Function to look for decimal literals.
bool is_decimal_literal(const std::string& word, int line) {
    //First Checks the most basic rules word needs to be a decimal literal
    if (word.length() > 1 && (word[0] > '0' && word[0] <= '9')) {
        //checks that all the characters are digiits
        for (size_t i = 1; i < word.length(); ++i) {
            if (std::isalpha(word[i]) || !std::isdigit(word[i])) {
                std::cout << "Incorrect Decimal Literal " << word << " at Line: " << line << std::endl;
                return false;
            }
        }
        return true;
    }
    return false;
}

//Function to look for Octal literals.
bool is_octal_literal(const std::string& word, int line) {
   //First Checks the most basic rules word needs to be a Octal literal 
    if (word.length() > 1 && word[0] == '0' && (word[1] >= '0' && word[1] <= '7')) {
        //checks that all characters are beteween '1' and '7'
        for (size_t i = 1; i < word.length(); ++i) {
            if (word[i] < '0' || word[i] > '7') {
                std::cout << "Incorrect Octal Literal " << word << " at Line: " << line << std::endl;
                return false;
            }
        }
        return true;
    }
    return false;
}

//Function to look for Hexical literals
bool is_hex_literal(const std::string& word, int line) {
    //First Checks the most basic rules word needs to be a Hexical literal 
    if (word.length() > 2 && word[0] == '0' && (word[1] == 'x' || word[1] == 'X')) {
        //checks that all characters are hexadecimal characters
        for (size_t i = 2; i < word.length(); ++i) {
            if (!std::isxdigit(word[i])) {
                std::cout << "Incorrect Hexadecimal Literal " << word << " at Line: " << line << std::endl;
                return false;
            }
        }
        return true;
    }
    return false;
}

//Function to look for Ninary literals
bool is_binary_literal(const std::string& word, int line) {
    //First Checks the most basic rules word needs to be a binary literal 
    if (word.length() > 2 && word[0] == '0' && (word[1] == 'b' || word[1] == 'B')) {
        //checks that all characters are numbers '0' and '1'
        for (size_t i = 2; i < word.length(); ++i) {
            if (word[i] != '0' && word[i] != '1') {
                std::cout << "Incorrect Binary Literal "<< word << " at Line: " << line << std::endl;
                return false; 
            }
        }
        return true;
    }
    return false;
}