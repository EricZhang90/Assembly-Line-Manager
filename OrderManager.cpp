#include "OrderManager.hpp"
#include "CustomerOrder.hpp"
#include "ItemManager.hpp"
#include "Item.hpp"
#include <string>

bool OrderManager::empty() const{
    return customerOrders.empty();
}

void OrderManager::push_back(CustomerOrder&& custOrder){
    customerOrders.push_back(std::move(custOrder));
}

std::vector<CustomerOrder>::iterator OrderManager::begin(){
    return customerOrders.begin();
}

std::vector<CustomerOrder>::iterator OrderManager::end(){
    return customerOrders.end();
}

const std::vector<CustomerOrder>::const_iterator OrderManager::cbegin() const{
    return customerOrders.cbegin();
}

const std::vector<CustomerOrder>::const_iterator OrderManager::cend() const{
    return customerOrders.cend();
}

void OrderManager::display(std::ostream& os) const{
    auto end = customerOrders.end();
    for (auto i = customerOrders.begin(); i != end; ++i) {
        i->display(os);
    }
}

void validate(const OrderManager& orders, const ItemManager& items, std::ostream& os){
    
    auto ordersEnd = orders.cend();
    auto itemsEnd = items.cend();
    
    const int EQUAL = 0;  // equal statement
    
    bool isAvailable;
    
    // enumerate all customer orders
    for (auto customerOrder = orders.cbegin(); customerOrder != ordersEnd; ++customerOrder) {
        
        // enumerate all single order stored in customer order
        for (int i = 0; i < customerOrder->noOrders(); ++i) {
            isAvailable = false; // assume all items are unavailable
            
            std::string singleOrderName = (*customerOrder)[i];
            
            // enumerate all items, and compare each stored item with ordered item
            for (auto eachItem = items.cbegin(); eachItem != itemsEnd; ++eachItem) {
                if(singleOrderName.compare(eachItem->getName()) == EQUAL){
                    isAvailable = true;
                    break;
                }
            }
            if (isAvailable == false) {
                os << singleOrderName << " is unavailable\n";
            }
        }
    }
}

void OrderManager::pop(){
    customerOrders.pop_back();
}

CustomerOrder&& OrderManager::extract(){
    return std::move(customerOrders.back());
}
