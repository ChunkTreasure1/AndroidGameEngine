//
// Created by ivar on 2021-07-15.
//

#ifndef TESTPROJECT_LANGUAGE_H
#define TESTPROJECT_LANGUAGE_H

#include <string>
#include <rapidjson/document.h>

class Language
{
public:
    static void Initialize();
    static void LoadLanguage(const std::string& name);
    static const char* GetSymbol(const std::string& symbol);

private:
    static rapidjson::Document s_currentlyLoadedLanguage;
};


#endif //TESTPROJECT_LANGUAGE_H
