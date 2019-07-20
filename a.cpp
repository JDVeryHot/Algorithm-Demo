
/**
 判断parentStr中有多少个subStr

 @param parentStr 字符串
 @param subStr 字符串
 @return 个数
 */
unsigned int  subStr(const string &parentStr,const string &subStr){
    unsigned int num = 0;
    const char *pStr   = parentStr.c_str();
    const char *pSub   = subStr.c_str();
   
    for (int i = 0,s = 0,last = 0; i<parentStr.length(); i++) {
        if (s == 0) {
            last = i;
            if (parentStr.length() - i < subStr.length())break;
        }
        
        if (pStr[i] != pSub[s]) {
            s = 0;
            i = last;
            continue;
        }
        
        if (s == subStr.length()-1) {
            num ++;
            s = 0;
            continue;
        }
        s ++;
    }
    
    return num;
}
