#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <Windows.h>

using namespace std;

double Input();

//Функция поддержи команд
bool Command(string& str) {
	bool command=false;

	bool end = false;
	bool help = false;
	bool clear = false;
	

	if (str == "/end") {
		end = true;
	}
	if (str == "/clear") {
		clear = true;
	}
	if (str == "/help") {
		help = true;
	}
	if(str == "/lan 15"){
		cout<<setprecision(15);
		command = true;
	}
	if (str == "/lan 6") {
		cout << setprecision(6);
		command = true;
	}

	if (end) {
		ExitProcess(0);
	}
	if (clear) {
		system("cls");
		clear = false;
		command = true;
	}
	if (help) {
		cout << endl;
		cout << "/clear\t - очистка консоли "<<endl;
		cout << "/lan 15\t - увеличенная длина вывода " << endl;
		cout << "/lan 6\t - стадартная длина вывода " << endl;
		cout << "/end\t - закрытие программы" << endl;
		help = false;
		command = true;
	}
	return command;
}


double calculate(string& str) {
	//Значение высчитываемого результата 
	double data;

	do

	{
		int a = -1, b = -1;
		for (int i = 0; i < str.size(); i++) {

			if (str[i] == '(') {
				a = i;

			}
			if (str[i] == ')' && a > -1) {
				b = i;

			}

			if (b > -1) {
				string nstr = str.substr(a + 1, b - a - 1);

				nstr = to_string(calculate(nstr));

				for (int i = 0; i < nstr.length(); ++i) {
					if (nstr[i] == ',') {
						nstr[i] = '.';
					}
				}

				str.replace(a, b - a + 1, nstr);

				return calculate(str);

			}

		}
		vector <char> Chars;
		vector <double> Values;

		stringstream ss(str);

		//Переменные для временного хрананения значений 
		char ch;
		double db;

		for (int i = 0; i < str.size(); i++) {
			if (str[i] == '+' && str[i + 1] == '-')
			{
				str.erase(str.begin() + i);
			}
			if (str[i] == '-' && str[i + 1] == '-')
			{
				str[i]='+';
				str.erase(str.begin() + i+1);
			}

		}

	
		bool isFirst = true;
		bool isNegative = false;
		bool isOperator = false; // Новая переменная для отслеживания операторов

		while (ss.get(ch)) {
			if (isdigit(ch)) {
				ss.putback(ch);
				if (ss >> db) {
					if (isNegative) {
						db = -db;
						isNegative = false;
					}
					Values.push_back(db);
				}
			}
			else if (ch == '-') {
				if (isFirst) {
					Chars.push_back(ch);
				}
				else {
					Chars.push_back('+');
					isNegative = true;
				}
			}
			else {
				Chars.push_back(ch);
			}
			isFirst = false;
		}


		if (str[0] == '-') {
			Chars.erase(Chars.begin());
			Values[0] = -(Values[0]);
		}
		
		
		for (int i = 0; i < Chars.size(); i++) {
			
			if (Chars[i] == '^') {
				
				if (Values[i + 1] < 0) {
					Values[i] = pow(Values[i], Values[i + 1]);
					Values.erase(Values.begin() + i + 1);
					Chars.erase(Chars.begin() + i);
					Chars.erase(Chars.begin() + i);
					i--;
				}
				else {
					Values[i] = pow(Values[i], Values[i + 1]);
					Values.erase(Values.begin() + i + 1);
					Chars.erase(Chars.begin() + i);
					
					i--;
				}
				
			}
		}
		

	

		bool flag_chars= 0;

		do
		{

		for (int i = 0; i < Chars.size(); i++) {
			flag_chars = 0;


			if (Chars[i] == '*') {

				Values[i] *= Values[i + 1];
				Values.erase(Values.begin() + i + 1);
				Chars.erase(Chars.begin() + i);

			}

			if (Chars[i] == '/') {
				//Проверка деления на 0
				if (Values[i+1] == 0) {

					cout << "Деление на 0 невозможно" << endl;
					cout << "==============" << endl;
					Values[0] = Input();
				}

				else
				{
					Values[i] /= Values[i + 1];
					Values.erase(Values.begin() + i + 1);
					Chars.erase(Chars.begin() + i);
				}
			}
			for (int i = 0; i < Chars.size(); i++) {
				if (Chars[i] == '*' || Chars[i] == '/') {
					flag_chars = 1;
				}
			}
		}
		} while (flag_chars);
		//Выполнение сложения и вычитания 
		data = Values[0];
		for (int i = 0; i < Chars.size(); i++) {

			if (Chars[i] == '+')
				data += Values[i + 1];

			if (Chars[i] == '-')
				data -= Values[i + 1];

		}

		break;

	} while (true);
	
	return data;

}



