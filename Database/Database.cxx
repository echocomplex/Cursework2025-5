#include "Database.hxx"

Database::Database (void) {
    this->filename = "database.txt";
    this->filename_enc = "database.enc";
    this->crypter.decrypt(this->filename_enc, this->filename);
    this->file.open(this->filename, true);
    this->file.readToList(this->data);
}

Database::Database (const std::string& filename) {
    this->filename = filename + ".txt";
    this->filename_enc = filename + ".enc";
    this->crypter.encrypt(this->filename_enc, this->filename);
    this->file.open(filename);
    this->file.readToList(this->data);
}

Database::Database (const List <SportEvent>& unit, const std::string& filename) {
    this->data = unit;
    this->filename = filename + ".txt";
    this->filename_enc = filename + ".enc";
    this->file.open(this->filename);
}

Database::Database (const Database& unit) {
    this->data = unit.data;
    this->file.open(unit.filename);
    this->filename = unit.filename;
    this->filename_enc = unit.filename_enc;
}

Database::~Database (void) {
    this->file.rewriteFromList(this->data);
    this->crypter.encrypt(this->filename, this->filename_enc);
}

Database& Database::operator= (const Database& unit) noexcept {
    if (this == &unit) return *this;
    this->data = unit.data;
    this->filename = unit.filename;
    this->filename_enc = unit.filename_enc;
    this->file.open(unit.filename);
    return *this;
}

SportEvent& Database::operator[] (const unsigned int index) noexcept {
    return this->data[index];
}

std::ostream& operator<< (std::ostream& os, const Database& unit) {
    for (unsigned int i = 0; i < unit.data.length(); ++i) os << i + 1 << ' ' << unit[i] << std::endl;
    return os;
}

const SportEvent& Database::operator[] (const unsigned int index) const noexcept {
    return this->data[index];
}

void Database::append (const SportEvent& unit) noexcept {
    this->data.append(unit);
}

void Database::remove (const unsigned int index) noexcept {
    this->data.remove(index);
}

unsigned int Database::size () noexcept {
    return this->data.length();
}

void Database::getScheduleBySport(List<SportEvent>& result, const std::string& sportType) const noexcept {
    for (unsigned int i = 0; i < data.length(); ++i) {
        if (data[i].getSportType() == sportType) {
            result.append(data[i]);
        }
    }
}

void Database::getTopTeams(List<std::string>& result, const std::string& sportType) const noexcept {
    std::map<std::string, int> teamWins;

    // Считаем победы для каждой команды
    for (unsigned int i = 0; i < data.length(); ++i) {
        if (data[i].getSportType() == sportType) {
            std::string winner = data[i].getWinner();
            teamWins[winner]++;
        }
    }

    std::vector<std::pair<std::string, int>> sortedTeams(teamWins.begin(), teamWins.end());
    std::sort(sortedTeams.begin(), sortedTeams.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    for (int i = 0; i < 3 && i < sortedTeams.size(); ++i) {
        result.append(sortedTeams[i].first);
    }
}

void Database::getLastYearChampions(List<std::string>& result, const List<std::string>& sportTypes) const noexcept {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int currentYear = 1900 + ltm->tm_year;
    int lastYear = currentYear - 1;

    for (unsigned int st = 0; st < sportTypes.length(); ++st) {
        const std::string& sportType = sportTypes[st];
        std::map<std::string, int> teamWins;

        // Считаем победы за прошлый год
        for (unsigned int i = 0; i < data.length(); ++i) {
            if (data[i].getSportType() == sportType) {
                std::string dateStr = data[i].getDate();
                try {
                    int year = std::stoi(dateStr.substr(0, 4));
                    if (year == lastYear) {
                        std::string winner = data[i].getWinner();
                        teamWins[winner]++;
                    }
                } catch (...) {
                    continue;
                }
            }
        }

        if (!teamWins.empty()) {
            auto champion = std::max_element(teamWins.begin(), teamWins.end(),
                [](const auto& a, const auto& b) { return a.second < b.second; });
            result.append(champion->first + " (" + sportType + ")");
        }
    }
}