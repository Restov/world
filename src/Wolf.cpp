#include "Wolf.h"
#include <utility>

Wolf::Wolf(int my_x, int my_y) : Alive() {
	x = my_x;
	y = my_y;
	range = 1;
	max_hunger = 20;

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

/*int Wolf::get_range(){
	return range;
}*/

std::pair<int,int> Wolf::try_to_hunt(Object*** vision , int max_x, int max_y){
	std::pair<int,int> coords;
	coords.first = x;
	coords.second = y;
	hunt = false;

	int vis_size = range * 2 + 1;
	int center = range;

	for(int i = -1; i < 2; ++i){
		if( x+i < 0 || x+i >= max_x || x+i == x){
			continue;
		}
		if(vision[center+i][center] != NULL){
			if(vision[center+i][center]->is_Alive){
				hunt = true;
				coords.first = x+i;
				coords.second = y;
				return coords;
			}
		}
	}

	for(int j = -1; j < 2; ++j){
		if( y+j < 0 || y+j >= max_y || y+j == y){
			continue;
		}
		if(vision[center][center+j] != NULL){
			if(vision[center][center+j]->is_Alive){	
				hunt = true;
				coords.first = x;
				coords.second = y+j;
				return coords;
			}
		}
	}
	// if(hunt){
		// std::cout << "gonna kill " << coords.first << " " << coords.second << std::endl;
	// }
	return coords;
}

std::pair<int,int> Wolf::default_move(Object*** vision , int max_x, int max_y){
	std::pair<int,int> coords;
	coords.first = x;
	coords.second = y;

	int vis_size = range * 2 + 1;
	int center = range;
	int new_x;
	int new_y;
	int repeat = 0;

	while(repeat < 2){
		new_x = x + direction.first;
		new_y = y + direction.second;
		if(new_x >= 0 && new_x < max_x){
			if(vision[center+direction.first][center] == NULL && horizontal == true){
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
			if(vision[center][center+direction.second] == NULL && horizontal == false){
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

std::pair<int,int> Wolf::move(Object*** vision , int max_x, int max_y){
	std::pair<int,int> coords;
	coords.first = x;
	coords.second = y;
	if(turn == false){
		return coords;
	}

	if(hunger == max_hunger){
		dead = true;
		return coords;
	}

	// std::cout << "try_to_hunt " << std::endl;
	coords = try_to_hunt(vision, max_x, max_y);
	if(hunt){
		turn = false;
		hunt = false;
		hunger = 0;
		x = coords.first;
		y = coords.second;
		// std::cout<<"--------------------"<<std::endl;
		return coords;
	}
	hunger++;
	std::cout<< "hunger = " << hunger <<std::endl;
	// std::cout << "hunt failed " << std::endl;
	
	coords = default_move(vision, max_x, max_y);

	return coords;
}

void Wolf::draw(sf::RenderWindow* window, int size){

	int start_x = size * x;
	int start_y = size * y;
	sf::Texture wolf;
	wolf.loadFromFile("wolf_v3.png");
	sf::Sprite wolfsp;
	wolfsp.setTexture(wolf);
	wolfsp.setPosition(start_x+size/4, start_y+size/4);
	window->draw(wolfsp);
}