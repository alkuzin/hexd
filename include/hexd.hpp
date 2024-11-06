/**
 * Tool for displaying file contents in hexadecimal, octal,
 * binary and ascii formats.
 * Copyright (C) 2024 Alexander (@alkuzin).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _HEXD_HPP_
#define _HEXD_HPP_

#include <string>

namespace hexd {

enum class MODE {
    HEX,
    OCT,
    BIN,
};

/** @brief Display list of commands.*/
void help(void) noexcept;

/** @brief Display version.*/
void version(void) noexcept;

/**
 * @brief Memory dump of given file.
 *
 * @param [in] mode - given bytes output mode.
 * @param [in] filename - given target filename.
 */
void dump(MODE mode, const std::string_view& filename) noexcept;

} // namespace hexd

#endif // _HEXD_HPP_