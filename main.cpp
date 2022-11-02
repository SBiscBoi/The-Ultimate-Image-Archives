#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    const int width = 1920; //TODO: set to read from file later
    const int height = 1080; //TODO: set to read from file later
    const unsigned int totalDigits = width * height * 9;

    string input = "134329874183275897480195717482378490783965871283974873289471829374089173289478190237589742358978957123894789321748917328497218390472189748912738497128904783912748902137489327489123708947892078978979780978978097897089787987987098709870987908709870987897897098797980798879879878907098709879879834718092374892307493274079547432890572389475898768768768767868768678687622122233344454545454545454545465465498876789678678678678678999999999999999999999999999999768765976457654976555656565656567565656565656565656565565656554583490583490583490589340589864230589724350987234545094309834298043289023489024389043289024839082439048392032489038294098324098043289240389043298340292038482390490849024908934049829048290348902384902384914820398520398523095890352488243095824309584039584203958209358024358954303459678908345762345723958"; //input goes here

    //fibonacci part
    unsigned int num1 = 0;
    unsigned int num2 = 1;
    int lastNumLength;
    while (input.length() != (totalDigits)) { //let's try * 9 instead of * 3
        input.append(input + to_string(num1));
        unsigned int temp = num1 + num2;
        num1 = num2;
        num2 = temp;
        if (input.length() > (totalDigits)) {
            const int lastNumLength = to_string(num2).length(); //can be num2 or temp, at this point both are the same value
            input = input.substr(0, ((totalDigits) - lastNumLength) + 1);
            break;
        }
    }

    while (input.length() != (totalDigits)) { //second loop, could probably be optomized but this should work for now
        input += "0";
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
    //ofstream arrayFile("C:\\Users\\Owner\\Desktop\\The-Ultimate-Image-Archives-master\\The-Ultimate-Image-Archives-master\\arrayCont.txt");

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