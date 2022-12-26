#include "User.h"

int main(int argc, char* argv[]) {
    try {
        Interface interface; // Блок интерфейса(разбор ком.строки)
        interface.ReceiveArguments(argc, argv); //
        
        User user(interface); // Блок получения ID и пароля
        UserHandler handler;    //
        user.SetIdPassword(handler.GetAutDataFromFile(user.GetAutFile()));  //
        //cout << "User id: " << user.GetId() << "\t" << "User password: " << user.GetPassword() << endl; // Тест
        
        user.SetVectorNumber(handler.GetVectorNumberFromFile(user.GetInputFile()));   // Блок получения числа всех векторов, размера 1 вектора и его элементов(все в двоичном формате)
        //cout << "\tVector number: " << user.GetVectorNumber() << endl;    //Тест*/
        
        TCPclient client(user); // Блок авторизации
		cout << "Autentification started..." << endl;
        client.Connection();    //
        client.SendAutMsg(user.GetId());    // Отправляем серверу айди
        user.SetSALT(client.ReceiveAndGetResponce()); // Принимаем от вектора соль
        user.SetHASH(handler.GetHashFromPassword(user.GetSALT(), user.GetPassword())); // Берем соль и пароль из юзера, создаем из них хэш в обработчике и засовываем его в юзера
        client.SendAutMsg(user.GetHASH());  // Отправляем серверу хэш
        client.ReceiveAndGetResponce(); // Принимаем от сервера ответ
		cout << "Autentification was successful!" << endl;
        
        //Блок передачи векторов серверу и получения результатов вычислений
        client.SendVectorNumber(user.GetVectorNumber());	// Отправляем количество векторов
		user.SetCalcNumber(user.GetVectorNumber());	// Присваиваем количеству результатов вычислений значение количества векторов
		handler.RecordCalcNumber(user.GetCalcNumber(), user.GetOutputFile());	// Записываем количество результатов вычислений в файл
		
		cout << "Data exchange started..." << endl;
		for(int i = 2; i < 2 + user.GetVectorNumber(); i++) {
			user.SetVector(handler.GetVectorFromFile(user.GetInputFile(), i));	// Устанавливаем в юзера размер вектора и его элементы
			client.SendVectorSize(user.GetVectorSize());	// Отсылаем серверу размер вектора
			client.SendVector(user.GetVector());	// Отсылаем серверу элементы вектора одним блоком данных
			user.SetCalcResult(client.ReceiveCalcResult());	// Устанавливаем в юзера принятый результат вычислений
			handler.RecordCalcResult(user.GetCalcResult(), user.GetOutputFile());	// Записываем в бинарный файл результат вычислений
		}
		cout << "Data exchange was successful!" << endl;
		client.CloseConnection();
    }
    catch (ErrorHandler<string>& eh) {
        cout << eh << endl;
        return 1;
    }
}