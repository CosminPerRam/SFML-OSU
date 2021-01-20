
#pragma once

#include <unordered_map>
#include <string>
#include <stdexcept>

namespace engine::resource
{
    template<typename resource>
    class manager
    {
    public:
        manager(const std::string& folder, const std::string& extension)
            : m_folder("res/" + folder + "/"), m_extension("." + extension)
        {

        }

        const resource& get(const std::string& name)
        {
            if (!exists(name)) {
                add(name);
            }

            return m_resources.at(name);
        }

    private:
        bool exists(const std::string& name) const {
            return (m_resources.find(name) != m_resources.end());
        }

        void add(const std::string& name)
        {
            resource f_resource;

            if (f_resource.loadFromFile(path(name)))
                m_resources.insert(std::make_pair(name, f_resource));
            else
            {
                throw std::runtime_error("Couldn't find " + path(name) + "!");
                f_resource.loadFromFile(path("_missing"));
                m_resources.insert(std::make_pair(name, f_resource));
            }
        }

        std::string path(const std::string& name) {
            return (m_folder + name + m_extension);
        }

        const std::string m_folder;
        const std::string m_extension;

        std::unordered_map<std::string, resource> m_resources;
    };
}