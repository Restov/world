#include "Sheep.h"
#include <utility>

Sheep::Sheep(int my_x, int my_y) : Alive() {
	x = my_x;
	y = my_y;
	range = 1;
	if(rand()%2 == 0){
		direction.first = 1;
		horizontal = true;
	} else{
		direction.first = -1;
		horizontal = false;
	}
	if(rand()%2 == 0){
		direction.second = 1;
	} else{
		direction.second = -1;
	}
	turn = true;
}

/*int Sheep::get_range(){
	return range;
}*/

std::pair<int,int> Sheep::move(Object*** map , int max_x, int max_y){
	std::pair<int,int> coords;
	coords.first = x;
	coords.second = y;
	if(turn == false){
		return coords;
	}

	int new_x;
	int new_y;
	int repeat = 0;

	while(repeat < 2){
		new_x = x + direction.first*range;
		new_y = y + direction.second*range;
		if(new_x >= 0 && new_x < max_x){
			if(map[new_x][y] == NULL && horizontal == true){
				coords.first = new_x;
				x = new_x;
				turn = false;
				return coords;
			} else{
				if(horizontal == true){
					direction.first *= -1;
					horizontal = false;
				}
			}
		} else{
			direction.first *= -1;
			horizontal = false;
		}
		if(new_y >= 0 && new_y < max_y){
			if(map[x][new_y] == NULL && horizontal == false){
				coords.second = new_y;
				y = new_y;
				turn = false;
				return coords;
			} else{
				if(horizontal == false){
					direction.second *= -1;
					horizontal = true;
				}
			}
		} else{
			direction.second *= -1;
			horizontal = true;
		}
		repeat++;
	}
	return coords;
}

void Sheep::draw(sf::RenderWindow* window, int size){

	int start_x = size * x;
	int start_y = size * y;
	sf::Texture Sheep;
	Sheep.loadFromFile("wolf_v2.png");
	sf::Sprite Sheepsp;
	Sheepsp.setTexture(Sheep);
	Sheepsp.setPosition(start_x + size / 4, start_y + size / 4);
	window->draw(Sheepsp);
}