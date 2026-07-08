#include <iostream>
#include <string>
#include <fstream>

// добавить переменную молотое кофе
// добавить меню (как на кофемашине)
// добавить оплату и проверку оплаты
// добавить название напитков в переменную к CoffeeDrink (сделать вывод: ваш Latte/Espresso готов)

class CoffeeDrink {

public:
	int water_value;
	int coffee_value;
	int milk_value;
	CoffeeDrink(int wv, int cv, int mv) : water_value(wv), coffee_value(cv), milk_value(mv) {};

};

class Storage {
protected:
	int max_water_capacity;
	int water_capacity = 0;
	int max_coffee_capacity;
	int coffee_capacity = 0;
	int max_milk_capacity;
	int milk_capacity = 0;

public:

	Storage() :
		max_water_capacity(0),
		max_coffee_capacity(0), 
		max_milk_capacity(0) {};

	Storage(int max_water_capacity, int max_coffee_capacity, int max_milk_capacity) :
		max_water_capacity(max_water_capacity),
		max_coffee_capacity(max_coffee_capacity), 
		max_milk_capacity(max_milk_capacity) {};

	bool CheckWater(int needed_water) {
		if (water_capacity - needed_water >= 0) {
			return 1;
		}
		else {
			return 0;
		}
	}

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

	void AddWater(int value) {
		if (water_capacity + value > max_water_capacity) {
			std::cout << "Storage overflow." << std::endl << "Added the maximum possible amount of water: " << max_water_capacity - water_capacity << std::endl;
			water_capacity = max_water_capacity;
		}
		else {
			water_capacity += value;
		}
		
	}

	void AddCoffee(int value) {
		if (coffee_capacity + value > max_coffee_capacity) {
			std::cout << "Storage overflow." << std::endl << "Added the maximum possible amount of coffee: " << max_coffee_capacity - coffee_capacity << std::endl;
			coffee_capacity = max_coffee_capacity;
		}
		else {
			coffee_capacity += value;
		}
	}

	void AddMilk(int value) {
		if (milk_capacity + value > max_milk_capacity) {
			std::cout << "Storage overflow." << std::endl << "Added the maximum possible amount of milk: " << max_milk_capacity - milk_capacity << std::endl;
			milk_capacity = max_milk_capacity;
		}
		else {
			milk_capacity += value;
		}
		
	}

	void ReduceWater(CoffeeDrink& drink) {
		water_capacity -= drink.water_value;
	}

	void ReduceCoffee(CoffeeDrink& drink) {
		coffee_capacity -= drink.coffee_value;
	}

	void ReduceMilk(CoffeeDrink& drink) {
		milk_capacity -= drink.milk_value;
	}

	void ShowStorage() {
		std::cout << std::endl  << "max_water_capacity: " << max_water_capacity << std::endl
		<< "water_capacity: " << water_capacity << std::endl
		<< "max_coffee_capacity: " << max_coffee_capacity << std::endl 
		<< "coffee_capacity: " << coffee_capacity << std::endl
		<< "max_milk_capacity: " << max_milk_capacity << std::endl 
		<< "milk_capacity: " << milk_capacity << std::endl << std::endl;
	}

	

protected:
	

};

class CoffeeGrinder {

public:
	void Grind(Storage &storage, CoffeeDrink& drink) {
		std::cout << "Grinding the coffee..." << std::endl;
		storage.ReduceCoffee(drink);

	};
};

class CoffeeMaker {

public:
	void Make(Storage& storage, CoffeeDrink& drink) {
		std::cout << "Making the coffee..." << std::endl;
		storage.ReduceWater(drink);
		storage.ReduceMilk(drink);
		
	}
};

class CoffeeMachine {
	
public:
	CoffeeMachine(int mwc, int mcc, int mmc) : storage(mwc, mcc, mmc) {
	}
	Storage storage;
	CoffeeGrinder grinder;
	CoffeeMaker maker;

	void start(CoffeeDrink &drink) {
		if (storage.CheckCoffee(drink.coffee_value) && storage.CheckMilk(drink.milk_value) && storage.CheckWater(drink.water_value)) {
			grinder.Grind(storage, drink);
			maker.Make(storage, drink);
		}
		else {
			std::cout << "Insufficient resources" << std::endl;
		}
		
	}

};

int main() {
	// Drink(вода, кофе, молоко)

	CoffeeDrink Latte(50, 5, 100);
	CoffeeDrink Espresso(50, 5, 0);

	CoffeeMachine LOKO(1500, 200, 1000);


	LOKO.storage.AddCoffee(20);
	LOKO.storage.AddMilk(100);
	LOKO.storage.AddWater(500);
	LOKO.storage.ShowStorage();

	LOKO.start(Espresso);

	LOKO.storage.ShowStorage();

	

}