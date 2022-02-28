#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <optional>
#include <ostream>
#include <string>
#include <vector>

namespace cli
{

namespace detail
{

std::ostream& usage(std::ostream& stream, std::string program_name);
void set_program_name(std::string program_name);

}

struct parsed_arguments
{
    std::vector<std::string> input_files;
    std::optional<std::string> output_file;
    bool enable_verbose;
    bool show_usage;
    bool show_version;
};

std::ostream& error(std::ostream& stream);
std::ostream& verbose(std::ostream& stream);
std::ostream& usage(std::ostream& stream);

void setup_output(parsed_arguments const& arguments);

std::optional<parsed_arguments> parse_arguments(int argc, char const** argv);

}

#endif /* CONSOLE_HPP */
