#include <gtest/gtest.h>
#include <sstream>
#include "driver.hh"

class InterpreterTest : public ::testing::Test {
public:
	std::istringstream in;
	std::ostringstream out = std::ostringstream(std::ios::ate);
	std::ostringstream errOut = std::ostringstream(std::ios::ate);
	Driver driver;
	void SetUp() override {
		driver.configStreams(in, out, errOut);
	}
	void TearDown() override {
		//in.str("");
		//out.str("");
		//errOut.str("");
	}
};

TEST_F(InterpreterTest, Functions) {
	in.str("3243");
	driver.parse("functions.test");
	EXPECT_EQ(out.str(), 
			"Hello%"
			"\nu"
			"WoRld\\123$"
			"\t\r\"^"
			"123"
			"\n"
			"2424545"
			"\n"
			"3243");
}

TEST_F(InterpreterTest, Arithmetic) {
	in.str("");
	driver.parse("arithmetic.test");
	EXPECT_EQ(out.str(), "32343");
}

TEST_F(InterpreterTest, LogicAndComparasions) {
	in.str("-42");
	driver.parse("logic.test");
	EXPECT_EQ(out.str(), "12122132");
}

TEST_F(InterpreterTest, Variables) {
	in.str("11");
	driver.parse("variables.test");
	EXPECT_EQ(out.str(), "125121-6");
}

TEST_F(InterpreterTest, Loops) {
	in.str("3 4 5 1 0");
	driver.parse("loops.test");
	EXPECT_EQ(out.str(), 
			"03182153440"
			"321\n"
			"963\n"
			"15105\n");
}