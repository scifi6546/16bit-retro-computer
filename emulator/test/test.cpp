#include <stdio.h>
#include <gtest/gtest.h>
#include "../cpu_hardware.hpp"
int main(int argc, char **argv){
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
	printf("worked\n\n");
	return 0;
}
class FooTest: public::testing::Test{
	protected:
		FooTest(){}
		~FooTest() override{};
		void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }
};
TEST(FooTest,TESTING_TERM){
	std::vector<unsigned char> test={0x00,0x00,0x00,0x00};
	Cpu test_cpu(test);
	std::vector<unsigned short> test1=test_cpu.getRegisters();
	std::vector<unsigned short> compare_regs = {0x0,0x0,0x0,0x0,0x0,0x0,0x0};
	ASSERT_EQ(test1,compare_regs);
}
TEST(FooTest,Testing_MOVC){
	std::vector<unsigned char> test={0x04,0x2,0x0,0x8,0x00,0x00,0x00,0x00};
	Cpu test_cpu(test);
	std::vector<unsigned short> test1=test_cpu.getRegisters();
	std::vector<unsigned short> compare_regs = {0x0,0x0,0x8,0x0,0x0,0x0,0x1};
	ASSERT_EQ(test1,compare_regs);
} 
TEST(FooTest,Testing_PUSH_and_POP){
	std::vector<unsigned char> test_code={/*MOVC*/0x4,0x2,0x0,0x8,/*PUSH*/0x1,0x2,0x0,0x0,
		/*POP*/0x2,0x1,0x0,0x0,/*TERM*/0x0,0x0,0x0,0x0};	
	Cpu test_cpu(test_code);
	std::vector<unsigned short> test_reg=test_cpu.getRegisters();
	std::vector<unsigned short> compare_regs={0x0,0x8,0x8,0x0,0x0,0x0,0x3};
	ASSERT_EQ(test_reg,compare_regs);
}
