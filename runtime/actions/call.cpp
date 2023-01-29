#include <fabulist/runtime/actions/call.hpp>

#include <fabulist/runtime/action.hpp>
#include <fabulist/runtime/decoder.hpp>
#include <fabulist/runtime/runtime.hpp>
#include <fabulist/runtime/state.hpp>
#include <fabulist/runtime/story.hpp>

namespace fr = fabulist::runtime;
using namespace fr::actions;

struct detail::call
{
    std::string method;
    std::vector<std::string> parameters;
};

call::call(std::string const& method, std::vector<std::string> parameters)
: action{}
, _pimpl{ new detail::call { method, parameters }}
{ }
call::~call() noexcept = default;
call::call(call&&) = default;
call& call::operator=(call&&) = default;

void call::execute(state& state) const
{
    auto const& methods = state.get_story()->get_runtime()->methods();
    auto method = methods.at(_pimpl->method);

    method(_pimpl->parameters);
}

std::string call::type() const noexcept
{
    return "call";
}

std::string call::method() const noexcept
{
    return _pimpl->method;
}

template<>
call fr::decoder_traits<call>::decoder(decoder_ctx const& ctx)
{
    return call{
        ctx.get_value<std::string>("method"),
        ctx.get_value<std::vector<std::string>>("parameters")
    };
}
