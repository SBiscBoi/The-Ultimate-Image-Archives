#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
    const int width = 1920;
    const int height = 1080;


    string input = "1"; //input goes here

    cout << input.max_size();

    //fibonacci part
    int num1 = 0;
    int num2 = 0;

    while(input.length() != (width*height*3)){
        input.append(input + to_string(num1));
        int temp = num1 + num2;
        num1 = num2;
        num2 = temp;
        if(input.length() > (width*height*3)){
            input = input.substr(0, width*height*3);
        }
    }

    //now the long re-assignment part
    int pos = 0;

    while(pos < input.length()){
        if(stoi(input.substr(pos, pos+3)) >= 256){
            input = input.substr(0, pos) + to_string(stoi(input.substr(pos, pos+3)) % 256) + input.substr(pos+1); //probably better way to do this
        }
        pos += 3;
    }

    //re-assignment done, reset pos
    pos = 0;

    //now for the hard part
    int arr[width*height][3];

    for(int row = 0; row < sizeof arr; row++){
        for(int col = 0; col < sizeof arr[0]; col++){
            arr[row][col] = stoi(input.substr(pos, pos+3));
            pos += 3;
        }
    }

    //write to file for python script to use
    fstream arrayFile;
    arrayFile.open("arrayCont.txt", ios::out);
    //ofstream arrayFile("C:\\Users\\Owner\\Desktop\\The-Ultimate-Image-Archives-master\\The-Ultimate-Image-Archives-master\\arrayCont.txt");

    if(!arrayFile)
    {
       cout<<"Error in creating file!!!";
       return 0;
    }

    for(int i = 0; i < sizeof arr; i++){
        arrayFile << arr[i] << " ";
    }

    arrayFile.close();

    return 0;
}