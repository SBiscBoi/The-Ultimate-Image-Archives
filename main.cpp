#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    const int width = 1920;
    const int height = 1080;


    string input = "1"; //input goes here

    //fibonacci part
    unsigned int num1 = 0;
    unsigned int num2 = 1;

    while (input.length() != (width * height * 9)) { //let's try * 9 instead of * 3
        input.append(input + to_string(num1));
        unsigned int temp = num1 + num2;
        num1 = num2;
        num2 = temp;
        if (input.length() > (width * height * 9)) {
            input = input.substr(0, width * height * 9);
        }
    }

    //now the long re-assignment part
    int pos = 0;

    while (pos < input.length()) {
        if (stoi(input.substr(pos, 3)) >= 256) {
            string additive = to_string(stoi(input.substr(pos, 3)) % 256);
            while (additive.length() < 3) {
                additive.insert(0, "0");
            }
            input = input.substr(0, pos) + additive + input.substr(pos + 1); //probably better way to do this
        }
        pos += 3;
    }

    //re-assignment done, reset pos
    pos = 0;

    //now for the hard part
    vector<vector<string>> vect(
        (width * height),
        vector<string>(3, "000") //column count, default "empty" value
    );

    //int arr[width * height][3];

    for (int row = 0; row < (width*height); row++) {
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
    //ofstream arrayFile("C:\\Users\\Owner\\Desktop\\The-Ultimate-Image-Archives-master\\The-Ultimate-Image-Archives-master\\arrayCont.txt");

    if (!arrayFile)
    {
        cout << "Error in creating file!!!";
        return 0;
    }

    for (int i = 0; i < (width*height); i++) {
        arrayFile << std::setfill('0') << std::setw(3) << stoi(vect[i][0]) % 256 << " ";
        arrayFile << std::setfill('0') << std::setw(3) << stoi(vect[i][1]) % 256 << " ";
        arrayFile << std::setfill('0') << std::setw(3) << stoi(vect[i][2]) % 256 << " ";
    }

    arrayFile.close();

    return 0;
}