

#include "Task.hpp"
#include "Utilities.hpp"
#include <iostream>
#include <memory>
#include <iomanip>
#include <stdlib.h>

using std::string;
using std::endl;

char Task::delimiter = '\0';
size_t Task::field_width = 1;

Task::Task(const string& record){
    
    slots = "1";
    pNextTask[0] = pNextTask[1] = nullptr;
    bool more;
    size_t width = 0;
    
    try{
        std::unique_ptr<Utilities> utility(new Utilities(Task::field_width));
        
        name = utility->nextToken(record, width, more);
        
        if(more)
            slots = utility->nextToken(record, width, more);
        
        if(more)
            nextTask[0] = utility->nextToken(record, width, more);
        
        if(more)
            nextTask[1] = utility->nextToken(record, width, more);
        
        if (utility->getFieldWidth() > Task::getFieldWidth()){
            Task::setFieldWidth(utility->getFieldWidth());
        }
    }catch( const char* msg){
        
    }
    
}

const string& Task::getName() const{
    return name;
}

const unsigned int Task::getSlots() const{
    return atoi(slots.c_str());
}

bool Task::validate(const Task& task){
    
    bool validTask1 = false, validTask2 = false;
    
    if(pNextTask[0]  == nullptr && !nextTask[0].empty()){
        if(nextTask[0].compare(task.name) == 0){
            pNextTask[0] = &task;
            validTask1 = true;
        }
    }
    else
        validTask1 = true;
    
    
    if(pNextTask[1] == nullptr && !nextTask[1].empty()){
        if(nextTask[1].compare(task.name) == 0){
            pNextTask[1] = &task;
            validTask2 = true;
        }
    }
    else
        validTask2 = true;
    
    if (validTask1 && validTask2)
        return true;
    else
        return false;
}

const Task* Task::getNextTask(Quality quality) const{
    if (pNextTask[0] == nullptr)
        throw (string)"*** Validate  [" + nextTask[0] + "] @ [" + name + "] ***";
    
    //if(!nextTask[0].empty())
    
    return quality == passed ? pNextTask[0] : pNextTask[1];
}

void Task::display(std::ostream& os) const{
    
    string resivedName;
    
    resivedName = name + "]";
    os << "Task Name    : [" << std::left << std::setw((int)Task::getFieldWidth()+1) << resivedName;
    os << "[" << getSlots() << "]" << endl;
    
    if (!nextTask[0].empty()){
        resivedName = nextTask[0] + "]";
        os << " Continue to : [" << std::left << std::setw((int)Task::getFieldWidth()+1) << resivedName;
        
        if(pNextTask[0] == nullptr)
            os << "*** to be validated ***";
        os << endl;
    }
    if (!nextTask[1].empty()){
        resivedName = nextTask[1] + "]";
        os << " Redirect to : [" << std::left << std::setw((int)Task::getFieldWidth()+1) << resivedName;
        
        if(pNextTask[1] == nullptr)
            os << "*** to be validated ***";
        os << endl;
    }
    
}

void Task::setDelimiter(const char c){
    delimiter = c;
}

void Task::setFieldWidth(size_t FW){
    field_width = FW;
}

size_t Task::getFieldWidth(){
    return field_width;
}

bool operator==(const Task& first, const Task& second){
    return !first.getName().compare(second.getName());
}

