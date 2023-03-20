
#include "strsh.h"
#include "Location.h"


namespace strsh
{


    Location::Location()
    : line(1),
      column(1)
    {
    }


    Location::Location(std::fs::path const& new_path)
    : line(1),
      column(1),
      path(std::make_shared<std::fs::path>(new_path))
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
