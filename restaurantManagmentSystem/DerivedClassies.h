#pragma once


class Stock {
	vector<Ingredient*>ingredient;
	unordered_map<int, int> ingredientCounts;
	double mcBudget;
public:

	Stock(double mcBudget, vector<Ingredient*>ing)
	{
		SetBudget(mcBudget);

		ingredient = ing;
	}
	void SetBudget(double mcBudget)
	{
		if (mcBudget < 0)
			throw runtime_error("mcBudget cant be less zero");
		this->mcBudget = mcBudget;


	}
	void SetCount(int id, int count)
	{
		if (ingredientCounts[id] - count > 0)
		{
			ingredientCounts[id] -= count;
		}
		else if (ingredientCounts[id] - count == 0)
		{
			ingredientCounts[id] -= count;
			ingredient.erase(std::remove_if(ingredient.begin(), ingredient.end(),
				[id](Ingredient* i) { return id == i->getid(); }), ingredient.end());
		}
		else
		{
			throw runtime_error("NOT ENOUGH INGREDENT IN STOCK");
		}
	}
#pragma region Getter
	double GetBudget() { return mcBudget; }
	vector<Ingredient*> GetIngredient() { return ingredient; }
	int getIngredientCounts(int id) {

		return ingredientCounts[id];
	}
#pragma endregion Getter

	void readFileBudget(const string& filePath)
	{
		ifstream fs(filePath, ios::in);
		if (fs.is_open())
		{
			string line;
			while (getline(fs, line) && line.find("Budget:") == string::npos);

			size_t budgetPos = line.find(':');
			if (budgetPos != string::npos) {
				mcBudget = stod(line.substr(budgetPos + 1));
			}
		}
	}
	void readFileStoreIngredient(const string& filePath) {
		ifstream fs(filePath, ios::in);
		if (fs.is_open()) {
			string line;


			while (getline(fs, line)) {

				size_t pos1 = line.find('#');
				size_t pos2 = line.find('#', pos1 + 1);
				size_t pos3 = line.find('#', pos2 + 1);
				size_t pos4 = line.find('#', pos3 + 1);
				size_t pos5 = line.find('#', pos4 + 1);
				size_t pos6 = line.find('#', pos5 + 1);
				size_t pos7 = line.find('#', pos6 + 1);

				if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos &&
					pos4 != string::npos && pos5 != string::npos && pos6 != string::npos && pos7 != string::npos) {

					int id = stoi(line.substr(0, pos1));
					string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
					float price = stof(line.substr(pos2 + 1, pos3 - pos2 - 1));
					double fats = stod(line.substr(pos3 + 1, pos4 - pos3 - 1));
					double protein = stod(line.substr(pos4 + 1, pos5 - pos4 - 1));
					double carbo = stod(line.substr(pos5 + 1, pos6 - pos5 - 1));
					int kcal = stoi(line.substr(pos6 + 1, pos7 - pos6 - 1));
					int count = stoi(line.substr(pos7 + 1));



					ingredient.push_back(new Ingredient(id, name, price, fats, protein, carbo, kcal));
					ingredientCounts[id] = count;
				}
			}

			fs.close();
		}
		else {
			cerr << "Error opening file: " << filePath << endl;
		}
	}
	bool isIngredientInFile(Ingredient* ingredient, const string& fileName)
	{
		ifstream fs(fileName);
		if (fs.is_open())
		{
			string line;
			while (getline(fs, line))
			{

				size_t pos1 = line.find("#");
				size_t pos2 = line.find("#", pos1 + 1);

				if (pos1 != string::npos && pos2 != string::npos)
				{
					int id = stoi(line.substr(0, pos1));



					if (id == ingredient->getid())
					{
						fs.close();
						return true;
					}
				}
			}
			fs.close();
		}
		return false;
	}

	void writeFileStoreIngredient(const vector<Ingredient*>& ing, const string& filePath) {
		ofstream fs(filePath, ios::out);
		if (fs.is_open()) {
			for (const auto& i : ing) {
				if (isIngredientInFile(i, filePath))
					continue;
				fs << i->getid() << "#" << i->getName() << "#" << i->getPrice() << "#"
					<< i->getFats() << "#" << i->getprotein() << "#" << i->getCarbohydrates() << "#" << i->getKcal()
					<< "#" << ingredientCounts[i->getid()] << "\n";
			}

			fs.close();
		}
		else {
			cerr << "Error opening file for writing: " << filePath << endl;
		}
	}
	void writeBudgetToFile(const string& filePath)
	{
		ofstream fs(filePath, ios::out);
		if (fs.is_open()) {
			fs << "Budget: " << mcBudget << "\n";
			fs.close();
		}
		else {
			cerr << "Error opening file for writing: " << filePath << endl;
		}
	}

	vector<Ingredient*> addIngredient(Ingredient* newIngredient, int count)
	{
		if (newIngredient == nullptr)
			throw runtime_error("NewIngredient is Null");

		if (count < 0)
			throw runtime_error("Count of NewIngredient cant be less then zero");

		if (mcBudget < newIngredient->getPrice() * count)
			throw runtime_error("Not enough Money");


		int ingredientId = newIngredient->getid();

		if (ingredientCounts.find(ingredientId) != ingredientCounts.end()) {
			ingredientCounts[ingredientId] += count;
		}
		else {
			ingredientCounts[ingredientId] = count;
			ingredient.push_back(newIngredient);
		}
		mcBudget -= newIngredient->getPrice() * count;
		writeBudgetToFile("budget.txt");
		writeFileStoreIngredient(ingredient, "stock.txt");

		return ingredient;
	}
	vector<Ingredient*> addIngredient(Ingredient* newIngredient, int count,int i)
	{
		if (newIngredient == nullptr)
			throw runtime_error("NewIngredient is Null");

		if (count < 0)
			throw runtime_error("Count of NewIngredient cant be less then zero");

		if (mcBudget < newIngredient->getPrice() * count)
			throw runtime_error("Not enough Money");


		int ingredientId = newIngredient->getid();

		if (ingredientCounts.find(ingredientId) != ingredientCounts.end()) {
			ingredientCounts[ingredientId] += count;
		}
		else {
			ingredientCounts[ingredientId] = count;
			ingredient.push_back(newIngredient);
		}
		

		return ingredient;
	}
	void showStock()
	{
		cout << "------------------------------------{Stock}----------------------------------------\n";
		for (auto& i : ingredient) {
			int ingredientId = i->getid();
			int count = ingredientCounts[ingredientId];
			cout << "Count: " << count << endl;
			i->Show();
			cout << endl;
		}

		cout << "-----------------------------------------------------------------------------------\n";
	}

	~Stock() {



	}

};




