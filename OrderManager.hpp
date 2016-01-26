

#ifndef OrderManager_hpp
#define OrderManager_hpp

#include <iostream>
#include <string>
#include <vector>

class ItemManager;
class CustomerOrder;

class OrderManager {
  public:
    CustomerOrder&& extract();
    
    void push_back(CustomerOrder&&);
    void pop();
    std::vector<CustomerOrder>::iterator begin();
    std::vector<CustomerOrder>::iterator end();
    const std::vector<CustomerOrder>::const_iterator cbegin() const;
    const std::vector<CustomerOrder>::const_iterator cend() const;
    void display(std::ostream&) const;
    bool empty() const;
    
  private:
    std::vector<CustomerOrder> customerOrders;
};

void validate(const OrderManager&, const ItemManager&, std::ostream&);


#endif /* OrderManager_hpp */
