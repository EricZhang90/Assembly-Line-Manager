
#ifndef TaskManager_hpp
#define TaskManager_hpp

#include <iostream>
#include <vector>

class Task;
class ItemManager;

class TaskManager {
  public:
    void push_back(Task&&);
    std::vector<Task>::iterator begin();
    std::vector<Task>::iterator end();
    const std::vector<Task>::const_iterator cbegin() const;
    const std::vector<Task>::const_iterator cend() const;
    void validate(std::ostream&);
    void display(std::ostream&) const;
    
  private:
    std::vector<Task> tasks;
};

void validate(const TaskManager&, const ItemManager&, std::ostream&);

#endif /* TaskManager_hpp */
