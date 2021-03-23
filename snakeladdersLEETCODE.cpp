#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

//COLOR ATTRIBUTES
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */



#define RESET   "\033[0m" //back to normal

//GAME FUNCTIONS
void display_top(const int& dice_rolls, const int& player_pos, const bool& player_state, const int& dice_val);
void display_bottom(const bool& ladder, const bool& snake, const int& player_pos, const bool& player_state);

string state(const int& player_state);

int roll_dice();
bool player_input();

bool ladder_check(int& player_pos);
bool snake_check(int& player_pos);

//GAME CONSTANTS
const int START_POS = 0;
const int FINISH = 100;

const int ROAMFREE = 0; //false
const int ATHOME = 1; //true

//LADDERS
const int LADDER1_START = 5;
const int LADDER1_END = 10;

const int LADDER2_START = 30;
const int LADDER2_END = 45;

const int LADDER3_START = 55;
const int LADDER3_END = 70;

//SNAKES
const int SNAKE1_HEAD = 20;
const int SNAKE1_TAIL = 7;

const int SNAKE2_HEAD = 40;
const int SNAKE2_TAIL = 25;

const int SNAKE3_HEAD = 80;
const int SNAKE3_TAIL = 30;

int main()
{
	//player stats
	int player_pos;
	bool player_state;
	bool finished;
	bool player_inp;

	//game stats
	int dice_val;
	int dice_rolls;

	bool ladder;
	bool snake;

	//initializations
	player_pos = START_POS;
	player_state = ATHOME;
	finished = false;
	dice_rolls = 0;
	dice_val = 0;

	ladder = false;
	snake = false;
	player_inp = false;

	srand(time(NULL));

	//GAME

	while (!finished) {
		display_top(dice_rolls, player_pos, player_state, dice_val);

		//check for continue or exit
		player_inp = player_input();
		if (player_inp == true) {
			exit(1);
		}

		if (player_state == ROAMFREE) {
			dice_val = roll_dice();
			dice_rolls += 1;

			if (player_pos + dice_val < FINISH) {
				player_pos += dice_val;
			}
			else if (player_pos + dice_val == FINISH) {
				finished = true;
			}
		}
		else {
			dice_val = roll_dice();
			dice_rolls += 1;
			if (dice_val == 6) {
				player_state = ROAMFREE;
			}

		}

		ladder = ladder_check(player_pos);
		snake = snake_check(player_pos);

		display_bottom(ladder, snake, player_pos, player_state);
	}

	cout << BOLDGREEN << " Hurray you won!" << RESET << endl;

	return 0;
}

void display_top(const int& dice_rolls, const int& player_pos, const bool& player_state, const int& dice_val) {
	cout << " ----------------- | Total Prior Dice Rolls: " << BOLDGREEN << dice_rolls << RESET << "| ------------------ " << endl;
	cout << " ----------------- |       You Rolled: " << BOLDGREEN << dice_val << RESET << "       | ------------------ \n" << endl;
	cout << " Ladders: [ (" << LADDER1_START << ", " << LADDER1_END << "), (" << LADDER2_START << ", " << LADDER2_END << "), (" << LADDER3_START << ", " << LADDER3_END << ") ]" << endl;
	cout << " Snakes:  [ (" << SNAKE1_HEAD << ", " << SNAKE1_TAIL << "), (" << SNAKE2_HEAD << ", " << SNAKE1_TAIL << "), (" << SNAKE3_HEAD << ", " << SNAKE1_TAIL << ") ]" << endl;
	cout << endl;
	cout << BOLDBLUE << " Current Position: " << player_pos << RESET << endl;
	cout << " Current State: " << state(player_state) << endl;
}

void display_bottom(const bool& ladder, const bool& snake, const int& player_pos, const bool& player_state) {
	cout << "\n\n";
	cout << BOLDWHITE << " After the dice is rolled: " << RESET << endl;
	cout << " Current Position: " << player_pos;

	if (ladder) {
		cout << BOLDGREEN << " - Found a ladder! " << RESET << endl;
	}
	else if (snake) {
		cout << BOLDRED << " - Bitten by a snake! " << RESET << endl;
	}
	else {
		cout << endl;
	}

	cout << " Current State: " << state(player_state) << endl;

	cout << " --------------------------------------------------------------- \n" << endl;
}

string state(const int& player_state) {
	string state;
	if (player_state == ROAMFREE) {
		state = "Roam Free";
	}
	else {
		state = "At Home";
	}

	return state;
}

bool player_input() {
	int input;
	bool state;

	input = 0;

	while (input != 1 && input != 2) {
		cout << " Press 1 to roll a die, and 2 to exit: ";
		cin >> input;

		if (input == 1) {
			state = 0; //NOT EXIT
		}
		if (input == 2) {
			cout << "Good bye!";
			state = 1; //EXIT
		}
	}

	return state;
}

int roll_dice() {
	int roll = rand() % 6 + 1;
	return roll;
}

bool ladder_check(int& player_pos) {
	switch (player_pos) {
	case LADDER1_START:
		player_pos = LADDER1_END;
		return true;
		break;
	case LADDER2_START:
		player_pos = LADDER2_END;
		return true;
		break;
	case LADDER3_START:
		player_pos = LADDER3_END;
		return true;
		break;
	default:
		break;
	}

	return false;
}

bool snake_check(int& player_pos) {
	switch (player_pos) {
	case SNAKE1_HEAD:
		player_pos = SNAKE1_TAIL;
		return true;
		break;
	case SNAKE2_HEAD:
		player_pos = SNAKE2_TAIL;
		return true;
		break;
	case SNAKE3_HEAD:
		player_pos = SNAKE3_TAIL;
		return true;
		break;
	default:
		break;
	}

	return false;
}