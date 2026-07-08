#include <iostream>
#include <string>
#include <fstream>

// Добавить пополнение кофе и молока.
// storage сделать приватными или протектед переменные
// добавить переменную вода
// добавить переменную молотое кофе
// добавить меню (как на кофемашине)
// добавить оплату и проверку оплаты
// добавить название напитков в переменную к CoffeeDrink (сделать вывод: ваш Latte/Espresso готов)

class CoffeeDrink {

public:
	int coffee_value;
	int milk_value;
	CoffeeDrink(int cv, int mv) : coffee_value(cv), milk_value(mv) {};

};

class Storage {

public:
	

	Storage() : 
		max_coffee_capacity(0), 
		max_milk_capacity(0) {};

	Storage(int max_coffee_capacity, int max_milk_capacity) :
		max_coffee_capacity(max_coffee_capacity), 
		max_milk_capacity(max_milk_capacity) {};

	bool CheckCoffee(int needed_coffee) {
		if (coffee_capacity - needed_coffee >= 0) {
			return 1;
		}
		else {
			return 0;
		}
	}

	bool CheckMilk(int needed_milk) {
		if (milk_capacity - needed_milk >= 0) {
			return 1;
		}
		else {
			return 0;
		}
	}

	void ShowStorage() {
		std::cout << "max_coffee_capacity: " << max_coffee_capacity << std::endl 
		<< "coffee_capacity: " << coffee_capacity << std::endl;
		std::cout << "max_milk_capacity: " << max_milk_capacity << std::endl 
		<< "milk_capacity: " << milk_capacity << std::endl;
	}

	int max_coffee_capacity;
	int coffee_capacity = 10;
	int max_milk_capacity;
	int milk_capacity = 150;

protected:
	

};

class CoffeeGrinder {

public:
	void Grind(Storage &storage, CoffeeDrink& drink) {
		std::cout << "Grinding the coffee..." << std::endl;
		storage.coffee_capacity -= drink.coffee_value;

	};
};

class CoffeeMaker {

public:
	void Make(Storage& storage, CoffeeDrink& drink) {
		std::cout << "Making the coffee..." << std::endl;
		storage.milk_capacity -= drink.milk_value;
		
	}
};

class CoffeeMachine {
	
public:
	CoffeeMachine(int mcc, int mmc) : storage(mcc, mmc) {
	}
	Storage storage;
	CoffeeGrinder grinder;
	CoffeeMaker maker;

	void start(CoffeeDrink &drink) {
		if (storage.CheckCoffee(drink.coffee_value) && storage.CheckMilk(drink.milk_value)) {
			grinder.Grind(storage, drink);
			maker.Make(storage, drink);
		}
		else {
			std::cout << "Insufficient resources" << std::endl;
		}
		
	}

};

int main() {
	CoffeeDrink Latte(5, 100);
	CoffeeDrink Espresso(5, 0);

	CoffeeMachine LOKO(100, 500);

	LOKO.storage.ShowStorage();

	LOKO.start(Espresso);

	LOKO.storage.ShowStorage();

	

}