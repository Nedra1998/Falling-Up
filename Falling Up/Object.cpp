#include "Libraries.h"
#include "Object.h"
#include "Logging.h"
using namespace std;
/*>>>>>-----DATA DECLARATIONS-----<<<<<*/
unsigned tex_id = -1, col_id = -1, gra_id = -1;
typedef struct{
	GLubyte Header[12];
}TGAHeader;
typedef struct{
	GLubyte header[6];
	GLuint bytesPerPixel;
	GLuint imageSize;
	GLuint type;
	GLuint Height;
	GLuint Width;
	GLuint Bpp;
}TGA;
/*>>>>>-----PRIVATE FUNCTIONS-----<<<<<*/
/*-----Object Functions-----*/
void Object::Genorate_Points(){
	if (Object_Data[1] > 100){
		Logging::log_error("Invalid Point Amount, Maximum of 100", "Object Genoration");
		Object_Data[1] = 100;
	}
	int b = 0;
	float Xpos, Ypos, Xrad, Yrad;
	float Theta, Pull_Back, Spacing;
	float radtheta;
	Pull_Back = 360 / (Object_Data[1] * 2);
	Spacing = 360 / Object_Data[1];
	Theta = 0 - 90 - Pull_Back;
	Xrad = Object_Data[4];
	Yrad = Object_Data[5];
	for (int a = 0; a < Object_Data[1]; a++){
		radtheta = Theta * 3.1415 / 180;
		Points[b] = Xrad * cos(radtheta) * 1.41417913;
		b++;
		Points[b] = Yrad * sin(radtheta) * 1.41417913;
		b++;
		Points[b] = 0.0;
		b++;
		Theta = Theta + Spacing;
	}
}
string Object::GFAS(string filename){
	string line;
	string filestr;
	ifstream file(filename.c_str());
	if (file.is_open()){
		Logging::log_success("Opened " + filename, "Shaders");
		while (getline(file, line)){
			filestr = filestr + line + "\n";
		}
		file.close();
	}
	else{
		Logging::log_error("Unable to open " + filename, "Shaders");
	}
	return filestr;
}
void Object::Genorate_Colored_Object(){
	GLint compile_ok;
	glGenBuffers(1, &Points_Vbo);
	glBindBuffer(GL_ARRAY_BUFFER, Points_Vbo);
	glBufferData(GL_ARRAY_BUFFER, Object_Data[1] * 3 * sizeof(float), Points, GL_STATIC_DRAW);

	glGenBuffers(1, &Color_Vbo);
	glBindBuffer(GL_ARRAY_BUFFER, Color_Vbo);
	glBufferData(GL_ARRAY_BUFFER, Object_Data[1] * 4 * sizeof(float), Colors, GL_STATIC_DRAW);
	glGenVertexArrays(1, &Vao);
	glBindVertexArray(Vao);
	glBindBuffer(GL_ARRAY_BUFFER, Points_Vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, Color_Vbo);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	if (col_id == -1) {
		string temp1 = GFAS("Colored Vertex Shader.txt");
		string temp2 = GFAS("Colored Fragment Shader.txt");
		const char* vertex_shader = temp1.c_str();
		const char* fragment_shader = temp2.c_str();
		unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &vertex_shader, NULL);
		glCompileShader(vs);
		glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
		if (0 == compile_ok)
		{
			Logging::log_error("Error Compiling the Colored Vertex Shader", "Colored Object");
		}
		unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &fragment_shader, NULL);
		glCompileShader(fs);
		glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
		if (0 == compile_ok)
		{
			Logging::log_error("Error compiling the Colored Fragment Shader", "Colored Objects");
			char buffer[2048];
			int len;
			glGetShaderInfoLog(fs, sizeof(buffer), &len, buffer);
			cout << buffer;
		}
		col_id = glCreateProgram();
		glAttachShader(col_id, fs);
		glAttachShader(col_id, vs);
		glLinkProgram(col_id);
		GLint link_ok;
		glGetProgramiv(tex_id, GL_LINK_STATUS, &link_ok);
		if (!link_ok) {
			Logging::log_error("Uncatagorized error in colored id", "Colored Objects");
		}
	}

	Uniform_Mvp_Color = glGetUniformLocation(col_id, "matrix");
}
void Object::Read_TGA(string file){
	file = file + ".tga";
	GLubyte* imageData;
	TGAHeader tgaheader;
	TGA tga;
	FILE* fTGA;
	fTGA = fopen(file.c_str(), "rb");
	if (!fTGA){
		Logging::log_error("Unable to open TGA file: " + file, "TGA Reader");
	}
	if (fread(&tgaheader, sizeof(TGAHeader), 1, fTGA) == 0){
		Logging::log_error("Incorect header for TGA file", "TGA Reader");
	}
	if (fread(tga.header, sizeof(tga.header), 1, fTGA) == 0){
		Logging::log_error("Unable to read the next six bytes", "TGA Reader");
	}
	tga.Width = tga.header[1] * 256 + tga.header[0];
	tga.Height = tga.header[3] * 256 + tga.header[2];
	tga.Bpp = tga.header[4];
	if (tga.Width <= 0 || tga.Height <= 0 || tga.Bpp != 24 && tga.Bpp != 32){
		Logging::log_error("Un exceptable data values", "TGA Reader");
		cout << tga.Bpp << endl;
	}
	if (tga.Bpp == 24){
		tga.type = GL_RGB;
	}
	else{
		tga.type = GL_RGBA;
	}
	tga.bytesPerPixel = tga.Bpp / 8;
	tga.imageSize = tga.bytesPerPixel * tga.Width * tga.Height;
	imageData = (GLubyte *)malloc(tga.imageSize);
	if (imageData == NULL){
		Logging::log_error("Unable to allocate memory for Image Data", "TGA Reader");
	}
	if (fread(imageData, 1, tga.imageSize, fTGA) != tga.imageSize){
		Logging::log_error("Unable to read Image Data from file", "TGA Reader");
	}
	for (GLuint cswap = 0; cswap < (int)tga.imageSize; cswap += tga.bytesPerPixel){
		imageData[cswap] ^= imageData[cswap + 2] ^=
			imageData[cswap] ^= imageData[cswap + 2];
	}
	fclose(fTGA);
	data = imageData;
	width = tga.Width;
	height = tga.Height;
}
void Object::Genorate_Textured_Object(){
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f
	};
	glGenVertexArrays(1, &texture_vao);
	glBindVertexArray(texture_vao);

	unsigned vbo;

	glGenBuffers(1, &vbo);

	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, Object_Data[1] * 3 * sizeof(float), Points, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,     // width
		height,    // height
		0,                     // border, always 0 in OpenGL ES
		GL_RGBA,                // format
		GL_UNSIGNED_BYTE,      // type
		data
		);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	GLfloat cube_texcoords[] = {
		// front
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
	};
	glGenBuffers(1, &vbo_texcoords);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_texcoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_texcoords), cube_texcoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_texcoords);
	glVertexAttribPointer(
		1, // attribute
		2,                  // number of elements per vertex, here (x,y)
		GL_FLOAT,           // the type of each element
		GL_FALSE,           // take our values as-is
		0,                  // no extra data between each position
		0                   // offset of first element
		);
	if (tex_id == -1) {
		GLint compile_ok;
		string temp1 = GFAS("Textured Vertex Shader.txt");
		string temp2 = GFAS("Textured Fragment Shader.txt");
		const char* vertex_shader = temp1.c_str();
		const char* fragment_shader = temp2.c_str();
		unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &vertex_shader, NULL);
		glCompileShader(vs);
		glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
		if (0 == compile_ok)
		{
			Logging::log_error("Error Compiling the Tedtured Vertex Shader", "Textured Object");
		}
		unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &fragment_shader, NULL);
		glCompileShader(fs);
		glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
		if (0 == compile_ok)
		{
			Logging::log_error("Error compiling the Textured Fragment Shader", "Textured Objects");
			char buffer[2048];
			int len;
			glGetShaderInfoLog(fs, sizeof(buffer), &len, buffer);
			cout << buffer;
		}
		tex_id = glCreateProgram();
		glAttachShader(tex_id, fs);
		glAttachShader(tex_id, vs);
		glLinkProgram(tex_id);
		GLint link_ok;
		glGetProgramiv(tex_id, GL_LINK_STATUS, &link_ok);
		if (!link_ok) {
			Logging::log_error("Uncatagorized error in textured id", "Textured Objects");
		}
	}
	Uniform_Mvp_Texture = glGetUniformLocation(tex_id, "MVP");
}

