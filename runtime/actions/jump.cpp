#include <fabulist/runtime/actions/jump.hpp>

#include <fabulist/runtime/decoder.hpp>
#include <fabulist/runtime/state.hpp>

namespace fr = fabulist::runtime;
using namespace fr::actions;

struct detail::jump
{
    std::string section;
};

jump::jump(std::string const& section)
    : action{}
    , _pimpl{ new detail::jump { section }}
{ }
jump::~jump() noexcept = default;
jump::jump(jump&&) = default;
jump& jump::operator=(jump&&) = default;

void jump::execute(state& state) const
{
    state.jump_to_section(_pimpl->section);
}

std::string jump::type() const noexcept
{
    return "jump";
}

std::string jump::section() const noexcept
{
    return _pimpl->section;
}

template<>
jump fr::decoder_traits<jump>::decoder(decoder_ctx const& ctx)
{
    return jump{
        ctx.get_value<std::string>("section")
    };
}
