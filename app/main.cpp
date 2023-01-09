#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <array>
#include <vector>
#include <cstdlib>
#include <queue>
#include <any>
#include <variant>
#include <json.h>
#include <json-forwards.h>
#include <fstream>
#include <string>
#include <ctime>
#include <time.h>
#include <chrono>

#undef main



bool open = false;

typedef std::array<int, 4> Sgrid;
typedef std::array<Sgrid, 4> Garray;
typedef std::array<int, 10> SPgrid;
typedef std::array<SPgrid, 20> Pgrid;


Uint32 frameStart;
int frameTime;
int level; 
int score;
class Blocks;

SDL_Renderer* renderer = nullptr;

SDL_Window* window = nullptr;

SDL_Texture* longboy = nullptr;
SDL_Texture* square = nullptr;
SDL_Texture* z1 = nullptr;
SDL_Texture* z2 = nullptr;
SDL_Texture* l1 = nullptr;
SDL_Texture* l2 = nullptr;
SDL_Texture* t = nullptr;
SDL_Texture* button = nullptr;
TTF_Font* font = nullptr;
SDL_Texture* background = nullptr;
std::vector<Blocks> list = {};
time_t current_time = time(NULL);
int FPS = 60;
int HEIGHT = 640;
double SCALE = 1;


void LoadSettings() {
	Json::Value settings;
	std::fstream file("settings.json");
	if (!file){
		std::ofstream settingsFile("settings.json");
		settingsFile << "{\n	\"FPS\" : 60,\n	\"PCHEIGHT\" : 640, \"\/\/comment\":  \"height should be a multiple or a divisor of 640 for better scaling\" \n}";
		settingsFile.close();
	}
	std::fstream file1("settings.json");
	if (!file1){
		std::cerr << "a problem happened with settings.json";
	}
	file1 >> settings;

	if (settings["FPS"]){
		FPS = settings["FPS"].asInt();
	}else{
		file.close();
		file1.close();
		if (remove("settings.json")!=0) {
			std::cerr << "a problem happened with settings.json";
		}else {
			LoadSettings();
		}
	}
	if (settings["PCHEIGHT"]){
		HEIGHT = settings["PCHEIGHT"].asInt();
	}else {
		file.close();
		file1.close();
		if (remove("settings.json") != 0) {
			std::cerr << "a problem happened with settings.json";
		}
		else {
			LoadSettings();
		}
	}
	file.close();
	file1.close();
	SCALE = HEIGHT / 640.0;
}



int RandomNumber(int max, int min) {
	long long x = rand();
	//current_time = time(NULL);
	//long long y = current_time;
	return (x) % (max - min) + min;

}

void Draw(SDL_Texture* tex, SDL_Rect dest);


void Clean() {
	open = false;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}


class Txt
{
public:
	Txt(const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color){
		texture = loadFont(font_path, font_size, message_text, color);
		SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	}
	void Render(int x, int y) {
		rect.x = x;
		rect.y = y;
		SDL_RenderCopy(renderer, texture, nullptr, &rect);
	}
	static SDL_Texture* loadFont(const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color) {
		TTF_Font* font = TTF_OpenFont(font_path.c_str(), font_size);
		if (!font){
			Clean();
		}
		auto surface = TTF_RenderText_Solid(font, message_text.c_str(), color);
		if (!surface){
			Clean();
		}
		auto text_texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (!text_texture){
			Clean();
		}
		SDL_FreeSurface(surface);
		return text_texture;

	}

private:
	SDL_Texture* texture = nullptr;
	SDL_Rect rect;
};







enum class Orientation
{
	up=0,
	right=1,
	down=2,
	left=3

};

enum class Mode
{
	remove=0,
	add=1
};

enum class Type
{
	none=0,
	longboys=1,
	square=2,
	z1=3,
	z2=4,
	l1=5,
	l2=6,
	t=7
};

std::queue<Type> nexts10 = {};
Type GetNext() {
	Type next = nexts10.front();
	int next1 = RandomNumber(7,1);
	nexts10.pop();
	nexts10.push((Type)next1);
	return (Type)next;
}

