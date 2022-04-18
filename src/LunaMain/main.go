// ------------------------------------------------------------------------------------
//
//   Luna Programming Language Compiler - Main module
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

package main

import (
	"fmt"
	Compiler "github.com/SolindekDev/Luna/src/LunaCompiler"
	Error "github.com/SolindekDev/Luna/src/LunaError"
	ErrorCodes "github.com/SolindekDev/Luna/src/LunaErrorCodes"
	Lexer "github.com/SolindekDev/Luna/src/LunaLexer"
	Parser "github.com/SolindekDev/Luna/src/LunaParser"
)

func main() {
	Compiler.Compiler()
	Error.Create_error()
	fmt.Println(ErrorCodes.ERROR_CODE_001)
	Lexer.Lexer()
	Parser.Parser()
}
