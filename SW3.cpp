// SW3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <ctime>
#include <clocale>
#include <limits.h>
#include <cstdlib>
#include <typeinfo>
#include <conio.h>
#include <cmath>
#include <clocale>
#include <random>
#define _USE_MATH_DEFINES 
#define p_coeff 1.0675
#define M_PI 3.14

/*Создать класс - интерфейс пространственной фигуры, 
который содержит три элемента с модификатором 
доступа protected.Создать производные классы : 
шаровой сегмент, эллипсоид, прямой круговой цилиндр.
Для каждой из фигур предусмотреть вывод ее названия 
и вычисление площади поверхности.
Случайным образом выбрать фигуру и 
с помощью оператора typeid определить ее тип.*/
using namespace std;

class figure
{
protected:
	double dim1, dim2;
public:
		void setdim(double d1, double d2)
		{
			dim1 = d1;
			dim2 = d2;
		}
		void getdim(double &d1, double &d2)
		{
			d1 = dim1;
			d2 = dim2;
		}
		virtual void get_name()
		{
			cout << "It's just a figure" << endl;
		}
		virtual double get_area()
		{
			return 1;			//спросить у Лерика
		}
	
};

class sphere_segment:public figure
{
public:
	double get_area()
	{
		double d1, d2;
		getdim(d1, d2);
		return 2 * d1*d2*M_PI;
	}
	void get_name()
	{
		cout << "It's a sphere segment" << endl;
	}
};

class ellipsoid:public figure 
{
protected:
	double d3;
public:
	void set_third(double dim3)
	{
		d3 = dim3;
	}
	double get_area()
	{
		double d1, d2;
		getdim(d1, d2);

			return 4*M_PI*pow(((pow((d1*d2), p_coeff) + pow((d1*d3), p_coeff) + pow((d2*d3), p_coeff))/3),(1/p_coeff));
	}
	void get_name()
	{
		cout << "It's an ellipsoid" << endl;
	}
};

class cylinder:public figure
{
	//double h;
public:
	//void set_h(double h1) { h = h1; }
	double get_area()
	{
		double d1, d2;
		getdim(d1, d2);
		//return M_PI * fabs(d1 * d1 - d2 * d2) * h;
		return 2 * M_PI*d1*(d1 + d2);
	}
	void get_name()
	{
		cout << "It's a cylinder" << endl;
	}
};

figure *GetObj();

int main()
{
	//int p;
	setlocale(LC_ALL, "Russian");
	figure *Ptr;
	ellipsoid *cPtr;
	double d1, d2, d3;
	for (int i = 0; i < 10; i++)
	{
		Ptr = GetObj();
		cout << "-What would typeid say?\n-";
		cout << typeid(*Ptr).name() << endl;
		cPtr = dynamic_cast<ellipsoid *>(Ptr);
		Ptr->get_name();
		if (Ptr != NULL)
		{
			cout << "Input dimensions" << endl;
			cout << "d1:";
			cin >> d1;
			cout << "\nd2:";
			cin >> d2;
			Ptr->setdim(d1, d2);
			if (cPtr != NULL)
			{
				//cout << "Input d3" << endl;
				cout << "\nd3:";
				cin >> d3;
				cPtr->set_third(d3);
			}
			cout << "\nSquare of figure = "
				<< Ptr->get_area() << endl;
			cout << "\n______________________________\n" << endl;
		}
	}




}
figure *GetObj()
{
	figure *p = nullptr;
	//time_t(NULL);
	srand(time(NULL));
	switch (rand() % 4)
	{
	case 0: p = new figure;
		break;
	case 1: p = new sphere_segment;
		break;
	case 2: p = new ellipsoid;
		break;
	case 3: p = new cylinder;
		break;
	}
	return p;
}



/*
________________________________________________________________________________________
1.Что такое динамическая идентификация типов? В каких случаях она используется?			|
2.Какие действия выполняет оператор dynamic_cast?										|
3.В чем состоят различия использования операторов typeid (имя_типа) и typeid (объект)?	|
4.Что описывает и какие элементы содержит структура класса type_info?					|
5.Перечислите операторы приведения типа, используемые в С и в С++.						|
________________________________________________________________________________________|


1.Динамическое определение типа позволяет получать информацию о классе объекта, 
а также изменять этот класс во время работы программы. 

2.оператор dynamic_cast приводит тип одного указателя к типу другого указателя 
или тип одной ссылки к типу другой ссылки. 
Приведение dynamic_cast используется в тех случаях, 
когда правильность преобразования не может быть определена компилятором.
В основном, оператор dynamic_cast предназначен для реализации операции приведения полиморфных типов. 
Обычно оператор dynamic_cast выполняется успешно, если указатель (или ссылка) после приведения типов 
становится указателем (или ссылкой) на объект целевого типа, или на объект типа, производного от целевого.

3.typeid (объект) где объект - тот объект, тип которого нужно определить
typeid (имя_типа)позволяет получить объект типа type_info, 
который можно использовать при сравнении типов.
Оператор typeid чаще всего применяют к разыменованным указателям

4.Структура класса type_info содержит информацию об определенном типе. 
В классе type_info определены следующие открытые элементы:
bool operator == (const type_info &объект);
bool operator != (const type_info &объект);
bool before (const type_info &объект);
const char *name();
Сравнение типов возможно благодаря перегруженным операторам == и !=. Функция before() возвращает значение true, если вызывающий объект расположен раньше объекта, заданного в качестве параметра, в смысле сортировки. Функция name() возвращает указатель на имя типа.
Реализации класса type_info могут варьироваться, но все они содержат функцию-элемент name(), которая возвращает имя класса.

5.Приведения компилятором неявно
Также неявные приведения знака: -1 = uint 'b11111...111
явные:(int) x; int(x);
dynamic_cast:безопаснее всего использовать дайнемик
const_cast:
reinterpret_cast:
static_cast:приведения, которые проверяются только во время компиляции.


*/