//
// Created by ZAINANA Salma on 22/11/2021.
//


/* this code is supposed to keep the data permanently
 * if something happened.
*/

#include <fstream>
#include <iostream>

using namespace std;




int main(){
    char line[200];

    /* we open a file for both reading and writing purposes
     * ios::out
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
}

