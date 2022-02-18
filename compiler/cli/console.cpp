#include <iostream>

#include "console.hpp"

// A dummy ostream used to disable verbose output if the flag isn't set
class null_buffer : public std::streambuf
{ };

class null_ostream : private null_buffer, public std::ostream
{
public:
    null_ostream() : std::ostream(this)
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

void cli::setup_output(cli::parsed_arguments const& arguments)
{
    enable_verbose = arguments.enable_verbose;
}
