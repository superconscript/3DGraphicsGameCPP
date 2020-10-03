#pragma once
#include "TextureManager.h"
#include "math.h"
#include <vector>

class menuItem {
public:
	menuItem(int width, int height, int xpos, int ypos, SDL_Color* color, SDL_Renderer* ren, SDL_Color* defaultColor, bool fixed, vector2d screenSize);
	menuItem(vector2d size, vector2d position, SDL_Color* color, SDL_Renderer* ren, SDL_Color* defaultColor, bool fixed, vector2d screenSize);
	~menuItem();
//	void* getObjPointer();
	SDL_Rect getMenuBox(); // these functions return the Actual Position (not the proportion position)
	void virtual Resize(int screenWidth, int screenHeight);
	void virtual Render();
	void changeColor(SDL_Color* newColor);
	void changeTexture(const char* newTexture);
	void clicked();
	bool isClicked();
	void unClick();
	bool isStarted();
	void virtual handleClick();
	//vector2d getSize(vector2d screenSize); // returns converted size (not proportion)
	//void* objectPointer; // used to return the object from the vector menuArray
protected:
	vector2d position;
	vector2d size;
	bool fixed;
	SDL_Color* color;
	SDL_Color* defaultColor;
	SDL_Rect r;
	SDL_Rect pos;
	SDL_Renderer* renderer;
	bool click = false;
	bool Started = false;
};

class textureMenuItem : public menuItem {
public:
	textureMenuItem(int width, int height, int srcWidth, int srcHeight, int xpos, int ypos, SDL_Color* color, SDL_Renderer* ren, const char* texture1, SDL_Color* defaultColor, bool fixed, vector2d screenSize);
	textureMenuItem(vector2d size, int srcWidth, int srcHeight, vector2d position, SDL_Color* color, SDL_Renderer* ren, const char* texture1, SDL_Color* defaultColor, bool fixed, vector2d screenSize);
	~textureMenuItem();

	void Render();
	void Resize(int screenWidth, int screenHeight);
protected:
	const char texture;
	SDL_Texture* tex;
	SDL_Rect srcRect;
	SDL_Rect destRect;
};

class startButton : public menuItem {
public:
	startButton(int width, int height, int xpos, int ypos, SDL_Color* color, SDL_Renderer* ren, SDL_Color* defaultColor, bool fixed, vector2d screenSize);
	startButton(vector2d size, vector2d position, SDL_Color* color, SDL_Renderer* ren, SDL_Color* defaultColor, bool fixed, vector2d screenSize);
	~startButton();

	void StartGame(); // Will act as a second initializer for game
	bool isStarted();
	void handleClick();
private:
	//bool Started;
};


class textureStartButton : public textureMenuItem {
public:
	textureStartButton(int width, int height, int srcWidth, int srcHeight, int xpos, int ypos, SDL_Color* color, SDL_Renderer* ren, const char* texture1, SDL_Color* defaultColor, bool fixed, vector2d screenSize);
	textureStartButton(vector2d size, int srcWidth, int srcHeight, vector2d position, SDL_Color* color, SDL_Renderer* ren,  const char* texture1, SDL_Color* defaultColor, bool fixed, vector2d screenSize);
	~textureStartButton();

	void Render();
	void StartGame(); // Will act as a second initializer for game
	bool isStarted();
	void handleClick();

private:
	//bool Started;
};


// We can run the creation functions through this guy to have an array of all menu's
class MenuManager {
	// This guy knows all the menu's and holds the array of them
public:
	MenuManager(int screenWidth, int screenHeight);
	~MenuManager();

	void Resize(int screenWidth, int screenHeight); // Will Resize all menu's
	std::vector<menuItem*>* getMenuArray();
	vector2d getScreenSize();
	menuItem* getMenuFromCoordinates(int x, int y);
//Create Functions
	textureStartButton* createTextureStartButton(int width, int height, int srcWidth, int srcHeight, int xpos, int ypos, SDL_Color* color, SDL_Renderer* ren, const char* texture1, SDL_Color* defaultColor, bool fixed, vector2d screenSize);
	textureStartButton* createTextureStartButton(vector2d size, int srcWidth, int srcHeight, vector2d position, SDL_Color* color, SDL_Renderer* ren, const char* texture1, SDL_Color* defaultColor, bool fixed, vector2d screenSize);
	startButton* createStartButton(int width, int height, int xpos, int ypos, SDL_Color* color, SDL_Renderer* ren, SDL_Color* defaultColor, bool fixed, vector2d screenSize);
	startButton* createStartButton(vector2d size, vector2d position, SDL_Color* color, SDL_Renderer* ren, SDL_Color* defaultColor, bool fixed, vector2d screenSize);
	menuItem* createMenuItem(int width, int height, int xpos, int ypos, SDL_Color* color, SDL_Renderer* ren, SDL_Color* defaultColor, bool fixed, vector2d screenSize);
	menuItem* createMenuItem(vector2d size, vector2d position, SDL_Color* color, SDL_Renderer* ren, SDL_Color* defaultColor, bool fixed, vector2d screenSize);
	textureMenuItem* createTextureMenuItem(int width, int height, int srcWidth, int srcHeight, int xpos, int ypos, SDL_Color* color, SDL_Renderer* ren, const char* texture1, SDL_Color* defaultColor, bool fixed, vector2d screenSize);
	textureMenuItem* createTextureMenuItem(vector2d size, int srcWidth, int srcHeight, vector2d position, SDL_Color* color, SDL_Renderer* ren, const char* texture1, SDL_Color* defaultColor, bool fixed, vector2d screenSize);
// Delete Functions
	void deleteTextureStartButton(textureStartButton& tSB);
	void deleteStartButton(startButton& sB);
	void deleteMenuItem(menuItem& mI);
	void deleteTextureMenuItem(textureMenuItem& tMI);
private:
	std::vector<menuItem*>	menuArray; // holds all the menu's
	vector2d ScreenSize;
};