class PlayGrid
{
public:
	PlayGrid() {
		SPgrid spgrid1 = { 0,0,0,0,0,0,0,0,0,0 };
		SPgrid spgrid2 = { 0,0,0,0,0,0,0,0,0,0 };
		SPgrid spgrid3 = { 0,0,0,0,0,0,0,0,0,0 };
		SPgrid spgrid4 = { 0,0,0,0,0,0,0,0,0,0 };
		SPgrid spgrid5 = { 0,0,0,0,0,0,0,0,0,0 };
		SPgrid spgrid6 = { 0,0,0,0,0,0,0,0,0,0 };
		SPgrid spgrid7 = { 0,0,0,0,0,0,0,0,0,0 };
		SPgrid spgrid8 = { 0,0,0,0,0,0,0,0,0,0 };
		SPgrid spgrid9 = { 0,0,0,0,0,0,0,0,0,0 };
		SPgrid spgrid10 = { 0,0,0,0,0,0,0,0,0,0 };
		SPgrid spgrid11 = { 0,0,0,0,0,0,0,0,0,0 };
		SPgrid spgrid12 = { 0,0,0,0,0,0,0,0,0,0 };
		SPgrid spgrid13 = { 0,0,0,0,0,0,0,0,0,0 };
		SPgrid spgrid14 = { 0,0,0,0,0,0,0,0,0,0 };
		SPgrid spgrid15 = { 0,0,0,0,0,0,0,0,0,0 };
		SPgrid spgrid16 = { 0,0,0,0,0,0,0,0,0,0 };
		SPgrid spgrid17 = { 0,0,0,0,0,0,0,0,0,0 };
		SPgrid spgrid18 = { 0,0,0,0,0,0,0,0,0,0 };
		SPgrid spgrid19 = { 0,0,0,0,0,0,0,0,0,0 };
		SPgrid spgrid20 = { 0,0,0,0,0,0,0,0,0,0 };
		grid = { spgrid1, spgrid2, spgrid3, spgrid4, spgrid5, spgrid6, spgrid7, spgrid8, spgrid9, spgrid10, spgrid11, spgrid12, spgrid13, spgrid14, spgrid15, spgrid17, spgrid18, spgrid19, spgrid20 };


	};
	bool CheckLine(int line) {
		for (int i = 0; i < 10; i++)
		{
			if (grid[line][i]==0) {
				return false;
			}
		}
		return true;
	}
	std::vector<int> CheckAllLines() {
		std::vector<int> result = {};
		for (int i = 0; i < 20; i++)
		{
			if (CheckLine(i)) {
				result.push_back(i);
			}
		}
		return result;
	}
	void Render() {
		SDL_Rect dstrect = { 90, 0, 32, 32 };
		for (int y = 0; y < 20; y++){
			for (int x = 0; x < 10; x++){
				dstrect = { 90 + 32 * x, 32 * y, 32, 32 };
				switch (grid[y][x]){
				case 0:
					break;
				case 1:
					Draw(longboy, dstrect);
					break;
				case 2:
					Draw(square, dstrect);
					break;
				case 3:
					Draw(z1, dstrect);
					break;
				case 4:
					Draw(z2, dstrect);
					break;
				case 5:
					Draw(l1, dstrect);
					break;
				case 6:
					Draw(l2, dstrect);
					break;
				case 7:
					Draw(t, dstrect);
					break;
				default:
					Clean();
					break;
				 }
			}
		}
	}
	Pgrid ReturnGrid() {
		return grid;
	}
	void SetVal(int x, int y, int val) {
		grid[y][x] = val;
	}
private:
	Pgrid grid;
};
class BlockManager
{
public:
	BlockManager();
	void New();
	PlayGrid* GetGrid();
	void DelLine(int line);
	void Update(Orientation orientation, int*score);
	void Render();
	void DelBlock(int index);
	void RefreshGrid();
private:
	std::vector < Blocks* > list;
	PlayGrid* grid;
	
};


