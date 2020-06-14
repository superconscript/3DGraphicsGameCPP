#pragma once
class math {
	math();
		~math();
};
struct vector2d {

	//vector2d(int x1 = 0, int y2 = 0);
	vector2d(double x1 = 0, double y2 = 0);
	double x;
	double y;
	/*void addVectors(vector2d* VectorToChange, vector2d otherVector) {
		VectorToChange->x += otherVector.x;
		VectorToChange->y += otherVector.y;
	}
	*/
};