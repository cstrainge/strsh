
#pragma once



namespace strsh
{


    enum class TokenType
    {
        String,
        Number,
        Identifier,

        Add,
        Subtract,
        Multiply,
        Divide,

        RedirectTo,
        RedirectFrom
    };


    struct Token
    {
        TokenType type;
        Location location;
    };


    using OptionalToken = std::optional<Token>;
    using TokenList = std::vector<Token>;


    class Lexer
    {
        private:
            TokenList tokens;
            size_t current;

        public:
            Lexer(std::fs::path const& new_path, std::string const& new_source);
            Lexer(std::fs::path const& new_path, std::istream& new_source);

        public:
            operator bool() const noexcept;

        public:
            OptionalToken peek_next() const noexcept;
            OptionalToken next() noexcept;

        private:
            TokenList read_tokens(SourceBuffer&& source) const;
    };


}
