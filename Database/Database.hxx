#ifndef DATABASE_HXX
#define DATABASE_HXX


#include <List.hxx>
#include <SportEvent.hxx>
#include <Filer.hxx>
#include <iostream>
#include <Crypter.hxx>
#include <ctime>
#include <algorithm>
#include <map>
#include <vector>


class Database {
protected:
    Filer file;
    std::string filename;
    std::string filename_enc;
    List <SportEvent> data;
    Crypter crypter;
public:
    Database (void);
    Database (const std::string& filename);
    Database (const List <SportEvent>& unit, const std::string& filename);
    Database (const Database& unit);
    ~Database (void);
    Database& operator= (const Database& unit) noexcept;
    SportEvent& operator[] (const unsigned int index) noexcept;
    friend std::ostream& operator<< (std::ostream& os, const Database& unit);
    const SportEvent& operator[] (const unsigned int index) const noexcept;
    void append (const SportEvent& unit) noexcept;
    void remove (const unsigned int index) noexcept;
    unsigned int size () noexcept;
    unsigned int size () noexcept;
    
    void getScheduleBySport(List <SportEvent>& result, const std::string& sportType) const noexcept;
    void getTopTeams(List <std::string>& result, const std::string& sportType) const noexcept;
    void getLastYearChampions(List <std::string>& result, const List <std::string>& sportTypes) const noexcept;
};


#endif // DATABASE_HXX