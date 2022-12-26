#include "User.h"

TCPclient::TCPclient(User user) {
    tcp_socket_ = socket(AF_INET, SOCK_STREAM, 0); 
    if (tcp_socket_ == -1) {
        cerr << "Socket error" << endl;
        exit(1);
    }

    self_addr_ = new (sockaddr_in);
    self_addr_->sin_family = AF_INET; 
    self_addr_->sin_port = htons(55555);
    self_addr_->sin_addr.s_addr = inet_addr("127.0.0.1");

    server_address_ = user.GetServerAddress();
    server_port_ = user.GetServerPort();
}

int TCPclient::Connection() {
    unsigned int port = stoi(server_port_); // Преобразование порта из строки в целочисленное значение для sin_port
    char* server_address_char = new char[server_address_.length()]; // Блок преобразования строки с адресом в массив чар для sin_addr
    server_address_.copy(server_address_char, server_address_.length());    //
    server_address_char[server_address_.length()] = '\0';//
    
    server_addr_ = new (sockaddr_in);
    server_addr_->sin_family = AF_INET;
    server_addr_->sin_port = htons(port);
    server_addr_->sin_addr.s_addr = inet_addr(server_address_char);

    required_connection_ = connect(tcp_socket_,(const sockaddr*)server_addr_, sizeof(sockaddr_in));
    if (required_connection_ == -1) {
        cerr << "Invalid connection" << endl;
        exit(1);
    }
    return 0;
}

int TCPclient::SendAutMsg(string aut_msg) {
    char msg_to_send[aut_msg.length()];
	strcpy(msg_to_send, aut_msg.c_str());

    send(tcp_socket_, msg_to_send, sizeof(msg_to_send), 0);
    cout << "Message: " << '"' << msg_to_send << '"' << " was sent to server" << endl;
    return 0;
}

int TCPclient::SendVectorNumber(uint32_t vector_number) {
	send(tcp_socket_, &vector_number, sizeof(vector_number), 0);
	cout << "Message vector number: " << vector_number << " was sent to server" << endl;
    return 0;
}

int TCPclient::SendVectorSize(uint32_t vector_size) {
    send(tcp_socket_, &vector_size, sizeof(vector_size), 0);
    cout << "Message vector size: " << vector_size << " was sent to server" << endl;
    return 0;
}
int TCPclient::SendVector(vector<float> vectorvr) {
    float msg_vector[vectorvr.size()];
	cout << "Vector: ";
    for(int i = 0; i < vectorvr.size(); i++) {
        msg_vector[i] = vectorvr[i];
		cout << msg_vector[i] << ' ';
    }
	send(tcp_socket_, msg_vector, sizeof(msg_vector), 0);
	cout << "was sent to server" << endl; 
    return 0;
}

string TCPclient::ReceiveAndGetResponce() {
    char received_msg[16] = {0};
    recv(tcp_socket_, received_msg, sizeof(received_msg), 0);
	string responce;
    for(auto& c : received_msg)
		responce += c;
    cout << "Responce from server: " << responce  << endl;
    return responce;
}

float TCPclient::ReceiveCalcResult() {
    float received_calc_result;
    recv(tcp_socket_, &received_calc_result, sizeof(received_calc_result), 0);
	cout << "Received calculation result: " << received_calc_result << endl;
	return received_calc_result;
}

int TCPclient::CloseConnection() {
	cout << "Connection closed." << endl;
    close(tcp_socket_);
    return 0;
}