class Blocks
{
public:
	Blocks() {
		x = 3;
		y = 0;
		settled = false;
	}
	virtual void Spin(BlockManager* manager)=0;
	void SetPos(int _x, int _y) {
		if (-3 < x < 12 && 0 <= y < 20) {
			x = _x;
			y = _y;
		}
	}
	int GetX() {
		return x;
	}
	int GetY() {
		return y;
	}
	int GetVal(int _x, int _y) {
		return grid[_y][_x];
	};
	void SetVal(int _x, int _y, int val) {
		grid[_y][_x] = val;
	};
	Garray GetGrid() {
		return grid;
	}
	void SetGrid(Garray Grid) {
		grid = Grid;
	};
	Orientation GetOrient() {
		return orientation;
	}
	void SetOrient(Orientation orient) {
		orientation = orient;
	}
	void DelLine(BlockManager* manager, int line) {
		UpdateGrid(manager, Mode::remove);
		for (int i = line - 1; i >= 0; i--)
		{
			grid[i + 1] = grid[i];

		}
		grid[0] = { 0,0,0,0 };
		UpdateGrid(manager, Mode::add);
	}
	void Settle(BlockManager* manager) {
		manager->New();
		settled = true;
	}
	bool SettleCheck(BlockManager* manager) {
		UpdateGrid(manager, Mode::remove);
		if (!settled){
			if (y == 16){
				Settle(manager);
				UpdateGrid(manager, Mode::add);
				return true;
			}
			for (int i = 0; i < 4; i++){
				for (int j = 0; j < 4; j++) {
					if (grid[i][j]==1){
						if (manager->GetGrid()->ReturnGrid()[y + i + 1][x + j] != 0){
							if (!(i < 3 && grid[i + 1][j] == 0)) {
								Settle(manager);
								UpdateGrid(manager, Mode::add);
								return true;
							}
						}
					}
				}
			}
		}
		UpdateGrid(manager, Mode::add);
		return false;
	}
	void MoveDown(BlockManager* manager) {
		if (!SettleCheck(manager)) {
			UpdateGrid(manager, Mode::remove);
			y++;
			UpdateGrid(manager, Mode::add);
		}
	}
	void MoveRight(BlockManager* manager) {
		bool move = true;
		UpdateGrid(manager, Mode::remove);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (grid[i][j] == 1) {
					if (!(x + j + 1 >= 10)) {
						if (manager->GetGrid()->ReturnGrid()[y + i][x + j + 1] != 0 && j < 3 && grid[i][j + 1] == 0) {
							move = false;
						}
					}else{
						move = false;
					}

				}
			}
		}
		UpdateGrid(manager, Mode::add);
		if (move) {
			UpdateGrid(manager, Mode::remove);
			x++;
			UpdateGrid(manager, Mode::add);
		}
		
		
		
	}
	void MoveLeft(BlockManager* manager) {
		bool move = true;
		UpdateGrid(manager, Mode::remove);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (grid[i][j] == 1) {
					if (!(x + j - 1 < 0)) {
						if (manager->GetGrid()->ReturnGrid()[y + i][x + j - 1] != 0 && j > 3 && grid[i][j - 1] == 0) {
							move = false;
						}
					}
					else {
						move = false;
					}

				}
			}
		}
		UpdateGrid(manager, Mode::remove);
		if (move){
			UpdateGrid(manager, Mode::remove);
			x--;
			UpdateGrid(manager, Mode::add);
		}
		
	}
	void UpdateGrid(BlockManager* manager, Mode mode) {
		switch (mode)
		{
		case Mode::remove:
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (grid[i][j] == 1) {
						manager->GetGrid()->SetVal(x+j, y+i, 0);
					}
				}
			}
			break;
		case Mode::add:
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (grid[i][j] == 1) {
						if ((y + i)<20){
							if ((x+j)<10){
								if (0<=(x+j) < 10 && 0<=(y+i) < 20){
									switch (type){
									case Type::none:
										Clean();
										break;
									case Type::longboys:
										manager->GetGrid()->SetVal(x + j, y + i, 1);
										break;
									case Type::square:
										manager->GetGrid()->SetVal(x + j, y + i, 2);
										break;
									case Type::z1:
										manager->GetGrid()->SetVal(x + j, y + i, 3);
										break;
									case Type::z2:
										manager->GetGrid()->SetVal(x + j, y + i, 4);
										break;
									case Type::l1:
										manager->GetGrid()->SetVal(x + j, y + i, 5);
										break;
									case Type::l2:
										manager->GetGrid()->SetVal(x + j, y + i, 6);
										break;
									case Type::t:
										manager->GetGrid()->SetVal(x + j, y + i, 7);
										break;
									default:
										Clean();
										break;
									}
								}
							}
							
						}
						
						
					}
				}
			}
			break;
		default:
			Clean();
			break;
		}
		
	}
	void SetType(Type _type) {
		type = _type;
	}
	bool IsEmpty() {
		Sgrid sgrid1 = { 0,0,0,0 };
		Sgrid sgrid2 = { 0,0,0,0 };
		Sgrid sgrid3 = { 0,0,0,0 };
		Sgrid sgrid4 = { 0,0,0,0 };
		Garray garray = { sgrid1, sgrid2, sgrid3, sgrid4 };
		return (grid == garray);
	}
	void CheckSpin(bool* spin, Garray Grid, BlockManager* manager) {
		UpdateGrid(manager, Mode::remove);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (Grid[i][j] == 1) {
					if (0<=(y+i)<20 && 0<=(x+j)<10){
						if (manager->GetGrid()->ReturnGrid()[y + i][x + j] != 0 || x < 0 || x > 9) {
							*spin = false;
						}
					}else{
						*spin = false;
					}

				}
			}
		}
		UpdateGrid(manager, Mode::add);
	}

