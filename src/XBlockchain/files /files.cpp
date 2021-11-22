//
// Created by ZAINANA Salma on 22/11/2021.
//


/* this code is supposed to keep the data permanently
 * if something happened.
*/

#include <fstream>
#include <iostream>

using namespace std;

int write(fstream file,char line = NULL ){

    file.open("filename.txt", ios::out);
    if (line == NULL){
        char line[1000000];
        cout<<" Text you want to write on the file: " <<endl;
        cin.getline(line, sizeof(line));
        file <<line << endl;}
    else{
        file <<line << endl;}
    }
    file.close();
    return 0;
}

int read(fstream file){
    char line[100000];
    file.open("filename.txt", ios::in );
    file >> line ;
    cout << line <<endl;
    file.close();
    return 0;
}

int main(){
    char line[100000];

    /* we open a file for both reading and writing purposes
     */

    fstream file;
    file.open("file.txt", ios::out | ios::in );

    /* we ask you what you want to write
     */
    cout<<" Text you want to write on the file: " <<endl;
    cin.getline(line, sizeof(line));

    /*we write on the file
     */
    file <<line << endl;

    /*we read from the file
     */
    file >> line ;
    cout << line <<endl;

    /* we close because we are a good programmers
     */
    file.close();

    return 0 ;
}

