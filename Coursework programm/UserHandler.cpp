#include "User.h"

uint32_t UserHandler::GetVectorNumberFromFile(string input_data_file) {
		CheckVectorFile(input_data_file);
        uint32_t vector_number;
        ifstream file(input_data_file);
		string vector_number_string;
		getline(file, vector_number_string);
		CheckVectorNumber(vector_number_string);
		vector_number = stoi(vector_number_string);
		file.close();
        return vector_number;
}
vector <float> UserHandler::GetVectorFromFile(string input_data_file, int string_number) {
	    CheckVectorFile(input_data_file);
        CheckStringNumber(string_number);
        vector <float> vectorvr;
        ifstream file(input_data_file);
		for(int i = 1; i < string_number; i++) {
			string garbage;
			getline(file, garbage);
		}
		string s;
		getline(file, s);
		CheckStreamValue(s);
		istringstream is(s);
		float word;
		while (is >> word) {
			vectorvr.push_back(word);
		}
		file.close();
        CheckVector(vectorvr);
        return vectorvr;
}

vector <string>UserHandler::GetAutDataFromFile(string aut_data_file) {
	CheckAutFile(aut_data_file);
    vector <string> aut_data;
    string str;
    char delimiter = ' ';
    ifstream file(aut_data_file);
	getline(file, str, delimiter);
	aut_data.push_back(str);
        
	getline(file, str);
	aut_data.push_back(str);
	file.close();
	CheckAutData(aut_data, aut_data_file);
    return aut_data;
}

string UserHandler::GetHashFromPassword(string Salt, string user_password) {
	CheckSaltAndPassword(Salt, user_password);
    string result,Hash, salted_password = Salt + user_password;
    HexEncoder encoder(new StringSink(result));
    Weak::MD5 md5;
    md5.Update((const byte*)&salted_password[0], salted_password.size());
    Hash.resize(md5.DigestSize());
    md5.Final((byte*)&Hash[0]);
    StringSource(Hash, true, new Redirector(encoder));
    return result;
}

int UserHandler::RecordCalcNumber(uint32_t calculations_number, string output_data_file) {
    CheckFileForRecordNumber(output_data_file);
    ofstream file(output_data_file, ios::binary);
    file.write((char*)&calculations_number, sizeof(calculations_number));
    file.close();
    return 0;
}

int UserHandler::RecordCalcResult(float calculation_result, string output_data_file) {
    CheckFileForRecordResult(output_data_file);
    ofstream file(output_data_file, ios::binary | ios::app);
    file.write((char*)&calculation_result, sizeof(calculation_result));
	cout << "Calculations result: " << calculation_result << " was record in file" << endl;
    file.close();
    return 0;
}

bool UserHandler::isNumber(const string str) {
    return !str.empty() && (str.find_first_not_of("[0123456789]") == string::npos);
}

int UserHandler::CheckVectorNumber(const string vector_number_string) {
	if(!isNumber(vector_number_string))
		throw ErrorHandler<string>("UserHandler error:	Invalid digit in string for vector number", 
								   "vector_number_string = ", vector_number_string, 
								   "GetVectorNumberFromFile(string input_data_file)");
	return 0;
}

int UserHandler::CheckStringNumber(const int string_number) {
	if (string_number < 2)
		throw ErrorHandler<string>("UserHandler error:	Too small string number for start read vectors", 
								   "string_number = ", to_string(string_number), 
								   "GetVectorFromFile(string input_data_file)");
	return 0;
}

int UserHandler::CheckVector(const vector<float> vectorvr) {
	if(vectorvr[0] + 1 != vectorvr.size()) {
		int tmp = vectorvr[0];
		throw ErrorHandler<string>("UserHandler error:	Vector size taken from input file does not match real vector size",
								   "vectorvr[0] = ", to_string(tmp),
								   "GetVectorFromFile(string input_data_file)");
	}
	return 0;
}

