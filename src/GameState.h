#pragma once

class GameState
{
public:
	virtual ~GameState() = default;

	virtual void Enter() = 0;	// Load state-specific assets, reset variables, spawn initial objects.
	virtual void Update() = 0;	// Runs every frame, includes game logic and math.
	virtual void Draw() = 0;	// Read-only, UI and graphics.
	virtual void Exit() = 0;	// Stop, cleanup, free resources, and safely package data to send to next state.
};