/*-----Text Object Functions-----*/
void Object::Read_Line(string line){
	char b;
	int size = line.size();
	for (int a = 0; a < size; a++){
		b = line[a];
		if (b == 'a' || b == 'A'){
			Charictars[a] = "A";
		}
		else if (b == 'b' || b == 'B'){
			Charictars[a] = "B";
		}
		else if (b == 'c' || b == 'C'){
			Charictars[a] = "C";
		}
		else if (b == 'd' || b == 'D'){
			Charictars[a] = "D";
		}
		else if (b == 'e' || b == 'E'){
			Charictars[a] = "E";
		}
		else if (b == 'f' || b == 'F'){
			Charictars[a] = "F";
		}
		else if (b == 'g' || b == 'G'){
			Charictars[a] = "G";
		}
		else if (b == 'h' || b == 'H'){
			Charictars[a] = "H";
		}
		else if (b == 'i' || b == 'I'){
			Charictars[a] = "I";
		}
		else if (b == 'j' || b == 'J'){
			Charictars[a] = "J";
		}
		else if (b == 'k' || b == 'K'){
			Charictars[a] = "K";
		}
		else if (b == 'l' || b == 'L'){
			Charictars[a] = "L";
		}
		else if (b == 'm' || b == 'M'){
			Charictars[a] = "M";
		}
		else if (b == 'n' || b == 'N'){
			Charictars[a] = "N";
		}
		else if (b == 'o' || b == 'O'){
			Charictars[a] = "O";
		}
		else if (b == 'p' || b == 'P'){
			Charictars[a] = "P";
		}
		else if (b == 'q' || b == 'Q'){
			Charictars[a] = "Q";
		}
		else if (b == 'r' || b == 'R'){
			Charictars[a] = "R";
		}
		else if (b == 's' || b == 'S'){
			Charictars[a] = "S";
		}
		else if (b == 't' || b == 'T'){
			Charictars[a] = "T";
		}
		else if (b == 'u' || b == 'U'){
			Charictars[a] = "U";
		}
		else if (b == 'v' || b == 'V'){
			Charictars[a] = "V";
		}
		else if (b == 'w' || b == 'W'){
			Charictars[a] = "W";
		}
		else if (b == 'x' || b == 'X'){
			Charictars[a] = "X";
		}
		else if (b == 'y' || b == 'Y'){
			Charictars[a] = "Y";
		}
		else if (b == 'z' || b == 'Z'){
			Charictars[a] = "Z";
		}
		else if (b == ' '){
			Charictars[a] = "Space";
		}
		else if (b == '0'){
			Charictars[a] = "0";
		}
		else if (b == '1'){
			Charictars[a] = "1";
		}
		else if (b == '2'){
			Charictars[a] = "2";
		}
		else if (b == '3'){
			Charictars[a] = "3";
		}
		else if (b == '4'){
			Charictars[a] = "4";
		}
		else if (b == '5'){
			Charictars[a] = "5";
		}
		else if (b == '6'){
			Charictars[a] = "6";
		}
		else if (b == '7'){
			Charictars[a] = "7";
		}
		else if (b == '8'){
			Charictars[a] = "8";
		}
		else if (b == '9'){
			Charictars[a] = "9";
		}
		else if (b == ':'){
			Charictars[a] = "Colon";
		}
		else if (b == '/'){
			Charictars[a] = "Slash";
		}
		else if (b == '|'){
			Charictars[a] = "<Return>";
		}
		else{
			Logging::log_error("Unknown charictar with ACII value of: " + to_string(b), "Text Object");
			Charictars[a] = "<Error>";
		}
		if (int(b) >= 91 && b != '|'){
			Charictars[a] = "l" + Charictars[a];
		}
	}
}
void Object::Update_Text_Object(){
	string File;
	float Temp_X = Text_Data[7], Temp_Y = Text_Data[8];
	for (int a = 0; a < Text_Data[6]; a++){
		if (Charictars[a] != "<Return>" && Charictars[a] != "<Error>"){
			File = Directory + Charictars[a];
			Object *Letter = new Object();
			string Temp = Charictars[a];
			if (Temp[0] == 'l'){
				if (Temp[1] == 'B' || Temp[1] == 'D' || Temp[1] == 'F' || Temp[1] == 'G' || Temp[1] == 'H' || Temp[1] == 'I' || Temp[1] == 'J' || Temp[1] == 'K' || Temp[1] == 'L' || Temp[1] == 'P' || Temp[1] == 'Q' || Temp[1] == 'T'){
					Letter->New_Textured_Object(File.c_str(), 4, Text_Data[0], Text_Data[1], Text_Data[4]);
				}
				else{
					Letter->New_Textured_Object(File.c_str(), 4, Text_Data[0], (Text_Data[1] - Text_Data[1] / 4), Text_Data[4]);
				}
			}
			else{
				Letter->New_Textured_Object(File.c_str(), 4, Text_Data[0], Text_Data[1], Text_Data[4]);
			}
			Letter->Translate_Object(Temp_X, Temp_Y, 0.0);
			if (Temp[0] == 'l'){
				Letter->Translate_Object(0.0, -Text_Data[1] / 3, 0.0);
				if (Temp[1] == 'B' || Temp[1] == 'D' || Temp[1] == 'F' || Temp[1] == 'G' || Temp[1] == 'H' || Temp[1] == 'I' || Temp[1] == 'J' || Temp[1] == 'K' || Temp[1] == 'L' || Temp[1] == 'P' || Temp[1] == 'Q' || Temp[1] == 'T'){
					Letter->Translate_Object(0.0, Text_Data[1] / 3, 0.0);
				}
				if (Temp[1] == 'G' || Temp[1] == 'J' || Temp[1] == 'P' || Temp[1] == 'Q'){
					Letter->Translate_Object(0.0, -Text_Data[1] / 3, 0.0);
				}
			}
			Temp_X = Temp_X + (2 * Text_Data[0]) + (Text_Data[0] / 3);
			Letters.push_back(Letter);
		}
		else if (Charictars[a] == "<Error>"){
			Object *Letter = new Object();
			Letter->New_Textured_Object("Text/ERROR", 4, Text_Data[0], Text_Data[1], 0);
			Letter->Translate_Object(Temp_X, Temp_Y, 0.0);
			Temp_X = Temp_X + (2 * Text_Data[0]) + (Text_Data[0] / 3);
			Letters.push_back(Letter);
		}
		else if (Charictars[a] == "<Return>"){
			Temp_X = Text_Data[7];
			Temp_Y = Temp_Y - Text_Data[1] - (Text_Data[1] / 6);
		}
	}
}

