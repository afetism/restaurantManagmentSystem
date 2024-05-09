#pragma once

 #pragma region Register
class Register
{
	string email;
	string password;


	bool isValidEmailFormat(string& email) const
	{
		regex emailRegex("^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$");
		return regex_match(email, emailRegex);
	}

	bool isValidPasswordFormat(string& password) const
	{
		if (password.length() < 8)
			return false;

		bool hasUpperCharacter = false;
		for (char ch : password)
		{
			if (isupper(ch))
			{
				hasUpperCharacter = true;
				break;
			}

		}

		bool hasLowCharacter = false;
		for (char ch : password)
		{
			if (islower(ch))
			{
				hasLowCharacter = true;
				break;
			}

		}

		if (!(hasUpperCharacter && hasLowCharacter))
			return false;

		bool hasValidSymbol = false;
		for (char ch : password)
		{
			if (ch == '.' || ch == '!' || ch == ',' || ch == '?')
			{
				hasValidSymbol = true;
				break;
			}
		}
		if (!hasValidSymbol)
			return false;


		return true;

	}
public:
	Register(string email, string password)
	{
		setEmail(email);
		setPassWord(password);
	}

#pragma region Setters
	void setEmail(string& email)
	{
		if (!isValidEmailFormat(email))
			throw runtime_error("Invalid Email Format");

		this->email = email;
	}

	void setPassWord(string& password)
	{

		if (!isValidPasswordFormat(password))
			throw runtime_error("Invalid Password Format (must be min 1 Up symbol, min 1 Low symbol, min 8 symbol len, and use 1 symbol(.,!?)");


		this->password = password;
	}
#pragma endregion Setters


#pragma region Getters

	string getEmail() const { return email; }
	string getPassword() const { return password; }

#pragma endregion  Getters


	bool signIn(vector<Register>& registeredUsers)
	{


		for (auto& user : registeredUsers)
		{
			if (user.getEmail() == email && user.getPassword() == password)
				return true;
		}

		return false;
	}


	bool signUp(vector<Register>& registeredUsers)
	{

		for (auto users : registeredUsers)
		{
			if (users.getEmail() == email)
				throw runtime_error("Email is already registered.");
		}

		registeredUsers.push_back(*this);
		return true;


	}

};

bool isUserInFile(const Register& user, const string& fileName)
{
	ifstream fs(fileName);
	if (fs.is_open())
	{
		string line;
		while (getline(fs, line))
		{
			size_t pos = line.find("#");
			if (pos != string::npos)
			{
				string emailInFile = line.substr(0, pos);
				if (emailInFile == user.getEmail())
				{
					fs.close();
					return true;  // User is already present in the file
				}
			}
		}
		fs.close();
	}
	return false;  // User is not found in the file
}

void writeAllUserFiles(const vector<Register>& users, const string& fileName)
{
	ofstream fs(fileName, ios::app);
	if (fs.is_open())
	{
		for (const auto& user : users)
		{

			if (isUserInFile(user, fileName))
			{
				continue;
			}

			fs << user.getEmail() << "#" << user.getPassword() << "\n";
			fs.seekp(0, ios::beg);
		}
		fs.close();
	}
	else
	{
		throw runtime_error("Failed to open the file for writing!");
	}
}



void readAllUserFiles(vector<Register>& users, const string& fileName) {
	ifstream fs(fileName, ios::in);
	if (fs.is_open()) {
		string line;

		while (getline(fs, line)) {
			int pos = line.find('#');
			if (pos != string::npos) {
				string email = line.substr(0, pos);
				string password = line.substr(pos + 1);


				users.push_back(Register(email, password));
			}
		}

		fs.close();
	}
	else {
		cerr << "Error opening file: " << fileName << endl;
	}
}
vector<string> getMenuItemsNames(Stock& stock, vector<MenuItem*>& items, vector<string>& result) {
	result.clear();

	items.erase(remove_if(items.begin(), items.end(), [&stock](MenuItem* item) {
		for (auto& count : item->getRecieptItem()) {
			if (count.getAmount() > stock.getIngredientCounts(count.getIngredient()->getid())) {
				return true;
			}
		}
		return false;
		}), items.end());

	for (const auto& item : items) {
		int id = item->GetId();
		result.push_back("Id :" + to_string(id) + "." + item->getName());
	}

	result.push_back("My Basket");
	result.push_back("Exit");
	return result;
}

