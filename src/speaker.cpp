#include <fabulist/speaker.hpp>

#include <speaker_impl.hpp>

using namespace fabulist;

speaker::speaker(std::string name)
    : _impl(std::make_unique<detail::speaker_impl>(name))
{ }

speaker::~speaker() noexcept = default;
speaker::speaker(speaker&&) = default;
speaker& speaker::operator=(speaker&&) = default;

std::string speaker::get_name() const
{
    return _impl->name;
}
