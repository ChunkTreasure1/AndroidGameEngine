//
// Created by ivar on 2021-07-15.
//

#include "Language.h"
#include <rapidjson/rapidjson.h>
#include <Application/Filesystem/Filesystem.h>
#include <vector>

rapidjson::Document Language::s_currentlyLoadedLanguage;

void Language::Initialize()
{
    LoadLanguage("sv");
}

void Language::LoadLanguage(const std::string &name)
{
    AAsset* pFile = Filesystem::Open("lang/" + name + ".json");
    uint32_t size = Filesystem::GetLength(pFile);

    std::vector<char> text;
    text.resize(size);

    Filesystem::Read(pFile, static_cast<void*>(text.data()), size);
    Filesystem::Close(pFile);

    s_currentlyLoadedLanguage.Parse(text.data());
}

const char * Language::GetSymbol(const std::string &symbol)
{
    if (s_currentlyLoadedLanguage.HasMember(symbol.c_str()))
    {
        if (s_currentlyLoadedLanguage[symbol.c_str()].IsString())
        {
            return s_currentlyLoadedLanguage[symbol.c_str()].GetString();
        }
    }

    return "NOTFOUND";
}