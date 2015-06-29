#include "Libraries.h"
using namespace std;
class Object{
private:
	/*>>>>>-----PRIVATE DATA-----<<<<<*/

	/*-----Object Data-----*/
	glm::mat4 Model_Matrix, View_Matrix;
	float Object_Data[16];
	vector<Object*> Collision_Objects;

	/*-----Colored Object Data-----*/
	unsigned Uniform_Mvp_Color, Points_Vbo, Color_Vbo, Vao, Uniform_Color;
	float Colors[400], Points[300];

	/*-----Textured Object Data-----*/
	GLuint texture_id, texture_vao, program_id, uniform_mytexture;
	unsigned vbo_texcoords, Uniform_Mvp_Texture;
	unsigned char * data;
	unsigned int width, height;
	string Texture;

	/*-----Animated Object Data-----*/
	time_t Start, End;
	int Frames_Per_Seconed, Pause_Time, Timer, Count, Frame;
	/*-----Text Object Data-----*/
	float Text_Data[10];
	string Charictars[400];
	vector<Object*> Letters;
	string Directory;

	/*-----Button Data-----*/
	Object* Text;
	Object* Background;
	string Font;
	int Mouse_Over = 0;
	bool Mouse;

	/*-----Partical Data-----*/
	struct Partical_Object{
		float Velocity_X, Velocity_Y;
		float Acceleration_X, Acceleration_Y;
		int Life;
		Object* Partical = new Object();
	};
	vector <Partical_Object*> Particals;
	int Max_Particals, Current_Particals, Max_Particals_Per_Spawn, Spawns_Per_Seconed, Spawn_Timer;
	float Spawner_X, Spawner_Y;
	bool Fade;

	int Number_Of_Points, Partical_Life, Partical_Life_Range;
	float Partical_X, Partical_Y;
	float Red, Blue, Green, Alpha;
	string Partical_Texture;
	float Spawn_Velocity_X, Spawn_Velocity_Y, Spawn_Acceleration_X, Spawn_Acceleration_Y;
	float Velocity_Range_X, Velocity_Range_Y, Acceleration_Range_X, Acceleration_Range_Y;

	/*-----Physics Data-----*/
	struct Collision_Object{
		float Center_X, Center_Y, Max_X, Max_Y, Min_X, Min_Y;
	};
	vector<Collision_Object*> Collision;
	float Velocity_X, Velocity_Y, Acceleration_X, Acceleration_Y, Mass, Friction_Static, Friction_Kinetic, Reflection_Percent, Transfer_Percent;
	float Force_X, Force_Y;
	bool Stationary = true, Forces = false;

	/*>>>>>-----PRIVATE FUNCTIONS-----<<<<<*/
	/*-----Objects Functions-----*/
	void Genorate_Points();
	string GFAS(string file);
	void Genorate_Colored_Object();
	void Read_TGA(string file);
	void Genorate_Textured_Object();

	/*-----Text Object Functions-----*/
	void Read_Line(string line);
	void Update_Text_Object();

	/*-----Partical Object Functions-----*/
	
	/*-----Physics Object Functions-----*/

public:
	/*>>>>>-----PUBLIC DATA-----<<<<<*/

	int Object_Type;

	/*-----Physics Data-----*/
	Object* Physics;
	/*>>>>>-----PUBLIC FUNCTIONS-----<<<<<*/
	/*-----Objects Functions-----*/
	void Edit_Object(int Type, float Value);
	void Set_View_Matrix_Object(glm::vec3 view);
	void Translate_Object(float x, float y, float z);
	float Return_Float_Value(int val);
	string Return_String_Value(int val);
	void Display_Object();
	void New_Colored_Object(int points, float xsize, float ysize, float r, float g, float b, float a, int colision);
	void New_Textured_Object(string texture, int points, float xsize, float ysize, int colision);
	void New_Animated_Object(string texture, int points, float xsize, float ysize, int colision, int timer);
	int Move_Object(float x, float y, float z, int level, float Max_Move);
	void Run_Animation();
	void Set_Collision_Set(vector<Object*> Collisions, int Start, int Ignore);
	void Clear_Collision_Set();

	/*-----Text Object Functions-----*/
	void Set_Text_Data(int Type, float Value);
	void Reset_Text_Data(float X_Size, float Y_Size, float Font, float Color, float Collision);
	void New_Text_Object(string Line, string font);
	void Edit_Text_Object(string Line);
	void Display_Text_Object();
	void Set_View_Matrix_Text_Object(glm::vec3 view);
	void Translate_Text_Object(float x, float y, float z);

	/*-----Button Objects Functions-----*/
	void New_Button_Object(string text, string texture, string font, float x, float y);
	void Edit_Button_Object(string text);
	bool Check_Button_Object(float x, float y, float cx, float cy);
	void Translate_Button_Object(float x, float y, float z);

	/*-----Partical Object Functions-----*/
	void New_Partical_Spawner(int Partical_Type, float x_size, float y_size);
	void Set_Color_Partial_Spawner_Data(int total_max, int spawn_max, int spawns_per_seconed, int partical_points, float partical_x_size, float partical_y_size, float velocity_x, float velocity_range_x, float acceleration_x, float acceleration_range_x, float velocity_y, float velocity_range_y, float acceleration_y, float acceleration_range_y, int life, int life_range, float r, float g, float b, float a, bool fade);
	void Set_Texture_Partial_Spawner_Data(int total_max, int spawn_max, int spawns_per_seconed, int partical_points, float partical_x_size, float partical_y_size, float velocity_x, float velocity_range_x, float acceleration_x, float acceleration_range_x, float velocity_y, float velocity_range_y, float acceleration_y, float acceleration_range_y, int life, int life_range, string texture);
	void Run_Particals();
	void Display_Particals();
	void Translate_Partical_Spawner(float x, float y, float z);

	/*-----Physics Object Function-----*/
	void New_Color_Physics_Object(int points, float xsize, float ysize, float r, float g, float b, float a, int colision);
	void New_Texture_Physics_Object(string texture, int points, float xsize, float ysize, int colision);
	void Set_Object_Mass(float mass);
	void Set_Object_Friction(float friction_s, float friction_k);
	void Accelerate_Physics_Object(float x, float y, float z);
	void Translate_Physics_Object(float x, float y, float z);
	void Set_Velocity_Physics_Object(float x, float y, float z);
	void Add_Velocity_Physics_Object(float x, float y, float z);
	void Apply_Foce_Axis(float x, float y, float z);
	void Apply_Foce_Ange(float theta, float force);
	void Set_Velocity_Reflection(float Percent);
	void Set_Velocity_Transfer(float Percent);
	void Reset_Physics_Data(int Type);
	void Display_Physics_Object();
	void Set_Collsion_Objects(vector<Object*> Collisions, int Start, int Ignore);
	void Run_Physics();

};