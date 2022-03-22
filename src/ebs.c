/// MIT License
///
/// Copyright (c) 2022 Salimgereyev Adi
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation
/// the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the
/// Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included
/// in all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
/// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
/// DEALINGS IN THE SOFTWARE.

#include <stdio.h>
#include "println.h"
#include "find_compiler.h"
#include "build_info.h"
#include "parser.h"
#include "file.h"

int main(void) {
	print_build_info();

	char* compiler = find_compiler();
	if (!compiler) {
		println("compiler not found");
		exit(1);
	}

	char* build_script_content = read_file("EBSFile");

	if (!build_script_content) {
		println("unable to open EBSFile");
		exit(1);
	}

	struct parser_state* parser_state = new_parser_state(
		new_lexer_state("EBSFile", build_script_content));
	struct build_file_AST* ast = parse_build_file(parser_state);
	free_parser_state(parser_state);
	
	println("compiler detected: %s", compiler);
}
