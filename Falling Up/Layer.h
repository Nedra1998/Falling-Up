#include "Libraries.h"
#include "Object.h"
using namespace std;
class Layer{
private:
public:
	vector<Object*> Colored_Objects;
	vector<Object*> Textured_Objects;
	vector<Object*> Animated_Objects;
	vector<Object*> Text_Objects;
	vector<Object*> Button_Objects;
	vector<Object*> Partical_Objects;
	vector<Object*> Physics_Objects;
	void Display_All();
	void Display_All_Colored_Objects();
	void Display_All_Textured_Objects();
	void Display_All_Text_Objects();
	void Display_All_Button_Objects();
	void Display_All_Partical_Objects();
	void Display_All_Physics_Objects();
	void Display_All_Animated_Objects();
	void Clear_All();
	void Clear_All_Colored_Objects();
	void Clear_All_Textured_Objects();
	void Clear_All_Text_Objects();
	void Clear_All_Button_Objects();
	void Clear_All_Partical_Objects();
	void Clear_All_Physics_Objects();
	void Clear_All_Animated_Objects();
	void Check_All_Buttons(int& Button, float x, float y, float cx, float cy);
	void Run_All_Particals();
	void Run_All_Physics();
	void Run_All_Animations();
	void Initilize_Object(int Catagory);
};