//Функция записи строки в массивы и проверки корректности ввода 
double Input() {
	string str;

	do
	{
		
		getline(cin, str);
		stringstream ss(str);

		if (Command(str)) {
			cout << "==============" << endl;
			continue;
		}

		vector <char> Chars;
		vector <double> Values;

		//Переменные для временного хрананения значений 
		char ch;
		double db;
		
		
		
		while (ss.get(ch)) {
			if (isdigit(ch) || ch == '.') {
				ss.putback(ch);
				if (ss >> db) {
					Values.push_back(db);
				}
			}
			else {
				Chars.push_back(ch);
			}
		}

		//Проверка на ввод неподдерживаемых операторов
	
		
		bool flag = false;
		int counter1 = 0;
		int counter2 = 0;
		for (int i = 0; i < Chars.size(); i++) {
			
			if (Chars[i] == '(') {
				counter1++;
			}
			if (Chars[i] ==')'&& counter1> counter2) {
				counter2++;
			}
		
			if (Chars[i] != '+' && Chars[i] != '-' && Chars[i] != '*' && Chars[i] != '/' 
				&& Chars[i] != '^' && Chars[i] != '(' && Chars[i] != ')') {
				flag = true;
				break;
			}
		}
		
		if (counter1 != counter2) {
			flag = true;
		}

		

		for (int i = 0; i < str.size(); i++) {
			if (str[i] == ')' && str[i + 1] == '(') {
				str.insert(i + 1, 1, '*');
			}
			if (str[i] == ')' && isdigit(str[i + 1])) {
				str.insert(i + 1, 1, '*');
			}
			if (str[i] == '(' && isdigit(str[i - 1])) {
				
				str.insert(i , 1, '*');
			}
			if (str[i] == '(' && str[i + 1] == ')') {
				flag = true;
				break;
			}
			if (str[i] == str[i + 1]&& str[i] == '*') {
				flag = true;
				break;
			}
			if (str[i] == str[i + 1] && str[i] == '/') {
				flag = true;
				break;
			}
			if (str[i] == str[i + 1] && str[i] == '+') {
				flag = true;
				break;
			}
			
			if (str.back()=='+'|| str.back() == '-' || str.back() == '*' || str.back() == '/' || str.back() == '^' ) {
				flag = true;
				break;
			}
			if (str[i] == str[i+1] && str[i]=='+' || str[i] == str[i + 1] && str[i] == '-' || 
				str[i] == str[i + 1] && str[i] == '*' || str[i] == str[i + 1] && str[i] == '/' ||
				str[i] == str[i + 1] && str[i] == '^') {
				flag = true;
				break;
			}
			if (str[0] == '*' || str[0] == '/' || str[0] == '^') {
				flag = true;
				break;
			}
		}


		if (flag){
			cout << "Некорректный ввод " << endl;
			cout << "==============" << endl;
			Values.clear();
			Chars.clear();
			continue;
		}
		
		break;

	} while (true);
	
	int a = -1, b = -1;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '(') {
			a = i;
			
		}
		if (str[i] == ')' && a > -1) {
			b = i;
			
		}

		if (b > -1) {
			string nstr = str.substr(a +1, b - a -1 );
		
			nstr=to_string(calculate(nstr));

			for (int i = 0; i < nstr.length(); ++i) {
				if (nstr[i] == ',') {
					nstr[i] = '.';
				}
			}

			str.replace(a, b - a + 1,nstr);
			
			return calculate(str);

		}
	
	}
	return calculate(str);
}



int main() {
	setlocale(LC_ALL, "ru");

	cout << "Введите выражение одной строкой без пробелов" << endl;
	cout << "Для вычисления значения выражения используйте операторы: + - * / ^" << endl;
	cout <<"/help - список доступных команд" << endl;
	cout << "==============" << endl ;

	while (true) {

		
		cout << Input() << endl;
		cout << "==============" << endl;

	}

	return 0;
}