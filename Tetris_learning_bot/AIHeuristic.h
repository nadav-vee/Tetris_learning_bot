#pragma once
#include "const.h"
#include "Stack.h"

class AIHeuristic
{
public:
	AIHeuristic(float scalar)
		: m_scalar(scalar)
	{

	}

	virtual float GetScore(Stack* tetrisBoard, Stack* BoardCopy) = 0;
	float m_scalar;
};

class AIHeuristic_AggregateHeight : public AIHeuristic
{
public:
	using AIHeuristic::AIHeuristic;
	virtual float GetScore(Stack* tetrisBoard, Stack* BoardCopy);
};


class AIHeuristic_GameLoss : public AIHeuristic
{
public:
	using AIHeuristic::AIHeuristic;
	virtual float GetScore(Stack* tetrisBoard, Stack* BoardCopy);
};

class AIHeuristic_Holes : public AIHeuristic
{
public:
	using AIHeuristic::AIHeuristic;
	virtual float GetScore(Stack* tetrisBoard, Stack* BoardCopy);
};


class AIHeuristic_Blockade : public AIHeuristic
{
public:
	using AIHeuristic::AIHeuristic;
	virtual float GetScore(Stack* tetrisBoard, Stack* BoardCopy);
};

class AIHeuristic_Bumpiness : public AIHeuristic
{
public:
	using AIHeuristic::AIHeuristic;
	virtual float GetScore(Stack* tetrisBoard, Stack* BoardCopy);
};