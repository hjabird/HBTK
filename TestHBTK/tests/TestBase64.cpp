#include <HBTK/Base64.h>
#include <catch2/catch.hpp>

#include <string>
#include <vector>

TEST_CASE("Base64 encoding") {
	SECTION("Perfect length object (multiple of 3 bytes long)") {
		std::string	text("unit test");
		std::vector<unsigned char> bytes;
		for (auto c : text) bytes.push_back(c);
		REQUIRE((int)bytes.size() % 3 == 0); // Otherwise this test won't work!
		text = HBTK::encode_base64(&bytes[0], (int)bytes.size());
		REQUIRE(text == "dW5pdCB0ZXN0");
	}

	SECTION("Object multiple of 3 bytes + 2 long") {
		std::string	text("unit tests.");
		std::vector<unsigned char> bytes;
		for (auto c : text) bytes.push_back(c);
		REQUIRE((int)bytes.size() % 3 == 2); // Otherwise this test won't work!
		text = HBTK::encode_base64(&bytes[0], (int)bytes.size());
		REQUIRE(text == "dW5pdCB0ZXN0cy4=");
	}

	SECTION("Object multiple of 3 bytes + 1 long") {
		std::string	text("unit tests");
		std::vector<unsigned char> bytes;
		for (auto c : text) bytes.push_back(c);
		REQUIRE((int)bytes.size() % 3 == 1); // Otherwise this test won't work!
		text = HBTK::encode_base64(&bytes[0], (int)bytes.size());
		REQUIRE(text == "dW5pdCB0ZXN0cw==");
	}
}

TEST_CASE("Base64 decode") {
	SECTION("Perfect length object (multiple of 3 bytes long)") {
		std::string	text("dW5pdCB0ZXN0");
		std::vector<unsigned char> bytes = HBTK::decode_base64(text);
		REQUIRE((int)bytes.size() % 3 == 0); // Otherwise this test won't work!
		text = std::string(bytes.begin(), bytes.end());
		REQUIRE(text == "unit test");
	}

	SECTION("Object multiple of 3 bytes + 2 long") {
		std::string	text("dW5pdCB0ZXN0cy4=");
		std::vector<unsigned char> bytes = HBTK::decode_base64(text);
		REQUIRE((int)bytes.size() % 3 == 2); // Otherwise this test won't work!
		text = std::string(bytes.begin(), bytes.end());
		REQUIRE(text == "unit tests.");
	}

	SECTION("Object multiple of 3 bytes + 1 long") {
		std::string	text("dW5pdCB0ZXN0cw==");
		std::vector<unsigned char> bytes = HBTK::decode_base64(text);
		REQUIRE((int)bytes.size() % 3 == 1); // Otherwise this test won't work!
		text = std::string(bytes.begin(), bytes.end());
		REQUIRE(text == "unit tests");
	}
}