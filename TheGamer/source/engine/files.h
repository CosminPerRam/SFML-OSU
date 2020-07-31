
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <vector>

#include <filesystem>

namespace engine::utilities::files
{
    std::string getFileContent(const std::string& path)
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

    void setFileContent(const std::string& filePath, const std::string& content)
    {
        std::ofstream fout(filePath);

        fout << content;
        fout.close();
    }

    bool exists(const std::string& filePath)
    {
        return std::filesystem::exists(filePath);
    }

    bool is_folder(const std::string& folderPath)
    {
        if (exists(folderPath))
            return false;

        return std::filesystem::is_directory(folderPath);
    }

    std::vector<std::string> folderContents(const std::string& folderPath, unsigned type = 0, const std::string& extension = ".")
    {
        std::vector<std::string> names;

        if (!is_folder(folderPath))
            return names;

        switch (type)
        {
        case 0:
            for (auto& p : std::filesystem::directory_iterator(folderPath))
                names.emplace_back(p.path().generic_string());

            break;
        case 1:
            for (auto& p : std::filesystem::directory_iterator(folderPath))
            {
                if (p.is_directory())
                    names.emplace_back(p.path().generic_string());
            }

            break;
        case 2:
            for (auto& p : std::filesystem::directory_iterator(folderPath))
            {
                if (p.path().has_extension() && p.path().extension() == extension)
                    names.emplace_back(p.path().generic_string());
            }

            break;
        default:
            break;
        }

        return names;
    }
}