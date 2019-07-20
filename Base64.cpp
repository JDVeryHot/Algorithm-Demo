//
//  Base64.cpp
//  Sort
//
//  Created by weida on 02/07/2019.
//  Copyright © 2019 TCL. All rights reserved.
//

#include "Base64.hpp"

string Base64::decode(const string& base64Str){
    
    string str;
    unsigned char (*p4Char)[4] = (unsigned char (*)[4])base64Str.c_str();
    char *endAdd = (char*)(base64Str.c_str() + base64Str.length());
    
    for (;(char*)p4Char <= endAdd-3 ; p4Char ++) {
        unsigned char *arry = (unsigned char*)*p4Char;
        
        unsigned char index0 = index(arry[0]);
        unsigned char index1 = index(arry[1]);
        unsigned char index2 = index(arry[2]);
        unsigned char index3 = index(arry[3]);
        
        str += (index0<<2) | (index1>>4);
        str += (index1<<4) | (index2>>2);
        str += (index2<<6) | index3;
    }
    
    return str;
}


string Base64::encode(const string& source){
    
    string strBase64;
    unsigned char (*p3Char)[3] = (unsigned char (*)[3])source.c_str();
    char *endAdd = (char*)(source.c_str() + source.length());
    
    for (;(char*)p3Char <= endAdd-3 ; p3Char ++) {
        unsigned char *arry = (unsigned char*)*p3Char;
        
        strBase64 += encodingTable[arry[0] >> 2];
        strBase64 += encodingTable[((arry[0] & 0x03) << 4) | (arry[1]>>4)];
        strBase64 += encodingTable[((arry[1] & 0x0F) << 2) | (arry[2]>>6)];
        strBase64 += encodingTable[arry[2] & 0x3F];
    }
    
    if (source.length()%3 > 0) {
        char tail[3] = {0};
        char *last = (char*)*p3Char;
        for (int j=0;j < source.length() %3; j++) {
            tail[j] = last[j];
        }
        
        strBase64 += encodingTable[tail[0] >> 2];
        strBase64 += encodingTable[((tail[0] & 0x03) << 4) | (tail[1]>>4)];
        strBase64 += encodingTable[((tail[1] & 0x0F) << 2) | (tail[2]>>6)];
        strBase64 += encodingTable[tail[2] & 0x3F];
    }

    return strBase64;
}