void deleteMenuItemfromMenu(Basket& basket, Stock& stock)
{
	int id;
	cout << "Enter ID to remove: ";
	cin >> id;

	vector<MenuItem*>& menu = basket.getMenu();

	auto it = std::find_if(menu.begin(), menu.end(), [id](const auto& item) {
		return item->GetId() == id;
		});

	if (it != menu.end()) {

		vector<RecipetItem> ingredientsToRemove = (*it)->getRecieptItem();


		menu.erase(it);

		for (auto& ingredient : ingredientsToRemove) {

			stock.addIngredient(ingredient.getIngredient(), ingredient.getAmount(),1);

		}

		cout << "MenuItem with ID " << id << " removed successfully." << endl;
	}
	else {
		cout << "MenuItem with ID " << id << " not found in the basket." << endl;
	}
}
#pragma endregion Register



//ForBaksetButtom
void handleBasket(Basket& basket,Stock& stock, vector<MenuItem*>& items, vector<string>& result)
{
	system("cls");
	vector<string>s;
	basket.showBasket(s);
	int choose = 0;
	vector<string>deleteBas = displayMenu(s, choose, "BASKET CONTENTS: ");
	while (true)
	{
		int num = handleMenu(s, choose, "BASKET CONTENTS: ");

		if (num == 13)
		{
			if (s.size() - 2 == choose)  // BASKETIN EXIST BUTONU
			{
				system("cls");
				getMenuItemsNames(stock, items, result);
				vector<string>MENU = displayMenu(result,0, "MENU: ");
				break;
			}
			else if (s.size() - 3 == choose)  //BASKETIN TOTAL AMOUNT BUTTON
			{
				int sum = 0;
				for (auto& i : basket.getMenu())
				{
					sum += i->CalCulatePrice();
				}
				cout <<"Total Amount: " << sum;
			}
			if (s.size() - 4 == choose)  //DELETE BUTTONU
			{
				deleteMenuItemfromMenu(basket, stock);

				basket.showBasket(s);
			}
			else if (s.size() - 1 == choose)    // SUBMIT
			{
				int sum = 0;
				for (auto& i : basket.getMenu())
				{
					sum += i->CalCulatePrice();
				}
				stock.writeFileStoreIngredient(stock.GetIngredient(), "stock.txt");
				stock.SetBudget(stock.GetBudget() + sum);
				stock.writeBudgetToFile("budget.txt");
				cout << "NUSH OLSUN";
				writeExitFromFile(sum, "sifarisiTesdiqOlunanYemekler.txt");

				return;
			}
		}
		else
		{
			vector<MenuItem*>menu = basket.getMenu();
			int i = 0;
			for (auto& item : menu)
			{
				if (i == choose)
					item->showDishInfo();
				i++;
			}
		}
	}
}

//forShowMenuItemButton
void showMenuItem(int chooseItem,vector<MenuItem*>& menu)
{
	int i = 0;
	for (auto& item : menu)
	{
		if (i == chooseItem)
		{
			item->showDishInfo();
		}
		i++;
	}
}

//forUserAddIngredient
void UserAddIngredient(Stock& stock, vector<MenuItem*>& menu, int chooseItem)
{
	system("cls");
	while (true)
	{
		if (stock.GetIngredient().empty())
		{
			displayMenu(MenuMethods, 0, "MENU METHODS: ");
			return;
		}
		try
		{

			int i = 0;
			for (auto& item : menu)
			{
				if (i == chooseItem)
				{
					
						for (auto& i : item->getRecieptItem())
						{
							stock.SetCount(i.getIngredient()->getid(), i.getAmount());
						}
					
					stock.showStock();
					int id;
					int count;
					cout << "Elave etmek istediyiniz ingredientin idisin daxil edin: ";
					cin >> id;
					cout << "Elave etmek istediyiniz ingredientin sayini daxil edin: ";
					cin >> count;

					for (auto& i : stock.GetIngredient())
					{

						if (i->getid() == id)
						{
							RecipetItem rec(count, i);
							stock.SetCount(id, count);
							item->addIngredient(rec);



						
						}

					}

					
						for (auto& i : item->getRecieptItem())
						{
							stock.addIngredient(i.getIngredient(), i.getAmount(),1);
						}
					

					system("cls");
					displayMenu(MenuMethods, 0, "MENU METHODS: ");

				} // add ing

				i++;
			}
			break;
		}
		catch (const std::runtime_error& ex)
		{
			system("cls");
			cout << ex.what() << endl;
		}

	}
}

