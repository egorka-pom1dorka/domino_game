#pragma once
#include "Exception.h"
#include "Bone.h"
#include "Vector.h"

class Game {
	Vector * market;
	Vector * player;
	Vector * II;
	Vector * field;
public:
	static const int PLAYER_TURN = 331;
	static const int II_TURN = 13;
	static const int BONES_AMOUNT = 28;
	static const int EACH_BONE_VALUE_AMOUNT = 8;
	static const int START_BONES_AMOUNT = 7;
	static const int PLAYER_WIN = -21;
	static const int II_WIN = 4;
	static const int DRAW = 9;
	Game();
	~Game();
	int getRandomInteger(int diff, int offset);
	void init();
	void generateBones();
	void selectPlayerBones();
	void selectIIBones();
	int findFirstTurn();
	bool isTurnAvailableInStart(Vector *, int n);
	bool isTurnAvailableInEnd(Vector *, int n);
	void startGame(int);
	Bone getBoneFromMarket();
	void turn(int );
	bool isWin(Vector * );
	bool turnFromPlayer(Bone);
	bool turnFromII();
	void finishGame(int);
	int getPlayerInput(int from, int to);
};