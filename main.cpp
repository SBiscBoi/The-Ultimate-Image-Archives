#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>

using namespace std; //could be seen as bad practice but i'm pretty new to c++ so give me a break

int main() {
    const int width = 1920; 
    const int height = 1080; 
    const unsigned int totalDigits = width * height * 9; //width*height*9 because we need 3 numbers per pixel, and each number is 3 digits long

    string input; //inputFile goes here
    ifstream inputFile ("inputFile.txt");
    if(!inputFile){ //error handling
        cout << "unable to read input from file!" << endl;
        exit(-1); //0 = success, -1 = input file error, -2 = output error
    }

    getline(inputFile, input); //store input as string

    //format input to writable format 
    while (input.length() % 3 != 0) {
        input = "0" + input; //append 0's to front not back
    }
    
    int pos = 0; //position in string
    while (pos < input.length()) {
        if ((stoi(input.substr(pos, 3))) > 255) { //every 3 digit number cannot be greater than 255 as for 8-bit RGB values cannot exceed 255
            input = input.substr(0, pos) + "255" + input.substr(pos+1); //if greater than 255, simply set to 255. (NOTE: this could be changed for added "randomness" but it's a little needless)
        }
        pos += 3; //foward position by 3
    }

    //generate random number with first 3 input characters as seed
    string seedStr = input.substr(0, 3); //only use first 3 digits because no matter how small the input is there will always be at least 3 digits at this point
    int seed = stoi(seedStr); //store as int
    srand(seed); //set seed
    
    string additive = ""; //additive, is the string being appended to the input string to produce the colors
    while (input.length() < totalDigits) {
        additive = to_string(rand() % 256); //same rules as earlier, must be less than 256
        while (additive.length() < 3) {
            additive = additive.insert(0, "0"); //if less than 3 digits long, pad with 0's
        }
        input += additive; //append
    }
   
    //re-assignment done, reset pos
    pos = 0;

    //now for the hard part
    vector<vector<string>> vect(
        (width * height),
        vector<string>(3, "000") //column count, default "empty" value
    );

    for (int row = 0; row < (width * height); row++) {
        for (int col = 0; col < 3; col++) {
            if (pos < totalDigits) {
                vect[row][col] = input.substr(pos, 3); //set value at index to 3-digit long section of input string
                pos += 3; //foward to next 3-digit number
            }
        }
    }

    //write to file for python script to use
    fstream arrayFile;
    arrayFile.open("arrayCont.txt", fstream::out);

    if (!arrayFile) //error handling part 2
    {
        cout << "Error in creating file!!!";
        exit(-2);
    }

    for (int i = 0; i < (width * height); i++) {
        //i can't exactly tell why it's formatted like this but it works so I won't ask questions
        //write parts of 2D Vector to arrayFile
        arrayFile << std::setfill('0') << std::setw(3) << stoi(vect[i][0]) % 256 << " "; 
        arrayFile << std::setfill('0') << std::setw(3) << stoi(vect[i][1]) % 256 << " ";
        arrayFile << std::setfill('0') << std::setw(3) << stoi(vect[i][2]) % 256 << " ";
    }

    arrayFile.close(); //always clean up after yourself

    exit(0);
}