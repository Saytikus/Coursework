#include <UnitTest++/UnitTest++.h>
#include "/home/stud/C++Projects/Coursework/Coursework programm/User.h"
#include "/home/stud/C++Projects/Coursework/Coursework programm/Interface.cpp"
#include "/home/stud/C++Projects/Coursework/Coursework programm/TCPclient.cpp"
#include "/home/stud/C++Projects/Coursework/Coursework programm/User.cpp"
#include "/home/stud/C++Projects/Coursework/Coursework programm/UserHandler.cpp"

SUITE(ReceiveArgumentsTest) {
	Interface interface;
	TEST(UnknownOption) {
		char* argv[2] {"client", "--self_address"};
		int argc = sizeof(argv)/sizeof(argv[0]);
		CHECK_THROW(interface.ReceiveArguments(argc, argv), ErrorHandler<string>);
	}
	TEST(OptionInServerAddress) {
		char* argv[3] {"client", "--server_address", "--output_file"};
		int argc = sizeof(argv)/sizeof(argv[0]);
		CHECK_THROW(interface.ReceiveArguments(argc, argv), ErrorHandler<string>);
	}
	TEST(EmptyAddr) {
		char* argv[3] {"client", "--server_address", ""};
		int argc = sizeof(argv)/sizeof(argv[0]);
		CHECK_THROW(interface.ReceiveArguments(argc, argv), ErrorHandler<string>);
	}
	TEST(ErrorAddr) {
		char* argv[3] {"client", "--server_address", "hey"};
		int argc = sizeof(argv)/sizeof(argv[0]);
		CHECK_THROW(interface.ReceiveArguments(argc, argv), ErrorHandler<string>);
	}
	TEST(ErrorDigitInAddr) {
		char* argv[3] {"client", "--server_address", "f12.0.0.1"};
		int argc = sizeof(argv)/sizeof(argv[0]);
		CHECK_THROW(interface.ReceiveArguments(argc, argv), ErrorHandler<string>);
	}
	TEST(OptionInServerPort) {
		char* argv[3] {"client", "--server_port", "--input_file"};
		int argc = sizeof(argv)/sizeof(argv[0]);
		CHECK_THROW(interface.ReceiveArguments(argc, argv), ErrorHandler<string>);
	}
	TEST(ErrorPort) {
		char* argv[3] {"client", "--server_port", "noport"};
		int argc = sizeof(argv)/sizeof(argv[0]);
		CHECK_THROW(interface.ReceiveArguments(argc, argv), ErrorHandler<string>);
	}
	TEST(ErrorDigitInPort) {
		char* argv[3] {"client", "--server_port", "333g3"};
		int argc = sizeof(argv)/sizeof(argv[0]);
		CHECK_THROW(interface.ReceiveArguments(argc, argv), ErrorHandler<string>);
	}
	TEST(OptionInInputFile) {
		char* argv[3] {"client", "--input_file", "--server_port"};
		int argc = sizeof(argv)/sizeof(argv[0]);
		CHECK_THROW(interface.ReceiveArguments(argc, argv), ErrorHandler<string>);
	}
	TEST(NotRegularFileInInputFile) {
		char* argv[3] {"client", "--input_file", "/home/stud"};
		int argc = sizeof(argv)/sizeof(argv[0]);
		CHECK_THROW(interface.ReceiveArguments(argc, argv), ErrorHandler<string>);
	}
	TEST(EmptyInputFile) {
		char* argv[3] {"client", "--input_file", ""};
		int argc = sizeof(argv)/sizeof(argv[0]);
		CHECK_THROW(interface.ReceiveArguments(argc, argv), ErrorHandler<string>);
	}
	TEST(InvalidInputFile) {
		char* argv[3] {"client", "--input_file", "privet"};
		int argc = sizeof(argv)/sizeof(argv[0]);
		CHECK_THROW(interface.ReceiveArguments(argc, argv), ErrorHandler<string>);
	}
	TEST(OptionInOutputFile) {
		char* argv[3] {"client", "--output_file", "--aut_file"};
		int argc = sizeof(argv)/sizeof(argv[0]);
		CHECK_THROW(interface.ReceiveArguments(argc, argv), ErrorHandler<string>);
	}
	TEST(NotRegularFileInOutputFile) {
		char* argv[3] {"client", "--output_file", "/home"};
		int argc = sizeof(argv)/sizeof(argv[0]);
		CHECK_THROW(interface.ReceiveArguments(argc, argv), ErrorHandler<string>);
	}
	TEST(EmptyOutputFile) {
		char* argv[3] {"client", "--output_file", ""};
		int argc = sizeof(argv)/sizeof(argv[0]);
		CHECK_THROW(interface.ReceiveArguments(argc, argv), ErrorHandler<string>);
	}
	TEST(InvalidOutputFile) {
		char* argv[3] {"client", "--output_file", "zpzvf1"};
		int argc = sizeof(argv)/sizeof(argv[0]);
		CHECK_THROW(interface.ReceiveArguments(argc, argv), ErrorHandler<string>);
	}
	TEST(OptionInAutFile) {
		char* argv[3] {"client", "--aut_file", "--server_address"};
		int argc = sizeof(argv)/sizeof(argv[0]);
		CHECK_THROW(interface.ReceiveArguments(argc, argv), ErrorHandler<string>);
	}
	TEST(NotRegularFileInAutFile) {
		char* argv[3] {"client", "--aut_file", "/home/stud/Desktop"};
		int argc = sizeof(argv)/sizeof(argv[0]);
		CHECK_THROW(interface.ReceiveArguments(argc, argv), ErrorHandler<string>);
	}
	TEST(InvalidAutFile) {
		char* argv[3] {"client", "--aut_file", "zzzzzzzzzzzzzzzzzz"};
		int argc = sizeof(argv)/sizeof(argv[0]);
		CHECK_THROW(interface.ReceiveArguments(argc, argv), ErrorHandler<string>);
	}
}

