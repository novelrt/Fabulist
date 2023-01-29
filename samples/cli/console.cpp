#include <iostream>
#include <typeinfo>

#if defined(__has_include)
#if __has_include(<cxxabi.h>)
#define USE_CXXABI_DEMANGLE 1
#include <cxxabi.h>
#endif
#endif

#ifndef USE_CXXABI_DEMANGLE
#define USE_CXXABI_DEMANGLE 0
#endif

#include "console.hpp"

// A dummy ostream used to disable verbose output if the flag isn't set
class null_ostream : public std::ostream
{
public:
    null_ostream() : std::ostream(nullptr)
    { }
};

static std::string program;
static bool enable_verbose;
static null_ostream null_output;

void cli::detail::set_program_name(std::string name)
{
    program = name;
}

std::ostream& cli::error(std::ostream& stream)
{
    return stream << program << ": ";
}

std::ostream& cli::usage(std::ostream& stream)
{
    return cli::detail::usage(stream, program);
}

std::ostream& cli::verbose(std::ostream& stream)
{
    if (!enable_verbose)
    {
        return null_output;
    }
    else
    {
        return stream;
    }
}

std::string demangle(std::string name)
{
#if USE_CXXABI_DEMANGLE
    int status;
    char* buffer = abi::__cxa_demangle(name.c_str(), nullptr, nullptr, &status);

    if (status == 0)
    {
        // n is the size of the buffer, not the size of the string
        std::string result(buffer);

        // __cxa_demangle calls malloc() if buf is nullptr
        free(buffer);

        return result;
    }
    else
        throw std::runtime_error{"abi::__cxa_demangle failed"};
#else
    return name;
#endif
}

void output_exception(std::exception const& exception)
{
    std::cerr
        << demangle(typeid(exception).name()) << ": "
        << exception.what() << '\n';

    try
    {
        std::rethrow_if_nested(exception);
    }
    catch (std::exception const& nested)
    {
        std::cerr << "Caused by:\n";
        output_exception(nested);
    }
    catch(...)
    {
        std::cerr << "unknown exception type\n";
    }
}

void cli::setup_output(cli::parsed_arguments const& arguments)
{
    enable_verbose = arguments.enable_verbose;

    std::set_terminate([](){
        // Remove our handler in case terminate() gets called recursively
        std::set_terminate(nullptr);

        if (std::exception_ptr e = std::current_exception())
        {
            std::cerr << "Unhandled exception thrown\n";

            try
            {
                std::rethrow_exception(e);
            }
            catch(std::exception const& ex)
            {
                output_exception(ex);
            }
            catch(...)
            {
                std::cerr << "unknown exception type\n";
            }
        }

        std::abort();
    });
}
