
#include "strsh.h"
#include "Location.h"
#include "SourceBuffer.h"


namespace strsh
{


    SourceBuffer::SourceBuffer() noexcept
    : position(0),
      source_location("")
    {
    }


    SourceBuffer::SourceBuffer(std::fs::path const& new_path, std::string const& new_source)
    : source_location(new_path),
      source(new_source),
      position(0)
    {
    }


    SourceBuffer::SourceBuffer(std::fs::path const& new_path, std::istream& source)
    : source_location(new_path),
      source(read_stream(source)),
      position(0)
    {
    }


    SourceBuffer::SourceBuffer(SourceBuffer const& buffer)
    : source(buffer.source),
      position(buffer.position),
      source_location(buffer.source_location)
    {
    }


    SourceBuffer::SourceBuffer(SourceBuffer&& buffer)
    : source(std::move(buffer.source)),
      position(buffer.position),
      source_location(std::move(buffer.source_location))
    {
        buffer.position = 0;
        buffer.source_location = Location("");
    }


    OptionalChar SourceBuffer::peek_next(size_t lookahead) const noexcept
    {
        if (position >= source.size())
        {
            return OptionalChar();
        }

        return source[position];
    }


    OptionalChar SourceBuffer::next() noexcept
    {
        auto next = peek_next();

        if (next)
        {
            increment_position(next.value());
        }

        return next;
    }

    SourceBuffer& SourceBuffer::operator =(SourceBuffer const& buffer)
    {
        if (&buffer != this)
        {
            source = buffer.source;
            position = buffer.position;
            source_location = buffer.source_location;
        }

        return *this;
    }


    SourceBuffer& SourceBuffer::operator =(SourceBuffer&& buffer)
    {
        if (&buffer != this)
        {
            source = std::move(buffer.source);
            position = buffer.position;
            source_location = buffer.source_location;

            buffer.position = 0;
            buffer.source_location = Location("");
        }

        return *this;
    }


    Location SourceBuffer::current_location() const noexcept
    {
        return source_location;
    }


    std::string&& SourceBuffer::read_stream(std::istream& new_source) const
    {
        auto begin = std::istreambuf_iterator<char>(new_source);
        auto end = std::istreambuf_iterator<char>();

        return std::move(std::string(begin, end));
    }


    void SourceBuffer::increment_position(char next) noexcept
    {
        ++position;

        if (next == '\n')
        {
            source_location.next_line();
        }
        else
        {
            source_location.next();
        }
    }


}
