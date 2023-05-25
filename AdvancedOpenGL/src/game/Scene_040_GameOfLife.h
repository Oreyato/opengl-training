#ifndef Scene_040_GameOfLife_H
#define Scene_040_GameOfLife_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"


class Scene_040_GameOfLife : public Scene {
public:
    Scene_040_GameOfLife();
    ~Scene_040_GameOfLife();
    
    void setGame(Game *);
    void load();
    void clean();
    void pause();
    void resume();
    void handleEvent(const InputState &);
    void update(float dt);
    void draw();

private:
    Game *game;

    ComputeShader cShader;
};

#endif //Scene_040_GameOfLife_H