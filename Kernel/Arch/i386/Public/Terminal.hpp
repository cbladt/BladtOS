#pragma once
#include <etl/string_view.h>

namespace Terminal
{
    ///
    /// \brief Print a string to the terminal followed by and automatically added endline.
    /// \param etl::string_view representing a string.
    ///
    void Print(const etl::string_view& string);
}
