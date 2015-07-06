#include "Libraries.h"
#include "Game.h"
using namespace std;
class Menu{
private:
	string Save_1, Save_2, Save_3, Name;
	int Level_1, Level_2, Level_3, Save_Number, Level;
	int Menu_Number, Layer, Button, Action, Delay;
	int Load_Menu();
	int On_Click();
	int Every_Frame();
	bool Close();
public:
	Hephaestus H_Menu;
	GLFWwindow* W_Menu;
	Game G_Menu;
	void Begin_Menu_Program(Hephaestus H, GLFWwindow* W);
	int Run_Menu_Program(int menu);
};