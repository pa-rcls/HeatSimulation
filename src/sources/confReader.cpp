#include "confReader.hpp"
#include <iostream>

ConfReader::ConfReader(const std::string& filename) {
    // Read and parse the INI file
    if (ini_parse(filename.c_str(), ConfReader::iniHandler, this) < 0) {
        std::cerr << "Error: Unable to load INI file '" << filename << "'\n";
    }
}

// Function to get a value by the "section.name" key
std::string ConfReader::get(const std::string& section, const std::string& name) const {
    std::string key = section + "." + name;
    auto it = config.find(key);
    if (it != config.end()) {
        return it->second;
    } else {
        return "";  // Return an empty string if the key is not found
    }
}

// Handler used by the inih library to parse the file
int ConfReader::iniHandler(void* user, const char* section, const char* name, const char* value) {
    ConfReader* reader = (ConfReader*)user;
    std::string key = std::string(section) + "." + std::string(name);
    reader->config[key] = std::string(value);
    return 1;  // Return 1 to continue parsing
}
