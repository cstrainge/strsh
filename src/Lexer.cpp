
#include "strsh.h"
#include "Location.h"
#include "SourceBuffer.h"
#include "Lexer.h"


namespace strsh
{


    Lexer::Lexer() noexcept
    : position(0)
    {
    }


    Lexer::Lexer(Location original_location, std::string const& new_source)
    : tokens(read_tokens(SourceBuffer(original_location, new_source))),
      position(0)
    {
    }


    Lexer::Lexer(std::fs::path const& new_path, std::string const& new_source)
    : tokens(read_tokens(SourceBuffer(new_path, new_source))),
      position(0)
    {
    }


    Lexer::Lexer(std::fs::path const& new_path, std::istream& new_source)
    : tokens(read_tokens(SourceBuffer(new_path, new_source))),
      position(0)
    {
    }


    Lexer::operator bool() const noexcept
    {
        return position < tokens.size();
    }


    OptionalToken Lexer::peek_next() const noexcept
    {
        return OptionalToken();
    }


    OptionalToken Lexer::next() noexcept
    {
        return OptionalToken();
    }


    TokenList Lexer::read_tokens(SourceBuffer&& source) const
    {
        TokenList new_tokens;

        while (source)
        {
            auto next = source.peek_next();

            if (!next)
            {
                continue;
            }

            auto next_char = next.value();

            if (is_comment_char(next_char))
            {
                extract_comment(source);
            }
            else if (is_string_char(next_char))
            {
                new_tokens.push_back(extract_string(source));
            }
            else if (is_operator_char(next_char))
            {
                new_tokens.push_back(extract_operator(source));
            }
            else if (is_identifier_char(next_char))
            {
                new_tokens.push_back(extract_identifier(source));
            }
            else if (is_number_char(next_char))
            {
                new_tokens.push_back(extract_number(source));
            }
            else
            {
                new_tokens.push_back(extract_unquoted_string(source));
            }
        }

        return new_tokens;
    }


    bool Lexer::is_comment_char(char next) const
    {
        return next == '#';
    }


    bool Lexer::is_whitespace_char(char next) const noexcept
    {
        return (   (next == ' ')
                || (next == '\t')
                || (next == '\n'));
    }


    bool Lexer::is_string_char(char next) const
    {
        return (   (next == '`')
                || (next == '\'')
                || (next == '"'));
    }


    bool Lexer::is_operator_char(char next) const
    {
        return false;
    }


    bool Lexer::is_separator_char(char next) const noexcept
    {
        return (   (is_comment_char(next))
                || (is_whitespace_char(next))
                || (is_string_char(next))
                || (is_string_char(next))
                || (is_operator_char(next)));
    }


    void Lexer::extract_comment(SourceBuffer& source) const
    {
        char next = source.next().value();

        while ((next != '\n') && (source.peek_next()))
        {
            next = source.next().value();
        }
    }


    Token Lexer::extract_string(SourceBuffer& source) const
    {
        Location location = source.current_location();
        char quote_char = source.next().value();
        std::string value;
        TokenType type;

        switch (quote_char)
        {
            case '"':
                type = TokenType::String;
                break;

            case '\'':
                type = TokenType::OpaqueString;
                break;

            case '`':
                type = TokenType::CommandString;
                break;
        }

        while (   (source)
               && (source.peek_next().value() != quote_char))
        {
            auto next = source.next().value();

            if (next == '\\')
            {
                auto real_char = source.next();

                if (!real_char)
                {
                    // Throw unexpected end of stream.
                }

                // TODO: Do something more useful here like handling \n and numeric values etc.
                next = real_char.value();
            }

            value += next;
        }

        if (!source)
        {
            // TODO: Throw unexpected end of stream before finding quote_char.
        }

        return { .type = type, .location = location };
    }


    Token Lexer::extract_operator(SourceBuffer& source) const
    {
        return {};
    }


    bool Lexer::is_identifier_char(char next) const
    {
        return    ((next >= 'a') && (next <= 'z'))
               || ((next >= 'A') && (next <= 'Z'))
               || (next == '_');
    }


    Token Lexer::extract_identifier(SourceBuffer& source) const
    {
        // TODO: Extract possible sub expressions.
        // TODO: Support ${identifier} properly.

        Location location = source.current_location();
        source.next();

        std::string value;

        while ((source) && (!is_separator_char(source.peek_next().value())))
        {
            value += source.next().value();
        }

        return { .type = TokenType::Identifier, .location = location, .value = value };
    }


    bool Lexer::is_number_char(char next) const
    {
        return false;
    }


    Token Lexer::extract_number(SourceBuffer& source) const
    {
        return {};
    }


    Token Lexer::extract_unquoted_string(SourceBuffer& source) const
    {
        Location current = source.current_location();
        std::string string;

        string += source.next().value();

        while ((source) && !is_whitespace_char(source.peek_next().value()))
        {
            string += source.next().value();
        }

        return { .type = TokenType::String, .location = current, .value = string };
    }


}
