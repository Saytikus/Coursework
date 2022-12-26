/**
* @file User.h
* @author Galkin Kirill
* @version Release 1.0.0
* @brief Header file for client-programm
* @date 26.12.2022
* @copyright K.A.
*/
#pragma once
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <limits>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cryptopp/cryptlib.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <getopt.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <boost/algorithm/string.hpp>
#include <string>
#include <experimental/filesystem>
using namespace std;
using namespace CryptoPP;
namespace fs = std::experimental::filesystem::v1;
/** @brief Interface realisation. Contacts only the User class.
 * @details Attributes are set in method ReceiveArguments() by passing arguments to the program when the executable file is called. 
 * Contains methods: GetReference for call reference, which set in method ReceiveArguments(); ReceiveArguments for passing argument in interface and getters for returning class attributes.
 * @warning Strictly follow the instructions in the help! Without this class you will not be able to continue work with this program.
 */
class Interface {
    vector<string> interface_reference_;
    string server_address_, server_port_, input_data_file_, output_data_file_, aut_data_file_;
	int SetReference();
	int CheckServerAddress(const string server_address);
    int CheckServerPort(const string server_port);
    int CheckInputFile(const string input_data_file);
    int CheckOutputFile(const string output_data_file);
    int CheckAutFile(const string aut_data_file);
    bool isNumber(const string str);
public:
     /** @brief Getting the reference.
     * @return The reference.
     */
    int GetReference();
     /** @brief Passing arguments to the programm when the executable file is called.
     * @param argc Count of arguments which passing to main.
     * @param argv Container with arguments which passing to main.
     * @warning Throw ErrorHandler<string> when it finds an argument transfer error or an unsurrected argument format.
     * @return 0
     */
    int ReceiveArguments(int argc, char* argv[]);
    /** @brief Getting the server address.
     * @return A server address as a string.
     */
    string GetServerAddress();
    /** @brief Getting the server port.
     * @return A server port as a string.
     */
    string GetServerPort();
    /** @brief Getting the input file.
     * @return A absolute path to input file as a string.
     */
    string GetInputFile();
    /** @brief Getting the output file.
     * @return A absolute path to output file as a string.
     */
    string GetOutputFile();
    /** @brief Getting the autentification file.
     * @return A absolute path to autentification file as a string.
     */
    string GetAutFile();
};


/** @brief Class for error handling.
 * @details Is a template class. ErrorHandler have immutable initialization.
 * Contains methods: Constructor for output information about error, getters for returning class attributes and friendly overloaded operator<<.
 */
template <typename T>
class ErrorHandler {
    string what_error_, what_arg_, what_func_;
    const T arg_value_;
public:
	/** @brief Constuctor for initialization.
     * @param what_error Error name.
     * @param what_arg The name variable which contains error.
     * @param arg_value The variable value. It is template attribute.
     * @param what_func The name function which contains error.
     * @warning arg_value variable must be a data type that can be force to a string.
     */
    explicit ErrorHandler<T>(string what_error, string what_arg, const T& arg_value, string what_func) :
    what_error_{ what_error + '\n' }, what_arg_{ what_arg }, arg_value_ { string(arg_value) + '\n'}, what_func_{ what_func } { }
    /** @brief Getting error name.
     * @return Error name as string.
     */
    string GetError() { return what_error_; }
    /** @brief Getting the variable name.
     * @return The name variable which contains error as string.
     */
    string GetArg() { return what_arg_; }
    /** @brief Getting the variable value.
     * @return The variable value as string.
     */
	T GetArgValue() { return arg_value_; }
	/** @brief Getting The function name.
     * @return The function name as string.
     */
    string GetFunc() { return what_func_; }
    /** @brief Overloaded operator<<.
     * @return Output all getters.
     */
    friend ostream& operator<<(ostream& os, ErrorHandler& er) {
        return os << er.GetError() << er.GetArg() << er.GetArgValue() << er.GetFunc();
    }
};


/** @brief User class for storing large number of attributes.
 * @details User does not have a default constructor, and you must pass an Interface class object to it to create an object of this class.
 * Contains methods: Conctuctor for initialization and large number of getters and setters.
 * @warning Without this class you will not be able to work with UserHandler and TCPclient classes.
 */
