#ifndef INTERFACE_HXX
#define INTERFACE_HXX

#include <iostream>
#include <SportEvent.hxx>
#include <List.hxx>
#include <Database.hxx>

class Interface {
private:
    Database db;
    void displayMenu(void);
    void getSportEvent(SportEvent& event);
    int removeEvent(void);
    void clearInputBuffer(void);
    void displayResults(const List<SportEvent>& results);
public:
    Interface(void) = default;
    Interface(const Interface&) = delete;
    Interface& operator=(const Interface&) = delete;
    ~Interface(void) noexcept = default;
    void run(void);
};

#endif // INTERFACE_HXX