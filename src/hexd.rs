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

//! File dump functions.

use std::io::{BufReader, Read, Write};
use std::fs::File;

/// Output mode enumeration
#[derive(Debug)]
pub enum Mode {
    Hex,
    Oct,
    Bin,
}

/// Convert byte to ASCII.
///
/// # Parameters
/// - `ch` - given byte to convert.
///
/// # Returns
/// ASCII character to print.
#[inline]
fn to_print(ch: u8) -> char {
    if ch.is_ascii_graphic() {ch as char} else {'.'}
}

/// Get bytes per line for specific output mode.
///
/// # Parameters
/// - `mode` - given output mode.
///
/// # Returns
/// Bytes per line.
fn get_bytes_per_line(mode: &Mode) -> usize {
    match mode {
        Mode::Hex => return 16,
        Mode::Oct => return 16,
        Mode::Bin => return 8,
    }
}

/// Dump file.
///
/// # Parameters
/// - `mode` - given output mode.
/// - `filename` - given name of file to dump.
pub fn dump(mode: &Mode, filename: &str) -> Result<(), std::io::Error> {
    let file       = File::open(filename).expect("hexd: error to open file");
    let mut reader = BufReader::new(file);

    let bytes_per_line      = get_bytes_per_line(mode);
    let mut buffer: Vec<u8> = vec![0; bytes_per_line];
    let mut rows: usize     = 0;
    let mut output          = String::with_capacity(96);

    loop {
        let bytes_read = reader.read(&mut buffer)?;

        if bytes_read == 0 {
            break;
        }

        output.clear();
        output.push_str(&format!("{:08x}  ", rows));

        for i in 0..bytes_per_line {
            match mode {
                Mode::Hex => output.push_str(&format!("{:02x} ", buffer[i])),
                Mode::Oct => output.push_str(&format!("{:03o} ", buffer[i])),
                Mode::Bin => output.push_str(&format!("{:08b} ", buffer[i])),
            }

            if (i + 1) % 8 == 0 {
                output.push_str(" ");
            }
        }

        output.push_str("|");

        for i in 0..bytes_per_line {
            output.push_str(&format!("{}", to_print(buffer[i])));
        }

        if let Err(e) = writeln!(std::io::stdout(), "{}|", output) {
            // Ignore broken pipe error
            if e.kind() == std::io::ErrorKind::BrokenPipe {
                return Ok(());
            }
            else {
                return Err(e);
            }
        }

        rows += bytes_per_line;
        buffer.fill(0);
    }

    Ok(())
}