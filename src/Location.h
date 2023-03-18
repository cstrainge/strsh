
#pragma once


namespace strsh
{


    class Location
    {
        private:
            size_t line = 1;
            size_t column = 1;

            std::shared_ptr<std::fs::path> path;

        public:
            Location(std::fs::path const& new_path);

        public:
            std::fs::path get_path() const
            {
                return *path;
            }

            size_t get_line() const noexcept
            {
                return line;
            }

            size_t get_column() const noexcept
            {
                return column;
            }

        public:
            void next() noexcept;
            void next_line() noexcept;
    };


}
