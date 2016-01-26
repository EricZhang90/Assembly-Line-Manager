#include "Item.hpp"
#include "Utilities.hpp"
#include <memory>
#include <cstdlib>
#include <iomanip>

using std::endl;
using std::string;

char Item::delimiter = '\0';
size_t Item::field_width = 1;

Item::Item(const std::string& record){
    details = "no detailed description";
    code = 1;
    
    if(!record.empty()){
        bool more;
        size_t width = 0;
        std::unique_ptr<Utilities> utility(new Utilities(Item::field_width));
        //utility->setFieldWidth(0);
        
        try{
            name = utility->nextToken(record, width, more);
            if (name.length() == 0)
                throw (string)"no name is specified.";
            
            if(!more)
                throw (string)"no task is specified";
            else
                source = utility->nextToken(record, width, more);
            
            if(!more)
                throw (string)"no destination is specified";
            else
                destination = utility->nextToken(record, width, more);
            
            if(more)
                code = atoi(utility->nextToken(record, width, more).c_str());
            
            if(more){
                string temp = utility->nextToken(record, width, more);
                if(!temp.empty())
                    details = temp;
            }
            
            if (utility->getFieldWidth() > Item::getFieldWidth())
                Item::field_width = utility->getFieldWidth();
        }catch(const char* msg){
            
        }
        
    }
    //display(std::cout);
}

bool Item::empty() const{
    return code == 1;
}

void Item::operator++(int i){
    code += 1;
}

unsigned int Item::getCode() const{
    return code;
}

const std::string& Item::getName() const{
    return name;
}

const std::string& Item::getSource() const{
    return source;
}

const std::string& Item::getDestination() const{
    return destination;
}

void Item::display(std::ostream& os, bool full) const{
    
    os << std::setfill(' ') << std::left << std::setw((int)Item::getFieldWidth()) << name;
    os << "[" << std::setw(CODE_WIDTH) << std::setfill('0')  << std::right << code << "]";
    
    if (full) {
        os << " From " << std::setfill(' ') <<  std::left << std::setw((int)Item::getFieldWidth()) << source;
        os << " To " << std::left << std::setw((int)Item::getFieldWidth()) << destination << endl;
        os << std::setw((int)Item::getFieldWidth() + CODE_WIDTH) << "";
        os <<  " : " << details << endl;
    }
}

void Item::setDelimiter(const char c){
    delimiter = c;
}

size_t Item::getFieldWidth(){
    return field_width;
}
