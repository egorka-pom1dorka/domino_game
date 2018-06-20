#pragma once
#include "Game.h"
#include <ctime>

Game::Game() {
	market = new Vector;
	player = new Vector;
	II = new Vector;
	field = new Vector;
	this->init();
}

Game::~Game() {
	delete market;
	delete player;
	delete II;
	delete field;
}

void Game::init() {
	this->generateBones();
	this->selectIIBones();
	this->selectPlayerBones();
	int first = this->findFirstTurn();

	if (first == Game::II_TURN) {
		cout << "Computer make the first turn\n";
	}
	else {
		cout << "Your turn is first\n";
	}

	this->startGame(first);
}

int Game::getRandomInteger(int diff, int offset) {
	srand(time(NULL));
	int randValue;
	return randValue = rand() % diff + offset;
}

int Game::getPlayerInput(int from, int to) {
	cout << "Input integer [" << from << ", " << to << "]\n";
	int n;
	cin >> n;
	while (n < from || n > to) {
		cout << "Incorrect number, try again\n";
		cin >> n;
	}
	return n;
}

void Game::generateBones() {
	for(int i = 0; i <= Bone::MAX_NUMBER; i++){
		for (int j = i; j <= Bone::MAX_NUMBER; j++) {
			Bone bone(i, j);
			market->push_back(Bone(i, j));
		}
	}
}

void Game::selectIIBones() {
	int randValue; 
	Bone ptr;
	for (int i = 0; i < Game::START_BONES_AMOUNT; i++){
		randValue = this->getRandomInteger(Game::BONES_AMOUNT - i, 0);
		ptr = market->getBone(randValue);
		II->push_back(ptr);
		market->remove(randValue);
	}
}

void Game::selectPlayerBones() {
	int randValue;
	Bone ptr;
	for (int i = 0; i < Game::START_BONES_AMOUNT; i++) {
		randValue = this->getRandomInteger(Game::BONES_AMOUNT - Game::START_BONES_AMOUNT - i, 0);
		ptr = market->getBone(randValue);
		player->push_back(ptr);
		market->remove(randValue);
	}
}

int Game::findFirstTurn() {
	int findable = 1;
	Bone b1 ,b2;
	
	while (findable <= 6) {
		for (int i = 0; i < Game::START_BONES_AMOUNT; i++) {
			b1 = player->getBone(i);
			if (b1.left == findable && b2.right == findable) {
				return Game::PLAYER_TURN;
			}

			b2 = II->getBone(i);
			if (b2.left == findable && b2.right == findable) {
				return Game::II_TURN;
			}
		}
		findable++;
	}

	cout << "Nobody haven't any bone with the same numbers\n";
	return Game::PLAYER_TURN;
}

void Game::startGame(int who) {
	bool isWinner = false;
	int pointer;

	while (!isWinner) {
		if (field->size()) {
			cout << "Field: \n";
			field->print();
		}

		this->turn(who);

		if (who == Game::PLAYER_TURN) {
			who = Game::II_TURN;
			isWinner = this->isWin(player);
			pointer = Game::PLAYER_WIN;
		}
		else if (who == Game::II_TURN) {
			who = Game::PLAYER_TURN;
			isWinner = this->isWin(II);
			pointer = Game::II_WIN;
		}
	}

	this->finishGame(pointer);
}

void Game::turn(int who) {
	bool isTurnStart = false, isTurnEnd = false;
	int len = 0, n, amount = 0;
	Bone ptr;

	if(who == Game::PLAYER_TURN) {
		cout << "Your turn\nMy bones:\n";
		player->print();
		while (!isTurnEnd || !isTurnStart) {
			amount = 0;
			len = player->size();
			isTurnStart = this->isTurnAvailableInStart(player, len);
			isTurnEnd = this->isTurnAvailableInEnd(player, len);

			if (!isTurnEnd && !isTurnStart) {
				cout << "You can't do anything, you must take one bone from market\n";
				ptr = this->getBoneFromMarket();
				player->push_back(ptr);
				player->print();
			}
			else {
				break;
			}

		}
		bool flag = false;
		while (!flag) {
			n = getPlayerInput(0, len - 1);
			ptr = player->getBone(n);
			flag = this->turnFromPlayer(ptr);
			if (!flag) {
				cout << "Choose another bone\n";
			}
		}
		player->remove(n);
	}
	else if (who == Game::II_TURN) {
		cout << "Computer's turn:\n";
		while (!isTurnEnd && !isTurnStart) {
			len = II->size();
			isTurnStart = this->isTurnAvailableInStart(II, len);
			isTurnEnd = this->isTurnAvailableInEnd(II, len);
			ptr = this->getBoneFromMarket();
			II->push_back(ptr);
		}
		bool flag = false;
		while (!flag) {
			flag = this->turnFromII();
		}
	}
	
}

