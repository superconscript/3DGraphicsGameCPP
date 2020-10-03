#include "KeyboardManager.h"
// Control == 1 means WASD control set
//For KeyDown events

//UP
KeyboardManager::KeyboardManager(int ctrlCase) {
	this->controlCase = ctrlCase;
	this->updated = true;
	//*(SDL_GetKeyboardState(NULL))
	this->keySDL = SDL_GetKeyboardState(NULL);
/// Set Up Basic ActionObjects
	for (int x = 0; x < (int)Actions::LAST_COUNT; x++) {
		this->actionObjectArray[x].assignedAction = (Actions)x; // make sure we have all our ActionObjects assigned to an action
	}
	//Now lets assign keys to these action objects
//FORWARD
	Key* key_W = new Key(SDL_Scancode::SDL_SCANCODE_W);
	this->keyVector.push_back(key_W);
	Key* key_ArrowKeyUp = new Key(SDL_Scancode::SDL_SCANCODE_UP);
	this->keyVector.push_back(key_ArrowKeyUp);

	mapKeyToAction(key_W, Actions::MOVE_FORWARD);
	mapKeyToAction(key_ArrowKeyUp, Actions::MOVE_FORWARD);
//BACKWARD
	Key* key_S = new Key( SDL_Scancode::SDL_SCANCODE_S );
	this->keyVector.push_back(key_S);
	Key* key_ArrowKeyDown = new Key(SDL_Scancode::SDL_SCANCODE_DOWN);
	this->keyVector.push_back(key_ArrowKeyDown);

	mapKeyToAction(key_S, Actions::MOVE_BACKWARD);
	mapKeyToAction(key_ArrowKeyDown, Actions::MOVE_BACKWARD);
//LEFT
	Key* key_A = new Key(SDL_Scancode::SDL_SCANCODE_A);
	this->keyVector.push_back(key_A);
	Key* key_ArrowKeyLeft = new Key(SDL_Scancode::SDL_SCANCODE_LEFT);
	this->keyVector.push_back(key_ArrowKeyLeft);

	mapKeyToAction(key_A, Actions::MOVE_LEFT);
	mapKeyToAction(key_ArrowKeyLeft, Actions::MOVE_LEFT);

//Right
	Key* key_D = new Key(SDL_Scancode::SDL_SCANCODE_D);
	this->keyVector.push_back(key_D);
	Key* key_ArrowKeyRight = new Key(SDL_Scancode::SDL_SCANCODE_RIGHT);
	this->keyVector.push_back(key_ArrowKeyLeft);

	mapKeyToAction(key_D, Actions::MOVE_RIGHT);
	mapKeyToAction(key_ArrowKeyRight, Actions::MOVE_RIGHT);

//UP
	Key* key_SpaceBar = new Key(SDL_Scancode::SDL_SCANCODE_SPACE);
	this->keyVector.push_back(key_SpaceBar);
	Key* key_KeyPadSeven = new Key(SDL_Scancode::SDL_SCANCODE_KP_7);
	this->keyVector.push_back(key_KeyPadSeven);

	mapKeyToAction(key_SpaceBar, Actions::MOVE_UP);
	mapKeyToAction(key_KeyPadSeven, Actions::MOVE_UP);

	//Down
	Key* key_LeftControl = new Key(SDL_Scancode::SDL_SCANCODE_LCTRL);
	this->keyVector.push_back(key_LeftControl);
	Key* key_KeyPadNine = new Key(SDL_Scancode::SDL_SCANCODE_KP_9);
	this->keyVector.push_back(key_KeyPadNine);

	mapKeyToAction(key_LeftControl, Actions::MOVE_DOWN);
	mapKeyToAction(key_KeyPadNine, Actions::MOVE_DOWN);

	//ROTATION
//YAW
	//LEFT 
	Key* key_Q = new Key(SDL_Scancode::SDL_SCANCODE_Q);
	this->keyVector.push_back(key_Q);
	Key* key_KeyPadLeft = new Key(SDL_Scancode::SDL_SCANCODE_KP_4);
	this->keyVector.push_back(key_KeyPadLeft);

	mapKeyToAction(key_Q, Actions::ROTATE_LEFT);
	mapKeyToAction(key_KeyPadLeft, Actions::ROTATE_LEFT);
	//RIGHT
	Key* key_E = new Key(SDL_Scancode::SDL_SCANCODE_E);
	this->keyVector.push_back(key_E);
	Key* key_KeyPadRight = new Key(SDL_Scancode::SDL_SCANCODE_KP_6);
	this->keyVector.push_back(key_KeyPadRight);

	mapKeyToAction(key_E, Actions::ROTATE_RIGHT);
	mapKeyToAction(key_KeyPadRight, Actions::ROTATE_RIGHT);
//PITCH
		//UP
	Key* key_I = new Key(SDL_Scancode::SDL_SCANCODE_I);
	this->keyVector.push_back(key_I);
	Key* key_KeyPadUp = new Key(SDL_Scancode::SDL_SCANCODE_KP_8);
	this->keyVector.push_back(key_KeyPadUp);

	mapKeyToAction(key_I, Actions::ROTATE_UP);
	mapKeyToAction(key_KeyPadUp, Actions::ROTATE_UP);
	//DOWN
	Key* key_O = new Key(SDL_Scancode::SDL_SCANCODE_O);
	this->keyVector.push_back(key_O);
	Key* key_KeyPadDown = new Key(SDL_Scancode::SDL_SCANCODE_KP_2);
	this->keyVector.push_back(key_KeyPadDown);

	mapKeyToAction(key_O, Actions::ROTATE_DOWN);
	mapKeyToAction(key_KeyPadDown, Actions::ROTATE_DOWN);


}