int UserHandler::CheckStreamValue(const string s) {
		stringstream ss(s);
		vector<string> pair_integer_fractional;
		
		string size;
		getline(ss, size, ' ');
		if(size.empty())
			throw ErrorHandler<string>("UserHandler error:	Empty vector size", 
									   "vectorvr[0] = ", size, 
									   "GetVectorFromFile(string input_data_file)");
		if(!isNumber(size))
			throw ErrorHandler<string>("UserHandler error:	Invalid vector size", 
									   "vectorvr[0] = ", size, 
									   "GetVectorFromFile(string input_data_file)");
		
		string tmp;
		getline(ss, tmp, '.');
		pair_integer_fractional.push_back(tmp);
		getline(ss, tmp, ' ');
		pair_integer_fractional.push_back(tmp);
		for(int i = 0; i < pair_integer_fractional.size(); i++ ) {
			string str = pair_integer_fractional[i];
			if (str[str.size()-1] == '0')
				for (int v = str.size()-1; str[v]=='0'; v--)    
					str.erase(v,1);
			if (str.empty())
				str = '0';
			if(!isNumber(str))
				throw ErrorHandler<string>("UserHandler error:	Invalid vector element", 
										   "vectorvr = ", pair_integer_fractional[0], 
								           "GetVectorFromFile(string input_data_file)");
		}
		return 0;
}

int UserHandler::CheckAutData(const vector<string> aut_data, const string aut_data_file) {
	if(aut_data.size() == 2 && aut_data[0].find('\n') != -1 || aut_data[0].find('\t') != -1 || aut_data[0].find(' ') != -1) {
		string aut_data_string;
		ifstream file(aut_data_file);
		getline(file, aut_data_string);
		file.close();
		throw ErrorHandler<string>("UserHandler error:	Incorrect format user id and user password in aut_file", 
								   "aut_data = ", aut_data_string, 
								   "GetAutDataFromFile(string aut_data_file)");
	}
	
	if(aut_data.size() == 2 && aut_data[1].find('\n') != -1 || aut_data[1].find('\t') != -1 || aut_data[1].find(' ') != -1) {
		string aut_data_string;
		ifstream file(aut_data_file);
		getline(file, aut_data_string);
		file.close();
		throw ErrorHandler<string>("UserHandler error:	Incorrect format user id and user password in aut_file", 
								   "aut_data = ", aut_data_string, 
								   "GetAutDataFromFile(string aut_data_file)");
	}
	return 0;
}

int UserHandler::CheckAutFile(const string aut_data_file) {
	if(aut_data_file.empty())
		throw ErrorHandler<string>("UserHandler error: Empty autentification filename",
								   "aut_data_file = ", aut_data_file,
								   "GetAutDataFromFile(string aut_data_file)");
	ifstream check_file(aut_data_file);
    if(check_file.is_open() == false)
        throw ErrorHandler<string>("UserHandler error:	Invalid aut file", 
								   "aut_data_file_ = ", aut_data_file, 
								   "GetAutDataFromFile(string aut_data_file)");
    if (check_file.peek() == EOF)
		throw ErrorHandler<string>("UserHandler error:	Empty aut file", 
								   "aut_data = ", "", 
								   "GetAutDataFromFile(string aut_data_file)");
	check_file.close();
	fs::path aut_data_file_status(aut_data_file);
	if(!fs::is_regular_file(aut_data_file_status))
		throw ErrorHandler<string>("UserHandler error:	Aut file is not regular file", 
								   "aut_data_file_ = ", aut_data_file, 
								   "GetAutDataFromFile(string aut_data_file)");
	return 0;
}

