//
//  Utilities.hpp
//  ALM
//
//  Created by Eric on 2016-01-25.
//  Copyright © 2016 Eric. All rights reserved.
//

#ifndef Utilities_hpp
#define Utilities_hpp

#include <string>

const unsigned int CODE_WIDTH = 5; // item code field width (later)

class Utilities {
  public:
    Utilities(size_t minimum_field_width = 1u);
    void setFieldWidth(size_t fw);
    size_t getFieldWidth() const;
    const std::string nextToken(const std::string& str, size_t& next_pos,
                                bool& more);
    static void setDelimiter(const char c);
    static const char getDelimiter();
    
  private:
    size_t field_width;
    static char delimiter;
};

#endif /* Utilities_hpp */
