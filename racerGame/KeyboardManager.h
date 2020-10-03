#pragma once
#include <vector>
#include <SDL_keyboard.h>
#include <SDL_scancode.h>
#include <SDL_messagebox.h>
#include <string>
class PongPhysics;
//enum class direction { UP, DOWN, LEFT, RIGHT, IN, BACK, LAST_COUNT };
enum class Actions {UNASSIGNED, MOVE_FORWARD, MOVE_BACKWARD, MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, ROTATE_LEFT, ROTATE_RIGHT, ROTATE_UP, ROTATE_DOWN, LAST_COUNT };
//enum class keyValues {W, A, S, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, LAST_COUNT};
struct Key {
	Key(SDL_Scancode keyScanCode1) { 
	this->keyScanCode = keyScanCode1; 
	this->active = false; 
	}
	bool active = false;
	//keyValues keyName;
	SDL_Scancode keyScanCode;
	//direction keyDirection;
};
struct ActionObject {
	ActionObject(Actions assignedAction1 = Actions::UNASSIGNED ) { this->assignedAction = assignedAction1; }
		std::vector<Key*> assignedKeys = {};
	Actions assignedAction;
};
//struct Direction


class KeyboardManager {
public:
	KeyboardManager(int ctrlCase);
	~KeyboardManager();
	/*
	void upKey();// keyArray 1
	void kpUpKey();// Key Array 2

	void leftKey(); // Key array 3
	void kpLeftKey();// Key array 4

	void rightKey();// Key array 5
	void kpRightKey();// Key array 6

	void downKey(); // Key Array 7
	void kpDownKey(); // Key array 8



	void upKeyUp();// keyArray 0
	void kpUpKeyUp();// Key Array 1

	void leftKeyUp(); // Key array 2
	void kpLeftKeyUp();// Key array 3

	void rightKeyUp();// Key array 4
	void kpRightKeyUp();// Key array 5

	void downKeyUp(); // Key Array 6
	void kpDownKeyUp(); // Key array 7
	*/
	void Update();
	bool isUpdated();
	int getControlCase();
	
	ActionObject* getActionObject(Actions actionToFind); // get ActionObject from Actions ENUM

	void mapKeyToAction( Key* keyPtr, Actions actionToMap); // map a key to direction
	bool isActionActive(Actions action); // check whether action is active by checking whether if any of it's assigned keys are active
	//int& getKeyArray();
	//bool getKeyValue(keyValues key); // Get whether a key is active
	//void setKeyValue(keyValues key, bool active); //set a Key to active or inactive
	//direction getDirectionFromKey(keyValues key); // get what direction a key maps to
//	bool getDirectionValue(direction inputDirection); // Get if the key that maps to that direction is active
	//void handleSDLKEYEVENT (sdl.)
private:
//	Key keyArray[(int)keyValues::LAST_COUNT] = {};// stores all keys
	std::vector<Key*> keyVector; // include key controls
	ActionObject actionObjectArray[(int)Actions::LAST_COUNT]; // stores all our actions
	const Uint8* keySDL; // SDL_GetKeyState(NULL);
	bool updated;			   // Each control set has 4 controls Up Down Left Right
	friend class PongPhysics;
	int controlCase; // If player 1 is wasd case 0, If player 2 is WASD case 1;
};
