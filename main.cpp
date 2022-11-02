#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>

using namespace std;

int main() {
    const int width = 1920; //TODO: set to read from file later
    const int height = 1080; //TODO: set to read from file later
    const unsigned int totalDigits = width * height * 9;

    string input = "13432987418345762345723958"; //input goes here

    //format input to readable format 
    while (input.length() % 3 != 0) {
        input += "0";
    }
    
    int pos = 0;
    while (pos < input.length()) {
        if ((stoi(input.substr(pos, 3))) > 255) { //this part causes error?
            input = input.substr(0, pos) + "255" + input.substr(pos+1);
        }
        pos += 3;
    }

    //generate random number with input as seed
    cout << input.substr(0,3);
    string seedStr = input.substr(0, 3);
    int seed = stoi(seedStr);
    srand(seed); //set seed
    
    string additive = "";
    while (input.length() < totalDigits) {
        additive = to_string(rand() % 256);
        while (additive.length() < 3) {
            additive = additive.insert(0, "0");
        }
        input += additive;
    }
   
    //re-assignment done, reset pos
    pos = 0;

    //now for the hard part
    vector<vector<string>> vect(
        (width * height),
        vector<string>(3, "000") //column count, default "empty" value
    );

    //int arr[width * height][3];

    for (int row = 0; row < (width * height); row++) {
        for (int col = 0; col < 3; col++) {
            if (pos < 18662400) {
                vect[row][col] = input.substr(pos, 3);
                pos += 3;
            }
        }
    }

    //write to file for python script to use
    fstream arrayFile;
    arrayFile.open("arrayCont.txt", fstream::out);

    if (!arrayFile)
    {
        cout << "Error in creating file!!!";
        return 0;
    }

    for (int i = 0; i < (width * height); i++) {
        arrayFile << std::setfill('0') << std::setw(3) << stoi(vect[i][0]) % 256 << " ";
        arrayFile << std::setfill('0') << std::setw(3) << stoi(vect[i][1]) % 256 << " ";
        arrayFile << std::setfill('0') << std::setw(3) << stoi(vect[i][2]) % 256 << " ";
    }

    arrayFile.close();

    return 0;
}