bool Game::turnFromII() {
	Bone ptr;
	int len = II->size(), fsize = field->size();

	if (!fsize) {
		int i = this->getRandomInteger(len - 1, 0);
		ptr = II->getBone(i);
		field->push_back(ptr);
		II->remove(i);
		return true;
	}
	else {
		Bone start = field->getBone(0);
		Bone end = field->getBone(fsize - 1);

		while (true) {
			int i = this->getRandomInteger(len - 1, 0);
		
			ptr = II->getBone(i);
			if (start.left == ptr.left || start.left == ptr.right) {
				if (ptr.right != start.left) {
					ptr.swapData();
				}
				field->unshift(ptr);
				II->remove(i);
				return true;
			}
			else if (end.right == ptr.left || end.right == ptr.right) {
				if (end.right != ptr.left) {
					ptr.swapData();
				}
				field->push_back(ptr);
				II->remove(i);
				return true;
			}
		}
	}
	return false;
}

Bone Game::getBoneFromMarket() {
	int randValue, len = market->size();
	Bone ptr;

	while (true) {
		randValue = this->getRandomInteger(len, 0);
		ptr = market->getBone(randValue);
		if (ptr.left && ptr.right) {
			market->remove(randValue);
			return ptr;
		}
	}
}

bool Game::isTurnAvailableInStart(Vector * v, int n) {
	Bone temp;

	if (!field->size()) {
		return true;
	}

	Bone start = field->getBone(0);

	for (int i = 0; i < n; i++) {
		temp = v->getBone(i);
		if (start.left == temp.left || start.left == temp.right) {
			return true;
		}
	}
	return false;
}

bool Game::isTurnAvailableInEnd(Vector * v, int n) {
	if (!field->size()) {
		return true;
	}

	Bone start = field->getBone(0);
	int last = field->size() - 1;
	Bone end = field->getBone(last), temp;

	for (int i = 0; i < n; i++) {
		temp = v->getBone(i);
		if (end.right == temp.left || end.right == temp.right) {
			return true;
		}
	}
	return false;
}

bool Game::turnFromPlayer(Bone b) {
	int len = field->size(), n;
	if (!len) {
		field->push_back(b);
		return true;
	}
	
	Bone start = field->getBone(0);
	Bone end = field->getBone(len - 1), temp;

	if (start.left != b.left && start.left != b.right && end.right != b.right && end.right != b.left) {
		return false;
	}
	else if ((start.left == b.left || start.left == b.right) && (end.right == b.right || end.right == b.left)) {
		cout << "Choose in what way you want to put your bone, start or end\n";
		n = this->getPlayerInput(0, 1);
		if (n == 1) {
			if (end.right != b.left) {
				b.swapData();
			}
			field->push_back(b);
		}
		else {
			if (b.right != start.left) {
				b.swapData();
			}
			field->unshift(b);
		}
		return true;
	}
	else if(start.left == b.left || start.left == b.right){
		if (b.right != start.left) {
			b.swapData();
		}
		field->unshift(b);
		return true;
	}
	else if (end.right == b.right || end.right == b.left) {
		if (end.right != b.left) {
			b.swapData();
		}
		field->push_back(b);
		return true;
	}

	return false;
}


bool Game::isWin(Vector * v) {
	int n = v->size();
	return n ? false : true;
}

void Game::finishGame(int who) {
	switch (who) {
	case Game::PLAYER_WIN: {
		cout << "Win player, grats\n";
		break;
	}
	case Game::II_WIN: {
		cout << "Win computer, you are looser\n";
		break;
	}
	case Game::DRAW: {
		cout << "There is draw\n";
		break;
	}
	}
}