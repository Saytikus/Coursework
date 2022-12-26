#include "User.h"

User::User(Interface interface) {
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
