
#pragma once


namespace strsh
{


    class SourceBuffer
    {
        private:
            std::string source;
            size_t position;
            Location source_location;

        public:
            SourceBuffer() noexcept;
            SourceBuffer(Location original_location, std::string const& new_source);
            SourceBuffer(std::fs::path const& new_path, std::string const& new_source);
            SourceBuffer(std::fs::path const& new_path, std::istream& new_source);
            SourceBuffer(SourceBuffer const& buffer);
            SourceBuffer(SourceBuffer&& buffer);

        public:
            SourceBuffer& operator =(SourceBuffer const& buffer);
            SourceBuffer& operator =(SourceBuffer&& buffer);

            operator bool() const noexcept;

        public:
            OptionalChar peek_next() const noexcept;
            OptionalChar next() noexcept;

            Location current_location() const noexcept;

        private:
            std::string read_stream(std::istream& new_source) const;
            void increment_position(char next) noexcept;
    };


}
