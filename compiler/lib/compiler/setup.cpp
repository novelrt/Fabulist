#include <fabulist/compiler/compiler.hpp>
#include <fabulist/compiler/section.hpp>

#include "compiler.hpp"

using namespace fabulist::compiler;

#define ACTIONS \
    ACTION(jump) \
    ACTION(options)

enum class action
{
#define ACTION(name) name,
ACTIONS
#undef ACTION
};

compiler::compiler()
    : _pimpl{new detail::compiler{}}
{

}

compiler::~compiler() noexcept = default;
compiler::compiler(compiler&&) = default;
compiler& compiler::operator=(compiler&&) = default;
