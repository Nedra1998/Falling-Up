#include "Libraries.h"
using namespace std;
class Game{
private:
	float Gravity_Y, Gravity_X, Jump, Jump_Original, Spawn_X, Spawn_Y;
	int Level, Level_X, Level_Y;
	int Level_Grid[1000][1000];
	bool Key, Fall;
	int Load_Level();
	int Run_Level();
	int On_Collide(int x, int y);
	int Every_Frame();
	int Run_Level_Editor_2();
public:
	Hephaestus H_Game;
	GLFWwindow* W_Game;
	int Begin_Game_Program(Hephaestus H, GLFWwindow* W, int Level);
	int Run_Level_Editor_1(Hephaestus H, GLFWwindow* W);
};