/*
Задание №3
Создать абстрактный базовый класс «Транспортное средство» и производные классы «Автомобиль», «Велосипед», «Повозка».
Create an abstract base class "Vehicle" and derived classes "Car", "Bicycle", "Wagon".
Подсчитать время и стоимость перевозки пассажиров и грузов каждым транспортным средством.
Calculate the time and cost of transporting passengers and goods by each vehicle.
*/
#include <iostream>
#include <windows.h>
using namespace std;
class Vehicle {
public:
	double SPEED; // скорость транспортного средства
	double DISTANCE; // расстояние от пункта ВЫЕЗДА до пункта НАЗНАЧЕНИЯ
	double PRICE_OF_PASSENGER; // цена транспортировки пассажира за 1 час
	double PRICE_OF_BAGGAGE; // цена транспортировки багажа за 1 час
	int NUMBER_OF_PASSENGERS; // максимальное количество пассажиров
public:
	Vehicle() : SPEED(0), DISTANCE(0), PRICE_OF_PASSENGER(0.0), PRICE_OF_BAGGAGE(0.0), NUMBER_OF_PASSENGERS(0.0) {}
	Vehicle(double speed, double distance, double price_of_passenger, double price_of_baggage,
		int number_of_passengers) {
		SPEED = speed;
		DISTANCE = distance;
		PRICE_OF_PASSENGER = price_of_passenger;
		PRICE_OF_BAGGAGE = price_of_baggage;
		NUMBER_OF_PASSENGERS = number_of_passengers;
	}
	virtual void Show() {
		cout << "Скорость транспортного средства : " << SPEED << " км/час" << endl;
		cout << "Цена перевозки пассажира за 1 час : " << PRICE_OF_PASSENGER << " грн." << endl;
		cout << "Максимальное колличество пассажиров : " << NUMBER_OF_PASSENGERS << endl;
		cout << "Цена перевозки багажа за 1 час : " << PRICE_OF_BAGGAGE << " грн." << endl;
		cout << "Расстояние от пункта ВЫЕЗДА до пункта НАЗНАЧЕНИЯ : " << DISTANCE << " км." << endl;
		cout << "Ориентировочная стоимость перевозки пассажира : " << COST_OF_TRANSPORTING_PASSENGER() << " грн." << endl;
		cout << "Ориентировочная стоимость перевозки груза : " << COST_OF_TRANSPORTING_BAGGAGE() << " грн." << endl;
		cout << "Затраченное время на дорогу : " << TIME_OF_TRANSPORTING() << " ч." << endl;
	}
	virtual	~Vehicle() { }
	virtual double TIME_OF_TRANSPORTING() = 0 {	}
	virtual double COST_OF_TRANSPORTING_PASSENGER() = 0 {	}
	virtual double COST_OF_TRANSPORTING_BAGGAGE() = 0 {	}
	/*
	Формулы скорости, расстояния и времени:
	V = S / T;   S = V * T;   T = S / V;
	где V - скорость, S - расстояние, T - время
	where V - speed, S - distance, T - time
	*/
};

class Car :public Vehicle {
private:
	char* VEHICLE_LICENSE_PLATE;
	char* CAR_MODEL;
public:
	Car() : Vehicle(), VEHICLE_LICENSE_PLATE(nullptr), CAR_MODEL(nullptr) {}
	Car(double speed, double distance, double price_of_passenger, double price_of_baggage, int number_of_passengers, const char* vehicle_license_plate, const char* car_model)
		:Vehicle(speed, distance, price_of_passenger, price_of_baggage, number_of_passengers) {
		VEHICLE_LICENSE_PLATE = _strdup(vehicle_license_plate);
		CAR_MODEL = _strdup(car_model);
	}
	void Show() {
		cout << "Модель автомобиля: " << CAR_MODEL << endl;
		cout << "Номерной знак транспортного средства : " << VEHICLE_LICENSE_PLATE << endl;
		Vehicle::Show(); cout << endl << endl;
	}
	~Car() { delete[]VEHICLE_LICENSE_PLATE; delete[]CAR_MODEL; }
	double TIME_OF_TRANSPORTING() { return DISTANCE / SPEED; }
	double COST_OF_TRANSPORTING_PASSENGER() { return PRICE_OF_PASSENGER * TIME_OF_TRANSPORTING(); }
	double COST_OF_TRANSPORTING_BAGGAGE() { return PRICE_OF_BAGGAGE * TIME_OF_TRANSPORTING(); }
};

