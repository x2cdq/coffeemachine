#include <iostream>
#include <string>
#include <fstream>
#include <map>

// добавить переменную молотое кофе
// добавить оплату и проверку оплаты

class CoffeeDrink {

public:
	int water_value;
	int coffee_value;
	int milk_value;
	std::string name;

	CoffeeDrink() : water_value(0), coffee_value(0), milk_value(0), name("") {
	}

	CoffeeDrink(int wv, int cv, int mv, std::string name) : water_value(wv), coffee_value(cv), milk_value(mv), name(name) {};

	friend std::ostream& operator<<(std::ostream& out, const CoffeeDrink& drink) {
		out << drink.water_value << " " << drink.coffee_value << " " << drink.milk_value << " " << drink.name;
		return out;
	}

	friend std::istream& operator>>(std::istream& in, CoffeeDrink& drink) {
		if (in >> drink.water_value >> drink.coffee_value >> drink.milk_value) {
			std::getline(in >> std::ws, drink.name);
		}
		return in;
	}
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

	bool CheckTheIngridients(CoffeeDrink& drink) {
		if (water_capacity - drink.water_value >= 0 && coffee_capacity - drink.coffee_value >= 0 && milk_capacity - drink.milk_value >= 0) {
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
			std::cout << "Added " << value << " amount of water." << std::endl;
		}
		
	}

	void AddCoffee(int value) {
		if (coffee_capacity + value > max_coffee_capacity) {
			std::cout << "Storage overflow." << std::endl << "Added the maximum possible amount of coffee: " << max_coffee_capacity - coffee_capacity << std::endl;
			coffee_capacity = max_coffee_capacity;
		}
		else {
			coffee_capacity += value;
			std::cout << "Added " << value << " amount of coffee." << std::endl;
		}
	}

	void AddMilk(int value) {
		if (milk_capacity + value > max_milk_capacity) {
			std::cout << "Storage overflow." << std::endl << "Added the maximum possible amount of milk: " << max_milk_capacity - milk_capacity << std::endl;
			milk_capacity = max_milk_capacity;
		}
		else {
			milk_capacity += value;
			std::cout << "Added " << value << " amount of milk." << std::endl;
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
		std::cout << std::endl << "water_capacity: " << water_capacity << std::endl
			<< "coffee_capacity: " << coffee_capacity << std::endl
			<< "milk_capacity: " << milk_capacity << std::endl
			<< "max_water_capacity: " << max_water_capacity << std::endl
			<< "max_coffee_capacity: " << max_coffee_capacity << std::endl
			<< "max_milk_capacity: " << max_milk_capacity << std::endl << std::endl;
	}
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
		std::cout << "Your " << drink.name << " is ready!" << std::endl;
	}
};

class CoffeeMachine {
	std::string name;
public:
	CoffeeMachine(int mwc, int mcc, int mmc, std::string name) : storage(mwc, mcc, mmc), name(name) {
	}
	Storage storage;
	CoffeeGrinder grinder;
	CoffeeMaker maker;

	void start(CoffeeDrink &drink) {
		if (storage.CheckTheIngridients(drink)) {
			grinder.Grind(storage, drink);
			maker.Make(storage, drink);
		}
		else {
			std::cout << "Insufficient resources" << std::endl;
		}
		
	}

	std::string GetName() {
		return name;
	}
};

int main() {
	CoffeeMachine DELONGHI(2000, 200, 1000, "DELONGHI");
	DELONGHI.storage.AddWater(1000);
	DELONGHI.storage.AddCoffee(100);
	DELONGHI.storage.AddMilk(500);

	std::map<int, CoffeeDrink> menu_book;
	std::string path = "storage.txt";

	std::ifstream fs;
	CoffeeDrink temp;
	int n = 1;

	fs.open(path, std::ios::in);
	if (!fs.is_open()) {
		std::cout << "File error!" << std::endl;
	}
	else {
		while (fs >> temp) {
			menu_book.insert({ n, temp });
			n++;
		}
	}
	fs.close();

	while (true) {
		std::cout << "------------------------" << std::endl
			<< "CoffeeMachine " << DELONGHI.GetName() << std::endl
			<< "1. Menu" << std::endl
			<< "2. Add the ingridients" << std::endl
			<< "3. Check the storage" << std::endl
			<< "4. Exit" << std::endl;
		int menu_selection;
		std::cin >> menu_selection;

		switch (menu_selection) {
		case 1: {
			for (auto& [number, drink] : menu_book) {
				std::cout << number << ". " << drink.name << std::endl;
			}
			int drink_selection;
			std::cin >> drink_selection;
			if (menu_book.find(drink_selection) != menu_book.end()) {
				CoffeeDrink& selected_drink = menu_book.at(drink_selection);
				std::cout << "Starting " << (selected_drink).name << "..." << std::endl;
				DELONGHI.start(selected_drink);
			}
			else {
				std::cout << "Invalid number!" << std::endl;
			}
			

			break;
		}
		case 2: {
			int water_value;
			int coffee_value;
			int milk_value;
			std::cout << "Enter the resources." << std::endl;

			std::cout << "Water value: ";
			std::cin >> water_value;
			DELONGHI.storage.AddWater(water_value);

			std::cout << "Coffee value: ";
			std::cin >> coffee_value;
			DELONGHI.storage.AddCoffee(coffee_value);

			std::cout << "Milk value: ";
			std::cin >> milk_value;
			DELONGHI.storage.AddMilk(milk_value);
			

			break;
		}
		case 3: {
			DELONGHI.storage.ShowStorage();
			break;
		}
		case 4: {
			exit(0);
		}
		}
	}

	return 0;
}