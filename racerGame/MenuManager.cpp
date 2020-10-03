#include "MenuManager.h"



//Basic Menu Button

menuItem::menuItem(int width, int height, int xpos, int ypos, SDL_Color* color, SDL_Renderer* ren, SDL_Color* defaultColor, bool fixed, vector2d screenSize) {
	// Width and height = size based on screen percent
	float tmpWidth = width;
	float tmpHeight = height;
	float tmpXPos = xpos;
	float tmpYPos = ypos;
	this->size.x = tmpWidth / 100; // Size will be constant (
	this->size.y = tmpHeight / 100;// Size will be constant
	this->position.x = tmpXPos / 100; // pos will be constant
	this->position.y = tmpYPos / 100; // ops will be constant
	this->renderer = ren;
	this->color = color;
	this->r.w = size.x * screenSize.x;// r-> is causing a crash // This wont be constant
	this->r.h = size.y * screenSize.y;
	this->r.y = position.y * screenSize.y;
	this->r.x = position.x  * screenSize.x;
	this->fixed = fixed; // whether the object is resizeable or not
	this->defaultColor = defaultColor;
//	this->objectPointer = this;
}
menuItem::menuItem(vector2d size, vector2d position, SDL_Color* color, SDL_Renderer* ren, SDL_Color* defaultColor, bool fixed, vector2d screenSize) {
	this->size.x = size.x / 100;
	this->size.y = size.y / 100;
	this->position.y = position.y / 100;
	this->position.x = position.x / 100;
	this->renderer = ren;
	this->color = color;
	this->fixed = fixed;
	this->defaultColor = defaultColor;
	r.w = size.x * screenSize.x;
	r.h = size.y * screenSize.y;
	r.y = position.y * screenSize.y;
	r.x = position.x * screenSize.x;
//	this->objectPointer = this;
}

void menuItem::clicked() {
	if (click == false) {
		click = true;
		this->handleClick();
	}
	else {
		// do something else
		//this->unClick();
	}
}
bool menuItem::isClicked() {
	return click;
}
void menuItem::unClick() {
	click = false;
}
 void menuItem::handleClick() {
	// do stuff
	 this->click = false;
}
 bool menuItem::isStarted() {
	 return Started;
 }

// Destructor
menuItem::~menuItem() {


}
SDL_Rect menuItem::getMenuBox() { // Return Menu's position
	// Have to convert the proportion to actual size
	return this->r;
}


void menuItem::changeColor(SDL_Color* newColor) { // Change Color of Menu
	this->color = newColor;
}
void menuItem::changeTexture(const char* newTexture) { // To be Added
	

}
/*
vector2d menuItem::getSize(vector2d screenSize) {
	vector2d actualSize = { this->size.x * ScreenSize.x, this->size.y * ScreenSize.y};
	//double actualSize.x = this->size.x * screenWidth / 100;
	return ; // Had to convert size (which is a proportion) to the acutal size it is on screen
}
*/
 // For When Window Resizes
void menuItem::Resize(int screenWidth, int screenHeight) { // orignally its Width / 100 * screenWidth
	if (this->fixed == false) {
		this->r.w = this->size.x * screenWidth;
		this->r.h = this->size.y * screenHeight;
		this->r.x = this->position.x * screenWidth;
		this->r.y = this->position.y * screenHeight;
		//this->r
	}
}




// When filling a menuItem with coloor
void menuItem::Render() {
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	SDL_RenderFillRect(renderer, &r);
	SDL_SetRenderDrawColor(renderer, defaultColor->r, defaultColor->g, defaultColor->b, defaultColor->a);
	}
/*
void* menuItem::getObjPointer() {
	return this->objectPointer;
}
*/

////////////	Basic Texture Button (ex. Image on button) ////////////////////////////////////////////////

textureMenuItem::textureMenuItem(int width, int height, int srcWidth, int srcHeight, int xpos, int ypos, SDL_Color* color, SDL_Renderer* ren, const char* texture1, SDL_Color* defaultColor, bool fixed, vector2d screenSize)
	: menuItem(width, height, xpos, ypos, color, ren, defaultColor, fixed, screenSize),
	texture(*texture1)
{
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = srcHeight;
	srcRect.h = srcWidth;
	destRect.x = position.x * screenSize.x;
	destRect.y = position.y * screenSize.y;
	destRect.w = size.x * screenSize.x;
	destRect.h = size.y * screenSize.y;
	//this->objectPointer = this;
	tex = TextureManager::LoadTexture(texture1, renderer);
	/*
	this->size.x = width;
	this->size.y = height;
	this->position.x = xpos;
	this->position.y = ypos;
	this->renderer = ren;
	this->color = color;
	r->w = width;
	r->h = height;
	r->y = ypos;
	r->x = xpos;
	*/
}

