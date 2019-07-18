#include "Base64.h"
/*////////////////////////////////////////////////////////////////////////////
Base64.cpp

Base64 encode and decode. And what are you saying it looks kinda 
similar to a StackOverflow answer? Pfft. Perish the thought.

Copyright 2018 HJA Bird

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>

std::string HBTK::encode_base64(unsigned char * data, int n_bytes)
{
	assert(data);
	const std::string conversion = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";
	const uint8_t mask_c1 = 0xFC; //->2
	const uint8_t mask_c21 = 0x03; //-<4
	const uint8_t mask_c22 = 0xF0; //->4
	const uint8_t mask_c31 = 0x0F; //<-2
	const uint8_t mask_c32 = 0xC0; //->6
	const uint8_t mask_c4 = 0x3F; //0 
	std::string output;

	unsigned char* window;
	char scratch[5];
	scratch[4] = '\0';
	int windows = n_bytes / 3;
	for (int i = 0; i < windows; i++) {
		window = (data + 3 * i);
		scratch[0] = conversion[(mask_c1 & *(uint8_t*)window) >> 2];
		scratch[1] = conversion[((mask_c21 & *(uint8_t*)window) << 4) +
			((mask_c22 & *(uint8_t*) (window + 1)) >> 4)];
		scratch[2] = conversion[((mask_c31 & *(uint8_t*)(window + 1)) << 2) +
			((mask_c32 & *(uint8_t*)(window + 2)) >> 6)];
		scratch[3] = conversion[(mask_c4 & *(uint8_t*)(window + 2))];
		output.append(scratch);
	}
	window = data + windows * 3;
	if (n_bytes % 3 == 1) {
		scratch[0] = conversion[(mask_c1 & *(uint8_t*)window) >> 2];
		scratch[1] = conversion[(mask_c21 & *(uint8_t*)window) << 4];
		scratch[2] = '=';
		scratch[3] = '=';
		output.append(scratch);
	}
	if (n_bytes % 3 == 2) {
		scratch[0] = conversion[(mask_c1 & *(uint8_t*)window) >> 2];
		scratch[1] = conversion[((mask_c21 & *(uint8_t*)window) << 4) +
			((mask_c22 & *(uint8_t*)(window + 1)) >> 4)];
		scratch[2] = conversion[(0x0F & *(uint8_t*)(window + 1)) << 2];
		scratch[3] = '=';
		output.append(scratch);
	}
	return output;
}

std::vector<unsigned char> HBTK::decode_base64(const std::string & data)
{
	const std::string conversion = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";
	int bytes = 3 * (int)ceil(data.size() / 4.0);
	int ending_equals = 0;
	if (data.size() && data.back() == '=') ending_equals += 1;
	if (data.size() > 1 && data[data.size() - 2] == '=') ending_equals += 1;
	bytes -= (int)data.size() % 4 + ending_equals;

	std::vector<unsigned char> output(bytes);
	unsigned char c1, c2, c3, c4;
	
	int end_bytes = data.size() % 4;	// Theoretically == 0
	int bytes_pos = 0;
	for (int i = 0; i < (int) data.size() - ending_equals; i += 4) {
		c1 = data[i];
		c2 = data[i + 1];
		if (end_bytes == 0 || end_bytes >= 2) c3 = data[i + 2];
		if (end_bytes == 0 || end_bytes == 3) c4 = data[i + 3];
		output[bytes_pos] = ((uint8_t)conversion.find(c1) << 2) | ((uint8_t)conversion.find(c2) >> 4);
		if ((data.size() % 4) < 2 && (c3 != '=')) {
			output[bytes_pos + 1] = ((uint8_t)conversion.find(c2) << 4) | ((uint8_t)conversion.find(c3) >> 2);
		}		
		if ((data.size() % 4) < 3 && (c4 != '=')) {
			output[bytes_pos + 2] = ((uint8_t)conversion.find(c3) << 6) | ((uint8_t)conversion.find(c4));
		}
		bytes_pos += 3;
	}
	
	return output;
}