private:
	Garray grid;
	Orientation orientation;
	int x;
	int y;
	Type type;
	bool settled;
};
class Longboys: public Blocks
{
public:
	Longboys():Blocks() {
		Sgrid sgrid1 = { 0,0,1,0 };
		Sgrid sgrid2 = { 0,0,1,0 };
		Sgrid sgrid3 = { 0,0,1,0 };
		Sgrid sgrid4 = { 0,0,1,0 };
		Garray Grid ={sgrid1,sgrid2,sgrid3,sgrid4 };
		SetGrid( Grid);
		SetOrient(Orientation::up);
		SetType(Type::longboys);
	};
	void  Spin(BlockManager* manager) {
		UpdateGrid(manager, Mode::remove);
		Sgrid sgrid1 = { 0,0,0,0 };
		Sgrid sgrid2 = { 0,0,0,0 };
		Sgrid sgrid3 = { 1,1,1,1 };
		Sgrid sgrid4 = { 0,0,0,0 };
		Garray Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
		bool spin = true;
		CheckSpin(&spin, Grid, manager);
		switch (GetOrient())
		{	
		case Orientation::up:
			if (spin)
			{
				SetGrid(Grid);
				SetOrient(Orientation::right);
			}
			
			break;
		case Orientation::right:
			sgrid1 = { 0,1,0,0 };
			sgrid2 = { 0,1,0,0 };
			sgrid3 = { 0,1,0,0 };
			sgrid4 = { 0,1,0,0 };
			Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
			spin = true;
			CheckSpin(&spin, Grid, manager);
			if (spin)
			{
				SetGrid(Grid);
				SetOrient(Orientation::down);
			}
			
			break;
		case Orientation::down:
			sgrid1 = { 0,0,0,0 };
			sgrid2 = { 1,1,1,1 };
			sgrid3 = { 0,0,0,0 };
			sgrid4 = { 0,0,0,0 };
			Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
			spin = true;
			CheckSpin(&spin, Grid, manager);
			if (spin){
				SetGrid(Grid);
				SetOrient(Orientation::left);
			}

			break;
		case Orientation::left:
			sgrid1 = { 0,0,1,0 };
			sgrid2 = { 0,0,1,0 };
			sgrid3 = { 0,0,1,0 };
			sgrid4 = { 0,0,1,0 };
			Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
			spin = true;
			CheckSpin(&spin, Grid, manager);
			if (spin){
				SetGrid(Grid);
				SetOrient(Orientation::up);
			}

			break;
		default:
			Clean();
			break;
		}
		UpdateGrid(manager, Mode::add);
		
	}
	
private:

};
class Square : public Blocks
{
public:
	Square():Blocks() {
		Sgrid sgrid1 = { 0,0,0,0 };
		Sgrid sgrid2 = { 0,1,1,0 };
		Sgrid sgrid3 = { 0,1,1,0 };
		Sgrid sgrid4 = { 0,0,0,0 };
		Garray Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
		SetGrid(Grid);
		SetOrient(Orientation::up);
		SetType(Type::square);
	};
	void  Spin(BlockManager* manager)  {
		switch (GetOrient())
		{
		case Orientation::up:
			SetOrient(Orientation::right);
			break;
		case Orientation::right:
			SetOrient(Orientation::down);
			break;
		case Orientation::down:
			SetOrient(Orientation::left);
			break;
		case Orientation::left:
			SetOrient(Orientation::up);
			break;
		default:
			Clean();
			break;
		}
	}
	
private:

};
class Z1 : public Blocks
{
public:
	Z1():Blocks() {
		Sgrid sgrid1 = { 0,0,0,0 };
		Sgrid sgrid2 = { 0,0,1,0 };
		Sgrid sgrid3 = { 0,1,1,0 };
		Sgrid sgrid4 = { 0,1,0,0 };
		Garray Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
		SetGrid(Grid);
		SetOrient(Orientation::up);
		SetType(Type::z1);
	};
	void  Spin(BlockManager* manager)  {
		UpdateGrid(manager, Mode::remove);
		Sgrid sgrid1 = { 0,0,0,0 };
		Sgrid sgrid2 = { 0,0,0,0 };
		Sgrid sgrid3 = { 1,1,0,0 };
		Sgrid sgrid4 = { 0,1,1,0 };
		Garray Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
		bool spin = true;
		CheckSpin(&spin, Grid, manager);

		switch (GetOrient())
		{
		case Orientation::up:
			if (spin){
				SetGrid(Grid);
				SetOrient(Orientation::right);
			}
			
			break;
		case Orientation::right:
			sgrid1 = { 0,0,0,0 };
			sgrid2 = { 0,1,0,0 };
			sgrid3 = { 1,1,0,0 };
			sgrid4 = { 1,0,0,0 };
			Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
			spin = true;
			CheckSpin(&spin, Grid, manager);
			if (spin){
				SetGrid(Grid);
				SetOrient(Orientation::down);
			}
			
			break;
		case Orientation::down:
			sgrid1 = { 0,0,0,0 };
			sgrid2 = { 1,1,0,0 };
			sgrid3 = { 0,1,1,0 };
			sgrid4 = { 0,0,0,0 };
			Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
			spin = true;
			CheckSpin(&spin, Grid, manager);
			if (spin){
				SetGrid(Grid);
				SetOrient(Orientation::left);
			}
			
			break;
		case Orientation::left:
			sgrid1 = { 0,0,0,0 };
			sgrid2 = { 0,0,1,0 };
			sgrid3 = { 0,1,1,0 };
			sgrid4 = { 0,1,0,0 };
			Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
			spin = true;
			CheckSpin(&spin, Grid, manager);
			if (spin){
				SetGrid(Grid);
				SetOrient(Orientation::up);
			}

			break;
		default:
			Clean();
			break;
		}
		UpdateGrid(manager, Mode::add);
	}
	
private:

};
class Z2 : public Blocks
{
public:
	Z2():Blocks() {
		Sgrid sgrid1 = { 0,0,0,0 };
		Sgrid sgrid2 = { 0,1,0,0 };
		Sgrid sgrid3 = { 0,1,1,0 };
		Sgrid sgrid4 = { 0,0,1,0 };
		Garray Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
		SetGrid(Grid);
		SetOrient(Orientation::up);
		SetType(Type::z2);
	};
	void  Spin(BlockManager* manager)  {
		UpdateGrid(manager, Mode::remove);
		Sgrid sgrid1 = { 0,0,0,0 };
		Sgrid sgrid2 = { 0,0,0,0 };
		Sgrid sgrid3 = { 0,1,1,0 };
		Sgrid sgrid4 = { 1,1,0,0 };
		Garray Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
		bool spin = true;
		CheckSpin(&spin, Grid, manager);
		
		switch (GetOrient())
		{
		case Orientation::up:
			if (spin) {
				SetGrid(Grid);
				SetOrient(Orientation::right);
			}

			break;
		case Orientation::right:
			sgrid1 = { 0,0,0,0 };
			sgrid2 = { 1,0,0,0 };
			sgrid3 = { 1,1,0,0 };
			sgrid4 = { 0,1,0,0 };
			Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
			spin = true;
			CheckSpin(&spin, Grid, manager);
			if (spin) {
				SetGrid(Grid);
				SetOrient(Orientation::down);
			}
			
			break;
		case Orientation::down:
			sgrid1 = { 0,0,0,0 };
			sgrid2 = { 0,1,1,0 };
			sgrid3 = { 1,1,0,0 };
			sgrid4 = { 0,0,0,0 };
			Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
			spin = true;
			CheckSpin(&spin, Grid, manager);
			if (spin) {
				SetGrid(Grid);
				SetOrient(Orientation::left);
			}

			break;
		case Orientation::left:
			sgrid1 = { 0,0,0,0 };
			sgrid2 = { 0,1,0,0 };
			sgrid3 = { 0,1,1,0 };
			sgrid4 = { 0,0,1,0 };
			Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
			spin = true;
			CheckSpin(&spin, Grid, manager);
			if (spin) {
				SetGrid(Grid);
				SetOrient(Orientation::up);
			}

			break;
		default:
			Clean();
			break;
		}
		UpdateGrid(manager, Mode::add);
	}
	
private:

};
class L1 : public Blocks
{
public:
	L1():Blocks() {
		Sgrid sgrid1 = { 0,0,0,0 };
		Sgrid sgrid2 = { 0,1,0,0 };
		Sgrid sgrid3 = { 0,1,1,1 };
		Sgrid sgrid4 = { 0,0,0,0 };
		Garray Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
		SetGrid(Grid);
		SetOrient(Orientation::up);
		SetType(Type::l1);
	};
	void  Spin(BlockManager* manager)  {
		UpdateGrid(manager, Mode::remove);
		Sgrid sgrid1 = { 0,0,0,0 };
		Sgrid sgrid2 = { 0,0,1,1 };
		Sgrid sgrid3 = { 0,0,1,0 };
		Sgrid sgrid4 = { 0,0,1,0 };
		Garray Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
		bool spin = true;
		CheckSpin(&spin, Grid, manager);
		
		switch (GetOrient())
		{
		case Orientation::up:
			if (spin){
				SetGrid(Grid);
				SetOrient(Orientation::right);
			}

			break;
		case Orientation::right:
			sgrid1 = { 0,0,0,0 };
			sgrid2 = { 0,0,0,0 };
			sgrid3 = { 0,1,1,1 };
			sgrid4 = { 0,0,0,1 };
			Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
			spin = true;
			CheckSpin(&spin, Grid, manager);
			if (spin) {
				SetGrid(Grid);
				SetOrient(Orientation::down);
			}

			break;
		case Orientation::down:
			sgrid1 = { 0,0,0,0 };
			sgrid2 = { 0,0,1,0 };
			sgrid3 = { 0,0,1,0 };
			sgrid4 = { 0,1,1,0 };
			Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
			spin = true;
			CheckSpin(&spin, Grid, manager);
			if (spin) {
				SetGrid(Grid);
				SetOrient(Orientation::left);
			}

			break;
		case Orientation::left:
			sgrid1 = { 0,0,0,0 };
			sgrid2 = { 0,0,0,0 };
			sgrid3 = { 0,1,0,0 };
			sgrid4 = { 0,1,1,1 };
			Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
			spin = true;
			CheckSpin(&spin, Grid, manager);
			if (spin) {
				SetGrid(Grid);
				SetOrient(Orientation::up);
			}

			break;
		default:
			
			Clean();
			break;
		}
		UpdateGrid(manager, Mode::add);
	}
	
private:

};
class L2 : public Blocks
{
public:
	L2():Blocks() {
		Sgrid sgrid1 = { 0,0,0,0 };
		Sgrid sgrid2 = { 0,0,0,1 };
		Sgrid sgrid3 = { 0,1,1,1 };
		Sgrid sgrid4 = { 0,0,0,0 };
		Garray Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
		SetGrid(Grid);
		SetOrient(Orientation::up);
		SetType(Type::l2);
	};
	void  Spin(BlockManager* manager)  {
		UpdateGrid(manager, Mode::remove);
		Sgrid sgrid1 = { 0,0,0,0 };
		Sgrid sgrid2 = { 0,0,1,0 };
		Sgrid sgrid3 = { 0,0,1,0 };
		Sgrid sgrid4 = { 0,0,1,1 };
		Garray Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
		bool spin = true;
		CheckSpin(&spin, Grid, manager);
		
		switch (GetOrient())
		{
		case Orientation::up:
			if (spin)
			{
				SetGrid(Grid);
				SetOrient(Orientation::right);
			}

			break;
		case Orientation::right:
			sgrid1 = { 0,0,0,0 };
			sgrid2 = { 0,0,0,0 };
			sgrid3 = { 0,1,1,1 };
			sgrid4 = { 0,1,0,0 };
			Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
			spin = true;
			CheckSpin(&spin, Grid, manager);
			if (spin) {
				SetGrid(Grid);
				SetOrient(Orientation::down);
			}

			break;
		case Orientation::down:
			sgrid1 = { 0,0,0,0 };
			sgrid2 = { 0,1,1,0 };
			sgrid3 = { 0,0,1,0 };
			sgrid4 = { 0,0,1,0 };
			Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
			spin = true;
			CheckSpin(&spin, Grid, manager);
			if (spin) {
				SetGrid(Grid);
				SetOrient(Orientation::left);
			}

			break;
		case Orientation::left:
			sgrid1 = { 0,0,0,0 };
			sgrid2 = { 0,0,0,1 };
			sgrid3 = { 0,1,1,1 };
			sgrid4 = { 0,0,0,0 };
			Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
			spin = true;
			CheckSpin(&spin, Grid, manager);
			if (spin) {
				SetGrid(Grid);
				SetOrient(Orientation::up);
			}

			break;
		default:
			Clean();
			break;
		}
		UpdateGrid(manager, Mode::remove);
	}
private:

};
class T : public Blocks
{
public:
	T():Blocks() {
		Sgrid sgrid1 = { 0,0,0,0 };
		Sgrid sgrid2 = { 0,0,1,0 };
		Sgrid sgrid3 = { 0,1,1,1 };
		Sgrid sgrid4 = { 0,0,0,0 };
		Garray Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
		SetGrid(Grid);
		SetOrient(Orientation::up);
		SetType(Type::t);
	};
	void  Spin(BlockManager* manager)  {
		UpdateGrid(manager, Mode::remove);
		Sgrid sgrid1 = { 0,0,0,0 };
		Sgrid sgrid2 = { 0,0,1,0 };
		Sgrid sgrid3 = { 0,0,1,1 };
		Sgrid sgrid4 = { 0,0,1,0 };
		Garray Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
		bool spin = true;
		CheckSpin(&spin, Grid, manager);
		switch (GetOrient())
		{
		case Orientation::up:
			if (spin){
				SetGrid(Grid);
				SetOrient(Orientation::right);
			}
			break;
		case Orientation::right:
			sgrid1 = { 0,0,0,0 };
			sgrid2 = { 0,0,0,0 };
			sgrid3 = { 0,1,1,1 };
			sgrid4 = { 0,0,1,0 };
			Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
			spin = true;
			CheckSpin(&spin, Grid, manager);
			if (spin) {
				SetGrid(Grid);
				SetOrient(Orientation::down);
			}

			break;
		case Orientation::down:
			sgrid1 = { 0,0,0,0 };
			sgrid2 = { 0,0,1,0 };
			sgrid3 = { 0,1,1,0 };
			sgrid4 = { 0,0,1,0 };
			Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
			spin = true;
			CheckSpin(&spin, Grid, manager);
			if (spin) {
				SetGrid(Grid);
				SetOrient(Orientation::left);
			}

			break;
		case Orientation::left:
			sgrid1 = { 0,0,0,0 };
			sgrid2 = { 0,0,1,0 };
			sgrid3 = { 0,1,1,1 };
			sgrid4 = { 0,0,0,0 };
			Grid = { sgrid1,sgrid2,sgrid3,sgrid4 };
			spin = true;
			CheckSpin(&spin, Grid, manager);
			if (spin) {
				SetGrid(Grid);
				SetOrient(Orientation::up);
			}

			break;
		default:
			Clean();
			break;
		}
		UpdateGrid(manager, Mode::remove);
	}
	

private:

};


