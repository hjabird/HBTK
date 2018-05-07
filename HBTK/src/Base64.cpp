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

std::string HBTK::encode_base64(unsigned char * data, int n_bytes)
{
	assert(data);
	const std::string conversion = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxzy"
		"0123456789+/";
	const uint16_t mask_c1 = 0xFC00;
	const uint16_t mask_c2 = 0x03F0;
	const uint16_t mask_c3 = 0x0FC0;
	const uint16_t mask_c4 = 0x003F;
	std::string output;

	unsigned char* window;
	char scratch[5];
	scratch[4] = '\0';
	int position;
	int windows = n_bytes / 3;
	for (int i = 0; i < windows; i++) {
		window = (data + 3 * i);
		scratch[0] = conversion[(mask_c1 & *(uint16_t*)window) >> 10];
		scratch[1] = conversion[(mask_c2 & *(uint16_t*)window) >> 4];
		scratch[2] = conversion[(mask_c3 & *(uint16_t*)(window + 1)) >> 6];
		scratch[3] = conversion[(mask_c4 & *(uint16_t*)(window + 1))];
		output.append(scratch);
	}
	if (windows % 3 == 1) {
		scratch[0] = conversion[(0xFC & *(uint8_t*)windows) >> 2];
		scratch[1] = conversion[(0x03 & *(uint8_t*)windows) << 4];
		scratch[2] = scratch[3] = '=';
		output.append(scratch);
	}
	if (windows % 3 == 2) {
		scratch[0] = conversion[(mask_c1 & *(uint16_t*)windows) >> 10];
		scratch[1] = conversion[(mask_c2 & *(uint16_t*)windows) >> 4];
		scratch[2] = conversion[(0x000F & *(uint16_t*)windows) << 2];
		scratch[3] = '=';
		output.append(scratch);
	}
	return output;
}

std::vector<unsigned char> HBTK::decode_base64(const std::string & data)
{
	const std::string conversion = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxzy"
		"0123456789+/";
	int bytes = ceil(data.size() / 4);
	if (data.back() == '=') bytes -= 1;
	if (data.[data.size() - 2] == '=') bytes -= 1;
	bytes -= 4 - ((int)data.size() % 4);

	std::vector<unsigned char> output(bytes);
	uint8_t scratch;
	unsigned char c1, c2, c3, c4;
	
	for (int i = 0; i < data.size(); i += 4) {
		c1 = data[i];
		c2 = data[i + 1];
		if ((data.size() % 4) < 2) c3 = data[i + 2];
		if ((data.size() % 4) < 3) c4 = data[i + 3];
		output[i] = ((uint8_t)conversion.find(c1) << 2) | ((uint8_t)conversion.find(c2) >> 4);
		if ((data.size() % 4) < 2 && (c3 != '=')) {
			output[i + 1] = ((uint8_t)conversion.find(c2) << 4) | ((uint8_t)conversion.find(c3) >> 2);
		}		
		if ((data.size() % 4) < 3 && (c4 != '=')) {
			output[i + 1] = ((uint8_t)conversion.find(c3) << 4) | ((uint8_t)conversion.find(c4));
		}
	}
	
	return output;
}
