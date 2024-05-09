#pragma once
vector<string>RegisterMenu = {
          " ADMIN ",
          " USER  "
};

vector<string>UserRegisterMenu = {
          "  SIGN IN  ",
          "  SIGN UP  ",
          "RETURN BACK"
};
vector<string>AdminMainMenuItem =
{
    " Add MenuItem ",
    "Exist MenuItem",
    "  Show Stock  ",
    "    Store     ",
    " ADD TO STORE ",
    "  SHOW MENU   ",
    "    Exit      "

};
vector<string>mainMenu = {
         "  DISHS  ",
         "  DRINKS ",
         "MY BASKET",
         "  EXIT   "
};
vector<string>MenuMethods = {
         " ADD INGREDIENT  ",
         "   SHOW INFO     ",
         "   ADD BASKET    ",
         "     EXIT        "
};

vector<string>basketItemMethos = {
         "ADD INGREDIENT  ",
         "DELETE INGREDIENT",
         "     BACK        "
};

vector<string>MenuItems
{
    "  ADD INGREDIENT    ",
        "SHOW MENU INGREDIENT",
        "  ADD ITEM TO MENU  ",
        "        EXIT        "
};


void moveInMenu(vector<string>arr, int& choose, direction(dir))
{
    switch (direction(dir))
    {
    case UP:
        if (choose > 0)
        {
            swap(arr[choose], arr[choose - 1]);
            choose--;
        }
        else
        {
            swap(arr[choose], arr[arr.size() - 1]);
            choose = arr.size() - 1;
        }
        break;
    case DOWN:
        if (choose < arr.size() - 1)
        {
            swap(arr[choose], arr[choose + 1]);
            choose++;
        }
        else
        {
            swap(arr[choose], arr[0]);
            choose = 0;
        }
        break;
    default:
        break;
    }

}


vector<string> displayMenu(const vector<string>& items, int choose,string title)
{
    cout << "\n\n\n\n\n\n\n";
    cout << "\t\t\t\t\t     " << title<<endl;
    for (int i = 0; i < items.size(); i++)
    {
        
        if (i == choose)
        {
            setConsoleColor(Blue, WhiteBackground);
            cout <<"\t\t\t\t\t\t"<<items[i] <<endl;
            setConsoleColor(White, BlueBackground);
        }
        else
            cout << "\t\t\t\t\t\t" << items[i]<< endl;
    }
    return items;
}




vector<string> getIngredientName(vector<MenuItem*>& items,int choose)
{
    vector<string> s;
    int i = 0;
    for (auto& item : items)
    {
        if (choose == i)
        {
             vector<RecipetItem>& recipeItems = item->getRecieptItem();
             for (auto& res_Item : recipeItems)
                 s.push_back(res_Item.getIngredient()->getName());
        }
        i++;
     }
    s.push_back("EXIT");
    return s;
}
void writeFileDish(MenuItem& dish, const string& filePath)
{
    ofstream fs(filePath, ios::app);
    if (fs.is_open())
    {
        fs << dish.GetId() << "#" << dish.getName() << "#" << dish.getCount() << "#" << dish.getPrice() << "\n";
        for (auto& i : dish.getRecieptItem())
        {
            fs << i.getAmount() << "#" << i.getIngredient()->getid() << "#" << i.getIngredient()->getName() << "#"
                << i.getIngredient()->getPrice() << "#" << i.getIngredient()->getFats() << "#"
                << i.getIngredient()->getprotein() << "#" << i.getIngredient()->getCarbohydrates() << "#"
                << i.getIngredient()->getKcal() << "\n";
        }
        fs << "!\n";
        fs.close();
    }
    else
    {
        throw runtime_error("Failed to open the file for writing!");
    }
}

void writeFileDish(const vector<MenuItem*>& menu, const string& filePath)
{
    ofstream fs(filePath, ios::out);
    if (fs.is_open())
    {
        for (auto& dish : menu)
        {
            fs << dish->GetId() << "#" << dish->getName() << "#" << dish->getCount() << "#" << dish->getPrice() << "\n";
            for (auto& i : dish->getRecieptItem())
            {
                fs << i.getAmount() << "#" << i.getIngredient()->getid() << "#" << i.getIngredient()->getName() << "#"
                    << i.getIngredient()->getPrice() << "#" << i.getIngredient()->getFats() << "#"
                    << i.getIngredient()->getprotein() << "#" << i.getIngredient()->getCarbohydrates() << "#"
                    << i.getIngredient()->getKcal() << "\n";
            }
            fs << "!\n";
        }
        fs.close();
    }
    else
    {
        throw runtime_error("Failed to open the file for writing!");
    }
}
void writeExitFromFile(const float price, const string& filePath)
{
    ofstream fs(filePath, ios::app);
    if (fs.is_open())
    {
       
        fs << price <<"#"<<"Saat: "<<__TIME__ << endl;
        fs.close();
    }
    else
    {
        throw runtime_error("Failed to open the file for writing!");
    }
}







void readFileDish(vector<MenuItem*>& dishes, const string& filePath)
{
    ifstream fs(filePath, ios::in);
    if (fs.is_open())
    {
        string line;

        while (getline(fs, line))
        {
            size_t pos1 = line.find('#');
            size_t pos2 = line.find('#', pos1 + 1);
            size_t pos3 = line.find('#', pos2 + 1);

            if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos)
            {
                int  dishId = stoi(line.substr(0, pos1));
                string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
                int count = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
                float price = stof(line.substr(pos3 + 1));


                vector<RecipetItem> reciepts;

                while (getline(fs, line) && line != "!")
                {
                    size_t pos1 = line.find('#');
                    size_t pos2 = line.find('#', pos1 + 1);
                    size_t pos3 = line.find('#', pos2 + 1);
                    size_t pos4 = line.find('#', pos3 + 1);
                    size_t pos5 = line.find('#', pos4 + 1);
                    size_t pos6 = line.find('#', pos5 + 1);
                    size_t pos7 = line.find('#', pos6 + 1);

                    if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos &&
                        pos4 != string::npos && pos5 != string::npos && pos6 != string::npos && pos7 != string::npos)
                    {
                        int amount = stoi(line.substr(0, pos1));
                        int ingId = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
                        string ingName = line.substr(pos2 + 1, pos3 - pos2 - 1);
                        float ingPrice = stof(line.substr(pos3 + 1, pos4 - pos3 - 1));
                        double ingFats = stod(line.substr(pos4 + 1, pos5 - pos4 - 1));
                        double ingProtein = stod(line.substr(pos5 + 1, pos6 - pos5 - 1));
                        double ingCarbohydrates = stod(line.substr(pos6 + 1, pos7 - pos6 - 1));
                        int ingKcal = stoi(line.substr(pos7 + 1));




                        Ingredient* ing = new Ingredient(ingId, ingName, ingPrice, ingFats, ingProtein, ingCarbohydrates, ingKcal);
                        RecipetItem recItem(amount, ing);

                        reciepts.push_back(recItem);
                    }
                }

                MenuItem* dish = new MenuItem(dishId, name, count, reciepts);
                dishes.push_back(dish);
            }
        }

        fs.close();
    }
    else
    {
        throw runtime_error("Failed to open the file for reading!");
    }
}