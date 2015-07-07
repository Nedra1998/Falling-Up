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
	string Object;
	int Object_Number = 0, X, Y, Size, Object_Number_B = 0;
	string Level_File = "Levels/" + to_string(Level) + ".Level";
	ifstream Load(Level_File.c_str());
	H_Game.Create_New_Layer();
	H_Game.Create_New_Layer();
	H_Game.Create_New_Layer();
	H_Game.Layers[3]->Initilize_Object(6);
	H_Game.Layers[3]->Initilize_Object(6);
	H_Game.Layers[3]->Physics_Objects[1]->New_Texture_Physics_Object("Textures/Game/Player", 4, 0.05, 0.05, -1);
	H_Game.Layers[3]->Physics_Objects[1]->Translate_Physics_Object(100, 100, 0.0);
	Fall = false;
	if (Load.is_open()){
		Load >> X;
		Load >> Y;
		Size = X*Y + Y; 
		for (int a = 0; a < Size; a++){
			Load >> Object;
			if (Object == "P"){
				H_Game.Layers[3]->Physics_Objects[0]->New_Texture_Physics_Object("Textures/Game/Player", 4, 0.05, 0.05, -1);
				H_Game.Layers[3]->Physics_Objects[0]->Translate_Physics_Object(x, y + 0.001, 0.0);
				Spawn_X = x;
				Spawn_Y = y + 0.001;
			}
			else if (Object == "E"){
				H_Game.Layers[2]->Initilize_Object(2);
				H_Game.Layers[2]->Textured_Objects[Object_Number]->New_Textured_Object("Textures/Game/Exit", 4, 0.05, 0.05, 1);
				H_Game.Layers[2]->Textured_Objects[Object_Number]->Translate_Object(x, y, 0.0);
				H_Game.Layers[1]->Initilize_Object(5);
				H_Game.Layers[1]->Partical_Objects[Object_Number]->New_Partical_Spawner(0, 0.04, 0.04);
				H_Game.Layers[1]->Partical_Objects[Object_Number]->Set_Color_Partial_Spawner_Data(50, 10, 10, 4, 0.008, 0.008, 0.0, 0.008, 0.0, 0.0, 0.0, 0.008, 0.0, 0.0, 15, 5, 1.0, 1.0, 1.0, 1.0, true);
				H_Game.Layers[1]->Partical_Objects[Object_Number]->Translate_Partical_Spawner(x, y, 0.0);
				Object_Number++;
			}
			else if (Object == "C"){
				H_Game.Layers[3]->Initilize_Object(2);
				H_Game.Layers[3]->Textured_Objects[Object_Number_B]->New_Textured_Object("Textures/Game/C", 4, 0.05, 0.05, 2);
				H_Game.Layers[3]->Textured_Objects[Object_Number_B]->Translate_Object(x, y, 0.0);
				H_Game.Layers[2]->Initilize_Object(5);
				H_Game.Layers[2]->Partical_Objects[Object_Number_B]->New_Partical_Spawner(0, 0.04, 0.04);
				H_Game.Layers[2]->Partical_Objects[Object_Number_B]->Set_Color_Partial_Spawner_Data(50, 10, 10, 4, 0.008, 0.008, 0.0, 0.008, 0.0, 0.0, 0.0, 0.008, 0.0, 0.0, 15, 5, 1.0, 1.0, 1.0, 1.0, true);
				H_Game.Layers[2]->Partical_Objects[Object_Number_B]->Translate_Partical_Spawner(x, y, 0.0);
				Object_Number_B++;
			}
			else if (Object == "K"){
				H_Game.Layers[2]->Initilize_Object(2);
				H_Game.Layers[2]->Textured_Objects[Object_Number]->New_Textured_Object("Textures/Game/K", 4, 0.05, 0.05, 3);
				H_Game.Layers[2]->Textured_Objects[Object_Number]->Translate_Object(x, y, 0.0);
				H_Game.Layers[1]->Initilize_Object(5);
				H_Game.Layers[1]->Partical_Objects[Object_Number]->New_Partical_Spawner(0, 0.04, 0.04);
				H_Game.Layers[1]->Partical_Objects[Object_Number]->Set_Color_Partial_Spawner_Data(50, 10, 10, 4, 0.008, 0.008, 0.0, 0.008, 0.0, 0.0, 0.0, 0.008, 0.0, 0.0, 15, 5, 1.0, 1.0, 1.0, 1.0, true);
				H_Game.Layers[1]->Partical_Objects[Object_Number]->Translate_Partical_Spawner(x, y, 0.0);
				Object_Number++;
			}
			else if (Object == "G"){
				H_Game.Layers[2]->Initilize_Object(2);
				H_Game.Layers[2]->Textured_Objects[Object_Number]->New_Textured_Object("Textures/Game/G", 4, 0.05, 0.05, 4);
				H_Game.Layers[2]->Textured_Objects[Object_Number]->Translate_Object(x, y, 0.0);
				H_Game.Layers[1]->Initilize_Object(5);
				H_Game.Layers[1]->Partical_Objects[Object_Number]->New_Partical_Spawner(0, 0.04, 0.04);
				H_Game.Layers[1]->Partical_Objects[Object_Number]->Set_Color_Partial_Spawner_Data(50, 10, 10, 4, 0.008, 0.008, 0.0, 0.008, 0.0, 0.0, 0.0, 0.008, 0.0, 0.0, 15, 5, 1.0, 1.0, 1.0, 1.0, true);
				H_Game.Layers[1]->Partical_Objects[Object_Number]->Translate_Partical_Spawner(x, y, 0.0);
				Object_Number++;
			}
			else if (Object != "/" && Object != "0"){
				string Directory = "Textures/Game/Block ";
				int Collision_Type = 0, Int_Object = stoi(Object);
				if (Int_Object > 0 && Int_Object < 16){
					Collision_Type = 10;
				}
				if (Int_Object > 15 && Int_Object < 20){
					Collision_Type = 11;
				}
				Directory += Object;
				H_Game.Layers[2]->Initilize_Object(2);
				H_Game.Layers[2]->Textured_Objects[Object_Number]->New_Textured_Object(Directory, 4, 0.05, 0.05, Collision_Type);
				H_Game.Layers[2]->Textured_Objects[Object_Number]->Translate_Object(x, y, 0.0);
				H_Game.Layers[1]->Initilize_Object(5);
				H_Game.Layers[1]->Partical_Objects[Object_Number]->New_Partical_Spawner(0, 0.04, 0.04);
				H_Game.Layers[1]->Partical_Objects[Object_Number]->Set_Color_Partial_Spawner_Data(5, 3, 10, 4, 0.005, 0.005, 0.0, 0.007, 0.0, 0.0, 0.0, 0.007, 0.0, 0.0, 15, 5, 0.21, 0.52, 0.49, 1.0, true);
				H_Game.Layers[1]->Partical_Objects[Object_Number]->Translate_Partical_Spawner(x, y, 0.0);
				Object_Number++;
			}
			if (Object == "/"){
				y = y - 0.1;
				x = -0.95;
			}
			else if (Object != "/"){
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
	Gravity_Y = -1.5;
	Jump = 1;
	Jump_Original = 1;
	H_Game.Layers[3]->Physics_Objects[0]->Set_Acceleration_Physics_Object(Gravity_X, Gravity_Y, 0.0);
	while (Return == -1){
		if (glfwGetKey(W_Game, GLFW_KEY_D) && H_Game.Layers[3]->Physics_Objects[0]->Return_Physics_Data(1) < 0.7){
			H_Game.Layers[3]->Physics_Objects[0]->Add_Velocity_Physics_Object(0.1, 0.0, 0.0);
		}
		if (!glfwGetKey(W_Game, GLFW_KEY_D) && H_Game.Layers[3]->Physics_Objects[0]->Return_Physics_Data(1) > 0.05){
			H_Game.Layers[3]->Physics_Objects[0]->Add_Velocity_Physics_Object(-0.1, 0.0, 0.0);
		}
		if (glfwGetKey(W_Game, GLFW_KEY_A) && H_Game.Layers[3]->Physics_Objects[0]->Return_Physics_Data(1) > -0.7){
			H_Game.Layers[3]->Physics_Objects[0]->Add_Velocity_Physics_Object(-0.1, 0.0, 0.0);
		}
		if (!glfwGetKey(W_Game, GLFW_KEY_A) && H_Game.Layers[3]->Physics_Objects[0]->Return_Physics_Data(1) < -0.05){
			H_Game.Layers[3]->Physics_Objects[0]->Add_Velocity_Physics_Object(0.1, 0.0, 0.0);
		}
		if (glfwGetKey(W_Game, GLFW_KEY_SPACE) && Jump > 0){
			Jump--;
			H_Game.Layers[3]->Physics_Objects[0]->Add_Velocity_Physics_Object(0.0, 1.0, 0.0);
		}
		H_Game.Layers[3]->Physics_Objects[0]->Run_Physics(x, y);
		Return = On_Collide(x, y);
		if (Fall == true){
			if (glfwGetKey(W_Game, GLFW_KEY_D) && H_Game.Layers[3]->Physics_Objects[1]->Return_Physics_Data(1) < 0.7){
				H_Game.Layers[3]->Physics_Objects[1]->Add_Velocity_Physics_Object(0.1, 0.0, 0.0);
			}
			if (!glfwGetKey(W_Game, GLFW_KEY_D) && H_Game.Layers[3]->Physics_Objects[1]->Return_Physics_Data(1) > 0.05){
				H_Game.Layers[3]->Physics_Objects[1]->Add_Velocity_Physics_Object(-0.1, 0.0, 0.0);
			}
			if (glfwGetKey(W_Game, GLFW_KEY_A) && H_Game.Layers[3]->Physics_Objects[1]->Return_Physics_Data(1) > -0.7){
				H_Game.Layers[3]->Physics_Objects[1]->Add_Velocity_Physics_Object(-0.1, 0.0, 0.0);
			}
			if (!glfwGetKey(W_Game, GLFW_KEY_A) && H_Game.Layers[3]->Physics_Objects[1]->Return_Physics_Data(1) < -0.05){
				H_Game.Layers[3]->Physics_Objects[1]->Add_Velocity_Physics_Object(0.1, 0.0, 0.0);
			}
			if (glfwGetKey(W_Game, GLFW_KEY_SPACE) && Jump > 0){
				Jump--;
				H_Game.Layers[3]->Physics_Objects[1]->Add_Velocity_Physics_Object(0.0, 1.0, 0.0);
			}
			H_Game.Layers[3]->Physics_Objects[1]->Run_Physics(x, y);
			Return = On_Collide(x, y);
		}
		Every_Frame();
		H_Game.Run_All_Particals();
		H_Game.Run_All_Animations();
		H_Game.Display_All_Layers();
		H_Game.Frame();
	}
	return(0);
}
int Game::On_Collide(int x, int y){
	if (x == 1 || y == 1){
		return(1);
	}
	if (y == 10){
		Jump = Jump_Original;
	}
	if (x == 11 || y == 11){
		float cx, cy;
		cx = H_Game.Layers[3]->Physics_Objects[0]->Physics->Return_Float_Value(2);
		cy = H_Game.Layers[3]->Physics_Objects[0]->Physics->Return_Float_Value(3);
		H_Game.Layers[3]->Physics_Objects[0]->Set_Velocity_Physics_Object(0.0, 0.0, 0.0);
		H_Game.Layers[3]->Physics_Objects[0]->Translate_Physics_Object(-cx, -cy, 0.0);
		H_Game.Layers[3]->Physics_Objects[0]->Translate_Physics_Object(Spawn_X, Spawn_Y, 0.0);
	}
	return(-1);
}
int Game::Every_Frame(){
	float xp, yp, xc, yc;
	xp = H_Game.Layers[3]->Physics_Objects[0]->Physics->Return_Float_Value(2);
	yp = H_Game.Layers[3]->Physics_Objects[0]->Physics->Return_Float_Value(3);
	if (Fall == false){
		if (yp < -0.90 || yp > 0.90){
			Fall = true;
			float vx, vy;
			H_Game.Layers[3]->Physics_Objects[1]->Translate_Physics_Object(-100, -100, 0.0);
			if (yp < -0.9){
				H_Game.Layers[3]->Physics_Objects[1]->Translate_Physics_Object(xp, yp + 2.0, 0.0);
			}
			else{
				H_Game.Layers[3]->Physics_Objects[1]->Translate_Physics_Object(xp, yp - 2.0, 0.0);
			}
			H_Game.Layers[3]->Physics_Objects[1]->Set_Collsion_Objects(H_Game.Layers[2]->Textured_Objects, 0, -1);
			vx = H_Game.Layers[3]->Physics_Objects[0]->Return_Physics_Data(1);
			vy = H_Game.Layers[3]->Physics_Objects[0]->Return_Physics_Data(2);
			H_Game.Layers[3]->Physics_Objects[1]->Set_Velocity_Physics_Object(vx, vy, 0.0);
			H_Game.Layers[3]->Physics_Objects[1]->Set_Acceleration_Physics_Object(Gravity_X, Gravity_Y, 0.0);
		}
	}
	if (Fall == true){
		if (yp > 1.1 || yp < -1.1){
			Fall = false;
			float vx, vy;
			H_Game.Layers[3]->Physics_Objects[0]->Translate_Physics_Object(-xp, -yp, 0.0);
			xp = H_Game.Layers[3]->Physics_Objects[1]->Physics->Return_Float_Value(2);
			yp = H_Game.Layers[3]->Physics_Objects[1]->Physics->Return_Float_Value(3);
			H_Game.Layers[3]->Physics_Objects[1]->Translate_Physics_Object(-xp, -yp, 0.0);
			H_Game.Layers[3]->Physics_Objects[1]->Translate_Physics_Object(100, 100, 0.0);
			H_Game.Layers[3]->Physics_Objects[0]->Translate_Physics_Object(xp, yp, 0.0);
		}
	}
	for (int a = 0; a < H_Game.Layers[3]->Textured_Objects.size(); a++){
		xc = H_Game.Layers[3]->Textured_Objects[a]->Return_Float_Value(2);
		yc = H_Game.Layers[3]->Textured_Objects[a]->Return_Float_Value(3);
		if (xp < xc + 0.05 && xp > xc - 0.05 && yp < yc + 0.05 && yp > yc - 0.05){
			Spawn_X = xc;
			Spawn_Y = yc + 0.001;
			return(1);
		}
	}
	return(0);
}