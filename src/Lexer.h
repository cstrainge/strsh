
#pragma once



namespace strsh
{


    enum class TokenType
    {
        None
    };


    struct Token
    {
        TokenType type;
        Location location;
    };


    using OptionalToken = std::optional<Token>;


    class Lexer
    {
        private:
            SourceBuffer buffer;

        public:
            Lexer(std::fs::path const& new_path, std::string const& new_source);
            Lexer(std::fs::path const& new_path, std::istream& new_source);

        public:
            operator bool() const noexcept;

        public:
            OptionalToken peek_next() const noexcept;
            OptionalToken next() noexcept;
    };


}
