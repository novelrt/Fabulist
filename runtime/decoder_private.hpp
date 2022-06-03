#ifndef DECODER_PRIVATE_HPP
#define DECODER_PRIVATE_HPP

#include <nlohmann/json.hpp>

namespace fabulist::runtime
{

class decoder_ctx;
class runtime;

decoder_ctx create_decoder_context(runtime const& runtime, nlohmann::json const& value);

}

#endif /* DECODER_PRIVATE_HPP */