class User {
    string server_address_, server_port_, input_data_file_, output_data_file_, aut_data_file_;
    string user_id_, user_password_;
    string user_SALT_;
	string user_HASH_;
    uint32_t vector_number_;
    uint32_t vector_size_;
    vector<float> vector_;
    uint32_t calculation_number_;
    float calculation_result_;
	int CheckServerAddress(const string server_address);
    int CheckServerPort(const string server_port);
    int CheckInputFile(const string input_data_file);
    int CheckOutputFile(const string output_data_file);
    int CheckAutFile(const string aut_data_file);
    bool isNumber(const string str);
public:
	/** @brief Delete the default constructor.
     */
    User() = delete;
    /** @brief Constuctor for initialization
     * @param interface Object of class Interface. In this constructor attributes are initialized through all getters of the Interface class(see Interface class).
     */
    User(Interface interface);
    /** @brief Getting the output file.
     * @return A absolute path to output file as a string.
     */
    string GetInputFile();
    /** @brief Getting the output file.
     * @return A absolute path to output file as a string.
     */
    string GetOutputFile();
    /** @brief Getting the autentification file.
     * @return A absolute path to autentification file as a string.
     */
    string GetAutFile();
    /** @brief Getting the server address.
     * @return A server address as a string.
     */
    string GetServerAddress();
    /** @brief Getting the input file.
     * @return A absolute path to input file as a string.
     */
    string GetServerPort();
    /** @brief Getting the user id.
     * @return The user id as a string.
     */
    string GetId();
    /** @brief Getting the user password.
     * @return The user password as a string.
     */
    string GetPassword();
    /** @brief Getting the salt for md5 hash.
     * @return The salt as a hex numbers string.
     */
    string GetSALT();
    /** @brief Getting the md5 hash.
     * @return The hash as a hex numbers string.
     */
    string GetHASH();
    /** @brief Getting the vector number.
     * @return The vector number as uint32_t variable.
     */
    uint32_t GetVectorNumber();
    /** @brief Getting the vector size.
     * @return The vector size as uint32_t variable.
     */
    uint32_t GetVectorSize();
    /** @brief Getting the vector.
     * @return The vector as container float data.
     */
    vector<float> GetVector();
    /** @brief Getting the calculation number.
     * @return The calculation number as uint32_t variable.
     */
    uint32_t GetCalcNumber();
    /** @brief Getting the calculation result.
     * @return The calculation result as float variable.
     */
    float GetCalcResult();
    /** @brief Setting user id and user password.
	 *  @param aut_data Vector which contains id and password for user.
     */
    int SetIdPassword(vector<string> aut_data);
    /** @brief Setting salt.
	 *  @param SALT Hex number string.
     */
    int SetSALT(string SALT);
    /** @brief Setting hash.
	 *  @param HASH Hex number string.
     */
    int SetHASH(string HASH);
    /** @brief Setting vector number.
	 *  @param vector_number Uint32_t data type variable that contains number of vectors to be sent to the server.
     */
    int SetVectorNumber(uint32_t vector_number);
    /** @brief Setting vector.
	 *  @param vector Data type vector float variable that storing elements which to be sent to the server.
     */
    int SetVector(vector<float> vector);
    /** @brief Setting calculation number.
	 *  @param calculation_number Uint32_t data type variable that contains number of result to be record in output file.
     */
    int SetCalcNumber(uint32_t calculation_number);
    /** @brief Setting calculation result.
	 *  @param calculation_result Float data type variable that contains the sum of vector elements sent to the server.
     */
    int SetCalcResult(float calculation_result);
};


/** @brief UserHandler class for handling user information. Contacts only the User class.
 * @details Abstract class. Methods handling information and return it.
 * Contains methods: 3 getters for handling information from files, 1 getters for creating hash and 2 record methods for record data in binary file.
 * @warning Without this class User class does not matter.
 */
