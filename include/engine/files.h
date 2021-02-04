
#pragma once

#include <stdexcept>
#include <sstream>
#include <fstream>
#include <vector>

#include <filesystem>

namespace engine::utilities::files
{
    enum type { File, Directory };

    inline std::string getFileContent(const std::string& path)
    {
        std::ifstream fin(path);

        if (!fin.is_open())
        {
            std::string error = "Unable to open file: " + path + "!";

            throw std::runtime_error(error);
        }

        std::ostringstream stream;
        stream << fin.rdbuf();

        return stream.str();
    }

    inline void setFileContent(const std::string& filePath, const std::string& content)
    {
        std::ofstream fout(filePath);

        fout << content;
        fout.close();
    }

    inline bool exists(const std::string& filePath)
    {
        return std::filesystem::exists(filePath);
    }

    inline bool is_folder(const std::string& folderPath)
    {
        if (!exists(folderPath))
            return false;

        return std::filesystem::is_directory(folderPath);
    }

    inline std::vector<std::string> folderContents(const std::string& folderPath, unsigned type = 0, const std::string& extension = ".")
    {
        std::vector<std::string> names;

        if (!is_folder(folderPath))
            return names;

        switch (type)
        {
        case type::File:
            if (extension != ".") {
                for (auto& p : std::filesystem::directory_iterator(folderPath))
                {
                    if (p.path().has_extension() && p.path().extension() == extension)
                        names.emplace_back(p.path().generic_string());
                }
            }
            else {
                for (auto& p : std::filesystem::directory_iterator(folderPath))
                    names.emplace_back(p.path().generic_string());
            }

            break;
        case type::Directory:
            for (auto& p : std::filesystem::directory_iterator(folderPath))
            {
                if (p.is_directory())
                    names.emplace_back(p.path().generic_string());
            }

            break;
        default:
            break;
        }

        return names;
    }
}