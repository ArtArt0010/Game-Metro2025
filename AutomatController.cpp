#include "Automat_Controller.h"
#include "Automate.h"
#include <iostream>


AutomatController* AutomatController::controller = nullptr;

AutomatController::~AutomatController() {}

AutomatController* AutomatController::getAutomatController() {
    if (!controller) {
        controller = new AutomatController();
    }
    return controller;
}

void AutomatController::controllAutomat(Automat* automat, Player* player, sf::RenderWindow& window, float time) {
    //�������� �������� � ������
    if (player->is_Life() == false) {
        return;
    }

    automat->setOrigen(automat->getSize().x / 2.f, automat->getSize().y / 2.f);

    sf::Vector2f playerPos = player->getPosition();



    playerPos.x += 50.f;
    playerPos.y += 70.f;

    automat->setPosition(playerPos);


    Direction dir_player = player->getDirection();


    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);


    sf::Vector2f direction = worldPos - automat->getPosition();
    float angle = atan2(direction.y, direction.x);
    float angel_grad = angle * 180 / 3.14159265f;

    automat->setDirectionMause(direction);
    //������� ��������� � ����������� �� �������� ��������
    if ((angel_grad > -90.f && angel_grad < 90.f)) {
        automat->setDirection(Direction_weapon::RIGHT);
        player->setDirection(Direction::RIGHT);
    }
    else {
        automat->setDirection(Direction_weapon::LEFT);
        player->setDirection(Direction::LEFT);
    }

    if (dir_player == Direction::LEFT) {
        angel_grad += 180.f;
        automat->setScale(-3.f, 3.f);
        automat->setDirection(Direction_weapon::LEFT);
        
    }
    else {
        automat->setScale(3.f, 3.f);
        automat->setDirection(Direction_weapon::RIGHT);
        
    }

    automat->setRotation(angel_grad);



}
