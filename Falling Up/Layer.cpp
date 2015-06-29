#include "Libraries.h"
#include "Layer.h"
#include "Logging.h"
using namespace std;

void Layer::Display_All(){
	Display_All_Button_Objects();
	Display_All_Colored_Objects();
	Display_All_Textured_Objects();
	Display_All_Text_Objects();
	Display_All_Partical_Objects();
	Display_All_Physics_Objects();
	Display_All_Animated_Objects();
}
void Layer::Display_All_Colored_Objects(){
	for (unsigned i = 0; i < Colored_Objects.size(); i++){
		Colored_Objects[i]->Display_Object();
	}
}
void Layer::Display_All_Textured_Objects(){
	for (unsigned i = 0; i < Textured_Objects.size(); i++){
		Textured_Objects[i]->Display_Object();
	}
}
void Layer::Display_All_Text_Objects(){
	for (unsigned i = 0; i < Text_Objects.size(); i++){
		Text_Objects[i]->Display_Object();
	}
}
void Layer::Display_All_Button_Objects(){
	for (unsigned i = 0; i < Button_Objects.size(); i++){
		Button_Objects[i]->Display_Object();
	}
}
void Layer::Display_All_Partical_Objects(){
	for (unsigned i = 0; i < Partical_Objects.size(); i++){
		Partical_Objects[i]->Display_Particals();
	}
}
void Layer::Display_All_Physics_Objects(){
	for (unsigned i = 0; i < Physics_Objects.size(); i++){
		Physics_Objects[i]->Display_Physics_Object();
	}
}
void Layer::Display_All_Animated_Objects(){
	for (unsigned i = 0; i < Animated_Objects.size(); i++){
		Animated_Objects[i]->Display_Object();
	}
}
void Layer::Clear_All(){
	Clear_All_Button_Objects();
	Clear_All_Colored_Objects();
	Clear_All_Textured_Objects();
	Clear_All_Text_Objects();
	Clear_All_Partical_Objects();
	Clear_All_Physics_Objects();
	Clear_All_Animated_Objects();
}
void Layer::Clear_All_Colored_Objects(){
	Colored_Objects.clear();
}
void Layer::Clear_All_Textured_Objects(){
	Textured_Objects.clear();
}
void Layer::Clear_All_Text_Objects(){
	Text_Objects.clear();
}
void Layer::Clear_All_Button_Objects(){
	Button_Objects.clear();
}
void Layer::Clear_All_Partical_Objects(){
	Partical_Objects.clear();
}
void Layer::Clear_All_Physics_Objects(){
	Physics_Objects.clear();
}
void Layer::Clear_All_Animated_Objects(){
	Animated_Objects.clear();
}
void Layer::Check_All_Buttons(int& Button, float x, float y, float cx, float cy){
	for (unsigned i = 0; i < Button_Objects.size(); i++){
		if (Button_Objects[i]->Check_Button_Object(x, y, cx, cy) == true){
			Button = i;
			break;
		}
	}
}
void Layer::Run_All_Particals(){
	for (unsigned i = 0; i < Partical_Objects.size(); i++){
		Partical_Objects[i]->Run_Particals();
	}
}
void Layer::Run_All_Physics(){
	for (unsigned i = 0; i < Physics_Objects.size(); i++){
		Physics_Objects[i]->Run_Physics();
	}
}
void Layer::Run_All_Animations(){
	for (unsigned i = 0; i < Animated_Objects.size(); i++){
		Animated_Objects[i]->Run_Animation();
	}
}
void Layer::Initilize_Object(int Catagory){
	Object* Initilize = new Object();
	if (Catagory == 1){
		Colored_Objects.push_back(Initilize);
	}
	if (Catagory == 2){
		Textured_Objects.push_back(Initilize);
	}
	if (Catagory == 3){
		Text_Objects.push_back(Initilize);
	}
	if (Catagory == 4){
		Button_Objects.push_back(Initilize);
	}
	if (Catagory == 5){
		Partical_Objects.push_back(Initilize);
	}
	if (Catagory == 6){
		Physics_Objects.push_back(Initilize);
	}
	if (Catagory == 7){
		Animated_Objects.push_back(Initilize);
	}
}