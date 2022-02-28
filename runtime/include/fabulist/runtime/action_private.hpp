#ifndef ACTION_PRIVATE_HPP
#define ACTION_PRIVATE_HPP

#include <string>

#include "fabulist_runtime_export.hpp"

namespace fabulist::runtime::detail
{

class FABULIST_RUNTIME_EXPORT action
{
    public:
        std::string type;
};

}

#endif /* ACTION_PRIVATE_HPP */
