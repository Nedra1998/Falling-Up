#include "Libraries.h"
#include "Logging.h"
#include "Hephaestus.h"
#include "Game.h"
using namespace std;

int Game::Begin_Game_Program(Hephaestus H, GLFWwindow* W, int level){
	H_Game = H;
	W_Game = W;
	Level = level;
	Load_Level();
	H_Game.Layers[0]->Initilize_Object(5);
	H_Game.Layers[0]->Partical_Objects[0]->New_Partical_Spawner(0, 1.0, 1.0);
	H_Game.Layers[0]->Partical_Objects[0]->Set_Color_Partial_Spawner_Data(100, 3, 10, 5, 0.005, 0.005, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 300, 60, 1.0, 1.0, 1.0, 1.0, true);
	return(Run_Level());
}

int Game::Load_Level(){
	float x = -0.95, y = 0.95;
	char Object;
	int Object_Number = 0, X, Y, Size;
	string Level_File = "Levels/" + to_string(Level) + ".Level";
	ifstream Load(Level_File.c_str());
	H_Game.Create_New_Layer();
	H_Game.Create_New_Layer();
	H_Game.Create_New_Layer();
	H_Game.Layers[3]->Initilize_Object(6);
	if (Load.is_open()){
		Load >> X;
		Load >> Y;
		Size = X*Y + Y; 
		for (int a = 0; a < Size; a++){
			Load >> Object;
			if (Object == '1'){
				H_Game.Layers[2]->Initilize_Object(2);
				H_Game.Layers[2]->Textured_Objects[Object_Number]->New_Textured_Object("Textures/Game/Block B", 4, 0.05, 0.05, 0);
				H_Game.Layers[2]->Textured_Objects[Object_Number]->Translate_Object(x, y, 0.0);
				H_Game.Layers[1]->Initilize_Object(5);
				H_Game.Layers[1]->Partical_Objects[Object_Number]->New_Partical_Spawner(0, 0.04, 0.04);
				H_Game.Layers[1]->Partical_Objects[Object_Number]->Set_Color_Partial_Spawner_Data(5, 3, 10, 4, 0.005, 0.005, 0.0, 0.007, 0.0, 0.0, 0.0, 0.007, 0.0, 0.0, 15, 5, 0.21, 0.52, 0.49, 1.0, true);
				H_Game.Layers[1]->Partical_Objects[Object_Number]->Translate_Partical_Spawner(x, y, 0.0);
				Object_Number++;
			}
			if (Object == 'P'){
				H_Game.Layers[3]->Physics_Objects[0]->New_Texture_Physics_Object("Textures/Game/Player", 4, 0.05, 0.05, -1);
				H_Game.Layers[3]->Physics_Objects[0]->Translate_Physics_Object(x, y + 0.001, 0.0);
			}
			if (Object == 'E'){
				H_Game.Layers[2]->Initilize_Object(2);
				H_Game.Layers[2]->Textured_Objects[Object_Number]->New_Textured_Object("Textures/Game/Exit", 4, 0.05, 0.05, 1);
				H_Game.Layers[2]->Textured_Objects[Object_Number]->Translate_Object(x, y, 0.0);
				H_Game.Layers[1]->Initilize_Object(5);
				H_Game.Layers[1]->Partical_Objects[Object_Number]->New_Partical_Spawner(0, 0.04, 0.04);
				H_Game.Layers[1]->Partical_Objects[Object_Number]->Set_Color_Partial_Spawner_Data(50, 10, 10, 4, 0.008, 0.008, 0.0, 0.008, 0.0, 0.0, 0.0, 0.008, 0.0, 0.0, 15, 5, 1.0, 1.0, 1.0, 1.0, true);
				H_Game.Layers[1]->Partical_Objects[Object_Number]->Translate_Partical_Spawner(x, y, 0.0);
				Object_Number++;
			}
			if (Object == '/'){
				y = y - 0.1;
				x = -0.95;
			}
			else if (Object != '/'){
				x = x + 0.1;
			}
		}
		Load.close();
		H_Game.Layers[3]->Physics_Objects[0]->Set_Collsion_Objects(H_Game.Layers[2]->Textured_Objects, 0, -1);
	}
	else{
		cout << "Error\n";
	}
	return(0);
}
int Game::Run_Level(){
	int Return = -1, x, y;
	Gravity_X = 0.0;
	Gravity_Y = -1.0;
	Jump_Hold = 10;
	Jump = 2;
	Jump_Original = 2;
	H_Game.Layers[3]->Physics_Objects[0]->Set_Acceleration_Physics_Object(Gravity_X, Gravity_Y, 0.0);
	while (Return == -1){
		if (glfwGetKey(W_Game, GLFW_KEY_D) && H_Game.Layers[3]->Physics_Objects[0]->Return_Physics_Data(1) < 0.7){
			H_Game.Layers[3]->Physics_Objects[0]->Add_Velocity_Physics_Object(0.1, 0.0, 0.0);
		}
		else if (!glfwGetKey(W_Game, GLFW_KEY_D) && H_Game.Layers[3]->Physics_Objects[0]->Return_Physics_Data(1) > 0.0){
			H_Game.Layers[3]->Physics_Objects[0]->Add_Velocity_Physics_Object(-0.1, 0.0, 0.0);
		}
		if (glfwGetKey(W_Game, GLFW_KEY_A) && H_Game.Layers[3]->Physics_Objects[0]->Return_Physics_Data(1) > -0.7){
			H_Game.Layers[3]->Physics_Objects[0]->Add_Velocity_Physics_Object(-0.1, 0.0, 0.0);
		}
		else if (!glfwGetKey(W_Game, GLFW_KEY_A) && H_Game.Layers[3]->Physics_Objects[0]->Return_Physics_Data(1) < 0.0){
			H_Game.Layers[3]->Physics_Objects[0]->Add_Velocity_Physics_Object(0.1, 0.0, 0.0);
		}
		if (glfwGetKey(W_Game, GLFW_KEY_SPACE) && Jump_Hold > 0){
			Jump_Hold--;
			H_Game.Layers[3]->Physics_Objects[0]->Add_Velocity_Physics_Object(0.0, 0.08, 0.0);
		}
		if (Jump_Hold == 9){
			Jump--;
		}
		if (!glfwGetKey(W_Game, GLFW_KEY_SPACE) && Jump > 0){
			Jump_Hold = 10;
		}
		H_Game.Layers[3]->Physics_Objects[0]->Run_Physics(x, y);
		if (y == 0){
			Jump = Jump_Original;
		}
		H_Game.Run_All_Particals();
		H_Game.Run_All_Animations();
		H_Game.Display_All_Layers();
		H_Game.Frame();
		if (x == 1 || y == 1){
			return(1);
		}
	}
	return(0);
}
