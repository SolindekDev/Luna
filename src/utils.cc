// ------------------------------------------------------------------------------------
//
//   Luna Programming Language Compiler
//   Copyright (C) 2022 SolindekDev
//
//   This program is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// ------------------------------------------------------------------------------------

#include <string>
#include <iostream>

#include <utils.h>

/* 

    All of this code is taken from here https://stackoverflow.com/questions/12015571/how-to-print-unicode-character-in-c 

*/

int utf8_to_unicode(std::string utf8_code)
{
    unsigned utf8_size = utf8_code.length();
    int unicode = 0;

    for (unsigned p=0; p<utf8_size; ++p)
    {
        int bit_count = (p? 6: 8 - utf8_size - (utf8_size == 1? 0: 1)),
            shift = (p < utf8_size - 1? (6*(utf8_size - p - 1)): 0);

        for (int k=0; k<bit_count; ++k)
            unicode += ((utf8_code[p] & (1 << k)) << shift);
    }

    return unicode;
}

/*

    -----------------------------------------------------------------------------------------------------------------------------

*/