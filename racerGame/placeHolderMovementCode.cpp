/*// W key
			case SDLK_w: // FOR user using wasd
				keyMan->upKey();
				if (c1 == 0) {// WASD

					paddle0->setPosY(paddle0->getPosY() - yRate);
					break;
				}
				else {
					paddle1->setPosY(paddle1->getPosY() - yRate);
					break;
				}
				// A key
			case SDLK_a: // FOR user using wasd
				if (c1 == 0) {
					paddle0->setPosX(paddle0->getPosX() - xRate);
					break;
				}
				else {
					paddle1->setPosX(paddle1->getPosX() - xRate);
					break;
				}
				// S key
			case SDLK_s: // FOR user using wasd
				if (c1 == 0) {
					paddle0->setPosY(paddle0->getPosY() + yRate);
					break;
				}
				else {
					paddle1->setPosY(paddle1->getPosY() + yRate);
					break;
				}
				// D key
			case SDLK_d: // FOR user using wasd
				if (c1 == 0) {
					paddle0->setPosX(paddle0->getPosX() + xRate);
					break;
				}
				else {
					paddle1->setPosX(paddle1->getPosX() + xRate);
					break;

				}



				//////////////////////////

				// KP 8 AKA UP
			case SDLK_KP_8: // FOR user using wasd
				if (c1 != 0) {
					paddle0->setPosY(paddle0->getPosY() - yRate);
					break;
				}
				else {
					paddle1->setPosY(paddle1->getPosY() - yRate);
					break;
				}
				// KP 4 AKA LEFT
			case SDLK_KP_4: // FOR user using wasd
				if (c1 != 0) {
					paddle0->setPosX(paddle0->getPosX() - xRate);
					break;
				}
				else {
					paddle1->setPosX(paddle1->getPosX() - xRate);
					break;
				}
				// KP 2 AKA DOWN
			case SDLK_KP_2: // FOR user using wasd
				if (c1 != 0) {
					paddle0->setPosY(paddle0->getPosY() + yRate);
					break;
				}
				else {
					paddle1->setPosY(paddle1->getPosY() + yRate);
					break;
				}
				// KP 6 AKA RIGHT
			case SDLK_KP_6: // KP
				if (c1 != 0) {
					paddle0->setPosX(paddle0->getPosX() + xRate);
					break;
				}
				else {
					paddle1->setPosX(paddle1->getPosX() + xRate);
					break;

				}
			default:
				break;

			}
			*/

//Place HOlder COllision Check
/*
void PongPhysics::CheckCollisions(Paddle* paddleArrayPointer[2], int paddleArraySize, Ball* ballArrayPointer[1], int ballArraySize, PongPhysics& caller) {

	//Paddle Boundary Check
	for (int i = 0; i < paddleArraySize; i++) {

		//Handle the Paddle hitting walls
		if (paddleArrayPointer[i]->r.y <= (-1 * paddleArrayPointer[i]->pHeight)) {
			// if it collides with the top wall
			paddleArrayPointer[i]->velocity = vector2d(0, 0);
			paddleArrayPointer[i]->velocity = vector2d(0, 0);
			// make it stop;
		}

		if (paddleArrayPointer[i]->r.y >= (caller.screenHeight - paddleArrayPointer[i]->pHeight)) {
			// if it collides with the bottom wall
			paddleArrayPointer[i]->velocity = vector2d(0, 0);
			paddleArrayPointer[i]->velocity = vector2d(0, 0);
			// make it stop;
		}

		if (paddleArrayPointer[i]->r.x >= (caller.screenWidth - paddleArrayPointer[i]->pWidth)) {
			// if it collides with the right Wall
			paddleArrayPointer[i]->velocity = vector2d(0, 0);
			paddleArrayPointer[i]->velocity = vector2d(0, 0);
			// make it stop;
		}

		if (paddleArrayPointer[i]->r.x <= (-1 * paddleArrayPointer[i]->pWidth)) {
			// if it collides with the left Wall
			paddleArrayPointer[i]->velocity = vector2d(0, 0);
			paddleArrayPointer[i]->velocity = vector2d(0, 0);
			// make it stop;
		}
	}

	for (int x = 0; x < ballArraySize; x++) {
		// for every object check if there's a collision



		// Time to Check Ball and Wall Collisions


		if (ballArrayPointer[x]->r.y <= (-1 * ballArrayPointer[x]->pHeight)) {
			// if it collides with the top wall
			//this->BounceBall(&ballArrayPointer[x]->velocity, true); // give it the balls initial velocity for wall boucne
			ballArrayPointer[x]->velocity = vector2d(0, 0);
			// make it stop;
		}

		if (ballArrayPointer[x]->r.y >= (caller.screenHeight - ballArrayPointer[x]->pHeight)) {
			// if it collides with the bottom wall
			 // I need to figure out how to pass struct by reference to Bounce Ball
			//this->BounceBall(&ballArrayPointer[x]->velocity, true); // give it the balls initial velocity for wall boucne
			ballArrayPointer[x]->velocity = vector2d(0, 0);
			// make it BOUNCE

		}

		if (ballArrayPointer[x]->r.x >= (caller.screenWidth - ballArrayPointer[x]->pWidth)) {
			// if it collides with the right Wall
			ballArrayPointer[x]->velocity = vector2d(0, 0);
			// make it stop;
			//this->Goal(2);
		}

		if (ballArrayPointer[x]->r.x <= (-1 * ballArrayPointer[x]->pWidth)) {
			// if it collides with the left Wall
			ballArrayPointer[x]->velocity = vector2d(0, 0);
			//this->Goal(1);
			// make it stop;
		}

	}

	//Check Ball to Paddle Collisions
	for (int i = 0; i < paddleArraySize; i++) {
		for (int x = 0; x < ballArraySize; x++) {
			// Now time to check that the ball is in the same Y region and X region of the paddle for collision to occur
													// This states that if the bottom of the ball is lower than the top of paddle we have collision|				This states that if the top of the ball is higher than bottom of paddle we collide
			if ((paddleArrayPointer[i]->r.y - paddleArrayPointer[i]->pHeight) <= (ballArrayPointer[x]->r.y + ballArrayPointer[x]->pHeight) && (paddleArrayPointer[i]->r.y + paddleArrayPointer[i]->pHeight) >= (ballArrayPointer[x]->r.y - ballArrayPointer[x]->pHeight)) {
				// now lets check if they are in the same x region
				if ((paddleArrayPointer[i]->r.x - paddleArrayPointer[i]->pWidth) <= (ballArrayPointer[x]->r.x + ballArrayPointer[x]->pWidth) && (paddleArrayPointer[i]->r.x + paddleArrayPointer[i]->pWidth) >= (ballArrayPointer[x]->r.x - ballArrayPointer[x]->pWidth)) {
					// So it has hit the paddle
					//this->BounceBall(&ballArrayPointer[x]->velocity, false);
				}


			}
		}
	}

	//if ball collision
	//this->BounceBall();
}
*/