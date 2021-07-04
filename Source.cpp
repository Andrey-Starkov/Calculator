#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
using namespace std;
struct Node { //Стэк
	string value;
	Node* next;
};

int priority(string x) { //Приорететы знаков
	if ((x == "+") || (x == "-")) {
		return 1;
	}
	if ((x == "*") || (x == "/")) {
		return 2;
	}
	if ((x == "(") || (x == ")")) {
		return 0;
	}
}

Node* ADDfirst(Node* front, string b) { //Добавление в стэк
	Node* current = new Node;
	current->value = b;
	current->next = front;
	return current;
}

Node* first(string b) { //Создание первого элемента стэка
	Node* current = new Node;
	current->value = b;
	current->next = nullptr;
	return current;
}


Node* deletefirst(Node* front) { //Удаление в стэке
	Node* temp = front;
	front = temp->next;
	delete temp;
	return front;
}

string Converting(Node* front,string expression) { //Перевод в постфиксный вид
	string str="";
	string symbol = "";
	bool firsty = false;
	int i = 0;
	for (int i = 0; i < expression.size(); i++) {
		symbol = expression[i];
		if ((symbol != "+") && (symbol != "-") && (symbol != "/") && (symbol != "*") && (symbol != "(") && (symbol != ")")) {
				str += symbol;
		}
		else {
			str += " ";
			if (!firsty) { front = first(symbol); firsty = true; }
			else {

				if (symbol == "(") {
					front = ADDfirst(front, symbol);
				}

				if (symbol == ")") {


					while ((front->value != "(")) {
						str+= front->value;
						
						front = deletefirst(front);
					} 
					front = deletefirst(front);
				}


				if ((symbol == "+")||(symbol=="/")||(symbol=="*")||(symbol=="-"))
				{
					if (front == nullptr) { front = first(symbol); }
					else {
						while ((priority(front->value) >= priority(symbol))) {
							str += front->value+" ";
								front = deletefirst(front);
								if (front == nullptr) { break; }
						}

						if (front == nullptr) { front = first(symbol); }
						else {
							front = ADDfirst(front, symbol);
						}
					}
				}
			}

		}
	}
	str += " ";
	while (front!=nullptr) {
		str += front->value+" ";
		front = deletefirst(front);
	}
	return str;
}

void Calculation(Node* front, string c) { //Счёт выражения из постфиксной записи
	double a, b;
	double s=0;
	string symbol = "";
	string stroka="";
	bool firsti = false;
	int i = 0;
	for (int i = 0; i < c.size(); i++) {
		symbol = c[i];
		if (symbol == " ") {
			if (stroka != "") {
				if (firsti) {
					front = first(stroka);
				}
				else {
					front = ADDfirst(front, stroka);
				}
			}
			stroka = "";
			continue; };

		if ((symbol != "+") && (symbol != "-") && (symbol != "/") && (symbol != "*") && (symbol != "(") && (symbol != ")")) {
			stroka += symbol;
		}

		else {

			a = atof(front->value.c_str());
			front = deletefirst(front);
			b = atof(front->value.c_str());
			front = deletefirst(front);
			if (symbol == "+") {
				s = b + a;
			}
			if (symbol == "*") {
				s = b * a;
			}
			if (symbol == "-") {
				s = b - a;
			}
			if (symbol == "/") {
				s = b / a;
			}
			front = ADDfirst(front, to_string(s));
		}
	}
	cout << s;
}

bool test(string expression) { //Проверки на правильность ввода
	int count = 0;
	bool skobka=false;
	for (int i = 1; i < expression.size(); i++) {
		if ((expression[i] == '+') || (expression[i] == '-') || (expression[i] == '*') || (expression[i] == '/')) {
			count++;
				if ((expression[i - 1] == '+') || (expression[i - 1] == '-') || (expression[i - 1] == '*') || (expression[i - 1] == '/')) {
					cout << "Ошибка ввода"; return false;
			}
		}
		if (expression[i-1] == '(') { skobka = true; }
		if (expression[i-1] == ')') { if (!skobka) { cout << "Ошибка ввода"; return false; } else { skobka = false; } }
	}
	if (count == 0) { cout << "Ошибка ввода"; return false; }
	return true;
}

int main() {
	setlocale(LC_ALL, "Russian");
	Node* front = new Node;
	string expression; //Математическое выражение
	cin >> expression;

	if (test(expression)) {
	expression = Converting(front, expression);
	Calculation(front, expression);
		}
		else return 1;

}