void chooseMenuMetod(int chooseItem, Stock& stock, Basket& basket, vector<MenuItem*>& menu, vector<string>& strr)
{
	system("cls");
	int choose = 0;
	vector<string>str = MenuMethods;
	vector<string>MENUS = displayMenu(str, choose,"MENU METHODS: ");
	while (true)
	{
		int num = handleMenu(MENUS, choose, "MENU METHODS: ");
		if (num == 13)
		{

			if (choose == 1)
			{
				showMenuItem(chooseItem, menu);

			}
			else if (choose == 0)
			{
				while(true)
				{
					try
					{
						UserAddIngredient(stock, menu, chooseItem);
						break;
					}
					catch (runtime_error ex)
					{
						cout << ex.what() << endl;
					}
				}

			}

			else if (choose == 2)
			{
				int i = 0;
				for (auto& item : menu)
				{
					if (i == chooseItem)
					{
						basket.addItem(item);

						
							for (auto& i : item->getRecieptItem())
							{
								stock.SetCount(i.getIngredient()->getid(), i.getAmount());
							}
						

					}
					i++;
				}


			}

			else if (choose == str.size() - 1)
			{
				system("cls");
				getMenuItemsNames(stock, menu, strr);
				vector<string>MENU = displayMenu(strr, choose, "MENU: ");
				return;
			}
		}
	}
}







void menuRestorant(Stock& stock, Basket& basket)
{
	system("cls");
	vector<MenuItem*> items;
	vector<string> result;
	readFileDish(items, "Dishs.txt");
	int choose = 0;
	vector<string>s = getMenuItemsNames(stock, items, result);
	vector<string>MENU = displayMenu(result, choose,"MENU");
	while (true)
	{
		int num = handleMenu(result, choose, "MENU");
		if (num == 13)
		{
			if (choose == result.size() - 1)
			{
				system("cls");
				displayMenu(UserRegisterMenu, choose, "ADMIN OR USER");
				return;
			}
			else if (choose == result.size() - 2)
			{
				handleBasket(basket, stock, items, result);
			
			}
			else {
				chooseMenuMetod(choose, stock, basket, items, result);
			}
		}

	}


}

void userMenu(Stock& stock, Basket& basket) {
	int chooseReg = 0;
	system("cls");
	vector<string> menuReg = displayMenu(UserRegisterMenu, chooseReg, "Register");

	while (true) {
		int num = handleMenu(menuReg, chooseReg, "Register");
		if (num == 13)
		{

			vector<Register>registers;
			readAllUserFiles(registers, "usersBase.txt");
			string email;
			string password;
			if (chooseReg == 0)
			{
				while (true)
				{
					cout << "Email daxil edin: ";
					getline(cin, email);
					char ch;
					cout << "Password daxil edin: ";
					while ((ch = _getch()) != 13)
					{
						if (ch == 8)
						{
							if (!password.empty())
							{
								password.pop_back();
								cout << "\b \b";
							}
						}
						else
						{
							_putch('*');
							password += ch;
						}
					}
					try
					{
						Register user(email, password);
						user.signIn(registers);
						system("cls");
						menuRestorant(stock, basket);
						break;
					}
					catch (const std::runtime_error& ex)
					{
						system("cls");
						cout << "Error during registration: " << ex.what() << endl;
					}
				}
			}
			else if (chooseReg == 1)
			{
				while (true)
				{
					cout << "Email daxil edin: ";
					getline(cin, email);
					char ch;
					cout << "Password daxil edin: ";
					while ((ch = _getch()) != 13)
					{
						if (ch == 8)
						{
							if (!password.empty())
							{
								password.pop_back();
								cout << "\b \b";
							}
						}
						else
						{
							_putch('*');
							password += ch;
						}
					}
					try
					{

						Register user(email, password);
						user.signUp(registers);
						writeAllUserFiles(registers, "usersBase.txt");
						cout << "\nRegistration successful!" << endl;
						cout << "ENTER BACKSPACE  ";
						if (_getch() == 8)
						{
							system("cls");
							displayMenu(UserRegisterMenu, chooseReg, "Register");
						}
						break;
					}
					catch (const std::runtime_error& ex)
					{
						system("cls");
						cout << "Error during registration: " << ex.what() << endl;
						displayMenu(UserRegisterMenu, 0, "Register");
						break;
					}
				}

			}
			else if (chooseReg == menuReg.size() - 1)
			{
				system("cls");
				displayMenu(RegisterMenu, 0, "Register");
				return;
			}
		}
	}
}
