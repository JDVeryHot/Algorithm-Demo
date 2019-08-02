//
//  main.cpp
//  Sort
//
//  Created by weida on 2019/6/26.
//  Copyright © 2019 TCL. All rights reserved.
//

#include <iostream>
#include <array>

using namespace std;


inline bool isPalindromeString(const string& str,long from,long to){
    bool ret = true;
    
    while (from <= to) {
        if (str[from] != str[to]) {
            ret = false;
            break;
        }
        from ++;
        to --;
    }
    
    return ret;
}

string longestPalindromeString(const string&str){
    
    long step = 0;
    while (step < str.length()) {
        
        for (int from=0;; from++) {
            long to = from + str.length()-1-step;
            if (to >= str.length()) {
                break;
            }
            
            if (isPalindromeString(str, from, to)) {
                return str.substr(from,to-from+1);
            }
        }
        
        step++;
    }
    return "";
}

int main(int argc, const char * argv[]) {
    
    array<string, 8> strs = {"10566501abcba001","abckdkcba4kcba","12132312","010gg0","a","yyanana","aa7aa","k9jkmd",};
    
    for (auto s : strs) {
       string palidrome = longestPalindromeString(s);
        printf("%s---%s\n",s.c_str(),palidrome.c_str());
    }
    
    return 0;
}