SUITE(GetVectorNumberFromFileTest) {
	UserHandler handler;
	TEST(ValidFileAndNumber) {
		CHECK_EQUAL(3, handler.GetVectorNumberFromFile("/home/stud/test/test_input_file"));
	}
	TEST(EmptyFilename) {
		CHECK_THROW(handler.GetVectorNumberFromFile(""), ErrorHandler<string>);
	}
	TEST(InvalidFilename) {
		CHECK_THROW(handler.GetVectorNumberFromFile("welcome"), ErrorHandler<string>);
	}
	TEST(EmptyFile) {
		CHECK_THROW(handler.GetVectorNumberFromFile("/home/stud/test/test_empty_input_file"), ErrorHandler<string>);
	}
	TEST(NotRegularFile) {
		CHECK_THROW(handler.GetVectorNumberFromFile("/home/stud"), ErrorHandler<string>);
	}
	TEST(NotNumberInFile) {
		CHECK_THROW(handler.GetVectorNumberFromFile("/home/stud/test/test_incorrect_value_input_file"), ErrorHandler<string>);
	}
}

SUITE(GetVectorFromFileTest) {
	UserHandler handler;
	TEST(EmptyFilename) {
		CHECK_THROW(handler.GetVectorFromFile("", 2), ErrorHandler<string>);
	}
	TEST(InvalidFilename) {
		CHECK_THROW(handler.GetVectorFromFile("chtotakoe", 2), ErrorHandler<string>);
	}
	TEST(EmptyFile) {
		CHECK_THROW(handler.GetVectorFromFile("/home/stud/test/test_empty_input_file", 2), ErrorHandler<string>);
	}
	TEST(NotRegularFile) {
		CHECK_THROW(handler.GetVectorFromFile("/home/stud", 2), ErrorHandler<string>);
	}
	TEST(NoDigitInString) {
		CHECK_THROW(handler.GetVectorFromFile("/home/stud/test/test_incorrect_ value_input_file", 2), ErrorHandler<string>);
	}
	TEST(TooSmallStringNumber) {
		CHECK_THROW(handler.GetVectorFromFile("/home/stud/test/test_input_file", 1), ErrorHandler<string>);
	}
	TEST(EmptyVectorSize) {
		CHECK_THROW(handler.GetVectorFromFile("/home/stud/test/test_incorv_input_file№1", 2), ErrorHandler<string>);
	}
	TEST(NotDigitVectorSize) {
		CHECK_THROW(handler.GetVectorFromFile("/home/stud/test/test_incorv_input_file№2", 2), ErrorHandler<string>);
	}
	TEST(SymbolsInIntegerPartOfNumber) {
		CHECK_THROW(handler.GetVectorFromFile("/home/stud/test/test_incorv_input_file№3", 2), ErrorHandler<string>);
	}
	TEST(SymbolsInFractionalPartOfNumber) {
		CHECK_THROW(handler.GetVectorFromFile("/home/stud/test/test_incorv_input_file№3", 3), ErrorHandler<string>);
	}
	TEST(NotRealVectorSize) {
		CHECK_THROW(handler.GetVectorFromFile("/home/stud/test/test_incorv_input_file№4", 2), ErrorHandler<string>);
	}
}

