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

#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <stdio.h>
#include <hexd.h>


int32_t main(int32_t argc, char **argv)
{
    if (argc < 2) {
        puts("hexd: Use '-h' or '--help' for usage.");
        exit(EXIT_FAILURE);
    }

    struct option long_options[] = {
        {"hex",     required_argument, 0, 'x'},
        {"oct",     required_argument, 0, 'o'},
        {"bin",     required_argument, 0, 'b'},
        {"help",    no_argument,       0, 'h'},
        {"version", no_argument,       0, 'v'},
        {0,         0,                 0,  0 }
    };

    enum MODE mode = HEX;
    int32_t opt    = 0;

    while ((opt = getopt_long(argc, argv, "hvx:o:b:", long_options, 0)) != -1) {
        switch (opt) {
        // handle -x, --hex
        case 'x':
            mode = HEX;
            break;

        // handle -o, --oct
        case 'o':
            mode = OCT;
            break;

        // handle -b, --bin
        case 'b':
            mode = BIN;
            break;

        // handle -h, --help
        case 'h':
            hexd_help();
            break;

        // handle -v, --version
        case 'v':
            hexd_version();
            break;

        // handle unknown options
        case '?':
            puts("Use -h or --help for usage.");
            exit(EXIT_FAILURE);
            break;

        default:
            break;
        }
    }

    if (optind <= argc)
        hexd_dump(mode, argv[optind-1]);
    else
        puts("ntool: expected target after -x/--hex option");

    return 0;
}