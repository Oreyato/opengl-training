#ifndef Scene_Snake_H
#define Scene_Snake_H

#include "../engine/Scene.h"
// #include "../engine/Assets.h"

#include "Apple.h"

class Scene_Snake : public Scene {
public:
    Scene_Snake();
    ~Scene_Snake();
    void load();
    void clean();
    void pause();
    void resume();
    void handleEvent(const InputState &);
    void update(float dt);
    void draw();
    void setGame(Game *);

private:
    Game *game;

    Matrix4 projection;
    Shader shader;

    // Divergences from the Scene_008
    CubeMesh* cubeMesh;
    vector<Cube> cubes;

    vector<Apple> apples;

    int snakeBodyCount{3};
    int appleCount{1};

    float maxDepth{-10.0f};
};

#endif //Scene_Snake_H
