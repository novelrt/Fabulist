#include <fabulist/runtime/actions/action.hpp>

#include <fabulist/runtime/action.hpp>
#include <fabulist/runtime/decoder.hpp>
#include <fabulist/runtime/runtime.hpp>

#include "decoder_private.hpp"

using namespace fabulist::runtime;

struct detail::decoder_ctx
{
    fabulist::runtime::runtime const& runtime;
    nlohmann::json const& value;
};

decoder_ctx::decoder_ctx(detail::decoder_ctx* impl)
    : _pimpl{impl}
{ }
decoder_ctx::~decoder_ctx() noexcept = default;

decoder_ctx decoder_ctx::get(std::string const& key) const
{
    return decoder_ctx{new detail::decoder_ctx{_pimpl->runtime, _pimpl->value.at(key)}};
}

decoder_ctx decoder_ctx::get(size_t index) const
{
    return decoder_ctx{new detail::decoder_ctx{_pimpl->runtime, _pimpl->value.at(index)}};
}

size_t decoder_ctx::size() const
{
    return _pimpl->value.size();
}

decoder_ctx fabulist::runtime::create_decoder_context(runtime const& runtime, nlohmann::json const& value)
{
    return decoder_ctx{new detail::decoder_ctx{runtime, value}};
}

template<>
std::string fabulist::runtime::decoder_traits<std::string>::decoder(decoder_ctx const& ctx)
{
    return ctx._pimpl->value;
}

template<>
action fabulist::runtime::decoder_traits<action>::decoder(decoder_ctx const& ctx)
{
    auto const& value = ctx._pimpl->value;
    auto const& runtime = ctx._pimpl->runtime;

    std::string type = value.at("type").get<std::string>();

    auto decoder = runtime.decoders().find(type);
    if (decoder == runtime.decoders().end())
        throw std::out_of_range{"unknown action type " + type};

    return decoder->second(ctx);
}
