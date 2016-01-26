
#include "ItemOrder.hpp"
#include "Item.hpp"
#include "Utilities.hpp"
#include <iomanip>

using std::string;

ItemOrder::ItemOrder(const std::string& record){
    name = "";
    filled = code = 0;
    
    if(!record.empty()){
        name = record;
    }

}

bool ItemOrder::asksFor(const Item& stuff) const{
    return !name.compare(stuff.getName());
}

bool ItemOrder::isFilled() const{
    return filled;
}

void ItemOrder::fill(const unsigned int c){
    code = c;
    filled = true;
}

void ItemOrder::clear(){
    filled = code = 0;
}

const string& ItemOrder::getName() const{
    return name;
}

void ItemOrder::display(std::ostream& os) const{
    
    os << (filled ? '+': '-') << " [" << std::setw(CODE_WIDTH) << std::setfill('0')  << std::right << code;
    
    os << "] " << name << std::endl;
}