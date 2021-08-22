//
// Created by ivar on 2021-07-15.
//

#ifndef TESTPROJECT_SETTINGS_H
#define TESTPROJECT_SETTINGS_H

#include <string>

class Settings
{
public:
    static void SetTheme(const std::string& theme);
    static void SetFilesPath(std::string path) { s_filesPath = path; }
    static const std::string& GetFilesPath() { return s_filesPath; }

private:
    static std::string s_filesPath;
};


#endif //TESTPROJECT_SETTINGS_H
