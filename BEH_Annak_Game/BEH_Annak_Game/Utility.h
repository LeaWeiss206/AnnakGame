#pragma once

#include <string>
#include <vector>
#include <fstream>

static const char* ws1 = " \t\n\r\f\v";

static inline void strip(std::string& s) {
    s.erase(s.find_last_not_of(ws1) + 1);
    s.erase(0, s.find_first_not_of(ws1));
}

static inline std::vector<std::string> split(std::string s) {
    size_t pos = 0;
    std::string part;
    std::vector<std::string> strings;
    while ((pos = s.find(' ')) != std::string::npos) {
        strings.push_back(s.substr(0, pos));
        s.erase(s.begin(), s.begin() + (pos + 1));
    }
    strings.push_back(s);
    return strings;
}

static inline void read_lines(const std::string& file, std::vector<std::string>& lines) {
    std::ifstream infile(file);
    std::string line;
    while (std::getline(infile, line))
    {
        strip(line);
        lines.push_back(line);
    }
}

