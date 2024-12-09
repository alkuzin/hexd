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

#ifndef HEXD_H
#define HEXD_H

#include <string.h>


enum MODE {
    HEX,
    OCT,
    BIN,
};

/** @brief Display list of commands.*/
void hexd_help(void);

/** @brief Display version.*/
void hexd_version(void);

/**
 * @brief Memory dump of given file.
 *
 * @param [in] mode - given bytes output mode.
 * @param [in] filename - given target filename.
 */
void hexd_dump(enum MODE mode, const char *filename);

#endif // HEXD_H