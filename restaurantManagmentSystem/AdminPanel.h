#pragma once
int handleMenu(vector<string>& menuItems, int& choose, string title) {
	int num = _getch();
	if (num == 224) {
		num = _getch();
		moveInMenu(menuItems, choose, direction(num));
		system("cls");
		displayMenu(menuItems, choose, title);
	}
	return num;
}



//ForStoreButton
void chooseStore(int choose, Stock& stock, Store& store)
{

	if (choose == 1)
	{


		while (true)
		{


			string name;
			int id;
			int count;
			float price;
			double fats;
			double protein;
			double carbohydrates;
			int kcal;
			while (true)
			{
				bool isCheck = false;
				cout << "Enter Ingredient Name: ";
				getline(cin, name);
				for (auto& i : store.GetIngredient())
				{
					if (i->getName() == name)
						isCheck = true;


				}
				if (!isCheck)
					break;
				else
				{
					cout << "Invalid Ingredient Name\n";
				}
			}

			while (true)
			{
				bool isCheck = false;
				id = rand() % 1000;
				for (auto& i : store.GetIngredient())
				{
					if (i->getid() == id)
						isCheck = true;


				}
				if (!isCheck)
					break;
			}
			cout << "Enter Ingredient price: ";
			cin >> price;
			cout << "Enter Ingredient fats: ";
			cin >> fats;
			cout << "Enter Ingredient protein: ";
			cin >> protein;
			cout << "Enter Ingredient carbohydrates: ";
			cin >> carbohydrates;
			cout << "Enter Ingredient kcal: ";
			cin >> kcal;

			cin.ignore();
			try {
				Ingredient* ing = new Ingredient(id, name, price, fats, protein, carbohydrates, kcal);

				id++;
				store.addIngredient(ing);
				cout << "Press Enter";
				break;
			}
			catch (const std::runtime_error& ex)
			{
				cout << "\n";
				cout << ex.what();
			}
		}

	}
	else
	{
		cout << "MC Balance: " << stock.GetBudget() << endl;
		store.showStore();
		while (true)
		{
			try
			{
				cout << "Enter Id:";
				int id;
				int count;
				cin >> id;
				cout << "Count: ";
				cin >> count;
				if (count <= 0)
					throw runtime_error("Count big then 0 ");

				for (auto i : store.GetIngredient())
				{
					if (i->getid() == id)
						stock.addIngredient(i, count);
				}
				break;
			}
			catch (const runtime_error ex)
			{
				cout << ex.what();
			}
		}




	}

}

//ForAddIngredientToNewDish
void AddIngMenu(Stock& stock, MenuItem& menuItem)
{
	stock.showStock();
	while (true)
	{
		try
		{
			int id;
			int count;
			cout << "Enter ingedient id: ";
			cin >> id;
			cout << "Enter defoult Count: ";
			cin >> count;
			if (count < 0)
			{
				cin.ignore();
				throw runtime_error("Count must be big then zero");
			}
			for (auto& i : stock.GetIngredient())
			{
				if (i->getid() == id)
				{
					system("cls");
					stock.showStock();
					RecipetItem recItem(count, i);
					menuItem.addIngredient(recItem);
					menuItem.CalCulatePrice();
					menuItem.showDishInfo();
					return;
				}

			}

			//throw runtime_error("Dont Exist Ingredient in Stock");
		}
		catch (const runtime_error& ex)
		{
			cout << ex.what() << endl;
		}


	}
}

