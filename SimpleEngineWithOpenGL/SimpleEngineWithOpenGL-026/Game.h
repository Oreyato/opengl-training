#pragma once
#include <vector>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Window.h"
#include "Vector2.h"
#include "Camera.h"
#include "RendererOGL.h"
#include "AudioSystem.h"
#include "InputSystem.h"
#include "Ship.h"

using std::vector;

class Game
{
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game() : isRunning(true), isUpdatingActors(false), camera(nullptr) {}

public:
	bool initialize();
	void load();
	void loop();
	void unload();
	void close();

	void addActor(Actor* actor);
	void removeActor(Actor* actor);
	RendererOGL& getRenderer() { return renderer; }
	AudioSystem& getAudioSystem() { return audioSystem; }

	// Game specific
	vector<class Astroid*>& getAstroids();
	void addAstroid(class Astroid* astroid);
	void removeAstroid(class Astroid* astroid);

private:
	void processInput();
	void update(float dt);
	void render();

	bool isRunning;
	Window window;
	RendererOGL renderer;
	AudioSystem audioSystem;
	InputSystem inputSystem;

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;
	Camera* camera;

	// Game specific
	vector<Astroid*> astroids;
	Ship* ship;
};

