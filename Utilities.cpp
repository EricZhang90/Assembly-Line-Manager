

#include "Utilities.hpp"
#include <iostream>

using std::string;

char Utilities::delimiter = '\0';

Utilities::Utilities(size_t minimum_field_width){
    field_width = minimum_field_width;
}

void Utilities::setFieldWidth(size_t FW){
    field_width = FW;
}

size_t Utilities::getFieldWidth() const{
    return field_width;
}

const string Utilities::nextToken(const string& str, size_t& next_pos, bool& more){
    more = true;
    
    size_t curentPos = next_pos;
    string substring = str.substr(next_pos);  // get rest of string
    string result;                            // this string will be returned
    
    size_t strBegin = substring.find_first_not_of(' ');
    if (strBegin == -1) {
        
        strBegin = 1;
    }
    
    if(substring[strBegin] == '|' or strBegin > substring.length() or substring.empty()){
        throw "BAD CODE 2";   // bad tokens
    }
    
    int tokenEndPos = (int)substring.find_first_of(Utilities::getDelimiter());  // end of single token
    
    if (tokenEndPos > substring.length()) {            // there is not "|" any more,
        // it may means this token is last token in single repord
        // (except bad repord, such as "|" at the end.
        size_t strEnd = substring.find_last_not_of(' ');  // find extra spaces
        if (strEnd < substring.length()) {                  // there is not extra spaces if strEnd < string length
            result = substring.substr(strBegin, strEnd+1);
        }
        else{
            result = substring.substr(strBegin);
        }
        more = false;
    }
    else{                                       // there is "|" somewhere
        
        if(tokenEndPos + curentPos + 1 < str.length()){ // the "1" presents "|",
            next_pos += tokenEndPos + 1;        // it means this token is not the last one
        }
        else{
            more = false;
        }
        
        string token = substring.substr(strBegin, tokenEndPos - strBegin);
        size_t strEnd = token.find_last_not_of(' ');
        
        result = token.substr(0,strEnd+1);
    }
    
    if(result.empty())
        throw "BAD CODE 3";
    
    
    
    if(result.length()  > Utilities::getFieldWidth()){
        Utilities::setFieldWidth(result.length() );
    }
    
    return result;
}

void Utilities::setDelimiter(const char c){
    delimiter = c;
}

const char Utilities::getDelimiter(){
    return delimiter;
}

