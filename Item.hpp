#ifndef item_hpp
#define item_hpp

#include <iostream>
#include <string>

class Item {
  public:
    Item(const std::string& = std::string());
    
    bool empty() const;
    void operator++(int);
    unsigned int getCode() const;
    const std::string& getName() const;
    const std::string& getSource() const;
    const std::string& getDestination() const;
    void display(std::ostream&, bool = false) const;
    static void setDelimiter(const char);
    static size_t getFieldWidth();
    
  private:
    std::string name;
    std::string source;
    std::string destination;
    std::string details;
    unsigned int code;
    static char delimiter;
    static size_t field_width;
};


#endif /* item_hpp */
