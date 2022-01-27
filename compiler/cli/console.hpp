#ifndef ARGS_HPP
#define ARGS_HPP

namespace cli
{
    std::ostream& error(std::ostream& stream);
    std::ostream& usage(std::ostream& stream);
    bool parseargs(int argc, char** argv, char const** output, int* file_list);
}

#endif /* ARGS_HPP */
