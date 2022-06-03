#ifndef DECODER_HPP
#define DECODER_HPP

#include <memory>
#include <string>
#include <vector>

#include "fabulist_runtime_export.hpp"

namespace fabulist::runtime
{

class action;

namespace detail
{

struct decoder_ctx;

}

class decoder_ctx;

template <typename T>
struct FABULIST_RUNTIME_EXPORT decoder_traits
{
    static T decoder(decoder_ctx const& context);
};

class FABULIST_RUNTIME_EXPORT decoder_ctx
{
    public:
        explicit decoder_ctx(detail::decoder_ctx* impl);
        ~decoder_ctx() noexcept;

        decoder_ctx(const decoder_ctx&) = delete;
        decoder_ctx& operator=(const decoder_ctx&) = delete;
        decoder_ctx(decoder_ctx&&) = delete;
        decoder_ctx& operator=(decoder_ctx&&) = delete;

        decoder_ctx get(std::string const& key) const;
        decoder_ctx get(size_t index) const;

        size_t size() const;

        template <typename T>
        T get_value(std::string key) const
        {
            return decoder_traits<T>::decoder(get(key));
        }

        template <typename T>
        T get_value(size_t index) const
        {
            return decoder_traits<T>::decoder(get(index));
        }

    private:
        std::unique_ptr<detail::decoder_ctx> _pimpl;

        friend decoder_traits<bool>;
        friend decoder_traits<std::string>;
        friend decoder_traits<action>;
};

template <typename T>
struct decoder_traits<std::vector<T>>
{
    static std::vector<T> decoder(decoder_ctx const& context)
    {
        std::vector<T> result{};
        result.reserve(context.size());

        for (size_t n = 0; n < context.size(); n++)
        {
            result.emplace_back(context.get_value<T>(n));
        }

        return result;
    }
};

}

#endif /* DECODER_HPP */
