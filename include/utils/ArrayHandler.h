#pragma once
#include "Config.h"
#include <iostream>
#include <vector>

using std::string;

using intVector = std::vector<int>;
using intMatrix = std::vector<intVector>;
using charVector = std::vector<char>;
using charMatrix = std::vector<charVector>;

namespace Overtone {
	namespace Utils {
		void String_to_Char_1x18_MatrixFiller(const charMatrix& filler, string& emptyString, int i);
		void String_1x18_Filler(const char filler[WIDTH], string& emptyString);
		void Char_18x18_ArrayFiller(const char filler[HEIGHT][WIDTH], char emptyArray[HEIGHT][WIDTH]);
		void Char_3x18_ArrayFiller(const char filler[M_HEIGHT][WIDTH], char emptyArray[M_HEIGHT][WIDTH]);
		void Char_1x18_ArrayFiller(const char filler[WIDTH], char emptyArray[WIDTH]);
		void Char_Xx18_MatrixFiller(const charMatrix& filler, charMatrix& emptyArray);
		int intLength(int num);
		char IntToCharLength4(int num, int pos);
		char IntToCharLength3(int num, int pos);
		char IntToCharLength2(int num, int pos);
	}
}