#pragma once
class Ingredient {
protected:
	string name;
	float price;
	double fats;
	double protein;
	double carbohydrates;
	int kcal;
	int id;

public:


	Ingredient(int id, string name, float price, double fats, double protein, double carbohydrates, int kcal)
	{
		SetName(name);
		SetProtein(protein);
		SetFats(fats);
		SetCarbohydrates(carbohydrates);
		SetKcal(kcal);
		SetPrice(price);
		SetId(id);
	}
	//getter setter
#pragma region SETTERS 

	void SetName(string name)
	{
		if (name.length() < 2)
			throw runtime_error("Mehsulun adi en az 2 symbol");

		this->name = name;

	}


	void SetPrice(float price)
	{
		if (price <= 0)
			throw runtime_error("Mehsulun qiymeti menfi ola bilmez");

		this->price = price;
	}
	void SetId(int id)
	{
		if (id <= 0)
			throw runtime_error("Mehsulun idsi menfi ola bilmez");

		this->id = id;
	}


	void SetProtein(double protein)
	{
		if (protein <= 0)
			throw runtime_error("Protein menfi ola bilmez");

		this->protein = protein;
	}

	void SetFats(double fats)
	{
		if (fats <= 0)
			throw runtime_error("Yagliliq  menfi ola bilmez");

		this->fats = fats;

	}

	void SetCarbohydrates(double carbohydrates)
	{
		if (carbohydrates <= 0)
			throw runtime_error("Karbohidrat menfi ola bilmez");
		this->carbohydrates = carbohydrates;
	}

	void SetKcal(int kcal)
	{
		if (kcal <= 0)
			throw runtime_error("Kalori menfi ola bilmez");
		this->kcal = kcal;
	}


#pragma endregion SETTERS 

#pragma region GETTERS
	string getName() { return name; }
	double getprotein() { return protein; }
	double getFats() { return fats; }
	double getCarbohydrates() { return carbohydrates; }
	int getKcal() { return kcal; }

	float getPrice() { return price; }
	int getid() { return id; }
#pragma endregion  GETTERS

	 void Show(int amount) const
	{
		cout << "Id: " << id << "Name: " << name << " Price: " << amount * price << " Fats: " << amount * fats << " Protein : " << amount * protein << " Carbohydrates : " << amount * carbohydrates << " Kcal : " << amount * kcal;
	}
    void Show() const
	{
		cout << "Id: " << id << " Name: " << name << " Price: " << price << " Manat. " << " Fats: " << fats << " Protein : " << protein << " Carbohydrates : " << carbohydrates << " Kcal : " << kcal;
	}



};

class RecipetItem
{
	Ingredient* ingredient; //one object  
	int amount;
	
public:
	RecipetItem(int amount, Ingredient* ingredient)
	{
		SetAmount(amount);
		SetIngredient(ingredient);
	}


#pragma  region Setter
	void SetAmount(int amount)
	{
		if (amount <= 0)
			throw runtime_error("Invalid Amount");

		this->amount = amount;
	}

	void SetIngredient(Ingredient* ingredient)
	{
		if (ingredient == nullptr)
			throw runtime_error("Ingredient can't be NULL");
		this->ingredient = ingredient;
	}
#pragma endregion Setter


#pragma region Getter
	Ingredient* getIngredient() { return ingredient; }
	int getAmount() { return amount; }


#pragma endregion Getter


	void RecipetItemshow()
	{
		cout << "Amount: " << amount << endl;
		ingredient->Show(amount);

	}
	
};

class Basket;

class MenuItem
{
protected:
	vector<RecipetItem>recipetItems;
	string name;
	int count;
	float price;
	int dishId;
public:
	MenuItem()
	{
		name = "";
		count = 1;
	}
	MenuItem(int id, string& name, int count, vector<RecipetItem>& recipetItems)
	{
		SetName(name);
		SetCount(count);
		SetRecipet(recipetItems);
		dishId = id;
	}

#pragma region SETTER
	int SetId(int id)
	{
		if (id <= 0)
			throw("iNVALID ID");
		this->dishId = id;
	}
	void SetName(string name)
	{
		if (name.size() <= 1)
			throw runtime_error("Invalid Burger name");

		this->name = name;
	}
	void SetPrice(float price)
	{
		if (price <= 0)
			throw runtime_error("Price cont be less then zero");
		this->price = price;
	}

	void SetCount(int count)
	{
		if (count < 0 and count>10)
			throw runtime_error("Invalid Burger count Min 1 Max 10");


		this->count = count;

	}

	void SetRecipet(vector<RecipetItem>& recipetItems)
	{
		/*if (recipetItems.empty())
			throw runtime_error("Invalid recipets");*/

		this->recipetItems = recipetItems;
	}
#pragma endregion SETTER

#pragma region GETTER

	string getName() const { return this->name; }
	int getCount() const { return this->count; }
	vector<RecipetItem>& getRecieptItem() { return this->recipetItems; }
	float getPrice() { return price; }
	int GetId() const { return dishId; }

#pragma endregion GETTER



	float  CalCulatePrice()
	{
		float sum = 0;
		for (auto& i : recipetItems)
		{
			sum += i.getAmount() * i.getIngredient()->getPrice();

		}
		price = sum;
		return price;
	}

	virtual void addIngredient(RecipetItem recipetItem)
	{
		for (auto& i : recipetItems)
		{
			if (i.getIngredient()->getid() == recipetItem.getIngredient()->getid())
			{

				i.SetAmount(i.getAmount() + recipetItem.getAmount());
				return;
			}
		}

		recipetItems.push_back(recipetItem);



	}


	virtual void showDishInfo()
	{
		cout << "Dish Id: " << GetId() << "\n";
		cout << "Dish Name: " << getName() << "\n";
		cout << "Dish Count: " << getCount() << "\n";
		cout << "Dish Price: " << CalCulatePrice() << "\n";
		cout << "Show Ingredient: \n";
		for (auto& i : getRecieptItem())
		{
			cout << "- " << i.getAmount() << " x ";
			i.getIngredient()->Show(i.getAmount());
			cout << endl;

		}

	}

	

	



};

class Basket {
private:
	vector<MenuItem*> items;

public:


	vector<MenuItem*>& getMenu() { return items; }

	void addItem(MenuItem* item) {
		if(item!=nullptr)
		{
			items.push_back(item);
			cout << "Menu Item added to  basket " << endl;
		}
	}

	void removeItem(MenuItem* item) {
		auto it = find(items.begin(), items.end(), item);
		if (it != items.end()) {
			items.erase(it);
			cout << "Menu Item removed from  basket" << endl;
		}
		else {
			cout << "Menu Item not found in  basket" << endl;
		}
	}

	vector<string> showBasket(vector<string>& resut) {
		
		resut.clear();
		for (const auto& item : items) {
			resut.push_back("Id: " + to_string(item->GetId()) + " " + item->getName());
		}
		resut.push_back("Delete Dish");
		resut.push_back("Total Amount");
		resut.push_back("Exit");
		resut.push_back("Submit");
	   return resut ;
	}
};
bool compareByName(MenuItem* item, const std::string& name) {
	return item->getName() == name;
}

