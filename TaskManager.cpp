#include "TaskManager.hpp"
#include "Task.hpp"
#include "ItemManager.hpp"
#include "Item.hpp"
#include <algorithm>

void TaskManager::push_back(Task&& t){
    tasks.push_back(std::move(t));
}

std::vector<Task>::iterator TaskManager::begin(){
    return tasks.begin();
}

std::vector<Task>::iterator TaskManager::end(){
    return tasks.end();
}

const std::vector<Task>::const_iterator TaskManager::cbegin() const{
    return tasks.cbegin();
}

const std::vector<Task>::const_iterator TaskManager::cend() const{
    return tasks.cend();
}

void TaskManager::validate(std::ostream& os){
    bool valid = true;
    for (auto i = 0u; i < tasks.size() && valid; i++) {
        bool invalid = true;
        for (auto j = 0u; j < tasks.size() && invalid; j++) {
            if (tasks[i].validate(tasks[j]))
                invalid = false;
        }
        valid = !invalid;
    }
    if (!valid)
        os << "*** Not all Tasks have been validated ***\n";
    
}

void TaskManager::display(std::ostream& os) const{
    auto end = tasks.end();
    for (auto i = tasks.begin(); i != end; ++i) {
        i->display(os);
    }
}

void validate(const TaskManager& tasks, const ItemManager& items, std::ostream& os){
    auto taskEnd = tasks.cend();
    auto itemEnd = items.cend();
    
    const int EQUAL = 0;
    
    bool isAvailable;
    
    // enumerate all tiems
    for (auto item = items.cbegin(); item != itemEnd; ++item) {
        isAvailable = false;
        
        // enumerate all tasks, compare each task with item destination
        for (auto singleTask = tasks.cbegin(); singleTask != taskEnd; ++singleTask) {
            
            if((item->getDestination()).compare(singleTask->getName()) == EQUAL){
                isAvailable = true;
                break;
            }
        }
        if (isAvailable == false) {
            os << item->getDestination() << " is unavailable\n";
        }
    }
    
}