BlockManager::BlockManager() {
		list = {};
		switch (GetNext()){
		case Type::none:
			New();
			break;
		case Type::longboys:
			list.push_back(new Longboys());
			break;
		case Type::square:
			list.push_back(new Square());
			break;
		case Type::z1:
			list.push_back(new Z1());
			break;
		case Type::z2:
			list.push_back(new Z2());
			break;
		case Type::l1:
			list.push_back(new L1());
			break;
		case Type::l2:
			list.push_back(new L2());
			break;
		case Type::t:
			list.push_back(new T());
			break;
		default:
			Clean();
			break;
		}
		int next1 = RandomNumber(7, 1);
		nexts10.push((Type)next1);
		grid = new PlayGrid();
		
	}
void BlockManager::New() {
		switch (GetNext()) {
		case Type::none:
			New();
			break;
		case Type::longboys:
			list.push_back(new Longboys());
			break;
		case Type::square:
			list.push_back(new Square());
			break;
		case Type::z1:
			list.push_back(new Z1());
			break;
		case Type::z2:
			list.push_back(new Z2());
			break;
		case Type::l1:
			list.push_back(new L1());
			break;
		case Type::l2:
			list.push_back(new L2());
			break;
		case Type::t:
			list.push_back(new T());
			break;
		default:
			Clean();
			break;
		}
		int next1 = RandomNumber(7, 1);
		nexts10.push((Type)next1);
		
	}