/*-----Physics Object Functions-----*/

/*>>>>>>>>>>>>>>>>>>>>====================--------------------====================<<<<<<<<<<<<<<<<<<<<*/

/*>>>>>-----PUBLIC FUNCTIONS-----<<<<<*/
/*-----Object Functions-----*/
void Object::Edit_Object(int Type, float Value){
	Object_Data[Type] = Value;
	if (Object_Data[0] == 1){
		New_Colored_Object(Object_Data[1], Object_Data[4], Object_Data[5], Object_Data[10], Object_Data[11], Object_Data[12], Object_Data[13], Object_Data[14]);
	}
	else if (Object_Data[0] == 2){
		New_Textured_Object(Texture, Object_Data[1], Object_Data[4], Object_Data[5], Object_Data[10]);
	}
}
void Object::Set_View_Matrix_Object(glm::vec3 view){
	glm::vec3 up = glm::vec3(0, 1, 0);
	View_Matrix = glm::lookAt(view, view + glm::vec3(0, 0, -1), up);
}
void Object::Translate_Object(float x, float y, float z){
	Model_Matrix = glm::translate(Model_Matrix, x, y, z);
	Object_Data[2] = Object_Data[2] + x;
	Object_Data[3] = Object_Data[3] + y;
	Object_Data[6] = Object_Data[6] + x;
	Object_Data[7] = Object_Data[7] + x;
	Object_Data[8] = Object_Data[8] + y;
	Object_Data[9] = Object_Data[9] + y;
}
float Object::Return_Float_Value(int val){
	if (val == 1){
		return(Object_Data[1]);
	}
	if (val == 2){
		return(Object_Data[2]);
	}
	if (val == 3){
		return(Object_Data[3]);
	}
	if (val == 4){
		return(Object_Data[4]);
	}
	if (val == 5){
		return(Object_Data[5]);
	}
	if (val == 6){
		return(Object_Data[6]);
	}
	if (val == 7){
		return(Object_Data[7]);
	}
	if (val == 8){
		return(Object_Data[8]);
	}
	if (val == 9){
		return(Object_Data[9]);
	}
	if (val == 10){
		return(Object_Data[10]);
	}
	if (val == 11){
		return(Object_Data[11]);
	}
	if (val == 12){
		return(Object_Data[12]);
	}
	if (val == 13){
		return(Object_Data[13]);
	}
	if (val == 14){
		return(Object_Data[14]);
	}
	if (val == 15){
		return(Object_Data[15]);
	}
	if (val == 17){
		return(Text_Data[7]);
	}
	if (val == 18){
		return(Text_Data[8]);
	}
}
string Object::Return_String_Value(int val){
	return(" ");
}
void Object::Display_Object(){
	if (Object_Type == 1){
		glm::mat4 mvp = View_Matrix * Model_Matrix;
		glBindVertexArray(Vao);
		glUseProgram(col_id);
		glUniformMatrix4fv(Uniform_Mvp_Color, 1, GL_FALSE, &mvp[0][0]);
		glDrawArrays(GL_TRIANGLE_FAN, 0, Object_Data[1]);
	}
	else if (Object_Type == 2){
		glm::mat4 mvp = View_Matrix * Model_Matrix;
		glUseProgram(tex_id);
		glUniformMatrix4fv(Uniform_Mvp_Texture, 1, GL_FALSE, &mvp[0][0]);
		glBindVertexArray(texture_vao);
		glBindTexture(GL_TEXTURE_2D, texture_id);
		uniform_mytexture = glGetUniformLocation(program_id, "mytexture");
		glUniform1i(uniform_mytexture, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}
	else if (Object_Type == 4){
		for (int a = 0; a < Text_Data[6]; a++){
			Letters[a]->Display_Object();
		}
	}
	else if (Object_Type == 5){
		Background->Display_Object();
		Text->Display_Object();
	}
}
void Object::New_Colored_Object(int points, float xsize, float ysize, float r, float g, float b, float a, int colision){
	Object_Data[0] = 1;
	Object_Type = 1;
	Object_Data[1] = points;
	Object_Data[2] = 0.0;
	Object_Data[3] = 0.0;
	Object_Data[4] = xsize;
	Object_Data[5] = ysize;
	Object_Data[6] = xsize;
	Object_Data[7] = -xsize;
	Object_Data[8] = ysize;
	Object_Data[9] = -ysize;
	Object_Data[10] = r;
	Object_Data[11] = g;
	Object_Data[12] = b;
	Object_Data[13] = a;
	Object_Data[14] = colision;
	int d = 0;
	for (int c = 0; c < Object_Data[1]; c++){
		Colors[d] = Object_Data[10];
		d++;
		Colors[d] = Object_Data[11];
		d++;
		Colors[d] = Object_Data[12];
		d++;
		Colors[d] = Object_Data[13];
		d++;
	}
	Genorate_Points();
	Genorate_Colored_Object();
}
void Object::New_Textured_Object(string texture, int points, float xsize, float ysize, int colision){
	Texture = texture;
	Object_Type = 2;
	Object_Data[1] = points;
	Object_Data[2] = 0.0;
	Object_Data[3] = 0.0;
	Object_Data[4] = xsize;
	Object_Data[5] = ysize;
	Object_Data[6] = xsize;
	Object_Data[7] = -xsize;
	Object_Data[8] = ysize;
	Object_Data[9] = -ysize;
	Object_Data[14] = colision;
	Read_TGA(Texture);
	Genorate_Points();
	Genorate_Textured_Object();
}
void Object::New_Animated_Object(string texture, int points, float xsize, float ysize, int colision, int timer){
	Directory = texture;
	Object_Type = 2;
	Object_Data[1] = points;
	Object_Data[2] = 0.0;
	Object_Data[3] = 0.0;
	Object_Data[4] = xsize;
	Object_Data[5] = ysize;
	Object_Data[6] = xsize;
	Object_Data[7] = -xsize;
	Object_Data[8] = ysize;
	Object_Data[9] = -ysize;
	Object_Data[14] = colision;
	Timer = timer;
	Count = 0;
	Frame = 1;
	time(&Start);
	Read_TGA(Directory + " 1");
	Genorate_Points();
	Genorate_Textured_Object();
}
int Object::Move_Object(float x, float y, float z, int level, float Max_Move){
	int R = 1, a = 0;
	float maxxa, maxya, minxa, minya, maxxb, maxyb, minxb, minyb;
	int Return = -1;
	if (level == 0){
		while (x > Max_Move || y > Max_Move || z > Max_Move || x < (Max_Move * -1) || y < (Max_Move * -1) || z < (Max_Move * -1)){
			x = x / 2;
			y = y / 2;
			z = z / 2;
			R++;
		}
	}
	while (R > 0){
		R--;
		maxxa = Object_Data[6] + x;
		minxa = Object_Data[7] + x;
		maxya = Object_Data[8] + y;
		minya = Object_Data[9] + y;
		for (unsigned a = 0; a < Collision_Objects.size(); a++){
			maxxb = Collision_Objects[a]->Return_Float_Value(6);
			minxb = Collision_Objects[a]->Return_Float_Value(7);
			maxyb = Collision_Objects[a]->Return_Float_Value(8);
			minyb = Collision_Objects[a]->Return_Float_Value(9);
			if (minxa > maxxb || maxxa < minxb || minya > maxyb || maxya < minyb){
			}
			else{
				if (level < 5){
					Move_Object(x / 1.5, y / 1.5, z / 1.5, (level + 1), Max_Move);
				}
				Return = -2;
				if (Collision_Objects[a]->Object_Type == 10 || Collision_Objects[a]->Object_Type == 11){
					Return = a;
				}
				Return = Collision_Objects[a]->Return_Float_Value(14) + Collision_Objects.size();
			}
		}
		if (Return == -1){
			Translate_Object(x, y, z);
		}
	}
	return(Return);
}
void Object::Run_Animation(){
	time(&End);
	if (Start != End){
		Pause_Time = Frames_Per_Seconed / Timer;
		Start = End;
		Frames_Per_Seconed = 0;
		Count = 0;
	}
	else{
		Count++;
		if (Count >= Pause_Time){
			string Tester;
			Texture = Directory + " " + to_string(Frame);
			Tester = Texture + ".tga";
			ifstream Check(Tester.c_str());
			if (!Check.is_open()){
				Frame = 0;
				Texture = Directory + " " + to_string(Frame);
			}
			else{
				
			}
			Frame++;
			Read_TGA(Texture);
			Genorate_Textured_Object();
			Count = 0;
		}
		Frames_Per_Seconed++;
	}
}
void Object::Set_Collision_Set(vector<Object*> Collisions, int Start, int Ignore){
	for (unsigned a = Start; a < Collisions.size(); a++){
		if (a != Ignore){
			Collision_Objects.push_back(Collisions[a]);
		}
	}
}
void Object::Clear_Collision_Set(){
	Collision_Objects.clear();
}

/*-----Text Object Functions-----*/
void Object::Set_Text_Data(int Type, float Value){
	Text_Data[Type] = Value;
	Letters.clear();
	Update_Text_Object();
}
void Object::Reset_Text_Data(float X_Size, float Y_Size, float Font, float Color, float Collision){
	Text_Data[0] = X_Size;
	Text_Data[1] = Y_Size;
	Text_Data[2] = Font;
	Text_Data[3] = Color;
	Text_Data[4] = Collision;
	Letters.clear();
	Update_Text_Object();
}
void Object::New_Text_Object(string Line, string font){
	Object_Type = 4;
	string File, Temp;
	float Temp_X = 0, Temp_Y = 0;
	if (Text_Data[0] == 0){
		Text_Data[0] = 0.03;
		Text_Data[1] = 0.06;
		Text_Data[2] = 0;
		Text_Data[3] = 0;
		Text_Data[4] = 0;
		Text_Data[5] = 0;
		Text_Data[6] = 0;
		Text_Data[7] = 0;
		Text_Data[8] = 0;
		Text_Data[9] = 0;
	}
	Temp_X = Text_Data[8];
	Temp_Y = Text_Data[9];
	Text_Data[6] = Line.size();
	Directory = "Text/";
	Directory = Directory + font + "/";
	Read_Line(Line);
	for (int a = 0; a < Text_Data[6]; a++){
		if (Line[a] == '|'){
			Text_Data[7] = Text_Data[7] + 1;
		}
	}
	for (int a = 0; a < Text_Data[6]; a++){
		if (Charictars[a] != "<Return>" && Charictars[a] != "<Error>"){
			File = Directory + Charictars[a];
			Object *Letter = new Object();
			Temp = Charictars[a];
			if (Temp[0] == 'l'){
				Letter->New_Textured_Object(File.c_str(), 4, Text_Data[0], Text_Data[1] / 2, Text_Data[4]);
			}
			else{
				Letter->New_Textured_Object(File.c_str(), 4, Text_Data[0], Text_Data[1], Text_Data[4]);
			}
			Letter->Translate_Object(Temp_X, Temp_Y, 0.0);
			Temp_X = Temp_X + (2 * Text_Data[0]) + (Text_Data[0] / 3);
			Letters.push_back(Letter);
		}
		else if (Charictars[a] == "<Error>"){
			Object *Letter = new Object();
			Letter->New_Textured_Object("Text/ERROR", 4, Text_Data[0], Text_Data[1], 0);
			Letter->Translate_Object(Temp_X, Temp_Y, 0.0);
			Temp_X = Temp_X + (2 * Text_Data[0]) + (Text_Data[0] / 3);
			Letters.push_back(Letter);
		}
		else if (Charictars[a] == "<Return>"){
			Text_Data[6] = Text_Data[6] - 1;
			Temp_X = Text_Data[8];
			Temp_Y = Temp_Y - (2 * Text_Data[1]) - (Text_Data[1] / 6);
		}
	}
}
void Object::Edit_Text_Object(string Line){
	float x = Text_Data[7], y = Text_Data[8];
	string File, Directory;
	string Check[400];
	Directory = "Text/";
	if (Text_Data[2] == 0){
		Directory = Directory + "Basic/";
	}
	for (int a = 0; a < 400; a++){
		Check[a] = Charictars[a];
	}
	Read_Line(Line);
	for (int a = 0; a < Line.size(); a++){
		if (Charictars[a] != Check[a]){
			if (Charictars[a] != "<Return>" && Charictars[a] != "<Error>"){
				File = Directory + Charictars[a];
				if (Text_Data[6] > a){
					Letters[a]->New_Textured_Object(File.c_str(), 4, Text_Data[0], Text_Data[1], Text_Data[4]);
					Letters[a]->Translate_Object(x, y, 0.0);
				}
				else{
					Object* Letter = new Object();
					Letter->New_Textured_Object(File.c_str(), 4, Text_Data[0], Text_Data[1], Text_Data[4]);
					x = Text_Data[7];
					for (int b = 0; b < a; b++){
						x = x + Text_Data[0] + (Text_Data[0] / 2);
					}
					Letter->Translate_Object(x, y, 0);
					Letters.push_back(Letter);
				}
			}
		}
		else if (Charictars[a] == "<Error>"){
			if (Text_Data[6] > a){
				Letters[a]->New_Textured_Object("Text/ERROR", 4, Text_Data[0], Text_Data[1], Text_Data[4]);
				Letters[a]->Translate_Object(x, y, 0.0);
			}
			else{
				Object* Letter = new Object();
				Letter->New_Textured_Object("Text/ERROR", 4, Text_Data[0], Text_Data[1], Text_Data[4]);
				Letters.push_back(Letter);
				x = Text_Data[7];
				for (int b = 0; b < a; b++){
					x = x + Text_Data[0] + (Text_Data[0] / 2);
				}
				Letters[a]->Translate_Object(x, y, 0.0);
			}
		}
		else if (Charictars[a] == "<Return>"){
			x = Text_Data[7];
			y = y - Text_Data[1] - (Text_Data[1] / 7);
		}
	}
	Text_Data[6] = Line.size();
}
void Object::Set_View_Matrix_Text_Object(glm::vec3 View){
	for (unsigned a = 0; a < Text_Data[6]; a++){
		Letters[a]->Set_View_Matrix_Object(View);
	}
}
void Object::Translate_Text_Object(float x, float y, float z){
	for (unsigned a = 0; a < Text_Data[6]; a++){
		Letters[a]->Model_Matrix = glm::translate(Letters[a]->Model_Matrix, x, y, z);
	}
	Text_Data[7] = Text_Data[7] + x;
	Text_Data[8] = Text_Data[8] + y;
}

/*-----Button Object Functions-----*/
void Object::New_Button_Object(string text, string texture, string font, float x, float y){
	int Lines = 1;
	float Length, letter_sizex, letter_sizey, size, yshift, xshift;
	Font = font;
	Object_Type = 5;
	Object_Data[2] = 0.0;
	Object_Data[3] = 0.0;
	Object_Data[4] = x;
	Object_Data[5] = y;
	Object_Data[6] = x;
	Object_Data[7] = -x;
	Object_Data[8] = y;
	Object_Data[9] = -y;
	Texture = texture;
	Text = new Object();
	Background = new Object();
	for (int a = 0; a < text.size(); a++){
		if (text[a] == '|'){
			Lines++;
		}
	}
	Length = text.size();
	letter_sizex = (x * 2) / Length;
	letter_sizex = letter_sizex - (letter_sizex / 3);
	size = letter_sizex * Length;
	letter_sizey = (6 * (letter_sizex / 3));
	size = letter_sizey * Lines;
	if (letter_sizey * Lines > y){
		letter_sizey = (y) / Lines;
		letter_sizey = letter_sizey - (letter_sizey / 6);
		letter_sizex = (3 * (letter_sizey / 6));
	}
	size = letter_sizex * Length;
	size = letter_sizey * Lines;
	Text->New_Text_Object(text, font);
	Text->Reset_Text_Data(letter_sizex / 2, letter_sizey / 2, 0, 0, 0);
	xshift = -((letter_sizex * Length) / 2);
	yshift = ((Lines / 2) * letter_sizey);
	Text->Translate_Text_Object(xshift, yshift, 0);
	ifstream Test(texture + " 1.tga");
	if (Test.is_open()){
		Mouse = true;
		Test.close();
	}
	if (Mouse == true){
		Background->New_Textured_Object(texture + " 1", 4, x, y, 0);
	}
	else if (Mouse == false){
		Background->New_Textured_Object(texture, 4, x, y, 0);
	}
}
void Object::Edit_Button_Object(string text){
	Object* Tempor = new Object();
	int Lines = 1;
	float Length, letter_sizex, letter_sizey, size, yshift, xshift;
	for (int a = 0; a < text.size(); a++){
		if (text[a] == '|'){
			Lines++;
		}
	}
	Length = text.size();
	letter_sizex = (Object_Data[4] * 2) / Length;
	letter_sizex = letter_sizex - (letter_sizex / 3);
	size = letter_sizex * Length;
	letter_sizey = (6 * (letter_sizex / 3));
	size = letter_sizey * Lines;
	if (letter_sizey * Lines > Object_Data[5]){
		letter_sizey = (Object_Data[5]) / Lines;
		letter_sizey = letter_sizey - (letter_sizey / 6);
		letter_sizex = (3 * (letter_sizey / 6));
	}
	Tempor->New_Text_Object(text, Font);
	Tempor->Reset_Text_Data(letter_sizex / 2, letter_sizey / 2, 0, 0, 0);
	xshift = -((letter_sizex * Length) / 2);
	yshift = ((Lines / 2) * letter_sizey);
	Tempor->Translate_Text_Object(xshift, yshift, 0);
	Tempor->Translate_Text_Object(Object_Data[2], Object_Data[3], 0.0);
	Text = Tempor;
}
bool Object::Check_Button_Object(float x, float y, float cx, float cy){
	if (x > Object_Data[7] && x < Object_Data[6] && y > Object_Data[9] && y < Object_Data[8]){
		Mouse_Over = 1;
	}
	else{
		Mouse_Over = 3;
	}
	if (Mouse == true){
		if (Mouse_Over == 1){
			Mouse_Over = 2;
			Background->New_Textured_Object(Texture + " 2", 4, Object_Data[4], Object_Data[5], 0);
		}
		if (Mouse_Over == 3){
			Mouse_Over = 0;
			Background->New_Textured_Object(Texture + " 1", 4, Object_Data[4], Object_Data[5], 0);
		}
	}
	if (cx > Object_Data[7] && cx < Object_Data[6] && cy > Object_Data[9] && cy < Object_Data[8] && x > Object_Data[7] && x < Object_Data[6] && y > Object_Data[9] && y < Object_Data[8]){
		return(true);
	}
}
void Object::Translate_Button_Object(float x, float y, float z){
	Background->Translate_Object(x, y, z);
	Text->Translate_Text_Object(x, y, z);
	Object_Data[2] = Object_Data[2] + x;
	Object_Data[3] = Object_Data[3] + y;
	Object_Data[7] = Object_Data[7] + x;
	Object_Data[6] = Object_Data[6] + x;
	Object_Data[9] = Object_Data[9] + y;
	Object_Data[8] = Object_Data[8] + y;
}

/*-----Partical Object Funcitons-----*/
void Object::New_Partical_Spawner(int Partical_Type, float x_size, float y_size){
	Object_Type = Partical_Type + 6;
	Spawner_X = x_size;
	Spawner_Y = y_size;
	Object_Data[2] = 0.0;
	Object_Data[3] = 0.0;
	Current_Particals = 0;
	Spawn_Timer = 0;
}
void Object::Set_Color_Partial_Spawner_Data(int total_max, int spawn_max, int spawns_per_seconed, int partical_points, float partical_x_size, float partical_y_size, float velocity_x, float velocity_range_x, float acceleration_x, float acceleration_range_x, float velocity_y, float velocity_range_y, float acceleration_y, float acceleration_range_y, int life, int life_range, float r, float g, float b, float a, bool fade){
	Max_Particals = total_max;
	Max_Particals_Per_Spawn = spawn_max;
	Number_Of_Points = partical_points;
	Partical_Life = life;
	Partical_Life_Range = life_range;
	Partical_X = partical_x_size;
	Partical_Y = partical_y_size;
	Spawn_Velocity_X = velocity_x;
	Spawn_Velocity_Y = velocity_y;
	Spawn_Acceleration_X = acceleration_x;
	Spawn_Acceleration_Y = acceleration_y;
	Velocity_Range_X = velocity_range_x;
	Velocity_Range_Y = velocity_range_y;
	Acceleration_Range_X = acceleration_range_x;
	Acceleration_Range_Y = acceleration_range_y;
	Spawns_Per_Seconed = spawns_per_seconed;
	Red = r;
	Green = g;
	Blue = b;
	Alpha = a;
	Fade = fade;
}
void Object::Set_Texture_Partial_Spawner_Data(int total_max, int spawn_max, int spawns_per_seconed, int partical_points, float partical_x_size, float partical_y_size, float velocity_x, float velocity_range_x, float acceleration_x, float acceleration_range_x, float velocity_y, float velocity_range_y, float acceleration_y, float acceleration_range_y, int life, int life_range, string texture){
	Max_Particals = total_max;
	Max_Particals_Per_Spawn = spawn_max;
	Number_Of_Points = partical_points;
	Partical_Life = life;
	Partical_Life_Range = life_range;
	Partical_X = partical_x_size;
	Partical_Y = partical_y_size;
	Spawn_Velocity_X = velocity_x;
	Spawn_Velocity_Y = velocity_y;
	Spawn_Acceleration_X = acceleration_x;
	Spawn_Acceleration_Y = acceleration_y;
	Velocity_Range_X = velocity_range_x;
	Velocity_Range_Y = velocity_range_y;
	Acceleration_Range_X = acceleration_range_x;
	Acceleration_Range_Y = acceleration_range_y;
	Spawns_Per_Seconed = spawns_per_seconed;
	Partical_Texture = texture;
}
void Object::Run_Particals(){
	float vx, vy, ax, ay, Range, x, y, Temp_Float;
	int To_Spawn, Temp_Int, life;
	for (int a = 0; a < Current_Particals; a++){
		vx = Particals[a]->Velocity_X;
		vy = Particals[a]->Velocity_Y;
		ax = Particals[a]->Acceleration_X;
		ay = Particals[a]->Acceleration_Y;
		Particals[a]->Partical->Translate_Object(vx, vy, 0.0);
		vx = vx + ax;
		vy = vy + ay;
		Particals[a]->Velocity_X = vx;
		Particals[a]->Velocity_Y = vy;
		Particals[a]->Life--;
		if (Particals[a]->Life < 13 && Particals[a]->Life != 0 && Fade == true){
			x = 0.0;
			y = 0.0;
			x = Particals[a]->Partical->Return_Float_Value(2);
			y = Particals[a]->Partical->Return_Float_Value(3);
			Particals[a]->Partical->New_Colored_Object(Number_Of_Points, Partical_X, Partical_Y, Red, Green, Blue, (Alpha / 10) * Particals[a]->Life, 0);
		}
		if (Particals[a]->Life == 0){
			Particals.erase(Particals.begin() + a);
			Current_Particals--;
		}
	}
	if (Spawn_Timer > 0){
		Spawn_Timer--;
	}
	if (Current_Particals < Max_Particals){
		if (Spawn_Timer == 0){
			Spawn_Timer = 60 / Spawns_Per_Seconed;
			To_Spawn = (rand() % Max_Particals_Per_Spawn);
			while (To_Spawn + Current_Particals > Max_Particals){
				To_Spawn = (rand() % Max_Particals_Per_Spawn);
			}
			Current_Particals = Current_Particals + To_Spawn;
			for (int a = 0; a < To_Spawn; a++){
				Temp_Int = (Velocity_Range_X * 1000000) + 1;
				Range = (rand() % Temp_Int);
				if ((rand() % 2) == 0){
					Range = Range * -1;
				}
				Range = Range / 1000000;
				vx = Spawn_Velocity_X + Range;
				Temp_Int = (Velocity_Range_Y * 1000000) + 1;
				Range = (rand() % Temp_Int);
				if ((rand() % 2) == 0){
					Range = Range * -1;
				}
				Range = Range / 1000000;
				vy = Spawn_Velocity_Y + Range;
				Temp_Int = (Acceleration_Range_X * 1000000) + 1;
				Range = (rand() % Temp_Int);
				if ((rand() % 2) == 0){
					Range = Range * -1;
				}
				Range = Range / 1000000;
				ax = Spawn_Acceleration_X + Range;
				Temp_Int = (Acceleration_Range_Y * 1000000) + 1;
				Range = (rand() % Temp_Int);
				if ((rand() % 2) == 0){
					Range = Range * -1;
				}
				Range = Range / 1000000;
				ay = Spawn_Acceleration_Y + Range;

				Range = (rand() % Partical_Life_Range);
				life = Partical_Life + Range;
				Temp_Int = (Spawner_X * 100);
				x = (rand() % Temp_Int);
				x = x / 100;
				if (rand() % 2 == 0){
					x = x * -1;
				}
				Temp_Int = (Spawner_Y * 100);
				y = (rand() % Temp_Int);
				y = y / 100;
				if (rand() % 2 == 0){
					y = y * -1;
				}
				Partical_Object* Temp = new Partical_Object;
				Temp->Acceleration_X = ax;
				Temp->Acceleration_Y = ay;
				Temp->Velocity_X = vx;
				Temp->Velocity_Y = vy;
				Temp->Life = life;
				if (Object_Type == 6){
					Temp->Partical->New_Colored_Object(Number_Of_Points, Partical_X, Partical_Y, Red, Green, Blue, Alpha, 0);
				}
				if (Object_Type == 7){
					Temp->Partical->New_Textured_Object(Partical_Texture, Number_Of_Points, Partical_X, Partical_Y, 0);
				}
				Temp->Partical->Translate_Object(x + Object_Data[2], y + Object_Data[3], 0.0);
				Particals.push_back(Temp);
			}
		}
	}
}
void Object::Display_Particals(){
	for (int a = 0; a < Current_Particals; a++){
		Particals[a]->Partical->Display_Object();
	}
}
void Object::Translate_Partical_Spawner(float x, float y, float z){
	Object_Data[2] = Object_Data[2] + x;
	Object_Data[3] = Object_Data[3] + y;
}

/*-----Physics Object Functions-----*/
void Object::New_Color_Physics_Object(int points, float xsize, float ysize, float r, float g, float b, float a, int colision){
	Physics = new Object();
	Physics->New_Colored_Object(points, xsize, ysize, r, g, b, a, colision);
	Object_Type = 10;
	Object_Data[1] = points;
	Object_Data[2] = 0.0;
	Object_Data[3] = 0.0;
	Object_Data[4] = xsize;
	Object_Data[5] = ysize;
	Object_Data[6] = xsize;
	Object_Data[7] = -xsize;
	Object_Data[8] = ysize;
	Object_Data[9] = -ysize;
	Object_Data[10] = r;
	Object_Data[11] = g;
	Object_Data[12] = b;
	Object_Data[13] = a;
	Object_Data[14] = colision;
	Velocity_X = 0;
	Velocity_Y = 0;
	Acceleration_X = 0;
	Acceleration_Y = 0;
	Mass = 0;
	Friction_Static = 0;
	Friction_Kinetic = 0;
	Force_X = 0;
	Force_Y = 0;
	Reflection_Percent = 0;
	Transfer_Percent = 0;
}
void Object::New_Texture_Physics_Object(string texture, int points, float xsize, float ysize, int colision){
	Physics = new Object();
	Physics->New_Textured_Object(texture, points, xsize, ysize, colision);
	Texture = texture;
	Object_Type = 11;
	Object_Data[1] = points;
	Object_Data[2] = 0.0;
	Object_Data[3] = 0.0;
	Object_Data[4] = xsize;
	Object_Data[5] = ysize;
	Object_Data[6] = xsize;
	Object_Data[7] = -xsize;
	Object_Data[8] = ysize;
	Object_Data[9] = -ysize;
	Object_Data[14] = colision;
	Velocity_X = 0;
	Velocity_Y = 0;
	Acceleration_X = 0;
	Acceleration_Y = 0;
	Mass = 0;
	Friction_Static = 0;
	Friction_Kinetic = 0;
	Force_X = 0;
	Force_Y = 0;
	Reflection_Percent = 0;
	Transfer_Percent = 0;
}
void Object::Set_Object_Mass(float mass){
	Mass = mass;
}
void Object::Set_Object_Friction(float friction_s, float friction_k){
	Friction_Static = friction_s;
	Friction_Kinetic = friction_k;
}
void Object::Set_Acceleration_Physics_Object(float x, float y, float z){
	Acceleration_X = x;
	Acceleration_Y = y;
}
void Object::Add_Acceleration_Physics_Object(float x, float y, float z){
	Acceleration_X = Acceleration_X + x;
	Acceleration_Y = Acceleration_Y + y;
}
void Object::Translate_Physics_Object(float x, float y, float z){
	Physics->Translate_Object(x, y, z);
	Object_Data[2] = Object_Data[2] + x;
	Object_Data[3] = Object_Data[3] + y;
	Object_Data[6] = Object_Data[6] + x;
	Object_Data[7] = Object_Data[7] + x;
	Object_Data[8] = Object_Data[8] + y;
	Object_Data[9] = Object_Data[9] + y;
}
void Object::Set_Velocity_Physics_Object(float x, float y, float z){
	Velocity_X = x;
	Velocity_Y = y;
}
void Object::Add_Velocity_Physics_Object(float x, float y, float z){
	Velocity_X = Velocity_X + x;
	Velocity_Y = Velocity_Y + y;
}
void Object::Apply_Foce_Axis(float x, float y, float z){
	float To_Accelerate_X, To_Accelerate_Y;
	if (Mass == 0){
		Logging::log_error("Unregistered mass of object. Unable to compleate accurate force calculations", "Physics Object");
		Mass = 1;
	}
	Force_X = Force_X + x;
	Force_Y = Force_Y + y;
	Forces = true;
}
void Object::Apply_Foce_Ange(float theta, float force){
	Force_Y = Force_Y + (force * sin(theta));
	Force_X = Force_X + (force * cos(theta));
	Forces = true;
}
void Object::Set_Velocity_Reflection(float Percent){
	Reflection_Percent = Percent;
}
void Object::Set_Velocity_Transfer(float Percent){
	Transfer_Percent = Percent;
}
void Object::Reset_Physics_Data(int Type){
	Velocity_X = 0;
	Velocity_Y = 0;
	Acceleration_X = 0;
	Acceleration_Y = 0;
	Mass = 0;
	Friction_Static = 0;
	Friction_Kinetic = 0;
	Force_X = 0;
	Force_Y = 0;
	Forces = false;
	Stationary = true;
}
void Object::Display_Physics_Object(){
	Physics->Display_Object();
}
void Object::Set_Collsion_Objects(vector<Object*> Collisions, int Start, int Ignore){
	Set_Collision_Set(Collisions, Start, Ignore);
	Physics->Set_Collision_Set(Collisions, Start, Ignore);
}
void Object::Run_Physics(int &x, int &y){
	int Return = -3, Final = -1;
	float Distance_X, Distance_Y, Tic = (float)1 / (float)60;
	Distance_X = (Velocity_X *Tic) + (0.5 * Acceleration_X * (Tic * Tic));
	Distance_Y = (Velocity_Y *Tic) + (0.5 * Acceleration_Y * (Tic * Tic));
	Return = Physics->Move_Object(Distance_X, 0.0, 0.0, 0, 0.05);
	if (Return != -1){
		Velocity_X = -1 * (Velocity_X * (Reflection_Percent / (float)100));
	}
	if (Return >= 0 && Transfer_Percent != 0 && Return < Collision_Objects.size()){
		Collision_Objects[Return]->Add_Velocity_Physics_Object(-1* Velocity_X * (Transfer_Percent / (float)100), 0.0, 0.0);
		Velocity_X = Velocity_X - Velocity_X * (Transfer_Percent / (float)100);
	}
	else if (Return >= Collision_Objects.size()){
		Return = Return - Collision_Objects.size();
	}
	Final = Return;
	Return = Physics->Move_Object(0.0, Distance_Y, 0.0, 0, 0.05);
	if (Return != -1){
		Velocity_Y = -1 * (Velocity_Y * (Reflection_Percent / (float)100));
	}
	if (Return >= 0 && Transfer_Percent != 0 && Return < Collision_Objects.size()){
		Collision_Objects[Return]->Add_Velocity_Physics_Object(0.0, -1 * Velocity_Y * (Transfer_Percent / (float)100), 0.0);
		Velocity_Y = Velocity_Y - Velocity_Y * (Transfer_Percent / (float)100);
	}
	else if (Return >= Collision_Objects.size()){
		Return = Return - Collision_Objects.size();
	}
	Velocity_X = Velocity_X + (Acceleration_X * Tic);
	Velocity_Y = Velocity_Y + (Acceleration_Y * Tic);
	x = Final;
	y = Return;
}
float Object::Return_Physics_Data(int Value){
	if (Value == 1){
		return(Velocity_X);
	}
	if (Value == 2){
		return(Velocity_Y);
	}
}