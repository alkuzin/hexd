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

mod args;
mod hexd;

use args::handle_args;

fn main() {
    let (mode, filename) = handle_args();

    if let Err(e) = hexd::dump(&mode, filename.as_str()) {
        println!("hexd: some error occured: {e}");
    }
}