PlayGrid* BlockManager::GetGrid() {
		return grid;
	}
void BlockManager::DelLine(int line) {
	for (int i = 0; i < list.size(); i++) {
		if (list[i]!=nullptr){
			switch ((line - list[i]->GetY())) {
			case 0:
				list[i]->DelLine(this, 0);
				break;
			case 1:
				list[i]->DelLine(this, 1);
				break;
			case 2:
				list[i]->DelLine(this, 2);
				break;
			case 3:
				list[i]->DelLine(this, 3);
				break;
			default:
				break;
			}
		}
		
	}
	for (int i = 0; i < list.size(); i++) {
		if (list[i]!= nullptr){
			list[i]->MoveDown(this);
		}
	}
}
void BlockManager::Update(Orientation orientation, int* score) {
	switch (orientation)
	{
	case Orientation::up:
		list[list.size() - 1]->Spin(this);
		break;
	case Orientation::right:
		list[list.size() - 1]->MoveRight(this);
		break;
	case Orientation::down:
		list[list.size() - 1]->MoveDown(this);
		break;
	case Orientation::left:
		list[list.size() - 1]->MoveLeft(this);
		break;
	default:
		Clean();
		break;
	}
	std::vector<int> lines = grid->CheckAllLines();
	for (int i = 0; i < lines.size(); i++){
		DelLine(lines[i]);
	}
	switch (lines.size()){
	case 1:
		*score += 40;
		break;
	case 2:
		*score += 100;
		break;
	case 3:
		*score += 300;
		break;
	case 4:
		*score += 1200;
		break;
	default:
		break;
	}
	Render();
}
void BlockManager::Render() {
	RefreshGrid();
	grid->Render();
	
}
void BlockManager::DelBlock(int index) {
	if (list[index]!=nullptr){
		delete list[index];
		list[index] = nullptr;
	}
}
void BlockManager::RefreshGrid() {
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 20; j++) {
			grid->SetVal(i, j, 0);
		}
	}
	for (int i = 0; i < list.size(); i++){
		if (list[i] != nullptr) {
			list[i]->UpdateGrid(this, Mode::add);
		}
	}
}




