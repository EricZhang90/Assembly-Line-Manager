#include "CustomerOrder.hpp"

#include "CustomerOrder.hpp"
#include "Utilities.hpp"
#include "ItemOrder.hpp"
#include "Item.hpp"
#include <memory>
#include <vector>
#include <iostream>
#include <iomanip>

using std::string;
using std::unique_ptr;
using std::cout;
using std::endl;

char CustomerOrder::delimiter = '\0';
size_t CustomerOrder::field_width = 1;

CustomerOrder::CustomerOrder(const std::string& record){
    
    auto allAreSpace = [](string str){
        for(int i = 0; i < str.length(); i ++)
            if (str[i] != ' ')
                return false;
        return true;
    };
    
    
    nOrders = 0;
    order = nullptr;

    try{
        
        if(record.empty())
            throw "this record is empty";
        
        size_t width = 0;
        bool more;
        
        std::unique_ptr<Utilities> utility(new Utilities(CustomerOrder::field_width));
        
        name = utility->nextToken(record, width, more);
        
        if (name.empty() || allAreSpace(name))
            throw "this record is empty";
        
        if (!more)
            throw (string)"Prodcut missing";
        else{
            //int l = record.length();
            product = utility->nextToken(record, width, more);
        }
        
        if (!more){
            throw (string)"Item missing";
        }
        else{               // start to populate products
            std::vector<string> names;
            
            while (more) {
                string itemName = utility->nextToken(record, width, more);
                if (itemName.empty() || allAreSpace(itemName)) {
                    more = false;
                }
                else{
                    nOrders++;
                    names.push_back(itemName);
                }
            }
            
 
            order = new ItemOrder[nOrders];
            for(int i = 0; i < nOrders; i++){
                if(!names[i].empty() && !allAreSpace(names[i]))
                    order[i] = ItemOrder(names[i]);
                
            }
        }
        
        if (utility->getFieldWidth() > CustomerOrder::field_width)
            CustomerOrder::field_width = utility->getFieldWidth();
        
    }catch(const char* msg){
        
    }
 }

CustomerOrder::CustomerOrder(const CustomerOrder& src){
    name = src.name;
    product = src.product;
    nOrders = src.nOrders;
    order = new ItemOrder[nOrders];
    for(int i = 0; i < nOrders; i++){
        order[i] = src.order[i];
    }
}

CustomerOrder::CustomerOrder(CustomerOrder&& src){
    name = src.name;
    product = src.product;
    nOrders = src.nOrders;
    order = src.order;
    src.name = src.product = "";
    src.nOrders = 0;
    src.order = nullptr;
}

CustomerOrder&& CustomerOrder::operator=(CustomerOrder&& src){
    if(this != &src){
        if(order)
            delete [] order;
        name = src.name;
        product = src.product;
        nOrders = src.nOrders;
        order = src.order;
        src.name = src.product = "";
        src.nOrders = 0;
        src.order = nullptr;
    }
    return std::move(*this);
}

CustomerOrder::~CustomerOrder(){
    if(order) delete [] order;
}

unsigned int CustomerOrder::noOrders() const{
    return nOrders;
}

const std::string& CustomerOrder::operator[](unsigned int i) const{
    if(i > nOrders)
        throw (string)"the index is out of bounds";
    
    return order[i].getName();
}

void CustomerOrder::fill(Item& stuff){
    for (int i = 0; i < nOrders; i++){
        string oname = order[i].getName();
        string iname = stuff.getName();
        if(order[i].asksFor(stuff) && !order[i].isFilled()){
            order[i].fill(stuff.getCode());
            stuff++;
        }
    }
}

void CustomerOrder::remove(Item& stuff){
    for (int i = 0; i < nOrders; i++){
        if(order[i].asksFor(stuff) && order[i].isFilled()){
            order[i].clear();
            break;
        }
    }
}

bool CustomerOrder::empty() const{
    return nOrders == 0;
}

void CustomerOrder::display(std::ostream& os) const{
    os << std::left << std::setw((int)Item::getFieldWidth()) << std::setfill(' ') << name;
    os << ": " << std::left << std::setw((int)Item::getFieldWidth()) << product << endl;
    for (int i = 0; i < nOrders; i++) 
        order[i].display(os);
}

void CustomerOrder::setDelimiter(const char c){
    delimiter = c;
}
