#include "KeyboardManager.h"
// Control == 1 means WASD control set
//For KeyDown events

//UP
KeyboardManager::KeyboardManager(int ctrlCase) {
	this->controlCase = ctrlCase;
	this->updated = true;
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
int KeyboardManager::getKeyValue(int index) {
	//int falseArray[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };
	return keyArray[index];
	//return falseArray[index];
}
int KeyboardManager::getControlCase() {
	return controlCase;
}
void KeyboardManager::upKey() {
		this->keyArray[0] = 1; //(the W key pressed)4
		this->updated = true;
	}

void KeyboardManager::kpUpKey() {

		this->keyArray[1] = 1; //the KP 8 was pressed;
		this->updated = true;
	}
//Left
void KeyboardManager::leftKey() {
		this->keyArray[2] = 1; //(the A key pressed)
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

