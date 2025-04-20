#pragma once
#include"Player.h"
class Automat;
class AutomatController {
private:
    AutomatController() = default;
    float shooting_speed = 0.09;
    static AutomatController* controller;
public:
    AutomatController(AutomatController const&) = delete;
    void operator=(AutomatController const&) = delete;
    ~AutomatController();

    static AutomatController* getAutomatController();

    void controllAutomat(Automat* automat, Player* player, sf::RenderWindow& window, float time);

};