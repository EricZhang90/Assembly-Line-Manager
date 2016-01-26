

#ifndef Task_hpp
#define Task_hpp

#include <iostream>
#include <string>

class Task {
  public:
    enum Quality {
        passed,
        redirect
    };
    Task(const std::string& record);
    const std::string& getName() const;
    const unsigned int getSlots() const;
    bool validate(const Task& task);
    const Task* getNextTask(Quality quality) const;
    void display(std::ostream&) const;
    static void setDelimiter(const char c);
    static void setFieldWidth(size_t);
    static size_t getFieldWidth();
    
  private:
    std::string name;
    std::string slots;
    std::string nextTask[2];
    const Task* pNextTask[2];
    static char delimiter;
    static size_t field_width;
};

bool operator==(const Task&, const Task&);


#endif /* Task_hpp */
