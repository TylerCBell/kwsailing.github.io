#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

string Converter(string line);
string Centerboard(string line, int found);
string Keelboat(string line, int found);
string Multihull(string line, int found);
string Offshore(string line, int found);
string Windsurfer(string line, int found);

int main() {
    fstream inFile;
    string line;
    string output;
    vector<string> input;

    inFile.open("Raw_Handicap_Points_Table.txt",ios::in);
    if(inFile.is_open()) cout << "inFile opened successfully" << endl;

    while(getline(inFile,line)) {
        input.push_back(line);
        inFile.ignore(1,'\n');
    }

    inFile.close();

    fstream outFile;
    outFile.open("Handicap_Points_Table.txt",ios::out);
    if(outFile.is_open()) cout << "outFile opened successfully" << endl;

    for(size_t i = 0; i < input.size(); i++) {
        output = Converter(input[i]);
        outFile << output << endl;
    }

    outFile.close();

    return 0;
}

string Converter(string line) {
    int found;
    vector<string> boat = {",Centerboard", ",Keelboat", ",Multihull", ",Offshore", ",Windsurfer"};
    
    found = line.find(",Centerboard");

    for(size_t i = 0; i < boat.size(); i++) {
        found = line.find(boat[i]);
        if(found > -1) {
            switch(i) {
                case 0:
                    line = Centerboard(line,found);
                    break;
                case 1:
                    line = Keelboat(line,found);
                    break;
                case 2:
                    line = Multihull(line,found);
                    break;
                case 3:
                    line = Offshore(line,found);
                    break;
                case 4:
                    line = Windsurfer(line,found);
                    break;
                default:
                    break;
            }
        }
    }

    return line;
}

string BoatName(string line, int found) {
    char boatNameChars[30];
    string boatName = "";

    for(int i = 0; i < found; i++) {
        if(line[i] == ',') boatNameChars[i] = ' ';
        else boatNameChars[i] = line[i];

        boatName = boatName + boatNameChars[i];
    }

    return boatName;
}

string BoatCode(string line, int found) {
    char boatCodeChars[30];
    string boatCode = "";
    int i = found;

    while(true) {
        if(line[i] == ',') break;
        
        boatCodeChars[i] = line[i];

        boatCode = boatCode + boatCodeChars[i];

        i++;
    }

    return boatCode;
}

string BoatDPN(string line, int found) {
    char boatDPNChars[30];
    string boatDPN = "";
    int i = found;

    while(true) {
        if(line[i] == ',' || line[i] == ']' || line[i] == ')') break;
        
        if(line[i] == '[' || line[i] == ']' || line[i] == '(' || line[i] == ')');
        else {
            boatDPNChars[i] = line[i];
            boatDPN = boatDPN + boatDPNChars[i];
        }
        
        i++;
    }

    return boatDPN;
}

string ReturnLine(string boatName, string boatClass, string boatCode, string boatDPN) {
    return boatName + "," + boatClass + "," + boatCode + "," + boatDPN;
}

string Centerboard(string line, int found) {
    string boatName = BoatName(line,found);
    string boatClass = "Centerboard";
    string boatCode = BoatCode(line,found + 13);
    string boatDPN = BoatDPN(line,found + 14 + boatCode.length());

    return ReturnLine(boatName, boatClass, boatCode, boatDPN);
}

string Keelboat(string line, int found) {
    string boatName = BoatName(line,found);
    string boatClass = "Keelboat";
    string boatCode = BoatCode(line,found + 10);
    string boatDPN = BoatDPN(line,found + 11 + boatCode.length());
    
    return ReturnLine(boatName, boatClass, boatCode, boatDPN);
}

string Multihull(string line, int found) {
    string boatName = BoatName(line,found);
    string boatClass = "Multihull";
    string boatCode = BoatCode(line,found + 11);
    string boatDPN = BoatDPN(line,found + 12 + boatCode.length());
    
    return ReturnLine(boatName, boatClass, boatCode, boatDPN);
}

string Offshore(string line, int found) {
    string boatName = BoatName(line,found);
    string boatClass = "Offshore";
    string boatCode = BoatCode(line,found + 10);
    string boatDPN = BoatDPN(line,found + 11 + boatCode.length());
    
    return ReturnLine(boatName, boatClass, boatCode, boatDPN);
}

string Windsurfer(string line, int found) {
    string boatName = BoatName(line,found);
    string boatClass = "Windsurfer";
    string boatCode = BoatCode(line,found + 12);
    string boatDPN = BoatDPN(line,found + 13 + boatCode.length());
    
    return ReturnLine(boatName, boatClass, boatCode, boatDPN);
}