SDL_Texture* LoadTexture(const char* texture)
{
	SDL_Surface* tmpSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return tex;
}
SDL_Texture* LoadText(Uint8 r, Uint8 g, Uint8 b, const char* txt) {
	SDL_Color color = { r, g, b };
	SDL_Surface* tmpSurface = TTF_RenderText_Solid(font,
		txt, color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return tex;
}
void Draw(SDL_Texture* tex,  SDL_Rect dest)
{
	SDL_RenderCopy(renderer, tex, NULL, &dest);
}
void DrawText(SDL_Texture* tex, SDL_Rect dest, int* texW, int* texH) {
	if (SDL_QueryTexture(tex, NULL, NULL, texW, texH) == 0) {
		std::cout << "failed to querry texture";
	}
	SDL_RenderCopy(renderer, tex, NULL, &dest);
}
void RenderText() {

}
void AI();
void play();

void mainHandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		open = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (50 <= event.button.x && event.button.x <= 450){
			if(570 <= event.button.y && event.button.y <= 620){
				Clean();
			}else  if (350 <= event.button.y && event.button.y <= 400){
				play();
			}else if (200 <= event.button.y && event.button.y <= 250){
				AI();
			}
		}
		break;
	default:
		break;
	}
}
void AIHandleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		open = false;
		break;
	default:
		break;
	}
}
void playHandleEvents(BlockManager* manager, int* score) {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		open = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.scancode)
		{
		case SDLK_LEFT:
			manager->Update(Orientation::left, score);
			break;
		case SDLK_RIGHT:
			manager->Update(Orientation::right, score);
			break;
		case SDLK_UP:
			manager->Update(Orientation::up, score);
			break;
		case SDLK_DOWN:
			manager->Update(Orientation::down, score);
			break;
		default:
			break;
		}
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			manager->Update(Orientation::left, score);
			break;
		case SDLK_RIGHT:
			manager->Update(Orientation::right, score);
			break;
		case SDLK_UP:
			manager->Update(Orientation::up, score);
			break;
		case SDLK_DOWN:
			manager->Update(Orientation::down, score);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}