//ForAddingMenuItem
void addMenuItem(Stock& stock)
{
	string nameMenuItem;
	//cin.ignore();
	vector<RecipetItem>reciept;
	vector<MenuItem*>m;
	try
	{
		readFileDish(m, "DishS.txt");
	}
	catch (runtime_error ex)
	{
		cout << ex.what()<<endl;
	}
	cout << "Enter Dish Name:";
	getline(cin, nameMenuItem);
	int id;

	while (true)
	{
		bool isCheck = false;
		id = rand() % 1000;
		for (auto& i : m)
		{
			if (i->GetId() == id)
				isCheck = true;
		}
		if (!isCheck)
			break;
	}


	MenuItem menuItem(id, nameMenuItem, 1, reciept);
	int choose = 0;
	system("cls");
	vector<string>str = displayMenu(MenuItems, choose, nameMenuItem + " : ");
	while (true)
	{
		int num = handleMenu(str, choose,nameMenuItem+" : ");
		if (num == 13)
		{
			
			if (choose == 0)
			{
				while (true)
				{
					try
					{
						AddIngMenu(stock, menuItem);
						cin.ignore();
						break;
					}
					catch (const std::runtime_error& ex)
					{
						cout << ex.what() << endl;
					}

				}
			}
			else if (choose == 1)
			{
				while (true)
				{
					try
					{
						menuItem.showDishInfo();
						break;
					}
					catch (const std::runtime_error& ex)
					{
						cout << ex.what() << endl;
					}

				}
			}
			else if (choose == 2)
			{
				while (true)
				{
					try
					{
						if (menuItem.getRecieptItem().empty())
							cout << "RecieptItem yoxdur";
						writeFileDish(menuItem, "Dishs.txt");
						system("cls");
						displayMenu(AdminMainMenuItem, choose, "Menu");
						return;
					}
					catch (const std::runtime_error& ex)
					{
						cout << ex.what() << endl;
					}

				}
			}
			else if (choose == str.size() - 1)
			{
				system("cls");
				displayMenu(AdminMainMenuItem,0, "ADMIN");
				return;
			}
		}
	}

}

//forShowMenu
void showMenu(vector<MenuItem*>menu)
{
	
	for (auto& i : menu)
	{
		i->showDishInfo();
		cout << endl;
		cout << "------------------------------------------------------------------\n";
	}


}

//forExistMenuItemButton

void addIngredientExistItem(Stock& stock, vector<MenuItem*>menu)
{
	int id;
	cout << "Enter Exist Dish ID: ";
	cin >> id;
	for (auto& i : menu)
	{
		if (id == i->GetId())
		{
			AddIngMenu(stock, *i);
			
		}
	}
	writeFileDish(menu, "Dishs.txt");
}


void AdminPanel(Stock& stock,Store& store)
{
	system("cls");
	int choose = 0;
	vector<MenuItem*>menu;
	readFileDish(menu, "Dishs.txt");
	vector<string>str = displayMenu(AdminMainMenuItem, choose, "ADMIN: ");
	while (true)
	{
		int num = handleMenu(AdminMainMenuItem, choose, "ADMIN: ");
		if (num == 13)
		{
			if (choose == 4)
			{
				while (true) {
					try {
						chooseStore(1, stock, store);
						cin.ignore();
						system("cls");
						displayMenu(AdminMainMenuItem, choose, "ADMIN: ");
						break;
					}
					catch (const std::runtime_error& ex)
					{
						cout << ex.what() << endl;
					}
				}
			}
			else if (choose == 3)
			{

				while (true) {
					try {
						chooseStore(2, stock, store);
						cin.ignore();
						system("cls");
						displayMenu(AdminMainMenuItem, choose, "ADMIN: ");
						break;
					}
					catch (const std::runtime_error& ex)
					{
						cout << ex.what() << endl;
					}
				}
			}
			else if (choose == 1)
			{
				addIngredientExistItem(stock,menu);
			}
			else if (choose == 2)
			{
				stock.showStock();
			}
			else if (choose == 0)
			{
				while (true)
				{
					try {

						addMenuItem(stock);
						break;
					}
					catch (const std::runtime_error& ex)
					{
						cout << ex.what() << endl;
					}
				}
			}
			else if (choose ==5)
			{
				showMenu(menu);
			}
			else if (choose = str.size() - 1)
			{
				displayMenu(RegisterMenu, 0, "ADMIN OR USER");
				return;
			}
		}

	}
}


