
#include <catch2/catch.hpp>

#include <HBTK/Paths.h>

TEST_CASE("Paths") 
{
	SECTION("Doesn't crash") {
		std::string cwd = HBTK::Paths::current_working_directory();
		cwd = HBTK::Paths::executable_path();
	}

	SECTION("Path construction and convertion to string") {
		std::string str = "a/folder/to/far.exe";
		HBTK::Path pth(str);
#ifdef _WIN32
		REQUIRE(pth.to_string() == "a\\folder\\to\\far.exe");
		REQUIRE((std::string)pth == "a\\folder\\to\\far.exe");
#else
		REQUIRE(pth.to_string() == str);
		REQUIRE((std::string)pth == str);
#endif
	}

	SECTION("Test normalise") {
		std::string cor, rep, dot, back;
		cor = "a/b.c/e/f/";
		rep = "a/////b////c/d//e";
		dot = "a/././/b";
		back = "a/../b/c/d/../../e";
		HBTK::Path pcor(cor), prep(rep), pdot(dot), pback(back);
		pcor.normalise();
		prep.normalise();
		pdot.normalise();
		pback.normalise();
#ifdef _WIN32
		REQUIRE(pcor.to_string() == "a\\b.c\\e\\f\\");
		REQUIRE(prep.to_string() == "a\\b\\c\\d\\e");
		REQUIRE(pdot.to_string() == "a\\b");
		REQUIRE(pback.to_string() == "b\\e");
#else
		REQUIRE(pcor.to_string() == "a/b.c/e/f/");
		REQUIRE(prep.to_string() == "a/b/c/d/e");
		REQUIRE(pdot.to_string() == "a/b");
		REQUIRE(pback.to_string() == "b/e");
#endif
	}

	SECTION("Test exists") {
#ifdef _WIN32
		REQUIRE(HBTK::Path("C:\\Users\\").exists());
		REQUIRE(!HBTK::Path("C:\\Users_maximum_power_to_thrusters\\").exists());
		REQUIRE(HBTK::Path("C:\\Windows\\explorer.exe").exists());
#else
		// Unixy tests...
#endif
	}

	SECTION("Test is_file") {
#ifdef _WIN32
		REQUIRE(!HBTK::Path("C:\\Users\\").is_file());
		REQUIRE(!HBTK::Path("C:\\Users_maximum_power_to_thrusters\\").is_file());
		REQUIRE(HBTK::Path("C:\\Windows\\explorer.exe").is_file());
#else
		// Unixy tests...
#endif
	}

	SECTION("Test is_folder") {
#ifdef _WIN32
		REQUIRE(HBTK::Path("C:\\Users\\").is_folder());
		REQUIRE(!HBTK::Path("C:\\Users_maximum_power_to_thrusters\\").is_folder());
		REQUIRE(!HBTK::Path("C:\\Windows\\explorer.exe").is_folder());
		REQUIRE(HBTK::Path("C:\\").is_folder());
#else
		// Unixy tests...
#endif
	}

	SECTION("Test directory name") {
		HBTK::Path path("a/directory/file");
		HBTK::Path path2("a/directory/");
		HBTK::Path path3("directory/");
		REQUIRE(path.directory_name() == "directory");
		REQUIRE(path2.directory_name() == "directory");
		REQUIRE(path3.directory_name() == "directory");
	}

	SECTION("Test base name") {
		HBTK::Path path("a/directory/file");
		HBTK::Path path2("a/directory/file.exe");
		HBTK::Path path3("directory/");
		HBTK::Path path4("file.exe");
		HBTK::Path path5("");
		REQUIRE(path.base_name().to_string() == "file");
		REQUIRE(path2.base_name().to_string() == "file.exe");
		REQUIRE(path3.base_name().to_string() == "");
		REQUIRE(path4.base_name().to_string() == "file.exe");
		REQUIRE(path5.base_name().to_string() == "");
	}

	SECTION("Test is absolute path") {
		HBTK::Path path("a/directory/file");
		HBTK::Path path2("a/directory/file.exe");
		HBTK::Path path3("");
		REQUIRE(!path.is_absolute_path()) ;
		REQUIRE(!path2.is_absolute_path());
		REQUIRE(!path3.is_absolute_path());
#ifdef _WIN32
		HBTK::Path path4("a:/A/big/path");
		HBTK::Path path5("C:\\Toasty");
		REQUIRE(!path4.is_absolute_path());
		REQUIRE(path5.is_absolute_path());
#else
		HBTK::Path path4("/usr/blinky");
		HBTK::Path path5("/");
		REQUIRE(path4.is_absolute_path());
		REQUIRE(path5.is_absolute_path());
#endif
	}

	SECTION("Test absolute path") {
		// Not sure how to test this...?
	}
}