void mainMenu() {
	
	SDL_Rect dstrect={50,570,400,50};
	Txt quit = Txt("assets/characters/arial.ttf", 45, "QUIT", {0,255,0});
	Txt Play = Txt("assets/characters/arial.ttf", 45, "PLAY", { 0,255,0 });
	Txt Ai = Txt("assets/characters/arial.ttf", 45, "AI", { 0,255,0 });

	while (open){
		
		mainHandleEvents();
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0x1a, 0x1b, 0x26, 0xff);



		Draw(button, dstrect);
		
		dstrect.y = 350;
		Draw(button, dstrect);
		
		dstrect.y = 200;
		Draw(button, dstrect);
		quit.Render(190, 570);
		Play.Render(190, 350);
		Ai.Render(225, 200);



		SDL_RenderPresent(renderer);
	}
}

void AI(){}
void play() {
	
	
	level = 1;
	score = 0;
	double SPT = 1;
	SDL_Rect dstrect = {90,0,320,640};
	int next1 = RandomNumber(7, 1);
	int next2 = RandomNumber(7, 1);
	int next3 = RandomNumber(7, 1);
	int next4 = RandomNumber(7, 1);
	int next5 = RandomNumber(7, 1);
	int next6 = RandomNumber(7, 1);
	int next7 = RandomNumber(7, 1);
	int next8 = RandomNumber(7, 1);
	int next9 = RandomNumber(7, 1);
	int next10 = RandomNumber(7, 1);




	
	
	nexts10.push((Type)next1);
	nexts10.push((Type)next2);
	nexts10.push((Type)next3);
	nexts10.push((Type)next4);
	nexts10.push((Type)next5);
	nexts10.push((Type)next6);
	nexts10.push((Type)next7);
	nexts10.push((Type)next8);
	nexts10.push((Type)next9);
	nexts10.push((Type)next10);

	BlockManager manager = BlockManager();
	
	int FPT = FPS * SPT;
	int tickCount = FPT;
	while (open)
	{
		FPT = FPS * SPT;
		int frameDelay = 1000 / FPS;
		frameStart = SDL_GetTicks();

		playHandleEvents(&manager, &score);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0x1a, 0x1b, 0x26, 0xff);
		
		Draw(background, dstrect);
		if (tickCount >= FPT){
			manager.Update(Orientation::down, &score);
			tickCount = 0;
		}
		else{
			tickCount++;
			manager.Render();
		}
		










		SDL_RenderPresent(renderer);


		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

}







void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (TTF_Init() == 0) {
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		{

			window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

			renderer = SDL_CreateRenderer(window, -1, 0);
			font = TTF_OpenFont("arial.ttf", 25);
		
			open = true;
		}
	}
	
	longboy = LoadTexture("assets/sprites/long.png");
	square = LoadTexture("assets/sprites/bloc.png");
	l1 = LoadTexture("assets/sprites/l1.png");
	l2 = LoadTexture("assets/sprites/l2.png");
	z1 = LoadTexture("assets/sprites/z1.png");
	z2 = LoadTexture("assets/sprites/z2.png");
	t = LoadTexture("assets/sprites/t.png");
	button = LoadTexture("assets/sprites/buttons.png");
	background = LoadTexture("assets/sprites/grid.png");


}






void app() {
	init("Tetris", 200, 200, SCALE * 500,SCALE * 640, false);

	mainMenu();





	
	


	Clean();
}


int main(int argc, char* argv[]) {
	srand(time(NULL));
	LoadSettings();
	app();
	
}



// ************************beta-features***********************//

