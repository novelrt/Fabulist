#ifndef FABULIST_SPEAKER_IMPL_HPP
#define FABULIST_SPEAKER_IMPL_HPP

#include <string>

#include <fabulist_export.hpp>

namespace fabulist::detail
{

struct speaker_impl
{
    std::string name;

    explicit speaker_impl(std::string name)
        : name(name)
    { }
};

};

#endif /* FABULIST_SPEAKER_IMPL_HPP */
