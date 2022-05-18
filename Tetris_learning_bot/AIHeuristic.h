#pragma once
#include "const.h"
#include "Stack.h"

class AIDebugHeuristic
{
public:
	float m_lastScore;
	std::string m_description;
};

class AIHeuristic
{
public:
	AIHeuristic(float scalar)
		: m_scalar(scalar)
	{

	}

	virtual float GetScore(Stack* original) = 0;
	float m_scalar;
};

class AIHeuristic_AggregateHeight : public AIHeuristic
{
public:
	using AIHeuristic::AIHeuristic;
	virtual float GetScore(Stack* tetrisBoard);
};


class AIHeuristic_GameLoss : public AIHeuristic
{
public:
	using AIHeuristic::AIHeuristic;
	virtual float GetScore(Stack* tetrisBoard);
};

class AIHeuristic_Holes : public AIHeuristic
{
public:
	using AIHeuristic::AIHeuristic;
	virtual float GetScore(Stack* tetrisBoard);
};


class AIHeuristic_Blockade : public AIHeuristic
{
public:
	using AIHeuristic::AIHeuristic;
	virtual float GetScore(Stack* tetrisBoard);
};

class AIHeuristic_Bumpiness : public AIHeuristic
{
public:
	using AIHeuristic::AIHeuristic;
	virtual float GetScore(Stack* tetrisBoard);
};