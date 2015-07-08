#include "Libraries.h"
#include "Logging.h"
#include "Hephaestus.h"
#include "Menu.h"
using namespace std;
int Menu::Load_Menu(){
	H_Menu.Layers[1]->Clear_All();
	if (Menu_Number == 0){
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[0]->New_Button_Object("FALLING UP", "Textures/Buttons/Transparent", "Basic/White", 0.8, 0.4);
		H_Menu.Layers[1]->Button_Objects[0]->Translate_Button_Object(0.0, 0.7, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[1]->New_Button_Object("Play", "Textures/Buttons/Button A", "Basic/White", 0.5, 0.1);
		H_Menu.Layers[1]->Button_Objects[1]->Translate_Button_Object(0.0, 0.2, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[2]->New_Button_Object("Help", "Textures/Buttons/Button A", "Basic/White", 0.5, 0.1);
		H_Menu.Layers[1]->Button_Objects[2]->Translate_Button_Object(0.0, -0.05, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[3]->New_Button_Object("Settings", "Textures/Buttons/Button A", "Basic/White", 0.5, 0.1);
		H_Menu.Layers[1]->Button_Objects[3]->Translate_Button_Object(0.0, -0.3, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[4]->New_Button_Object("Level Editor", "Textures/Buttons/Button A", "Basic/White", 0.5, 0.1);
		H_Menu.Layers[1]->Button_Objects[4]->Translate_Button_Object(0.0, -0.55, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[5]->New_Button_Object("Quit", "Textures/Buttons/Button A", "Basic/White", 0.5, 0.1);
		H_Menu.Layers[1]->Button_Objects[5]->Translate_Button_Object(0.0, -0.8, 0.0);
		return(1);
	}
	if (Menu_Number == 1){
		int x, y;
		ifstream Load("Game Data.txt");
		if (Load.is_open()){
			Load.close();
		}
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[0]->New_Button_Object("SETTINGS", "Textures/Buttons/Transparent", "Basic/White", 0.8, 0.4);
		H_Menu.Layers[1]->Button_Objects[0]->Translate_Button_Object(0.0, 0.7, 0.0);
		H_Menu.Create_New_Layer();
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[1]->New_Button_Object("Resolution", "Textures/Buttons/Transparent", "Basic/White", 0.5, .1);
		H_Menu.Layers[1]->Button_Objects[1]->Translate_Button_Object(0.0, 0.3, 0.0);
		H_Menu.Win.Window_Res(x, y);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[2]->New_Button_Object(to_string(x) + "x" + to_string(y), "Textures/Buttons/Button A", "Basic/White", 0.5, .1);
		H_Menu.Layers[1]->Button_Objects[2]->Translate_Button_Object(0.0, 0.05, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		if (H_Menu.Win.Get_Window_Size(2) == 1){
			H_Menu.Layers[1]->Button_Objects[3]->New_Button_Object("Full Screen X ", "Textures/Buttons/Button A", "Basic/White", 0.5, .1);
		}
		else{
			H_Menu.Layers[1]->Button_Objects[3]->New_Button_Object("Full Screen   ", "Textures/Buttons/Button A", "Basic/White", 0.5, .1);
		}
		H_Menu.Layers[1]->Button_Objects[3]->Translate_Button_Object(0.0, -0.2, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[4]->New_Button_Object("BACK", "Textures/Buttons/Button A", "Basic/White", 0.5, .1);
		H_Menu.Layers[1]->Button_Objects[4]->Translate_Button_Object(0.0, -0.45, 0.0);
		return(1);
	}
	if (Menu_Number == 2){
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[0]->New_Button_Object("Main Menu", "Textures/Buttons/Button A", "Basic/White", 0.25, 0.1);
		H_Menu.Layers[1]->Button_Objects[0]->Translate_Button_Object(0.0, -0.8, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[1]->New_Button_Object("Next", "Textures/Buttons/Button A", "Basic/White", 0.3, 0.1);
		H_Menu.Layers[1]->Button_Objects[1]->Translate_Button_Object(0.65, -0.8, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[2]->New_Button_Object("Previous", "Textures/Buttons/Button A", "Basic/White", 0.3, 0.1);
		H_Menu.Layers[1]->Button_Objects[2]->Translate_Button_Object(-0.65, -0.8, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[3]->New_Button_Object("Help", "Textures/Buttons/Transparent", "Basic/White", 0.8, 0.4);
		H_Menu.Layers[1]->Button_Objects[3]->Translate_Button_Object(0.0, 0.7, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[4]->New_Button_Object("1/2", "Textures/Buttons/Transparent", "Basic/White", 0.2, 0.1);
		H_Menu.Layers[1]->Button_Objects[4]->Translate_Button_Object(0.0, 0.45, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[5]->New_Button_Object("You Are This:", "Textures/Buttons/Transparent", "Basic/White", 0.4, 0.1);
		H_Menu.Layers[1]->Button_Objects[5]->Translate_Button_Object(-0.6, 0.2, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[6]->New_Button_Object("You Are Trying To Get To This:", "Textures/Buttons/Transparent", "Basic/White", 0.8, 0.1);
		H_Menu.Layers[1]->Button_Objects[6]->Translate_Button_Object(-0.3, -0.05, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[7]->New_Button_Object("Move With The Left And Right Arrows Or A and D Keys", "Textures/Buttons/Transparent", "Basic/White", 1.25, 0.1);
		H_Menu.Layers[1]->Button_Objects[7]->Translate_Button_Object(-0.1, -0.3, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[8]->New_Button_Object("Press the SPACE Key To Jump", "Textures/Buttons/Transparent", "Basic/White", 1.0, 0.1);
		H_Menu.Layers[1]->Button_Objects[8]->Translate_Button_Object(0.0, -0.55, 0.0);
		return(1);
	}
	if (Menu_Number == 3){
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[0]->New_Button_Object("Main Menu", "Textures/Buttons/Button A", "Basic/White", 0.25, 0.1);
		H_Menu.Layers[1]->Button_Objects[0]->Translate_Button_Object(0.0, -0.8, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[1]->New_Button_Object("Next", "Textures/Buttons/Button A", "Basic/White", 0.3, 0.1);
		H_Menu.Layers[1]->Button_Objects[1]->Translate_Button_Object(0.65, -0.8, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[2]->New_Button_Object("Previous", "Textures/Buttons/Button A", "Basic/White", 0.3, 0.1);
		H_Menu.Layers[1]->Button_Objects[2]->Translate_Button_Object(-0.65, -0.8, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[3]->New_Button_Object("Help", "Textures/Buttons/Transparent", "Basic/White", 0.8, 0.4);
		H_Menu.Layers[1]->Button_Objects[3]->Translate_Button_Object(0.0, 0.7, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[4]->New_Button_Object("2/2", "Textures/Buttons/Transparent", "Basic/White", 0.2, 0.1);
		H_Menu.Layers[1]->Button_Objects[4]->Translate_Button_Object(0.0, 0.45, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[5]->New_Button_Object("R Restarts the Level", "Textures/Buttons/Transparent", "Basic/White", 1.0, 0.1);
		H_Menu.Layers[1]->Button_Objects[5]->Translate_Button_Object(0.0, 0.2, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[6]->New_Button_Object("Avoide These:", "Textures/Buttons/Transparent", "Basic/White", 0.8, 0.1);
		H_Menu.Layers[1]->Button_Objects[6]->Translate_Button_Object(-0.3, -0.05, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[7]->New_Button_Object("This:    Will Open This:", "Textures/Buttons/Transparent", "Basic/White", 1.25, 0.1);
		H_Menu.Layers[1]->Button_Objects[7]->Translate_Button_Object(-0.1, -0.3, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[8]->New_Button_Object("This Will Teleport You To The Matching One:", "Textures/Buttons/Transparent", "Basic/White", 1.0, 0.1);
		H_Menu.Layers[1]->Button_Objects[8]->Translate_Button_Object(-0.2, -0.55, 0.0);
		return(1);
	}
	if (Menu_Number == 4){
		string Temp;
		ifstream Load("Save Data.Saves");
		if (Load.is_open()){
			for (int i = 0; i < 3; i++){
				getline(Load, Temp);
				if (Temp == "<NONE>"){
					if (i == 0){
						Save_1 = "Create New Save";
					}
					if (i == 1){
						Save_2 = "Create New Save";
					}
					if (i == 2){
						Save_3 = "Create New Save";
					}
				}
				else{
					if (i == 0){
						Save_1 = Temp;
						Load >> Level_1;
					}
					if (i == 1){
						Save_2 = Temp;
						Load >> Level_2;
					}
					if (i == 2){
						Save_3 = Temp;
						Load >> Level_3;
					}
					getline(Load, Temp);
				}
			}
			Load.close();
		}
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[0]->New_Button_Object("SAVE SELECT", "Textures/Buttons/Transparent", "Basic/White", 0.8, 0.4);
		H_Menu.Layers[1]->Button_Objects[0]->Translate_Button_Object(0.0, 0.7, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[1]->New_Button_Object(Save_1, "Textures/Buttons/Button A", "Basic/White", 0.5, 0.1);
		H_Menu.Layers[1]->Button_Objects[1]->Translate_Button_Object(0.0, 0.2, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[2]->New_Button_Object(Save_2, "Textures/Buttons/Button A", "Basic/White", 0.5, 0.1);
		H_Menu.Layers[1]->Button_Objects[2]->Translate_Button_Object(0.0, -0.05, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[3]->New_Button_Object(Save_3, "Textures/Buttons/Button A", "Basic/White", 0.5, 0.1);
		H_Menu.Layers[1]->Button_Objects[3]->Translate_Button_Object(0.0, -0.3, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[4]->New_Button_Object("Back", "Textures/Buttons/Button A", "Basic/White", 0.5, 0.1);
		H_Menu.Layers[1]->Button_Objects[4]->Translate_Button_Object(0.0, -0.55, 0.0);
		return(1);
	}
	if (Menu_Number == 5){
		Name = "";
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[0]->New_Button_Object("CREATE NEW SAVE", "Textures/Buttons/Transparent", "Basic/White", 0.8, 0.4);
		H_Menu.Layers[1]->Button_Objects[0]->Translate_Button_Object(0.0, 0.7, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[1]->New_Button_Object(Name, "Textures/Buttons/Button A 1", "Basic/White", 0.9, 0.2);
		H_Menu.Layers[1]->Button_Objects[1]->Translate_Button_Object(0.0, 0.1, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[2]->New_Button_Object("Create", "Textures/Buttons/Button A", "Basic/White", 0.3, 0.1);
		H_Menu.Layers[1]->Button_Objects[2]->Translate_Button_Object(0.4, -0.3, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[3]->New_Button_Object("Back", "Textures/Buttons/Button A", "Basic/White", 0.3, 0.1);
		H_Menu.Layers[1]->Button_Objects[3]->Translate_Button_Object(-0.4, -0.3, 0.0);
		return(1);
	}
	else if (Menu_Number >= 6 && Menu_Number <= 10){
		int Object_Number = 4, Stage_Number = ((Menu_Number - 6) * 20) + 1;
		float x, y = 0.2;
		if (Save_Number == 1){
			Name = Save_1;
			Level = Level_1;
		}
		if (Save_Number == 2){
			Name = Save_2;
			Level = Level_2;
		}
		if (Save_Number == 3){
			Name = Save_3;
			Level = Level_3;
		}
		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[0]->New_Button_Object(Name, "Textures/Buttons/Transparent", "Basic/White", 0.8, 0.4);
		H_Menu.Layers[1]->Button_Objects[0]->Translate_Button_Object(0.0, 0.7, 0.0);

		H_Menu.Layers[1]->Initilize_Object(4);
		H_Menu.Layers[1]->Button_Objects[1]->New_Button_Object("Main Menu", "Textures/Buttons/Button A", "Basic/White", 0.25, 0.1);
		H_Menu.Layers[1]->Button_Objects[1]->Translate_Button_Object(0.0, -0.8, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		if (Menu_Number != 10){
			H_Menu.Layers[1]->Button_Objects[2]->New_Button_Object("Next", "Textures/Buttons/Button A", "Basic/White", 0.3, 0.1);
		}
		else if (Menu_Number == 10){
			H_Menu.Layers[1]->Button_Objects[2]->New_Button_Object("Next", "Textures/Buttons/Button B", "Basic/White", 0.3, 0.1);
		}
		H_Menu.Layers[1]->Button_Objects[2]->Translate_Button_Object(0.65, -0.8, 0.0);
		H_Menu.Layers[1]->Initilize_Object(4);
		if (Menu_Number != 6){
			H_Menu.Layers[1]->Button_Objects[3]->New_Button_Object("Previous", "Textures/Buttons/Button A", "Basic/White", 0.3, 0.1);
		}
		else if (Menu_Number == 6){
			H_Menu.Layers[1]->Button_Objects[3]->New_Button_Object("Previous", "Textures/Buttons/Button B", "Basic/White", 0.3, 0.1);
		}
		H_Menu.Layers[1]->Button_Objects[3]->Translate_Button_Object(-0.65, -0.8, 0.0);
		for (int a = 0; a < 4; a++){
			x = -0.6;
			for (int b = 0; b < 5; b++){
				H_Menu.Layers[1]->Initilize_Object(4);
				if (Stage_Number <= Level){
					H_Menu.Layers[1]->Button_Objects[Object_Number]->New_Button_Object(to_string(Stage_Number), "Textures/Buttons/Button A", "Basic/White", 0.1, 0.1);
				}
				else if (Stage_Number > Level){
					H_Menu.Layers[1]->Button_Objects[Object_Number]->New_Button_Object(to_string(Stage_Number), "Textures/Buttons/Button B", "Basic/White", 0.1, 0.1);
				}
				H_Menu.Layers[1]->Button_Objects[Object_Number]->Translate_Button_Object(x, y, 0.0);
				Object_Number++;
				Stage_Number++;
				x = x + 0.3;
			}
			y = y - 0.25;
		}
		return(1);
	}
	return(0);
}
int Menu::On_Click(){
	int Return = -1;
	if (Menu_Number == 0){
		if (Button == 1){
			Return = 4;
		}
		if (Button == 2){
			Return = 2;
		}
		if (Button == 3){
			Return = 1;
		}
		if (Button == 4){
			G_Menu.Run_Level_Editor_1(H_Menu, W_Menu);
			Return = 0;
		}
		if (Button == 5){
			Return = -2;
		}
		return(Return);
	}
	if (Menu_Number == 1){
		if (Button == 0 || Button == 1){
			Return = -1;
		}
		if (Button == 2){
			int i = H_Menu.Win.Get_Window_Size(1);
			int f = H_Menu.Win.Get_Window_Size(2);
			if (Action == 0){
				i++;
			}
			else if (Action == 1){
				i--;
			}
			if (i > 7){
				i = 1;
			}
			if (i < 1){
				i = 7;
			}
			H_Menu.Win.Set_Window(i, f);
			Return = 1;
		}
		if (Button == 3){
			int i = H_Menu.Win.Get_Window_Size(1);
			int f = H_Menu.Win.Get_Window_Size(2);
			if (f == 1){
				f = 0;
			}
			else{
				f = 1;
			}
			H_Menu.Win.Set_Window(i, f);
			Return = 1;
		}
		if (Button == 4){
			Return = 0;
		}
		return(Return);
	}
	if (Menu_Number == 2){
		if (Button == 0){
			Return = 0;
		}
		else if (Button == 1){
			Return = 3;
		}
		else if (Button == 2){
			Return = 3;
		}
		else {
			Return = -1;
		}
		return(Return);
	}
	if (Menu_Number == 3){
		if (Button == 0){
			Return = 0;
		}
		else if (Button == 1){
			Return = 2;
		}
		else if (Button == 2){
			Return = 2;
		}
		else {
			Return = -1;
		}
		return(Return);
	}
	if (Menu_Number == 4){
		if (Button == 1){
			Save_Number = 1;
			if (Save_1 == "Create New Save"){
				Return = 5;
			}
			else{
				Return = 6;
			}
		}
		if (Button == 2){
			Save_Number = 2;
			if (Save_2 == "Create New Save"){
				Return = 5;
			}
			else{
				Return = 6;
			}
		}
		if (Button == 3){
			Save_Number = 3;
			if (Save_3 == "Create New Save"){
				Return = 5;
			}
			else{
				Return = 6;
			}
		}
		if (Button == 4){
			Return = 0;
		}
		return(Return);
	}
	if (Menu_Number == 5){
		if (Button == 2){
			string Lines[6];
			string Line;
			int a = 0;
			ifstream Load("Save Data.Saves");
			if (Load.is_open()){
				while (getline(Load, Line)){
					Lines[a] = Line;
					if (Line == "<NONE>"){
						a++;
					}
					a++;
				}
				Load.close();
			}
			Lines[(Save_Number - 1) * 2] = Name;
			Lines[((Save_Number - 1) * 2) + 1] = "1";
			ofstream Save("Save Data.Saves");
			if (Save.is_open()){
				for (int b = 0; b < 6; b++){
					if (Lines[b] != ""){
						Save << Lines[b] << "\n";
					}
				}
				Save.close();
			}
			if (Save_Number == 1){
				Save_1 = Name;
				Level_1 = 1;
			}
			if (Save_Number == 2){
				Save_2 = Name;
				Level_2 = 1;
			}
			if (Save_Number == 3){
				Save_3 = Name;
				Level_3 = 1;
			}
			Return = 6;
		}
		if (Button == 3){
			Return = 4;
		}
		return(Return);
	}
	if (Menu_Number >= 6 && Menu_Number <= 10){
		if (Button == 1){
			Return = 4;
		}
		if (Button == 2 && Menu_Number != 10){
			Return = Menu_Number + 1;
		}
		if (Button == 3 && Menu_Number != 6){
			Return = Menu_Number - 1;
		}
		if (Button != 0 && Button != 1 && Button != 2 && Button != 3 && Level >= Button - 3){
			int Pass = -1;
			H_Menu.Clear_All_Layers();
			Pass = G_Menu.Begin_Game_Program(H_Menu, W_Menu, Button - 3);
			if (Pass == 1){
				string a = "", b = "", c = "";
				int al = -1, bl = -1, cl = -1;
				string Temp;
				ifstream Load("Save Data.Saves");
				if (Load.is_open()){
					for (int i = 0; i < 3; i++){
						getline(Load, Temp);
						if (i == 0){
							a = Temp;
						}
						if (i == 1){
							b = Temp;
						}
						if (i == 2){
							c = Temp;
						}
						if (Temp != "<NONE>"){
							if (i == 0){
								Load >> Level_1;
							}
							if (i == 1){
								Load >> Level_2;
							}
							if (i == 2){
								Load >> Level_3;
							}
							getline(Load, Temp);
						}
					}
					Load.close();
				}
				if (Level == Button - 3){
					if (Save_Number == 1){
						Level_1++;
					}
					if (Save_Number == 2){
						Level_2++;
					}
					if (Save_Number == 3){
						Level_3++;
					}
				}
				ofstream Save("Save Data.Saves");
				if (Save.is_open()){
					Save << a << "\n";
					if (a != "<NONE>"){
						Save << Level_1 << "\n";
					}
					Save << b << "\n";
					if (b != "<NONE>"){
						Save << Level_2 << "\n";
					}
					Save << c << "\n";
					if (c != "<NONE>"){
						Save << Level_3 << "\n";
					}
					Save.close();
				}
			}
			H_Menu.Create_New_Layer();
			H_Menu.Layers[0]->Initilize_Object(5);
			H_Menu.Layers[0]->Partical_Objects[0]->New_Partical_Spawner(0, 1.0, 1.0);
			H_Menu.Layers[0]->Partical_Objects[0]->Set_Color_Partial_Spawner_Data(100, 3, 10, 5, 0.005, 0.005, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 300, 60, 1.0, 1.0, 1.0, 1.0, true);
			Return = Menu_Number;
		}
		return(Return);
	}
}
int Menu::Every_Frame(){
	if (Menu_Number == 5){
		if (Delay > 0){
			Delay--;
			H_Menu.Set_Key(-1);
		}
		if (Delay == 0 && H_Menu.Return_Key_Int() != -1 && H_Menu.Return_Key_Int() != 259){
			Delay = 15;
			Name = Name + H_Menu.Return_Key_String();
			H_Menu.Layers[1]->Button_Objects[1]->Edit_Button_Object(Name);
		}
		if (Delay == 0 && H_Menu.Return_Key_Int() == 259){
			Delay = 15;
			if ((Name.size() - 1) != -1){
				Name.erase(Name.end() - 1);
			}
			H_Menu.Layers[1]->Button_Objects[1]->Edit_Button_Object(Name);
		}
	}
	return(0);
}
bool Menu::Close(){
	if (glfwWindowShouldClose(W_Menu)){
		return(true);
	}
	else{
		return(false);
	}
}
void Menu::Begin_Menu_Program(Hephaestus H, GLFWwindow* W){
	H_Menu = H;
	W_Menu = W;
	int Run = 0;
	H_Menu.Create_New_Layer();
	H_Menu.Layers[0]->Initilize_Object(5);
	H_Menu.Layers[0]->Partical_Objects[0]->New_Partical_Spawner(0, 1.0, 1.0);
	H_Menu.Layers[0]->Partical_Objects[0]->Set_Color_Partial_Spawner_Data(100, 3, 10, 5, 0.005, 0.005, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 300, 60, 1.0, 1.0, 1.0, 1.0, true);
	while (Run != -1){
		Layer = -1;
		Button = -1;
		Action = -1;
		Delay = 10;
		Run = Run_Menu_Program(Run);
	}
	H_Menu.Clear_All_Layers();
}
int Menu::Run_Menu_Program(int menu){
	int Return = -1;
	Menu_Number = menu;
	Load_Menu();
	while (Return == -1){
		if (Delay > 0){
			Delay--;
			H_Menu.Set_Mouse(-1, -1);
		}
		else{
			H_Menu.Check_All_Buttons(Layer, Button, Action);
		}
		if (Layer == 1){
			Return = On_Click();
		}
		Every_Frame();
		H_Menu.Run();
		H_Menu.Frame();
		if (Close()){
			Return = -2;
		}
	}
	if (Return == -2){
		Return = -1;
	}
	return(Return);
}