textureMenuItem::textureMenuItem(vector2d size, int srcWidth, int srcHeight, vector2d position, SDL_Color* color, SDL_Renderer* ren, const char* texture1, SDL_Color* defaultColor, bool fixed, vector2d screenSize)
: menuItem(size, position, color, ren, defaultColor, fixed, screenSize)
, texture(*texture1){
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = srcHeight;
	srcRect.h = srcWidth;
	destRect.x = this->position.x * screenSize.x;
	destRect.y = this->position.y * screenSize.y;
	destRect.w = this->size.x * screenSize.x;
	destRect.h = this->size.y * screenSize.y;
	//this->objectPointer = this;
	tex = TextureManager::LoadTexture(texture1, renderer);
	/*
	this->size = size;
	this->position = position;
	this->renderer = ren;
	this->color = color;
	this->r->w = size.x;
	this->r->h = size.y;
	this->r->y = position.y;
	this->r->x = position.x;
	this->pos = r;
	*/
}

void textureMenuItem::Render() {
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	SDL_RenderFillRect(renderer, &r);
	SDL_RenderCopy(renderer,tex, NULL, &destRect) ;
	SDL_SetRenderDrawColor(renderer, defaultColor->r, defaultColor->g, defaultColor->b, defaultColor->a);
}

void textureMenuItem::Resize(int screenWidth, int screenHeight) { // orignally its Width / 100 * screenWidth
	if (this->fixed == false) {
		
		this->r.x = this->position.x * screenWidth;
		this->r.y = this->position.y * screenHeight;
		this->r.w = this->size.x * screenWidth;
		this->r.h = this->size.y * screenHeight;
		this->destRect.h = r.h;
		this->destRect.x = r.x;
		this->destRect.y = r.y;
		this->destRect.w = r.w;
	}
}

/////////////	Texture Start Button //////////////////////////////////////
textureStartButton::textureStartButton(vector2d size, int srcWidth, int srcHeight, vector2d position, SDL_Color* color, SDL_Renderer* ren, const char* texture1, SDL_Color* defaultColor, bool fixed, vector2d screenSize)
	: textureMenuItem(size, srcWidth, srcHeight, position, color, ren, texture1, defaultColor, fixed, screenSize) {
	/*
	this->size = size;
	this->position = position;
	*/
	//this->objectPointer = this;
	this->Started = false;
}
//textureStartButton::~textureStartButton();

textureStartButton::textureStartButton(int width, int height, int srcWidth, int srcHeight, int xpos, int ypos, SDL_Color* color, SDL_Renderer* ren, const char* texture1, SDL_Color* defaultColor, bool fixed, vector2d screenSize)
	: textureMenuItem(width, height, srcWidth, srcHeight, xpos, ypos, color, ren, texture1, defaultColor, fixed, screenSize) {
	/*
	this->size.x = width;
	this->size.y = height;
	this->position.x = xpos;
	this->position.y = ypos;
	*/
	//this->objectPointer = this;
	this->Started = false;
}


void textureStartButton::StartGame() {
	this->Started = true;
}// Will act as a second initializer for game

bool textureStartButton::isStarted() {
	return this->Started;
}

void textureStartButton::handleClick() {
	StartGame();
	click = false;
}

void textureStartButton::Render() {
//	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	//	SDL_RenderFillRect(renderer, &r);
	//SDL_RenderCopy(renderer, tex, NULL , &r);
//	SDL_SetRenderDrawColor(renderer, defaultColor->r, defaultColor->g, defaultColor->b, defaultColor->a);
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	SDL_RenderFillRect(renderer, &r);
	SDL_RenderCopy(renderer, tex, NULL, &destRect);
	SDL_SetRenderDrawColor(renderer, defaultColor->r, defaultColor->g, defaultColor->b, defaultColor->a);
}


/////////////	Start Button	 ///////////////////////////////

startButton::startButton(int width, int height, int xpos, int ypos, SDL_Color* color, SDL_Renderer* ren, SDL_Color* defaultColor, bool fixed, vector2d screenSize)
 : menuItem(width, height, xpos, ypos, color, ren, defaultColor, fixed, screenSize){
	/*
	this->size.x = width;
	this->size.y = height;
	this->position.x = xpos;
	this->position.y = ypos;
	*/
	//this->objectPointer = this;
	this->Started = false;
}
startButton::startButton(vector2d size, vector2d position, SDL_Color* color, SDL_Renderer* ren, SDL_Color* defaultColor, bool fixed, vector2d screenSize)
: menuItem(size, position, color, ren, defaultColor, fixed, screenSize){
	/*
	this->size = size;
	this->position = position;
	*/
	//this->objectPointer = this;
	this->Started = false;
}
//startButton::~startButton();

void startButton::StartGame() {
	this->Started = true;
}// Will act as a second initializer for game

bool startButton::isStarted() {
	return this->Started;
}

void startButton::handleClick() {
	StartGame();
	click = false;
}

/////////////	Menu Manager		//////////////////////////////////////////

MenuManager::MenuManager( int screenWidth, int screenHeight) {
	ScreenSize.x = screenWidth;
	ScreenSize.y = screenHeight;
}

std::vector<menuItem*>* MenuManager::getMenuArray() {
	return &this->menuArray;
}

vector2d MenuManager::getScreenSize() {
	return this->ScreenSize;
}

