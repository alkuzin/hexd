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

#include <hexd.hpp>
#include <fstream>
#include <cstring>
#include <print>


namespace hexd {

inline const auto HEXD_VERSION  {"2.0"};
inline const auto HEXD_YEAR     {"2024"};
inline const auto FMT_SIZE      {8};
inline const auto HEXD_TITLE {
    "\n"
    " ██╗  ██╗███████╗██╗  ██╗██████╗  \n"
    " ██║  ██║██╔════╝╚██╗██╔╝██╔══██╗ \n"
    " ███████║█████╗   ╚███╔╝ ██║  ██║ \n"
    " ██╔══██║██╔══╝   ██╔██╗ ██║  ██║ \n"
    " ██║  ██║███████╗██╔╝ ██╗██████╔╝ \n"
    " ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝  \n"
};

void help(void)
{
    std::println(
        "{}\nUSAGE\n"
        "\thexd [options] <file>\n\n"
        "DESCRIPTION\n"
        "\thexd - display file contents in hexadecimal, octal, "
        "binary and ascii formats\n\n"
        "OPTIONS\n"
        "\t-x\t\tone-byte hexidecimal+ASCII display\n"
        "\t-o\t\tone-byte octal display\n"
        "\t-b\t\tone-byte binary display\n\n"
        "\t-h, --help\tdisplay options list\n"
        "\t-v, --version\tdisplay version of hexd", HEXD_TITLE
    );
    std::exit(EXIT_SUCCESS);
}

void version(void)
{
    std::println("{}\nhexd: v{} {} (@alkuzin)", HEXD_TITLE, HEXD_VERSION, HEXD_YEAR);
    std::exit(EXIT_SUCCESS);
}

/**
 * @brief Convert byte to ASCII.
 *
 * @param [in] ch - given byte to convert.
 * @return character to print.
 */
inline char to_print(uint8_t ch) noexcept
{
    return (ch > 31 && ch < 127)? ch : '.';
}

/**
 * @brief Handle bytes output mode.
 *
 * @param [in] mode - given bytes output mode.
 * @param [out] bpl - given bytes per line.
 * @param [out] fmt - given format string.
 */
static void handle_mode(MODE mode, std::size_t *bpl, std::string_view& fmt) noexcept
{
    switch(mode) {
		case MODE::BIN:
            *bpl = 8;
            fmt = "%08b ";
			break;

		case MODE::OCT:
            *bpl = 16;
            fmt = "%03o ";
			break;

		case MODE::HEX:
            *bpl = 16;
            fmt = "%02x ";
			break;

		default:
            *bpl = 16;
            fmt = "%02x ";
			break;
	};
}

void dump(MODE mode, const std::string_view& filename) noexcept
{
    std::ifstream fin(filename.data(), std::ios::in);

    if (!fin.is_open()) {
        std::println("error to open file \"{}\"", filename);
        std::exit(EXIT_FAILURE);
    }

    std::size_t      bytes_per_line {16};
    std::string_view fmt;

    handle_mode(mode, &bytes_per_line, fmt);

    std::uint8_t buffer[bytes_per_line];
    std::size_t  rows = 0;

    while (fin) {
        std::memset(buffer, 0, sizeof(buffer));
        fin.read(reinterpret_cast<char*>(buffer), bytes_per_line);

        std::print("{:08x}  ", rows);

        // print first half of 8 bytes in hexadecimal format
        for (std::size_t i = 0; i < bytes_per_line >> 1; i++)
            std::printf(fmt.data(), buffer[i]);

        std::putchar(' ');

        // print second half of 8 bytes in hexadecimal format
        for (std::size_t i = bytes_per_line >> 1; i < bytes_per_line; i++)
            std::printf(fmt.data(), buffer[i]);

        // print string representation of bytes
        std::putchar(' ');
        std::putchar('|');

        for (const auto& byte : buffer)
            std::putchar(to_print(byte));

        std::putchar('|');
        std::putchar('\n');

        rows += 0x10;
    }

    fin.close();
}

} // namespace hexd