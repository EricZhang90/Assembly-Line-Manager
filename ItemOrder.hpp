//
//  ItemOrder.hpp
//  ALM
//
//  Created by Eric on 2016-01-25.
//  Copyright © 2016 Eric. All rights reserved.
//

#ifndef ItemOrder_hpp
#define ItemOrder_hpp

#include <iostream>
#include <string>

class Item;

class ItemOrder {
  public:
    ItemOrder(const std::string& = std::string());
    
    bool asksFor(const Item&) const;
    bool isFilled() const;
    void fill(const unsigned int);
    void clear();
    const std::string& getName() const;
    void display(std::ostream&) const;
    
  private:
    std::string name;
    bool filled;
    unsigned int code;
};

#endif /* ItemOrder_hpp */