int UserHandler::CheckVectorFile(const string input_data_file) {
	if(input_data_file.empty())
		throw ErrorHandler<string>("UserHandler error:	Empty input filename", 
								   "input_data_file_ = ", input_data_file, 
								   "GetVectorNumberFromFile(string aut_data_file)");
	ifstream check_file(input_data_file);
    if(check_file.is_open() == false)
        throw ErrorHandler<string>("UserHandler error:	Invalid input filename", 
								   "input_data_file_ = ", input_data_file, 
								   "GetVectorNumberFromFile(string aut_data_file)");
    if (check_file.peek() == EOF)
		throw ErrorHandler<string>("UserHandler error:	Empty input file", 
								   "input_data = ", "", 
								   "GetVectorNumberFromFile(string aut_data_file)");
	check_file.close();
	fs::path input_data_file_status(input_data_file);
	if(!fs::is_regular_file(input_data_file_status))
		throw ErrorHandler<string>("UserHandler error:	Input file is not regular file", 
							       "input_data_file_ = ", input_data_file, 
								   "GetVectorNumberFromFile(string aut_data_file)");
	return 0;
}

int UserHandler::CheckSaltAndPassword(const string Salt, const string user_password) {
	if(Salt.empty())
		throw ErrorHandler<string>("UserHandler error:	Empty salt", 
							       "Salt = ", Salt, 
								   "GetHashFromPassword(string Salt, string user_password)");
	if(IsNotHexString(Salt))
		throw ErrorHandler<string>("UserHandler error:	Salt is not hex string", 
							       "Salt = ", Salt, 
								   "GetHashFromPassword(string Salt, string user_password)");
	if(user_password.empty())
		throw ErrorHandler<string>("UserHandler error:	Empty user password", 
							       "user_password = ", user_password, 
								   "GetHashFromPassword(string Salt, string user_password)");
	return 0;
}

int UserHandler::CheckFileForRecordNumber(const string output_data_file) {
	if(output_data_file.empty())
		throw ErrorHandler<string>("UserHandler error:	Empty output filename", 
								   "output_data_file_ = ", output_data_file, 
								   "RecordCalcNumber(uint32_t calculations_number, string aut_data_file)");
	ifstream check_file(output_data_file);
    if(check_file.is_open() == false)
        throw ErrorHandler<string>("UserHandler error:	Invalid output filename", 
								   "output_data_file_ = ", output_data_file, 
								   "RecordCalcNumber(uint32_t calculations_number, string aut_data_file)");
	check_file.close();
	fs::path output_data_file_status(output_data_file);
	if(!fs::is_regular_file(output_data_file_status))
		throw ErrorHandler<string>("UserHandler error:	Output file is not regular file", 
							       "output_data_file_ = ", output_data_file, 
								   "RecordCalcNumber(uint32_t calculations_number, string aut_data_file)");
	return 0;
}

int UserHandler::CheckFileForRecordResult(const string output_data_file) {
	if(output_data_file.empty())
		throw ErrorHandler<string>("UserHandler error:	Empty output filename", 
								   "output_data_file_ = ", output_data_file, 
								   "RecordCalcResult(float calculation_result, string output_data_file)");
	ifstream check_file(output_data_file);
    if(check_file.is_open() == false)
        throw ErrorHandler<string>("UserHandler error:	Invalid output filename", 
								   "output_data_file_ = ", output_data_file, 
								   "RecordCalcResult(float calculation_result, string output_data_file)");
	check_file.close();
	fs::path output_data_file_status(output_data_file);
	if(!fs::is_regular_file(output_data_file_status))
		throw ErrorHandler<string>("UserHandler error:	Output file is not regular file", 
							       "output_data_file_ = ", output_data_file, 
								   "RecordCalcResult(float calculation_result, string output_data_file)");
	return 0;
}

bool UserHandler::IsNotHexString(const string hex_string) {
	int i=0;
	string not_hex_numbers = "abcdefghijklmnopqrstuvwxyzGHIJKLMNOPQRSTUVWXYZ!#$%&'()*+,-./:;<=>?@[\]^_`{|}~";
	while (hex_string[i]!='\0') {
		for(int v = 0; v < not_hex_numbers.length(); v++) {
			if (hex_string[i]==not_hex_numbers[v])
				return true;
		}
		i++;
	}
	return false;
}