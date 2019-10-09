#pragma once

namespace Terminal
{
    ///
    /// \brief Print a string to the terminal followed by and automatically added endline.
    /// \param str null-terminated string to print.
    /// \note // TODO Should accept etl::string_view instead.
    ///
    void Print(const char* str);
}
