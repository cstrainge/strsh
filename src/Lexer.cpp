
#include "strsh.h"
#include "Location.h"
#include "SourceBuffer.h"
#include "Lexer.h"


namespace strsh
{


    Lexer::Lexer(std::fs::path const& new_path, std::string const& new_source)
    : buffer(new_path, new_source)
    {
    }


    Lexer::Lexer(std::fs::path const& new_path, std::istream& new_source)
    : buffer(new_path, new_source)
    {
    }


    Lexer::operator bool() const noexcept
    {
        return buffer;
    }


    OptionalToken Lexer::peek_next() const noexcept
    {
        return OptionalToken();
    }


    OptionalToken Lexer::next() noexcept
    {
        return OptionalToken();
    }


}
