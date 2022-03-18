#include <fabulist/runtime/actions/line.hpp>

#include <fabulist/runtime/decoder.hpp>
#include <fabulist/runtime/state.hpp>

namespace fr = fabulist::runtime;
using namespace fr::actions;

struct detail::line
{
    std::string speaker;
    std::string text;
};

line::line(std::string const& speaker, std::string const& text)
    : action{}
    , _pimpl{ new detail::line{ speaker, text } }
{ }
line::~line() noexcept = default;
line::line(line&&) = default;
line& line::operator=(line&&) = default;

void line::execute(state&) const
{

}

std::string line::type() const noexcept
{
    return "line";
}

std::string line::speaker() const noexcept
{
    return _pimpl->speaker;
}

std::string line::text() const noexcept
{
    return _pimpl->text;
}

template<>
line fr::decoder_traits<line>::decoder(decoder_ctx const& ctx)
{
    return line{
        ctx.get_value<std::string>("speaker"),
        ctx.get_value<std::string>("text")
    };
}