class Bicycle :public Vehicle {
private:
	char* BICYCLE_TYPE;
	char* BICYCLE_SUBTYPE;
	char* BICYCLE_MODEL;
public:
	Bicycle() : Vehicle(), BICYCLE_TYPE(nullptr), BICYCLE_SUBTYPE(nullptr), BICYCLE_MODEL(nullptr) {}
	Bicycle(double speed, double distance, double price_of_passenger, double price_of_baggage, int number_of_passengers, const char* bicycle_type, const char* bicycle_subtype, const char* bicycle_model)
		:Vehicle(speed, distance, price_of_passenger, price_of_baggage, number_of_passengers) {
		BICYCLE_TYPE = _strdup(bicycle_type);
		BICYCLE_SUBTYPE = _strdup(bicycle_subtype);
		BICYCLE_MODEL = _strdup(bicycle_model);
	}
	void Show() {
		cout << "Тип велосипеда : " << BICYCLE_TYPE << endl;
		cout << "Вид велосипеда: " << BICYCLE_SUBTYPE << endl;
		cout << "Модель велосипеда: " << BICYCLE_MODEL << endl;
		Vehicle::Show(); cout << endl << endl;
	}
	~Bicycle() { delete[]BICYCLE_TYPE; delete[]BICYCLE_SUBTYPE; delete[]BICYCLE_MODEL; }
	double TIME_OF_TRANSPORTING() { return DISTANCE / SPEED; }
	double COST_OF_TRANSPORTING_PASSENGER() { return PRICE_OF_PASSENGER * TIME_OF_TRANSPORTING(); }
	double COST_OF_TRANSPORTING_BAGGAGE() { return PRICE_OF_BAGGAGE * TIME_OF_TRANSPORTING(); }
};

class Wagon :public Vehicle { //повозка // Дилижанс — большая многоместная пассажирская или почтовая повозка, широко использовавшаяся в XIX веке.
private:
	char* WAGON_TYPE;
public:
	Wagon() : Vehicle(), WAGON_TYPE(nullptr) {}
	Wagon(double speed, double distance, double price_of_passenger, double price_of_baggage, int number_of_passengers, const char* wagon_type)
		:Vehicle(speed, distance, price_of_passenger, price_of_baggage, number_of_passengers) {
		WAGON_TYPE = _strdup(wagon_type);
	}
	void Show() { cout << "Тип повозки : " << WAGON_TYPE << endl; Vehicle::Show(); cout << endl; }
	~Wagon() { delete[]WAGON_TYPE; }
	double TIME_OF_TRANSPORTING() { return DISTANCE / SPEED; }
	double COST_OF_TRANSPORTING_PASSENGER() { return PRICE_OF_PASSENGER * TIME_OF_TRANSPORTING(); }
	double COST_OF_TRANSPORTING_BAGGAGE() { return PRICE_OF_BAGGAGE * TIME_OF_TRANSPORTING(); }
};

int main() {
	setlocale(LC_ALL, ""); //працює тільки з потоком виведення
	//Vehicle T(55.25, 100, 23.32, 42.56, 5); // так не должно работать в абстрактном классе.
	Car A(100.5, 300.3, 35.25, 11.35, 4, "АА 1234 АВ", "Toyota Corola");
	A.Show();
	Bicycle B(40.5, 50.5, 5, 2, 1, "Внедорожные велосипеды", "Горный велосипед", "Comanche Maxima 27.5 20.5");
	B.Show();
	Wagon C(45.5, 500.5, 10.5, 5.5, 6, "Грузо-пассажирский Дилижанс");
	C.Show();
}