ActionObject* KeyboardManager::getActionObject(Actions actionToFind) {
	for (int i = 0; i < (int)Actions::LAST_COUNT; i++) { // iterate through our actions til we find a match
		if (actionObjectArray[i].assignedAction == actionToFind) {
		//	std::string kString = std::to_string((int)actionObjectArray[i].assignedAction);
			//std::string kString = std::to_string(;
		//	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "keyScanCode", kString.c_str(), NULL);
			return &actionObjectArray[i]; // Return a pointer to the matching action
		}
	}
}

void KeyboardManager::mapKeyToAction(Key* keyPtr, Actions actionToMap) {
	getActionObject(actionToMap)->assignedKeys.push_back(keyPtr); // Add our key to the Actions assigned keys.
}

bool KeyboardManager::isActionActive(Actions action) {
	// Check if any of the keys are active to determine if action is active.
	ActionObject* actionPtr = getActionObject(action);
//	SDL_Scancode key
	for (int i = 0; i < actionPtr->assignedKeys.size(); i++) {
		/*if (actionPtr->assignedKeys[i]->active == true) {
			return true;
		}
		*/
		//std::string kString = std::to_string(actionPtr->assignedKeys[i]->keyScanCode);
		//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "keyScanCode", kString.c_str(), NULL);
		if (keySDL[actionPtr->assignedKeys[i]->keyScanCode]) { // used the SDL_GetKeyboardState /// This is crashing becaus keyScanCode is a random negative value;
			return true;
		}
	}
	return false;
}

void KeyboardManager::Update() {
	this->updated = false;
}
bool KeyboardManager::isUpdated() {
	return updated;
}
/*
int & KeyboardManager::getKeyArray(){
	int (&keyRef)[8] = keyArray;
	return &keyRef;
}
*/


/*
bool KeyboardManager::getKeyValue(keyValues key) {
	//int falseArray[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };
	//bool returnKeyValue
	for (int i = 0; i < (int)keyValues::LAST_COUNT; i++) {
		if (keyArray[i].keyName == key) {
			return true;// Create name each key in our key Array
		}
	}
		return false;
	//return falseArray[index];

}
*/

