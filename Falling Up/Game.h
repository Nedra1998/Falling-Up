#include "Libraries.h"
using namespace std;
class Game{
private:
	float Gravity_Y, Gravity_X, Jump, Jump_Hold, Jump_Original;
	int Level;
	int Load_Level();
	int Run_Level();
public:
	Hephaestus H_Game;
	GLFWwindow* W_Game;
	int Begin_Game_Program(Hephaestus H, GLFWwindow* W, int Level);
};