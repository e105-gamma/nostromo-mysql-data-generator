// Zapolniator.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <mysql_connection.h>
#include <Windows.h>

#include <sql.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "mysql_driver.h"
#include <locale.h>
#include <string>
#include <vector>
#include <conio.h>
#include <vector>
#include <fstream>

void print_logo() {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 1);
	std::cout << ("  _   _  ____   _____ _______  ______  ____  __  __  ____           ___  __ ") << std::endl;
	std::cout << (" | \\ | |/ __ \\ / ____|__   _ _|  __ \\ / __ \\|  \\/  |/ __ \\         / _ \\/_ |") << std::endl;
	std::cout << (" |  \\| | |  | | (___    | |   | |__) | |  | | \\  / | |  | | __   _| | | || |") << std::endl;
	std::cout << (" | . ` | |  | |\\___ \\   | |   |  _  /| |  | | |\\/| | |  | | \\ \\ / / | | || |") << std::endl;
	std::cout << (" | |\\  | |__| |____) |  | |   | | \\ \\| |__| | |  | | |__| |  \\ V /| |_| || |") << std::endl;
	std::cout << (" |_| \\_|\\____/|_____/   |_|   |_|  \\_\\\\____/|_|  |_|\\____/    \\_/  \\___(_)_|") << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << std::endl;

}

void success() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 2);
	std::cout << "Успешно!" << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
	std::cout;
}

sql::Connection* connectToServer(sql::Driver *driver) {
	using namespace std;
	std::cout << "Введите адрес сервера. (В случае локального сервера, введите localhost)." << endl << '>';
	string server, login, pass;
	cin >> server;
	cout << "Введите имя пользователя. (по умолчанию root)" << endl << '>';
	cin >> login;
	cout << "Введите пароль." << endl << '>';

	char ch = _getch();
	while (ch != 13) {//character 13 is enter
		pass.push_back(ch);
		cout << '*';
		ch = _getch();
	}
	cout << endl;

	//cin >> pass;
	sql::Connection *con = nullptr;

	std::cout << "Подключение к серверу...";
	try {
		if (server == "localhost") {
			server = "127.0.0.1";
		}
		con = driver->connect(server, login, pass);
		success();
		return con;
	}
	catch (...) {
		std::cout << "Ошибка подключения, проверьте правильность введенных данных." << endl;
		return nullptr;
	}


}


std::vector<std::string> get_all_db(sql::Connection *con) {

	sql::ResultSet *res;
	sql::Statement *stmt;
	stmt = con->createStatement();
	int i = 0;
	res = stmt->executeQuery("SELECT DISTINCT table_schema FROM information_schema.tables WHERE table_schema NOT IN ( 'information_schema', 'performance_schema', 'mysql' );");
	std::vector<std::string> result;
	while (res->next() != false) {
		result.push_back(res->getString("table_schema"));
	}
	return result;

}

std::vector<std::string> connecToDb(sql::Connection *con) {
	std::cout << "Найдены следующие базы данных " << std::endl;
	std::vector<std::string> dbs = get_all_db(con);
	sql::ResultSet *res = nullptr;
	sql::Statement *stmt = con->createStatement();
	int i = 0;
	for (auto n : dbs) {
		std::cout << i << "." << n << std::endl;
		i++;
	}
	std::cout << "К какой подключиться?" << std::endl;
	int choice = -1;
	while (choice<0 || choice >= i) {
		std::cin >> choice;
	}
	stmt->execute("USE " + dbs.at(choice));


	std::string showAllDbStatement = "SELECT table_name FROM information_schema.tables where table_schema=";
	showAllDbStatement = showAllDbStatement + "\"" + dbs.at(choice) + "\"" + ";";

	res = stmt->executeQuery(showAllDbStatement);
	std::vector<std::string> result;
	std::cout << "Эта БД включает в себе следующие таблицы." << std::endl;
	while (res->next() != false) {
		std::cout << res->getString("table_name") << std::endl;
		result.push_back(res->getString("table_name"));
	}
	return result;

}


void insert(sql::Connection *con) {
	sql::ResultSet *res = nullptr;
	sql::Statement *stmt = con->createStatement();
	std::string statement = "INSERT INTO workers VALUES (";
	//std::cin >> statement;
	//res = stmt->executeQuery(statement);

	for (int i = 0; i < 10; i++) {
		std::string s = statement + std::to_string(i) + "," + " \"aa" + "\"" + ");";
		stmt->execute(s);
	}
}



std::vector<std::string> readDictionary(std::string file){

	std::vector<std::string> dictionaryVector;
	std::ifstream dict_file(file);
	std::string line;

	while (std::getline(dict_file, line))
	{
		dictionaryVector.push_back(line);
	}
	return dictionaryVector;
}


int main()
{



	setlocale(LC_ALL, "Russian");
	print_logo();
	std::vector<std::string> a = readDictionary("0.txt");

	

	//sql::mysql::MySQL_Driver *driver;
	sql::Driver *driver;
	sql::Connection *con = nullptr;
	sql::ResultSet *res;



	driver = sql::mysql::get_driver_instance();
	con = connectToServer(driver);
	if (con == nullptr) {
		system("pause");
		return 0;
	}
	//con = driver->connect("127.0.0.1", "root", "Resa7qof");
	connecToDb(con);
	insert(con);


	system("pause");


	return 0;
}

