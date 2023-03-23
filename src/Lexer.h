
#pragma once



namespace strsh
{


    enum class TokenType
    {
        String,
        OpaqueString,
        CommandString,
        Number,
        Identifier,

        Add,
        Subtract,
        Multiply,
        Divide,

        RedirectTo,
        RedirectFrom,

        EndOfStatement
    };


    struct Token
    {
        TokenType type;
        Location location;
        std::string value;
    };


    using OptionalToken = std::optional<Token>;
    using TokenList = std::vector<Token>;


    class Lexer
    {
        private:
            TokenList tokens;
            size_t position;

        public:
            Lexer() noexcept;
            Lexer(Location original_location, std::string const& new_source);
            Lexer(std::fs::path const& new_path, std::string const& new_source);
            Lexer(std::fs::path const& new_path, std::istream& new_source);

        public:
            operator bool() const noexcept;

        public:
            OptionalToken peek_next() const noexcept;
            OptionalToken next() noexcept;

        private:
            TokenList read_tokens(SourceBuffer&& source) const;

            bool is_comment_char(char next) const noexcept;
            bool is_whitespace_char(char next) const noexcept;
            bool is_string_char(char next) const;
            bool is_operator_char(char next) const;
            bool is_separator_char(char next) const noexcept;

            void extract_comment(SourceBuffer& source) const;

            Token extract_string(SourceBuffer& source) const;

            Token extract_operator(SourceBuffer& source) const;

            bool is_identifier_char(char next) const;
            Token extract_identifier(SourceBuffer& source) const;

            bool is_number_char(char next) const;
            Token extract_number(SourceBuffer& source) const;

            Token extract_unquoted_string(SourceBuffer& source) const;
    };


}
