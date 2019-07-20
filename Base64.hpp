//
//  Base64.hpp
//  Sort
//
//  Created by weida on 02/07/2019.
//  Copyright © 2019 TCL. All rights reserved.
//

#ifndef Base64_hpp
#define Base64_hpp

#include <stdio.h>
#include "iostream"

using namespace std;

class Base64 {

private:
    
    char const *encodingTable  = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    inline int index(const char &c){
        for (int i=0;i < 64 ; i++) {
            if (encodingTable[i] == c) {
                return i;
            }
        }
        return -1; //Not found
    }
    
public:
    
    string encode(const string& source);
    
    string decode(const string& base64Str);
    
};

#endif /* Base64_hpp */
