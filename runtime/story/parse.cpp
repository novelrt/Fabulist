#include <fstream>
#include <stdexcept>

#include <nlohmann/json.hpp>

#include <fabulist/runtime/action.hpp>
#include <fabulist/runtime/actions/line.hpp>
#include <fabulist/runtime/section.hpp>
#include <fabulist/runtime/story.hpp>

using namespace fabulist::runtime;

story fabulist::runtime::parse_story(std::filesystem::path path)
{
    std::ifstream file{path};
    return parse_story(file);
}

section parse_section(nlohmann::json& value);
action parse_action(nlohmann::json const& value);

story fabulist::runtime::parse_story(std::istream& stream)
{
    nlohmann::json root;
    stream >> root;

    if (!root.is_object())
        throw std::runtime_error{"expected json object"};

    std::unordered_map<std::string, section> sections;

    for (const auto& [key, value] : root.items())
    {
        sections[key] = parse_section(value);
    }

    return story{};//sections};
}

section parse_section(nlohmann::json& value)
{
    if (!value.is_array())
        throw std::runtime_error{"expected json array"};

    std::vector<action> actions;

    for (const auto& elem : value)
    {
        actions.push_back(parse_action(elem));
    }

    return section{};//actions};
}

action parse_action(nlohmann::json const&)
{
    return actions::line{};
}
