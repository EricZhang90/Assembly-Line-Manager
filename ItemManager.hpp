//
//  ItemManager.hpp
//  ALM
//
//  Created by Eric on 2016-01-25.
//  Copyright © 2016 Eric. All rights reserved.
//

#ifndef ItemManager_hpp
#define ItemManager_hpp

#include <iostream>
#include <vector>

class Item;

class ItemManager {
  public:
    void push_back(Item&&);
    std::vector<Item>::iterator begin();
    std::vector<Item>::iterator end();
    const std::vector<Item>::const_iterator cbegin() const;
    const std::vector<Item>::const_iterator cend() const;
    void display(std::ostream&, bool = false) const;

  private:
    std::vector<Item> items;
};


#endif /* ItemManager_hpp */
