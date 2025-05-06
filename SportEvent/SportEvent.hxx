#ifndef SPORTEVENT_HXX
#define SPORTEVENT_HXX

#include <string>
#include <iostream>

class SportEvent {
private:
    std::string sportType;
    std::string team1;
    std::string team2;
    std::string date;
    std::string result; // "Win1" или "Win2"
public:
    SportEvent(void) noexcept;
    SportEvent(const std::string& sportType, const std::string& team1, 
              const std::string& team2, const std::string& date, 
              const std::string& result) noexcept;
    ~SportEvent(void) noexcept = default;
    
    std::string getSportType(void) const noexcept;
    std::string getTeam1(void) const noexcept;
    std::string getTeam2(void) const noexcept;
    std::string getDate(void) const noexcept;
    std::string getResult(void) const noexcept;
    
    void setSportType(const std::string& sportType) noexcept;
    void setTeam1(const std::string& team1) noexcept;
    void setTeam2(const std::string& team2) noexcept;
    void setDate(const std::string& date) noexcept;
    void setResult(const std::string& result) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const SportEvent& event);
    std::string getWinner() const noexcept {
        return (result == "Win1") ? team1 : team2;
    }
    
    std::string getLoser() const noexcept {
        return (result == "Win1") ? team2 : team1;
    }
};

#endif // SPORTEVENT_HXX