class UserHandler {
	bool isNumber(const string str);
	int CheckVectorNumber(const string vector_number_string);
	int CheckStringNumber(const int string_number);
	int CheckVector(const vector<float> check_vector);
	int CheckStreamValue(const string s);
	int CheckAutData(const vector<string> aut_data, const string aut_data_file);
	int CheckAutFile(const string aut_data_file);
	int CheckVectorFile(const string input_data_file);
	int CheckSaltAndPassword(const string Salt, const string user_password);
	int CheckFileForRecordNumber(const string output_data_file);
	int CheckFileForRecordResult(const string output_data_file);
	bool IsNotHexString(const string hex_string);
public:
	/** @brief Get number of vector from file.
     * @param input_data_file File with number of vector.
     * @warning throw ErrorHandler<string> when the input file is incorrect or its contents are incorrect. 
     * @return A number of vector.
     */
    uint32_t GetVectorNumberFromFile(string input_data_file);
    /** @brief Get vector from file.
     * @param input_data_file File with number of vector.
     * @param string_number String number for reading vector.   
     * @warning throw ErrorHandler<string> when the input file is incorrect or its contents are incorrect.
     * @return Data type vector float.
     */
    vector <float> GetVectorFromFile(string input_data_file, int string_number);
    /** @brief Get autentification data from file. This is id and password.
     * @param aut_data_file File with contents id and password. 
     * @warning throw ErrorHandler<string> when the autentification file is incorrect or its contents are incorrect. 
     * @return String vector with 2 cells, first id, second password.
     */
    vector<string>GetAutDataFromFile(string aut_data_file);
    /** @brief Create and get hash from salt + password.
     * @param Salt Hex string number. Must contains only hex numbers.
     * @param user_password String with password.
     * @warning throw ErrorHandler<string> when salt string having not hex numbers, salt is empty or password is empty.
     * @return Hash as string of hex numbers.
     */
    string GetHashFromPassword(string Salt, string user_password);
    /** @brief Record calculations number in binary file.
     * @param calculations_number Uint32_t variable that contains number of calculations.
     * @param output_data_file File for record.
     * @warning throw ErrorHandler<string> when the output file is incorrect.
     */
    int RecordCalcNumber(uint32_t calculations_number, string output_data_file);
    /** @brief Record calculations result in binary file.
     * @param calculations_result Float variable that contains the sum of vector elements sent to the server.
     * @param output_data_file File for record.
     * @warning throw ErrorHandler<string> when the output file is incorrect.
     */
    int RecordCalcResult(float calculation_result, string output_data_file);
};


/** @brief TCP class for connecting with server, send to server information and receive information from server. Contacts only the User class.
 * @details Storing server addres, server port, socket and connection. TCPclient does not have a default constructor, and you must pass an User class object to it to create an object of this class.
 * Contains methods: Consturctor for initialization, method for connection setup, 4 methods for sending information to server, 2 methods for receive information from server and method for close connection.
 * @warning Without this class you can not contacts with server.
 */
class TCPclient {
    string server_address_, server_port_;
    struct sockaddr_in {
        short sin_family;
        unsigned short sin_port;
        struct in_addr sin_addr;
        char sin_zero[8];
    };
    struct in_addr {
        unsigned long s_addr;
    };
    sockaddr_in * self_addr_;
    sockaddr_in * server_addr_;
    int tcp_socket_;
    int required_connection_;
public:
	/** @brief Delete the default constructor.
     */
    TCPclient() = delete;
    /** @brief Constuctor for initialization
     * @param user Object of class User. In this constructor attributes are initialized through server address and server port from User class(see User class).
     */
    TCPclient(User user);
    /** @brief Setup connection with server using server address and server port from User class(see constuctor).
     */
    int Connection();
    /** @brief Send autentification string to server.
     * @param aut_msg String that will be send to server.
     */
    int SendAutMsg(string aut_msg);
    /** @brief Send number of vectors.
     * @param vector_number Uint32_t data type variable that contains number of vectors to be sent to the server.
     */
    int SendVectorNumber(uint32_t vector_number);
    /** @brief Send size of vector.
	 *  @param vector_size Uint32_t data type variable that contains number of vector's elements.
     */
    int SendVectorSize(uint32_t vector_size);
    /** @brief Send vector.
	 *  @param vectorvr Data type vector float variable that storing elements which to be sent to the server.
     */
    int SendVector(vector<float> vectorvr);
    /** @brief Receive and get responce from server.
	 *  @return Server responce as string.
     */
    string ReceiveAndGetResponce();
    /** @brief Receive calculation result from server.
	 *  @return Calculation result as float variable.
     */
    float ReceiveCalcResult();
    /** @brief Close connection with server.
     */
    int CloseConnection();
};
