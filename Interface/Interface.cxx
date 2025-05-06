#include "Interface.hxx"

void Interface::clearInputBuffer(void) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Interface::getSportEvent(SportEvent& event) {
    std::string sportType, team1, team2, date, result;
    
    std::cout << "\n=== Add New Sports Event ===\n";
    
    std::cout << "Sport Type (Basketball/Volleyball/Soccer): ";
    std::getline(std::cin, sportType);
    
    std::cout << "First Team Name: ";
    std::getline(std::cin, team1);
    
    std::cout << "Second Team Name: ";
    std::getline(std::cin, team2);
    
    std::cout << "Date (YYYY-MM-DD): ";
    std::getline(std::cin, date);
    
    std::cout << "Result (Win1/Win2): ";
    std::getline(std::cin, result);
    
    event = SportEvent(sportType, team1, team2, date, result);
}

int Interface::removeEvent(void) {
    int number;
    while (true) {
        std::cout << "Enter event number to delete (1-" << this->db.size() << "): ";
        
        if (!(std::cin >> number)) {
            std::cin.clear();
            this->clearInputBuffer();
            std::cerr << "Error: Please enter a number\n\n";
            continue;
        }

        if (number > 0 && number <= this->db.size()) {
            return number - 1;
        }
        
        std::cerr << "Error: Number must be between 1 and " << this->db.size() << "\n\n";
    }
}

void Interface::displayResults(const List<SportEvent>& results) {
    if (results.length() == 0) {
        std::cout << "No results found.\n";
        return;
    }
    
    for (unsigned int i = 0; i < results.length(); ++i) {
        const SportEvent& e = results[i];
        std::cout << (i+1) << ". " << e.getSportType() << ": " 
                  << e.getTeam1() << " vs " << e.getTeam2() 
                  << " on " << e.getDate() << " - Result: " 
                  << (e.getResult() == "Win1" ? e.getTeam1() : e.getTeam2()) 
                  << " won\n";
    }
}

void Interface::displayMenu(void) {
    std::cout << "\n=== University Sports Championship Database ===" << std::endl;
    std::cout << "1. Display all events" << std::endl;
    std::cout << "2. Add new sports event" << std::endl;
    std::cout << "3. Remove event" << std::endl;
    std::cout << "4. View schedule by sport" << std::endl;
    std::cout << "5. View top 3 teams by sport" << std::endl;
    std::cout << "6. View last year champions" << std::endl;
    std::cout << "7. Exit program" << std::endl;
    std::cout << "Enter your choice (1-7): ";
}

void Interface::run(void) {
    short choice = 0;
    SportEvent newEvent;
    List<SportEvent> results;
    List<std::string> topTeams;
    List<std::string> sportTypes;
    std::string temp;
    
    sportTypes.append("Basketball");
    sportTypes.append("Volleyball");
    sportTypes.append("Soccer");
    
    while (true) {
        this->displayMenu();

        while (!(std::cin >> choice) || choice < 1 || choice > 7) {
            std::cout << "Invalid input. Please enter 1-7: ";
            this->clearInputBuffer();
        }

        this->clearInputBuffer();

        switch (choice) {
            case 1:
                std::cout << "\n[All Sports Events]\n";
                results.clear();
                for (unsigned int i = 0; i < db.size(); ++i) {
                    results.append(db[i]);
                }
                displayResults(results);
                break;
                
            case 2:
                this->getSportEvent(newEvent);
                this->db.append(newEvent);
                std::cout << "Event added successfully!\n";
                break;
                
            case 3:
                if (db.size() == 0) {
                    std::cout << "No events to remove.\n";
                    break;
                }
                std::cout << "\n[Remove Event]\n";
                this->db.remove(this->removeEvent());
                std::cout << "Event removed successfully!\n";
                break;
                
            case 4:
                std::cout << "Enter sport type (Basketball/Volleyball/Soccer): ";
                std::getline(std::cin, temp);
                std::cout << "\n[Schedule for " << temp << "]\n";
                results.clear();
                db.getScheduleBySport(results, temp);
                displayResults(results);
                break;
                
            case 5:
                std::cout << "Enter sport type (Basketball/Volleyball/Soccer): ";
                std::getline(std::cin, temp);
                std::cout << "\n[Top 3 Teams in " << temp << "]\n";
                topTeams.clear();
                db.getTopTeams(topTeams, temp);
                for (unsigned int i = 0; i < topTeams.length(); ++i) {
                    std::cout << (i+1) << ". " << topTeams[i] << "\n";
                }
                break;
                
            case 6:
                std::cout << "\n[Last Year Champions]\n";
                topTeams.clear();
                db.getLastYearChampions(topTeams, sportTypes);
                for (unsigned int i = 0; i < topTeams.length(); ++i) {
                    std::cout << "- " << topTeams[i] << "\n";
                }
                break;
                
            case 7:
                std::cout << "\nExiting program...\n";
                return;
        }

        std::cout << "\nPress Enter to continue...";
        this->clearInputBuffer();
    }
}