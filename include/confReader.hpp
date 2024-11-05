#ifndef CONF_READER_HPP
#define CONF_READER_HPP

#include <string>
#include "../../libs/inih/ini.h"
#include <map>

class ConfReader {
public:
    // Constructor that reads and parses an INI file
    ConfReader(const std::string& filename);

    // Function to get a value from the "section.name" key
    std::string get(const std::string& section, const std::string& name) const;

private:
    // Static function used by inih to parse files
    static int iniHandler(void* user, const char* section, const char* name, const char* value);

    // Map to store values with keys as "section.name" -> "value"
    std::map<std::string, std::string> config;
};

#endif  // CONF_READER_HPP
