#include "User.h"

User::User(Interface interface) {
	CheckServerAddress(interface.GetServerAddress());
    CheckServerPort(interface.GetServerPort());
    CheckInputFile(interface.GetInputFile());
    CheckOutputFile(interface.GetOutputFile());
    CheckAutFile(interface.GetAutFile());
	
    server_address_ = interface.GetServerAddress();
    server_port_ = interface.GetServerPort();
    input_data_file_ = interface.GetInputFile();
    output_data_file_ = interface.GetOutputFile();
    aut_data_file_ = interface.GetAutFile();
}

string User::GetInputFile() { return input_data_file_; }
string User::GetOutputFile() { return output_data_file_; }
string User::GetAutFile() { return aut_data_file_; }
string User::GetServerAddress() { return server_address_; }
string User::GetServerPort() { return server_port_; }
string User::GetId() { return user_id_; }
string User::GetPassword() { return user_password_; }
string User::GetSALT() { return user_SALT_; }
string User::GetHASH() { return user_HASH_; }
uint32_t User::GetVectorNumber() { return vector_number_; }
uint32_t User::GetVectorSize() { return vector_size_; }
vector<float> User::GetVector() { return vector_; }
uint32_t User::GetCalcNumber() { return calculation_number_; }
float User::GetCalcResult() { return calculation_result_; }



int User::SetIdPassword(vector<string> aut_data) {
    user_id_ = aut_data[0];
    user_password_ = aut_data[1];
    return 0;
}

int User::SetSALT(string SALT){
	user_SALT_ = SALT;
    return 0;
}

int User::SetHASH(string HASH) {
    user_HASH_ = HASH;
    return 0;
}

int User::SetVectorNumber(uint32_t vector_number) {
    vector_number_ = vector_number;
    return 0;
}

int User::SetVector(vector<float> vectorv) {
    int tmp_int = (uint32_t)vectorv[0]; // Блок для инициализации размера вектора( первый элемент в векторе)
    vector_size_ = tmp_int; //
    vectorv.erase(vectorv.begin()); // Выбрасываем из вектора его размер
    vector_ = vectorv;
    return 0;
}

int User::SetCalcNumber(uint32_t calculation_number) {
    calculation_number_ = calculation_number;
    return 0;
}

int User::SetCalcResult(float calculation_result) {
    calculation_result_ = calculation_result;
    return 0;
}

int User::CheckServerAddress(string server_address) {
    if(server_address.empty())
        throw ErrorHandler<string>("Interface error:	Empty server address", "server_address_ = ", 
								   server_address, "ReceiveArguments()");
    vector<string> server_address_vector;   // Создаем вектор для проверки каждого числа адреса
    boost::split(server_address_vector, server_address, boost::is_any_of(".")); // Разбиваем строку с адресом вектора на элементы
    if(server_address_vector.size() != 4)
        throw ErrorHandler<string>("Interface error:	Invalid server address", "server_address_ = ", server_address,
								   "ReceiveArguments()");
    for(auto& server_address_digit : server_address_vector) {   // Блок проверки каждого числа в адресе
        if(!isNumber(server_address_digit) || stoi(server_address_digit) < 0 || stoi(server_address_digit) > 255) 
            throw ErrorHandler<string>("Interface error:	Invalid digit in server address", "server_address_digit = ", 
									   server_address_digit, "ReceiveArguments()");
    }
    return 0;
}

int User::CheckServerPort(string server_port) {
    vector<string> server_port_vector;
    boost::split(server_port_vector, server_port, boost::is_any_of(""));
    for(auto& server_port_digit : server_port_vector) {
        if(!isNumber(server_port_digit))
            throw ErrorHandler<string>("Interface error:	Invalid digit in server port", "server_port_digit = ",
									   server_port_digit, "ReceiveArguments()");
    }
    if(stoi(server_port) < 1024 || stoi(server_port) > 65535)
        throw ErrorHandler<string>("Interface error:	Invalid server port", "server_port_ = ",
								   server_port, "ReceiveArguments()");
	return 0;
}

int User::CheckInputFile(string input_data_file) {
    if(input_data_file.empty())
        throw ErrorHandler<string>("Interface error:	Empty input filename", "input_data_file_ = ", input_data_file,
								   "ReceiveArguments()");
	fs::path input_data_file_status(input_data_file);
	if(!fs::is_regular_file(input_data_file_status))
		throw ErrorHandler<string>("Interface error:	Input file is not regular file", "input_data_file_ = ", 
							       input_data_file, "ReceiveArguments()");
    ifstream check_file(input_data_file);
    if(check_file.is_open() == false)
        throw ErrorHandler<string>("Interface error:	Invalid input filename", "input_data_file_ = ",
								   input_data_file_, "ReceiveArguments()");
	return 0;
}
int User::CheckOutputFile(string output_data_file) {
    if(output_data_file.empty())
        throw ErrorHandler<string>("Interface error:	Empty output filename", "output_data_file_ = ", 
								   output_data_file, "ReceiveArguments()");
    fs::path output_data_file_status(output_data_file);
	if(!fs::is_regular_file(output_data_file_status))
		throw ErrorHandler<string>("Interface error:	Output file is not regular file", "output_data_file_ = ", 
								   output_data_file, "ReceiveArguments()");
    ifstream check_file(output_data_file);
    if(check_file.is_open() == false)
        throw ErrorHandler<string>("Interface error:	Invalid output filename", "input_data_file_ = ", 
								   output_data_file_, "ReceiveArguments()");
	return 0;
}
int User::CheckAutFile(string aut_data_file) {
    fs::path aut_data_file_status(aut_data_file);
	if(!fs::is_regular_file(aut_data_file_status))
		throw ErrorHandler<string>("Interface error:	Autentification file is not regular file", 
								   "aut_data_file_ = ", aut_data_file, 
								   "ReceiveArguments()");
    ifstream check_file(aut_data_file);
    if(check_file.is_open() == false)
        throw ErrorHandler<string>("Interface error:	Invalid autentification filename", 
								   "aut_data_file_ = ", aut_data_file_, 
								   "ReceiveArguments()");
	return 0;
}

bool User::isNumber(const string str) {
    return !str.empty() && (str.find_first_not_of("[0123456789]") == string::npos);
}