menuItem* MenuManager::getMenuFromCoordinates(int x, int y) {
	SDL_Color change = { 90,2,140,0 }; // test stuff
	SDL_Color change2 = { 90,2,200,0 }; // test
	// New reverse loop
	for (auto i = this->menuArray.rbegin(); i != this->menuArray.rend(); ++i) { // WORKS

		SDL_Rect menuBox = (*i)->getMenuBox();

		if (menuBox.x <= x && (menuBox.x + menuBox.w) >= x && menuBox.y <= y && (menuBox.y + menuBox.h >= y)) { // Its within the button
			SDL_Color change = { 90,2,200,0 };
			return *i;

		}
		//i->changeColor(&change2);\
		*/ //
	}

	// Old forward loop
	/*
	for (auto i : this->menuArray) { // I need to make this a reverse iterator (since I want to click on things that are at the very front)
		SDL_Rect menuBox = i->getMenuBox();
		if (menuBox.x <= x) {
			i->changeColor(&change2);
		}

		if (menuBox.x <= x && (menuBox.x + menuBox.w) >= x && menuBox.y <= y && (menuBox.y + menuBox.h >= y)) { // Its within the button
			SDL_Color change = { 90,2,200,0 };
		i->changeColor(&change);
			return i;
		}
		//i->changeColor(&change2);\
		*/ //
	}



void MenuManager::Resize(int screenWidth, int screenHeight) {
	for ( auto v : this->menuArray) {
		v->Resize(screenWidth, screenHeight);
	}
	ScreenSize.x = screenWidth;
	ScreenSize.y = screenHeight;
}


// Texture Start Button
textureStartButton* MenuManager::createTextureStartButton(int width, int height, int srcWidth, int srcHeight, int xpos, int ypos, SDL_Color* color, SDL_Renderer* ren, const char* texture1, SDL_Color* defaultColor, bool fixed, vector2d screenSize) {
	textureStartButton* texSB = new textureStartButton(width, height, srcWidth, srcHeight, xpos, ypos, color, ren, texture1, defaultColor, fixed, screenSize);
	this->menuArray.push_back(texSB);
	return texSB;
}
textureStartButton* MenuManager::createTextureStartButton(vector2d size, int srcWidth, int srcHeight, vector2d position, SDL_Color* color, SDL_Renderer* ren, const char* texture1, SDL_Color* defaultColor, bool fixed, vector2d screenSize) {
	textureStartButton* texSB = new textureStartButton(size, srcWidth, srcHeight, position, color, ren, texture1, defaultColor, fixed, screenSize);
	this->menuArray.push_back(texSB);
	return texSB;
}
// Start Button
startButton* MenuManager::createStartButton(int width, int height, int xpos, int ypos, SDL_Color* color, SDL_Renderer* ren, SDL_Color* defaultColor, bool fixed, vector2d screenSize) {
	startButton* sB = new startButton(width, height, xpos, ypos, color, ren, defaultColor, fixed, screenSize);
	this->menuArray.push_back(sB);
	return sB;
}
startButton* MenuManager::createStartButton(vector2d size, vector2d position, SDL_Color* color, SDL_Renderer* ren, SDL_Color* defaultColor, bool fixed, vector2d screenSize) {
	startButton* sB = new startButton(size, position, color, ren, defaultColor, fixed, screenSize);
	this->menuArray.push_back(sB);
	return sB;
}

// Menu Item
menuItem* MenuManager::createMenuItem(int width, int height, int xpos, int ypos, SDL_Color* color, SDL_Renderer* ren, SDL_Color* defaultColor, bool fixed, vector2d screenSize) {
	menuItem* mI = new menuItem(width, height, xpos, ypos, color, ren, defaultColor, fixed, screenSize);
	this->menuArray.push_back(mI);
	return mI;
}
menuItem* MenuManager::createMenuItem(vector2d size, vector2d position, SDL_Color* color, SDL_Renderer* ren, SDL_Color* defaultColor, bool fixed, vector2d screenSize) {
	menuItem* mI = new menuItem(size, position, color, ren, defaultColor, fixed, screenSize);
	this->menuArray.push_back(mI);
	return mI;
}
// Texture Menu Item
textureMenuItem* MenuManager::createTextureMenuItem(int width, int height, int srcWidth, int srcHeight, int xpos, int ypos, SDL_Color* color, SDL_Renderer* ren, const char* texture1, SDL_Color* defaultColor, bool fixed, vector2d screenSize) {
	textureMenuItem* tMI = new textureMenuItem(width, height, srcWidth, srcHeight, xpos, ypos, color, ren, texture1, defaultColor, fixed, screenSize);
	this->menuArray.push_back(tMI);
	return tMI;
}
textureMenuItem* MenuManager::createTextureMenuItem(vector2d size, int srcWidth, int srcHeight, vector2d position, SDL_Color* color, SDL_Renderer* ren, const char* texture1, SDL_Color* defaultColor, bool fixed, vector2d screenSize) {
	textureMenuItem* tMI = new textureMenuItem(size, srcWidth, srcHeight, position, color, ren, texture1, defaultColor, fixed, screenSize);
	this->menuArray.push_back(tMI);
	return tMI;
}