// Tool for displaying file contents in hexadecimal, octal,
// binary and ascii formats.
// Copyright (C) 2025 Alexander (@alkuzin).
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

//! Command line arguments handleling functions.

use std::{process, env};
use crate::hexd::Mode;

/// Print list of available commands
fn help() {
    println!("{}\n{}", HEXD_TITLE, HEXD_HELP);
    process::exit(0);
}

/// Print current version of the program
fn version() {
    println!(
        "{}\n\nhexd v{} (c) @alkuzin - {}",
        HEXD_TITLE,
        HEXD_VERSION,
        HEXD_YEAR
    );
    process::exit(0);
}

/// Extract filename from command line arguments.
///
/// # Parameters
/// - `args` - given command line arguments.
/// - `pos`  - given position of filename in arguments list.
///
/// # Returns
/// String representation of filename.
fn get_filename(args: &Vec<String>, pos: usize) -> String {
    let arg = match args.get(pos) {
        Some(arg) => arg,
        None => {
            println!("hexd: target path is not set");
            process::exit(1);
        },
    };

    String::from(arg)
}

/// Handle command line arguments.
///
/// # Returns
///
/// Tuple of:
/// - Output mode (hex, octal or binary).
/// - Target filename.
pub fn handle_args() -> (Mode, String) {
    let args: Vec<String> = env::args().collect();
    let argc              = args.len();

    if argc < 2 {
        println!("hexd: Use '-h' or '--help' for usage.");
        process::exit(1);
    }

    let mut mode             = Mode::Hex;
    let mut filename: String = Default::default();

    for (i, arg) in args[1..argc].iter().enumerate() {
        match arg.as_str() {
            "-h" | "--help"    => help(),
            "-v" | "--version" => version(),
            "-x" | "--hex" => {
                mode     = Mode::Hex;
                filename = get_filename(&args, i + 2);
                break;
            },
            "-o" | "--oct" => {
                mode     = Mode::Oct;
                filename = get_filename(&args, i + 2);
                break;
            },
            "-b" | "--bin" => {
                mode     = Mode::Bin;
                filename = get_filename(&args, i + 2);
                break;
            },
            _ => {
                println!("hexd: unknown option '{}'", arg);
                process::exit(1);
            }
        }
    }

    if filename.is_empty() {
        println!("hexd: filename is empty");
        process::exit(1);
    }

    (mode, filename)
}

#[doc(hidden)]
static HEXD_VERSION: &str = "0.1.0";

#[doc(hidden)]
static HEXD_YEAR: &str = "2025";

#[doc(hidden)]
static HEXD_TITLE: &str = r#"
██╗  ██╗███████╗██╗  ██╗██████╗
██║  ██║██╔════╝╚██╗██╔╝██╔══██╗
███████║█████╗   ╚███╔╝ ██║  ██║
██╔══██║██╔══╝   ██╔██╗ ██║  ██║
██║  ██║███████╗██╔╝ ██╗██████╔╝
╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝"#;

#[doc(hidden)]
static HEXD_HELP: &str = r#"
USAGE
       hexd [options] <file>


DESCRIPTION

       hexd - display file contents in hexadecimal and ascii formats

OPTIONS

        -x                  one-byte hexidecimal + ASCII display
        -o                  one-byte octal display
        -b                  one-byte binary display

        -h,    --help       display options list
        -v,    --version    display version of hexd
"#;