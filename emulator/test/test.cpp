#include <stdio.h>
#include <gtest/gtest.h>
#include "../cpu_hardware.hpp"
int main(int argc, char **argv){
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
	printf("worked\n\n");
	return 0;
}
//dummy
void init_term(){};
//dummy
void set_char(char pos_x, char pos_y, char code){};
void end_term(){};
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
TEST(FooTest,TESTING_MOVE){
	std::vector<unsigned char> test_code={/*MOVC*/0x4,0x2,0x0,0x8,
		/*MOVE */0x3,0x02,0x0,0x0,/*TERM*/0x0,0x0,0x0,0x0};

	Cpu test_cpu(test_code);
	std::vector<unsigned short> test_reg=test_cpu.getRegisters();
	std::vector<unsigned short> compare_regs={0x8,0x0,0x8,0x0,0x0,0x0,0x2};
	ASSERT_EQ(test_reg,compare_regs);
}
TEST(FooTest,TESTING_MOVE_INTO_RC){
	std::vector<unsigned char> test_code={/*MOVC*/0x4,0x02,0x0,0x8,
		/*MOVE */0x3,0x02,0x0,0x0,/*TERM*/0x0,0x0,0x0,0x0};

	Cpu test_cpu(test_code);
	std::vector<unsigned short> test_reg=test_cpu.getRegisters();
	std::vector<unsigned short> compare_regs={0x8,0x0,0x8,0x0,0x0,0x0,0x2};
	ASSERT_EQ(test_reg,compare_regs);
}
TEST(FooTest,TESTING_JUMP){
	std::vector<unsigned char> test_code={/*JUMP*/0x5,0x0,0x2,0x0,
		/*MOVC */0x4,0x2,0xA,0xA,/*TERM*/0x0,0x0,0x0,0x0};
	Cpu test_cpu(test_code);
	std::vector<unsigned short> test_reg=test_cpu.getRegisters();
	std::vector<unsigned short> compare_regs={0x0,0x0,0x0,0x0,0x0,0x0,0x2};
	ASSERT_EQ(test_reg,compare_regs);
}
TEST(FooTest,TEST_CALL_AND_RET){
	std::vector<unsigned char> test_code={0x6,0x0,0x2,0x0,/*TERM*/0x0,0x0,0x0,0x0,
	/*MOVC*/0x4,0x0,0x0,0x6,/*RET*/0x7,0x0,0x0,0x0};
	Cpu test_cpu(test_code);
	std::vector<unsigned short> test_reg=test_cpu.getRegisters();
	std::vector<unsigned short> compare_regs={0x6,0x0,0x0,0x0,0x0,0x0,0x1};
	ASSERT_EQ(test_reg,compare_regs);
}
TEST(FooTest,TEST_ADDU){
	std::vector<unsigned char> test_code={/*MOVC into ra*/0x4,0x0,0x0,0xA,
	/*MOVC into rb */0x4,0x1,0x0,0x01,/*ADDU ra rb*/0x8,0x01,0x0,0x0,/*TERM*/0x0,0x0,0x0,0x0};
	Cpu test_cpu(test_code);
	std::vector<unsigned short> test_reg=test_cpu.getRegisters();
	std::vector<unsigned short> compare_regs={0xB,0x1,0x0,0x0,0x0,0x0,0x3};
	ASSERT_EQ(test_reg,compare_regs);
}

TEST(FooTest,Test_Je){
	std::vector<unsigned char> test_code={/*Je ra rb*/0x0B,0x01,0x0,0x2,
	/*TERM*/0x0,0x0,0x0,0x0,/*MOVC ra 10*/0x4,0x00,0x00,0x10,
	/*TERM*/0x0,0x0,0x0,0x0};
	Cpu test_cpu(test_code);
	std::vector<unsigned short> test_reg=test_cpu.getRegisters();
	std::vector<unsigned short> compare_regs={0x10,0x0,0x0,0x0,0x0,0x0,0x3};
	ASSERT_EQ(test_reg,compare_regs);
}
TEST(FooTest,TEST_JG){
	std::vector<unsigned char> test_code={/*movc ra 2*/0x04,0x00,0x0,0x2,
	/*Jg ra rb 3*/0x0C,0x01,0x0,0x3,/*TERM*/0x0,0x00,0x00,0x00,
	/*movc rb 3*/0x04,0x01,0x0,0x3,/*TERM*/0x0,0x0,0x0,0x0};

	Cpu test_cpu(test_code);
	std::vector<unsigned short> test_reg=test_cpu.getRegisters();
	std::vector<unsigned short> compare_regs={0x2,0x3,0x0,0x0,0x0,0x0,0x4};
	ASSERT_EQ(test_reg,compare_regs);
}
TEST(FooTest,TEST_JL){
	std::vector<unsigned char> test_code={/*movc ra 2*/0x04,0x00,0x0,0x2,
	/*JL rb ra 3*/0x0D,0x10,0x0,0x3,/*TERM*/0x0,0x00,0x00,0x00,
	/*movc rb 3*/0x04,0x01,0x0,0x3,/*TERM*/0x0,0x0,0x0,0x0};

	Cpu test_cpu(test_code);
	std::vector<unsigned short> test_reg=test_cpu.getRegisters();
	std::vector<unsigned short> compare_regs={0x2,0x3,0x0,0x0,0x0,0x0,0x4};
	ASSERT_EQ(test_reg,compare_regs);
}