/*
void KeyboardManager::setKeyValue(keyValues key, bool active) {
	for (int i = 0; i < (int)keyValues::LAST_COUNT; i++) {
		if (keyArray[i].keyName == key) {
			keyArray[i].active = active;// Create name each key in our key Array
		}
	}
}
*/

/*
direction KeyboardManager::getDirectionFromKey(keyValues key) {
	for (int i = 0; i < (int)keyValues::LAST_COUNT; i++) {
		if (keyArray[i].keyName == key) {
			return keyArray[i].keyDirection; // Create name each key in our key Array
		}
	}
}
*/
/*
bool KeyboardManager::getDirectionValue(direction inputDirection) { // check whether this direction is active
	for (int i = 0; i < (int)keyValues::LAST_COUNT; i++) {
		if (keyArray[i].keyDirection == inputDirection) { // find key that maps to htis direction
			return keyArray[i].active;
		}// Create name each key in our key Array
	}

}
*/
/*
void KeyboardManager::handleSDLKEYEVENT() {
/case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
			// W key
		case SDLK_w: // FOR user using wasd
			keyMan->upKey();
			break;

			// A key
		case SDLK_a: // FOR user using wasd
			keyMan->leftKey();
			break;
			// S key
		case SDLK_s: // FOR user using wasd
			keyMan->downKey();
			break;
			// D key
		case SDLK_d: // FOR user using wasd
			keyMan->rightKey();

			break;
}
*/
int KeyboardManager::getControlCase() {
	return controlCase;
}
/*
void KeyboardManager::upKey() {
		this->keyArray[0].active = true; //(the W key pressed)4
		this->updated = true;
	}

void KeyboardManager::kpUpKey() {

		this->keyArray[1].active = true; //the KP 8 was pressed;
		this->updated = true;
	}
//Left
void KeyboardManager::leftKey() {
		this->keyArray[2].active = 1; //(the A key pressed)
		this->updated = true;
	}
void	KeyboardManager::kpLeftKey(){
		this->keyArray[3] = 1; //the KP 4 was pressed;
		this->updated = true;
	}
//Right
void KeyboardManager::rightKey() {
		this->keyArray[4] = 1; //(the D key pressed)
		this->updated = true;
	}
void KeyboardManager::kpRightKey() {
		this->keyArray[5] = 1; //the KP 6 was pressed;
		this->updated = true;
	}
//Down
void KeyboardManager::downKey() {
		this->keyArray[6] = 1; //(the S key pressed)
		this->updated = true;
	}
void KeyboardManager::kpDownKey(){
		this->keyArray[7] = 1; //the KP 2 was pressed;
		this->updated = true;
	}


// For KeyUP events
//UP
void KeyboardManager::upKeyUp() {
	this->keyArray[0] = 0; //(the W key released)4
	this->updated = true;
}

void KeyboardManager::kpUpKeyUp() {

	this->keyArray[1] = 0; //the KP 8 was released;
	this->updated = true;
}
//Left
void KeyboardManager::leftKeyUp() {
	this->keyArray[2] = 0; //(the A key released)
	this->updated = true;
}
void	KeyboardManager::kpLeftKeyUp() {
	this->keyArray[3] = 0; //the KP 4 was released;
	this->updated = true;
}
//Right
void KeyboardManager::rightKeyUp() {
	this->keyArray[4] = 0; //(the D key released)
	this->updated = true;
}
void KeyboardManager::kpRightKeyUp() {
	this->keyArray[5] = 0; //the KP 6 was released;
	this->updated = true;
}
//Down
void KeyboardManager::downKeyUp() {
	this->keyArray[6] = 0; //(the S key released)
	this->updated = true;
}
void KeyboardManager::kpDownKeyUp() {
	this->keyArray[7] = 0; //the KP 2 was released;
	this->updated = true;
}
*/
