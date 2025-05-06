#include "Filer.hxx"

Filer::Filer (const std::string& path, const bool createNew) {
    if (createNew) {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) {
            this->file.open(path, std::ios::out);
            this->file.close();
            this->file.open(path, std::ios::in);
            if (!this->file.is_open()) throw std::runtime_error("Failed to create the file.");
        }
    }
    else {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) throw std::runtime_error("File cannot be opened or does not exists");
    }
    this->path = path;
}

Filer::~Filer (void) noexcept {
    if (this->file.is_open()) this->file.close();
}

void Filer::open (const std::string& path, const bool createNew) {
    if (createNew) {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) {
            this->file.open(path, std::ios::out);
            this->file.close();
            this->file.open(path, std::ios::in);
            if (!this->file.is_open()) throw std::runtime_error("Failed to create the file.");
        }
    }
    else {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) throw std::runtime_error("File cannot be opened or does not exists");
    }
    this->path = path;
}

void Filer::read (std::string& str) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    
    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::in);

    this->file.seekg(0, std::ios::beg);
    std::string temp;

    this->file.seekp(0, std::ios::beg);
    while (std::getline(this->file, temp)) str += temp + '\n';
    
    this->mutex.unlock();
}

void Filer::readToList (List <SportEvent>& unit) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    
    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::in);

    this->file.seekg(0, std::ios::beg);
    std::string temp;
    SportEvent node;
    while (std::getline(this->file, temp)) {
        node = SportEvent();
        this->stringToEvent(node, temp);
        unit.append(node);
    }

    this->mutex.unlock();
}

void Filer::writeBack (std::string& string) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    else if (string.empty()) return;

    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::app);

    this->file << string << '\n';
    this->file.flush();
    this->mutex.unlock();
}

void Filer::writeBackFromEvent (const SportEvent& unit) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");

    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::app);

    this->file << 
        unit.getSportType() << "$$" <<
        unit.getTeam1() << "$$" <<
        unit.getTeam2() << "$$" <<
        unit.getDate() << "$$" <<
        unit.getResult() << '\n'
    ;
    this->file.flush();
    
    this->mutex.unlock();
}

void Filer::rewrite (std::string& string) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    else if (string.empty()) return;

    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::trunc);

    this->file << string << '\n';
    this->file.flush();

    this->mutex.unlock();
}

void Filer::rewriteFromList (const List <SportEvent>& unit) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    else if (unit.length() == 0) return;

    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::trunc);

    this->file.seekg(0, std::ios::beg);

    for (unsigned int i = 0; i < unit.length(); ++i) {
        this->file << 
            unit[i].getSportType() << "$$" <<
            unit[i].getTeam1() << "$$" <<
            unit[i].getTeam2() << "$$" <<
            unit[i].getDate() << "$$" <<
            unit[i].getResult() << '\n'
        ;
    }
    this->file.flush();

    this->mutex.unlock();
}

void Filer::stringToEvent (SportEvent& unit, const std::string& str) {
    if (str.empty()) return;

    std::string arr[5];
    unsigned short count = 0;
    for (size_t i = 0; i < (str.size() - 1) && count < 5; ++i) {
        if (str[i] == '$' && str[i + 1] == '$') {
            ++count, ++i;
        } 
        else arr[count].push_back(str[i]);
    }
    if (count < 5) arr[count].push_back(str[str.size() - 1]);

    unit.setSportType(arr[0]);
    unit.setTeam1(arr[1]);
    unit.setTeam2(arr[2]);
    unit.setDate(arr[3]);
    unit.setResult(arr[4]);
}