class Store
{
	vector<Ingredient*>ingredient;
public:
	Store(vector<Ingredient*>ing)
	{
		SetIngredient(ing);
	}

	void SetIngredient(vector<Ingredient*>ingredient)
	{
		this->ingredient = ingredient;
	}
	vector<Ingredient*> GetIngredient() { return ingredient; }




	bool isIngredientInFile(Ingredient* ingredient, const string& fileName)
	{
		ifstream fs(fileName);
		if (fs.is_open())
		{
			string line;
			while (getline(fs, line))
			{

				size_t pos1 = line.find("#");
				size_t pos2 = line.find("#", pos1 + 1);

				if (pos1 != string::npos && pos2 != string::npos)
				{
					int id = stoi(line.substr(0, pos1));



					if (id == ingredient->getid())
					{
						fs.close();
						return true;
					}
				}
			}
			fs.close();
		}
		return false;
	}




	void writeFileStoreIngredient(const vector<Ingredient*>& ing, const string& filePath)
	{
		ofstream fs(filePath, ios::app);
		if (fs.is_open())
		{
			for (const auto& i : ing)
			{
				if (isIngredientInFile(i, filePath))
				{
					continue;
				}

				fs << i->getid() << "#" << i->getName() << "#"
					<< i->getPrice() << "#" << i->getFats() << "#"
					<< i->getprotein() << "#" << i->getCarbohydrates() << "#"
					<< i->getKcal() << "\n";
			}
			fs.close();
		}
		else
		{
			throw runtime_error("Failed to open the file for writing!");
		}
	}

	void readFileStoreIngredient(string filePath) {
		ifstream fs(filePath, ios::in);
		if (fs.is_open()) {
			string line;

			int lastId = 0;

			while (getline(fs, line)) {

				size_t pos1 = line.find('#');
				size_t pos2 = line.find('#', pos1 + 1);
				size_t pos3 = line.find('#', pos2 + 1);
				size_t pos4 = line.find('#', pos3 + 1);
				size_t pos5 = line.find('#', pos4 + 1);
				size_t pos6 = line.find('#', pos5 + 1);

				if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos &&
					pos4 != string::npos && pos5 != string::npos && pos6 != string::npos) {

					int id = stoi(line.substr(0, pos1));
					string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
					float price = stof(line.substr(pos2 + 1, pos3 - pos2 - 1));
					double fats = stod(line.substr(pos3 + 1, pos4 - pos3 - 1));
					double protein = stod(line.substr(pos4 + 1, pos5 - pos4 - 1));
					double carbo = stod(line.substr(pos5 + 1, pos6 - pos5 - 1));
					int kcal = stoi(line.substr(pos6 + 1));

					int maxId = id;
					for (const auto& ingredient : ingredient) {
						if (ingredient->getid() > maxId) {
							maxId = ingredient->getid();
						}
					}




					ingredient.push_back(new Ingredient(id, name, price, fats, protein, carbo, kcal));
				}
			}

			fs.close();
		}
		else {
			cerr << "Error opening file: " << filePath << endl;
		}
	}



	vector<Ingredient*> addIngredient(Ingredient* newIngredient)
	{
		if (newIngredient == nullptr)
			throw runtime_error("NewIngredient is Null");


		ingredient.push_back(newIngredient);
        writeFileStoreIngredient(ingredient, "StoreIngredient.txt");
		return ingredient;
	}
	void showStore()
	{
		cout << "--------------------------------{Store}-------------------------------------\n";
		for (auto i : ingredient)
		{
			i->Show();
			cout << endl;

		}
		cout << "--------------------------------{Store}-------------------------------------\n";
	}

};
