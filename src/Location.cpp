
#include "strsh.h"
#include "Location.h"


namespace strsh
{


    Location::Location(std::fs::path const& new_path)
    : path(std::make_shared<std::fs::path>(new_path))
    {
    }


    void Location::next() noexcept
    {
        ++column;
    }


    void Location::next_line() noexcept
    {
        ++line;
        column = 1;
    }


}
