#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include <filesystem>
#include <functional>
#include <istream>
#include <memory>
#include <string>
#include <type_traits>

#include "decoder.hpp"

#include "fabulist_runtime_export.hpp"

namespace fabulist::runtime
{

class action;
class state;
class story;

namespace detail
{

struct runtime;

}

class FABULIST_RUNTIME_EXPORT runtime
{
    template <typename Action>
    static action decoder_helper(decoder_ctx const& ctx)
    {
        return action { decoder_traits<Action>::decoder(ctx) };
    }

    public:
        using decoder_type = std::function<action(decoder_ctx const&)>;

        explicit runtime();
        ~runtime() noexcept;
        runtime(const runtime&) = delete;
        runtime& operator=(const runtime&) = delete;
        runtime(runtime&&);
        runtime& operator=(runtime&&);

        template <typename Action,
            typename = std::enable_if<std::is_base_of<actions::action, Action>::value>>
        void register_action(std::string type)
        {
            register_action(type, decoder_helper<Action>);
        }

        void register_action(std::string const& type, decoder_type decoder);
        std::unordered_map<std::string, decoder_type> const& decoders() const noexcept;

        story load_story(std::filesystem::path path);
        story load_story(std::istream& stream, std::string name);

    private:
        std::unique_ptr<detail::runtime> _pimpl;
};

void register_default_actions(runtime& runtime);

}

#endif /* RUNTIME_HPP */
