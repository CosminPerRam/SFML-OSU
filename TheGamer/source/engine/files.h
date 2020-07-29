
#include <stdexcept>
#include <sstream>
#include <fstream>

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
}