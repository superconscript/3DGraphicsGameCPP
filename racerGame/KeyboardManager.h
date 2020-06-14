#pragma once
class PongPhysics;
class KeyboardManager {
public:
	KeyboardManager(int ctrlCase);
	~KeyboardManager();

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

	void Update();
	bool isUpdated();
	int getControlCase();
	//int& getKeyArray();
	int getKeyValue(int index);

private:
	int keyArray[8] = {};// 8 ints that represent True / False values for two control sets
	bool updated;			   // Each control set has 4 controls Up Down Left Right
	friend class PongPhysics;
	int controlCase; // If player 1 is wasd case 0, If player 2 is WASD case 1;
};
