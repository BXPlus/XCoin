//
// Created by Lio Elalouf--Lewiner on 29/11/2021.
//

#include <openssl/md5.h>

std::string md5(const std::string &string) {
    unsigned long l = string.size();

    const unsigned char * constStr =
            reinterpret_cast<const unsigned char *>
            (string.c_str());
    // we need to use unsigned char because md5
    // only accepts unsigned char
    // This reinterpret_cast is fine on most platforms,
    // unless two-s complement negative numbers are used

    unsigned char res[17]; // 16 + 1 null byte
    MD5(constStr, l, res);

    // res is an array of bytes corresponding to the md5:
    // MD5("TEST") = {0x03, 0x3b, 0xd9, ..., 0xbf}

    // convert result of MD5 into ASCII representation
    // ex. 0x55 -> 0x53 0x53 "55"
    // ex. 0x3b -> 0x51 0x98 "3b"
    char hex_as_string[33]; // 32 + 1 null byte

    for (unsigned int i=0; i<16; i++){
        // it's not good practice to use sprintf usually
        // but here we hopefully count the bits correctly

        // if you want capital letters for the hexadecimal values
        // e.g. 0x3b -> 0x51 0x66 "3B" instead of 0x51 0x98 "3b"
        // replace x by X below.

        // This line places the two bytes (e.g. 0x51 0x98) corresponding to
        // the value of the i-th byte of res (e.g. 0x3b) to the 2i and 2i+1th
        // places in hex_as_string.
        sprintf(hex_as_string + 2*i, "%02x", *(res+i));

        // % means - convert this value to something else
        // x means - convert this value to the string (ASCII) representation
        //           of a hexadecimal number
        // for 0 and 2: see below:
        //
        // from man 3 printf:
        // 0      The value should be zero padded.  For d, i, o, u, x, X, a,
        //        A, e, E, f, F, g, and G conversions, the converted value is
        //        padded on the left with zeros rather than blanks.
        //
        // Field width
        //     An  optional  decimal  digit  string (with nonzero first digit)
        //     specifying a minimum field width.  If the converted value has
        //     fewer characters than the field width, it will be padded with
        //     spaces on the left.
    }

    // The result only has the result of the MD5, without the
    // leading 0x, it can be added by modifying the logic above
    // slightly. Usually the result of the MD5 is used without
    // the 0x anyway, like
    // MD5("TEST") = "033bd94b1168d7e4f0d644c3c95e35bf"

    std::string s(hex_as_string, 32); // 32 characters of the hash
    return s ;
}

// This is a test that should be added to the test suite:
bool test_md5() {
    return    md5("TEST") == "033bd94b1168d7e4f0d644c3c95e35bf"
              && md5("test") == "098f6bcd4621d373cade4e832627b4f6";
}

// This below function computes and shows the MD5 hash for the string "TEST"
int main() {
    const std::string test = "TEST";
    std::string r = md5(test);
    std::cout << r << std::endl;
    std::cout << (test_md5() ? "Tests work!" : "Tests fail :(") << std::endl;
    return 0;
}

// To compile this file without any other files, use the following command:
// c++ -lcrypto -lssl -o md5_test md5.cpp

// To run the example:
// ./md5_test
