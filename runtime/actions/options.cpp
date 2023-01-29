#include <iterator>
#include <algorithm>

#include <fabulist/runtime/action.hpp>
#include <fabulist/runtime/actions/options.hpp>

#include <fabulist/runtime/decoder.hpp>
#include <fabulist/runtime/state.hpp>

namespace fr = fabulist::runtime;
using namespace fr::actions;



struct detail::options
{
    std::vector<option> options;
};

options::options(std::vector<option>&& options)
    : action{}
    , _pimpl{ new detail::options{ std::move(options) } }
{ }
options::~options() noexcept = default;
options::options(options&&) = default;
options& options::operator=(options&&) = default;

void options::execute(state& state) const
{
    std::vector<std::string> options;
    options.reserve(size());

    std::transform(begin(), end(),
        std::back_inserter(options),
        [](option const& option)
        {
            return option.name;
        });

    // query() returns cend() if the user did not select an option
    auto selected = state.query(options);
    if (selected == options.cend())
        return;

    // Translate the valid iterator to the correct set of actions to take.
    auto it = std::next(begin(), std::distance(options.cbegin(), selected));
    for (auto const& action : it->actions)
    {
        action.execute(state);
    }
}

std::string options::type() const noexcept
{
    return "options";
}

option const& options::at(std::vector<option>::size_type index) const noexcept
{
    return _pimpl->options.at(index);
}

option const& options::operator[](std::vector<option>::size_type index) const noexcept
{
    return _pimpl->options.at(index);
}

std::vector<option>::const_iterator options::begin() const noexcept
{
    return _pimpl->options.cbegin();
}

std::vector<option>::const_iterator options::end() const noexcept
{
    return _pimpl->options.cend();
}

std::vector<option>::size_type options::size() const noexcept
{
    return _pimpl->options.size();
}

template<>
options fr::decoder_traits<options>::decoder(decoder_ctx const& ctx)
{
    return options{
        ctx.get_value<std::vector<option>>("options")
    };
}

template<>
option fr::decoder_traits<option>::decoder(decoder_ctx const& ctx)
{
    return option{
        ctx.get_value<std::string>("name"),
        ctx.get_value<std::vector<action>>("actions")
    };
}
