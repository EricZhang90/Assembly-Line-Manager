#include "ItemManager.hpp"
#include "Item.hpp"


void ItemManager::push_back(Item&& stuff){
    items.push_back(std::move(stuff));
}

std::vector<Item>::iterator ItemManager::begin(){
    return items.begin();
}

std::vector<Item>::iterator ItemManager::end(){
    return items.end();
}

const std::vector<Item>::const_iterator ItemManager::cbegin() const{
    return items.cbegin();
}

const std::vector<Item>::const_iterator ItemManager::cend() const{
    return items.cend();
}


void ItemManager::display(std::ostream& os, bool flag) const{
    auto end = items.end();
    for (auto i = items.begin(); i != end; ++i) {
        i->display(os,flag);
    }
}
