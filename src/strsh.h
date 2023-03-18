
#pragma once


#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <stdexcept>
#include <variant>
#include <optional>


namespace std
{
    namespace fs = filesystem;
}


namespace strsh
{
    using OptionalChar = std::optional<char>;
}
