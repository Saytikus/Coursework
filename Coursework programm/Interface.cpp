#include "User.h"

int Interface::GetReference() { cout << interface_reference_ << endl; return 0;}

string Interface::GetServerAddress() { return server_address_; }
string Interface::GetServerPort() { return server_port_; }
string Interface::GetInputFile() { return input_data_file_; }
string Interface::GetOutputFile() { return output_data_file_; }
string Interface::GetAutFile() { return aut_data_file_; }

int Interface::ReceiveArguments(int argc, char* argv[]) {
    if (argc == 1) {
        GetReference();
		exit(0);
	}
    static struct option long_options[] = {
        {"reference", 0, 0, 'h'},
        {"server_address", 1, 0, '0'},
        {"server_port", 1, 0, '1'},
        {"input_file", 1, 0, '2'},
        {"output_file", 1, 0, '3'},
        {"aut_file", 1, 0, '4'},
        {0, 0, 0, 0}
    };
    int opt;
	int opt_index = 0;
	string server_address, server_port, input_file, output_file, aut_file;
    while ((opt = getopt_long(argc, argv, ":h0:1:2::3:4::", long_options, &opt_index)) != -1)
    {
        string check;
        switch(opt) {
            case 'h':
                GetReference();
                exit(0);
                
            case '0':
                server_address = optarg;
				if(server_address.find('-') != -1)
					throw ErrorHandler<string>("Interface error:	Invalid argument in option server_address", 
											   "server_address = ", server_address, "ReceiveArguments()");
                break;
            
            case '1':
				server_port = optarg;
				if(server_port.find('-') != -1)
					throw ErrorHandler<string>("Interface error:	Invalid argument in option server_port", 
											   "server_port = ", server_port, "ReceiveArguments()");
                break;
                
            case '2':
                input_file = optarg;
				if(input_file.find('-') != -1)
					throw ErrorHandler<string>("Interface error:	Invalid argument in option input_file", 
											   "input_file = ", input_file, "ReceiveArguments()");
                break;
            
            case '3':
                output_file = optarg;
				if(output_file.find('-') != -1)
					throw ErrorHandler<string>("Interface error:	Invalid argument in option output_file", 
											   "output_file = ", output_file, "ReceiveArguments()");
				break;
                
            case '4':
				aut_file = optarg;
				if(aut_file.find('-') != -1)
					throw ErrorHandler<string>("Interface error:	Invalid argument in option aut_file", 
											   "aut_file = ", aut_file, "ReceiveArguments()");
				break;
				
			case '?':
				throw ErrorHandler<string>("Interface error:	Unknown option", 
										   "opt = ", "?", "ReceiveArguments()");
				break;
        }
    }
	if(server_port.empty())
		server_port = "33333";
	if(aut_file.empty())
		aut_file = "/home/stud/test/.config/vclient.conf";
    CheckServerAddress(server_address);
    CheckServerPort(server_port);
    CheckInputFile(input_file);
    CheckOutputFile(output_file);
    CheckAutFile(aut_file);
	server_address_ = server_address;
	server_port_ = server_port;
	input_data_file_ = input_file;
	output_data_file_ = output_file;
	aut_data_file_ = aut_file;
    //cout << "\n" << "address: " << server_address_ << "\nport: " << server_port_ << "\ninputfile: " << input_data_file_ << "\noutputfile: " << output_data_file_ << "\nautfile: " << aut_data_file_ << "\n\n";
    return 0;
}

int Interface::CheckServerAddress(string server_address) {
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

int Interface::CheckServerPort(string server_port) {
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

int Interface::CheckInputFile(string input_data_file) {
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
int Interface::CheckOutputFile(string output_data_file) {
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
int Interface::CheckAutFile(string aut_data_file) {
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

bool Interface::isNumber(const string str) {
    return !str.empty() && (str.find_first_not_of("[0123456789]") == string::npos);
}
