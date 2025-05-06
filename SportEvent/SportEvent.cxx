#include "SportEvent.hxx"

SportEvent::SportEvent(void) noexcept {
    sportType = "";
    team1 = "";
    team2 = "";
    date = "";
    result = "";
}

SportEvent::SportEvent(const std::string& sportType, const std::string& team1,
                      const std::string& team2, const std::string& date,
                      const std::string& result) noexcept {
    this->sportType = sportType;
    this->team1 = team1;
    this->team2 = team2;
    this->date = date;
    this->result = result;
}

std::ostream& operator<<(std::ostream& os, const SportEvent& event) {
    os << event.getSportType() << ": " 
       << event.getTeam1() << " vs " << event.getTeam2() 
       << " on " << event.getDate() 
       << " - Winner: " << (event.getResult() == "Win1" ? event.getTeam1() : event.getTeam2());
    return os;
}

std::string SportEvent::getSportType(void) const noexcept { return sportType; }
std::string SportEvent::getTeam1(void) const noexcept { return team1; }
std::string SportEvent::getTeam2(void) const noexcept { return team2; }
std::string SportEvent::getDate(void) const noexcept { return date; }
std::string SportEvent::getResult(void) const noexcept { return result; }

void SportEvent::setSportType(const std::string& sportType) noexcept { this->sportType = sportType; }
void SportEvent::setTeam1(const std::string& team1) noexcept { this->team1 = team1; }
void SportEvent::setTeam2(const std::string& team2) noexcept { this->team2 = team2; }
void SportEvent::setDate(const std::string& date) noexcept { this->date = date; }
void SportEvent::setResult(const std::string& result) noexcept { this->result = result; }