SUITE(GetAutDataFromFileTest) {
	UserHandler handler;
	TEST(EmptyFilename) {
		CHECK_THROW(handler.GetAutDataFromFile(""), ErrorHandler<string>);
	}
	TEST(InvalidFilename) {
		CHECK_THROW(handler.GetAutDataFromFile("kaktakto"), ErrorHandler<string>);
	}
	TEST(EmptyFile) {
		CHECK_THROW(handler.GetAutDataFromFile("/home/stud/test/test_empty_aut_file"), ErrorHandler<string>);
	}
	TEST(NotRegularFile) {
		CHECK_THROW(handler.GetAutDataFromFile("/home/stud"), ErrorHandler<string>);
	}
	TEST(TabOnUserId) {
		CHECK_THROW(handler.GetAutDataFromFile("/home/stud/test/test_incorv_aut_file№1"), ErrorHandler<string>);
	}
	TEST(TabOnUserPassword) {
		CHECK_THROW(handler.GetAutDataFromFile("/home/stud/test/test_incorv_aut_file№2"), ErrorHandler<string>);
	}
}

SUITE(GetHashFromPassword) {
	UserHandler handler;
	TEST(EmptySalt) {
		CHECK_THROW(handler.GetHashFromPassword("", "P@ssW0rd"), ErrorHandler<string>);
	}
	TEST(SaltIsNotHexString) {
		CHECK_THROW(handler.GetHashFromPassword("BD6109B990FC4H,8", "P@ssW0rd"), ErrorHandler<string>);
	}
	TEST(EmptyUserPassword) {
		CHECK_THROW(handler.GetHashFromPassword("BD6109B990FC4D78", ""), ErrorHandler<string>);
	}
}

SUITE(RecordCalcNumberTest) {
	UserHandler handler;
	TEST(EmptyFilename) {
		CHECK_THROW(handler.RecordCalcNumber(3, ""), ErrorHandler<string>);
	}
	TEST(InvalidFilename) {
		CHECK_THROW(handler.RecordCalcNumber(3, "ggvp"), ErrorHandler<string>);
	}
	TEST(NotRegularFile) {
		CHECK_THROW(handler.RecordCalcNumber(3, "/home/stud"), ErrorHandler<string>);
	}
}

SUITE(RecordCalcResultTest) {
	UserHandler handler;
	TEST(EmptyFilename) {
		CHECK_THROW(handler.RecordCalcResult(3, ""), ErrorHandler<string>);
	}
	TEST(InvalidFilename) {
		CHECK_THROW(handler.RecordCalcResult(3, "helloworld"), ErrorHandler<string>);
	}
	TEST(NotRegularFile) {
		CHECK_THROW(handler.RecordCalcResult(3, "/home/stud"), ErrorHandler<string>);
	}
}

int main()
{
	return UnitTest::RunAllTests();
}
