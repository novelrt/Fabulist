#ifndef @GITVERSION_INCLUDE_GUARD_NAME@
#define @GITVERSION_INCLUDE_GUARD_NAME@

#if @GITVERSION_USE_STD_STRING@ /* USE_STD_STRING */
#include <string>
#elseif @GITVERSION_USE_STD_STRING_VIEW@ /* USE_STD_STRING_VIEW */
#include <string_view>
#endif

#if @GITVERSION_USE_NAMESPACE@ /* USE_NAMESPACE */
namespace @GITVERSION_NAMESPACE@::version
{
#endif

#if @GITVERSION_USE_CONSTEXPR@ /* USE_CONSTEXPR */
    constexpr
#endif
#if @GITVERSION_USE_STD_STRING@ /* USE_STD_STRING */
    std::string
#elif @GITVERSION_USE_STD_STRING_VIEW@ /* USE_STD_STRING_VIEW */
    std::string_view
#else
    char const
#endif
    version_string
#if !(@GITVERSION_USE_STD_STRING@ || @GITVERSION_USE_STD_STRING_VIEW@) /* USE_STD_STRING || USE_STD_STRING_VIEW */
    []
#endif
    = "@GITVERSION_VERSION_STRING@";

#if @GITVERSION_USE_CONSTEXPR@ /* USE_CONSTEXPR */
    constexpr
#endif
    auto major = @GITVERSION_VERSION_MAJOR@;
#if @GITVERSION_USE_CONSTEXPR@ /* USE_CONSTEXPR */
    constexpr
#endif
    auto minor = @GITVERSION_VERSION_MINOR@;
#if @GITVERSION_USE_CONSTEXPR@ /* USE_CONSTEXPR */
    constexpr
#endif
    auto patch = @GITVERSION_VERSION_PATCH@;

#if @GITVERSION_USE_NAMESPACE@ /* USE_NAMESPACE */
}
#endif

#endif /* @GITVERSION_INCLUDE_GUARD_NAME@ */
