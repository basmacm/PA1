// parseURL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;


string findToken(string StringToParse, int& CurrentIndex, char StopChar, char StopChar2) {

    string token = "";
    while (StringToParse[CurrentIndex] != 0 && StringToParse[CurrentIndex] != StopChar && StringToParse[CurrentIndex] != StopChar2) {
        token += StringToParse[CurrentIndex];
        CurrentIndex++;
    }
    return token;
}

bool validateProtocol(string p) {
    if (p.compare("http") != 0 && p.compare("https") != 0 && p.compare("ftp") != 0 && p.compare("ftps") != 0) {
        return false;
    }
    return true;
}
//	Domain: must be of the form <x>.<y>.<z>, and z must be one of com, net, edu, biz, gov.
bool validateDomain(string p) {
    string x = "", y = "", z = "";
    int currentIndex = 0;

    x= findToken(p, currentIndex, '.', '.');
    currentIndex++;
    y = findToken(p, currentIndex, '.', '.');
    currentIndex++;
    z = findToken(p, currentIndex, '.', '.');
    
    if (x.length() == 0 || y.length() == 0 || z.length() == 0) {
        return false;
    }
    if (z.compare("com") != 0 && z.compare("net") != 0 && z.compare("edu") != 0 && z.compare("biz") != 0 && z.compare("gov") != 0) {
        return false;
    }
    return true;
}

//character and a number between 1 to 65535
bool validatePort(string port) {
    int num = std::atoi(port.c_str());
    if (num<1 || num>65535) {
        return false;
    }
    return true;
}


int main()
{
    string URL = "", protocol = "", domain = "", port= "", filePath = "", parameters = "";
    bool valProtocol = true, valDomain = true, valPort = true, valFilePath = true, valParameters = true, valURL = true;
    int currentIndex = 0;
    cout << "Please type a full URL here\n";
    cin >> URL;
    int length = URL.length();

    
    //https://cs.utdallas.edu:80/directory/faculty/people.html?name=Robert
    //invalid

    protocol = findToken(URL, currentIndex, ':', ':');

    if (currentIndex < length - 3) {
        currentIndex++;
        if (URL[currentIndex] == '/' && URL[currentIndex + 1] == '/') {
            currentIndex = currentIndex + 2;
        }
        else valURL = false;
    }
    domain = findToken(URL, currentIndex, ':', '/');

    //find port (if exists)
    if (URL[currentIndex] == ':') {
        currentIndex++;
        port = findToken(URL, currentIndex, '/', '/');
    }
    //find file path

    if (URL[currentIndex] == '/') {
        currentIndex++;
        filePath = findToken(URL, currentIndex, '?', '?');
    }

    //find parameter
    if (URL[currentIndex] == '?') {
        currentIndex++;
        parameters = findToken(URL, currentIndex, '#', '#');
    }

    valProtocol = validateProtocol(protocol);
    valDomain = validateDomain(domain);
    valPort = validatePort(port);
  
    if (valProtocol == false || valDomain == false || valPort == false) {
        cout << "Invalid URL with following erroneous components:"<< endl; 
        if (valProtocol == false){
            cout << "Protocol:  " << protocol << " is an invalid protocol" << endl;
        }
        if (valDomain == false) {
            cout << "Domain:   "<< domain << " is an invalid domain" << endl;
        }
        if (valPort == false) {
            cout << "Port:   " << port << " port number must be between 1 and 65535" << endl;
        }
    }
    else {
        cout << "Protocol:   " << protocol << endl;
        cout << "Domain:   " << domain << endl;
        cout << "Port:   " << port << endl;
        cout << "File path:   " << filePath << endl;
        cout << "Parameters:   " << parameters << endl;
    }

    return 0;
}



