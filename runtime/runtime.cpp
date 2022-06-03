#include <fstream>
#include <stdexcept>
#include <unordered_map>

#include <nlohmann/json.hpp>

#include <fabulist/runtime/actions/action.hpp>

#include <fabulist/runtime/action.hpp>
#include <fabulist/runtime/load_exception.hpp>
#include <fabulist/runtime/runtime.hpp>
#include <fabulist/runtime/section.hpp>
#include <fabulist/runtime/state.hpp>
#include <fabulist/runtime/story.hpp>

#include <fabulist/runtime/actions/jump.hpp>
#include <fabulist/runtime/actions/line.hpp>
#include <fabulist/runtime/actions/options.hpp>

#include "decoder_private.hpp"

using namespace fabulist::runtime;

struct detail::runtime
{
    std::unordered_map<std::string, fabulist::runtime::runtime::decoder_type> decoders;
};

runtime::runtime()
    : _pimpl{new detail::runtime()}
{ }
runtime::~runtime() noexcept = default;
runtime::runtime(runtime&&) = default;
runtime& runtime::operator=(runtime&&) = default;

void runtime::register_action(std::string const& type, decoder_type decoder)
{
    _pimpl->decoders[type] = decoder;
}

std::unordered_map<std::string, runtime::decoder_type> const& runtime::decoders() const noexcept
{
    return _pimpl->decoders;
}

story runtime::load_story(std::filesystem::path path)
{
    std::fstream file{path};
    return load_story(file, path.filename().string());
}

story runtime::load_story(std::istream& stream, std::string name)
{
    auto parse_section = [this](std::string const& name, nlohmann::json& value)
    {
        if (!value.is_array())
            throw std::runtime_error{"expected json array"};

        std::vector<action> actions{};
        actions.reserve(value.size());

        for (const auto& elem : value)
        {
            auto context = create_decoder_context(*this, elem);
            actions.push_back(decoder_traits<action>::decoder(context));
        }

        return section{name, std::move(actions)};
    };

    try
    {
        nlohmann::json root;
        stream >> root;

        if (!root.is_object())
            throw std::runtime_error{"expected json object"};

        std::unordered_map<std::string, section> sections;
        sections.reserve(root.size());

        for (const auto& [key, value] : root.items())
        {
            sections.emplace(key, parse_section(key, value));
        }

        return story{std::move(sections)};
    }
    catch(...)
    {
        std::throw_with_nested( load_exception{"failed to load story " + name, name} );
    }
}

void fabulist::runtime::register_default_actions(runtime& runtime)
{
    runtime.register_action<actions::line>("line");
    runtime.register_action<actions::options>("options");
    runtime.register_action<actions::jump>("jump");
}
