/*
for eight-directional movement

put diagonal tile collision and regular tile collision in separate functions so that diagonal can call the regular one if needed

if(collision) {
	if(tile collided with is diagonal)
		diagonalTileCollisionFunction()
		
}

diagonalTileCollisionFunction() {
	if(player is above and to the right of the obstacle to start with) {
		if(obstacle slopes downwards left to right) {
			if(actual collision occurs) {
				if(player is moving straight left) {
					straight left movement is valid
					adjust y (collision occurs until y + height is less than the y of the obstacle)
				}
				else if(player is moving straight down) {
					straight down movement is valid
					adjust x (collision occurs until y + height is greater than the y + height of the obstacle)
				}
				else if(player is moving down and left) {
					adjust x (collision occurs)
					adjust y (collision occurs
				}
			}
		}
		else
			handle like a normal collision
	}
	else if(player is above and to the left of the obstacle + obstacle width to start with) {
		if(obstacle slopes upwards left to right) {
			if(actual collision occurs) {
				if(player is moving straight right) {
					straight right movement is valid
					adjust y (collision occurs until y + height is less than the y of the obstacle)
				}
				else if(player is moving straight down) {
					straight down movement is valid
					adjust x (collision occurs until y + height is greater than the y + height of the obstacle)
				}
				else if(player is moving down and right) {
					adjust x (collision occurs)
					adjust y (collision occurs)
				}
			}
		}
		else
			handle like a normal collision
	}
	else if(player is below and to the right of the obstacle to start with) {
		if(obstacle slopes upwards left to right) {
			if(actual collision occurs) {
				if(player is moving straight left) {
					straight left movement is valid
					adjust y (collision occurs until y is less than the y + height of the obstacle)
				}
				else if(player is moving straight up) {
					straight up movement is valid
					adjust x (collision occurs until y is less than the y of the obstacle)
				}
				else if(player is moving up and left) {
					adjust x (collision occurs)
					adjust y (collision occurs)
				}
			}
		}
		else
			handle like a normal collision
	}
	else if(player is below and to the left of the obstacle + obstacle width to start with) {
		if(obstacle slopes downwards left to right) {
			if(actual collision occurs) {
				if(player is moving straight right) {
					straight right movement is valid
					adjust y (collision occurs until y is less than the y + height of the obstacle)
				}
				else if(player is moving straight up) {
					straight up movement is valid
					adjust x (collision occurs until y is less than the y of the obstacle)
				}
				else if(player is moving up and right) {
					adjust x (collision occurs)
					adjust y (collision occurs)
				}
			}
		}
		else
			handle like a normal collision
	}
	else
		handle like a normal collision
}

regularTileCollisionFunction() {
	if(player is above and to the left of the obstacle) {
		if(the player's distance on the x axis to the obstacle is shorter than the distance on the y axis) {
			movement to the right is valid
			adjust y (collision occurs)
		}
		else if(the player's distance on the y axis to the obstacle is shorter than the distance on the x axis) {
			movement downwards is valid
			adjust x (collision occurs)
		}
		else if(the distances are equal) {
			adjust x (collision occurs)
			adjust y (collision occurs)
		}
	{
	else if(player is above and alongside the obstacle on the x axis) {
		if(player is moving down and to the right) {
			movement to the left is valid
			adjust y (collision occurs until player x is greater than obstacle x + width)
		}
		else if(player is moving straight down) {
			adjust y (collision occurs)
		}
		else if(player is moving down and to the left) {
			movement to the right is valid
			adjust y (collision occurs until player x + width is less than obstacle width
		}
	}
	else if(player is above and to the right of the obstacle) {

	}
	else if(player is to the right and alongside the obstacle on the y axis) {
		
	}
	else if(player is under and to the right of the obstacle) {

	}
	else if(player is under and alongside the obstacle on the x axis) {
		
	}
	else if(player is under and to the left of the obstacle) {

	}
	else if(player is to the left and alongside the obstacle on the y axis) {
		
	}
}
*/
