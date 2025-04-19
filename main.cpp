#include <SFML/Graphics.hpp>
#include<iostream>
#include"Load_Texture.h"
#include "Player.h"
using namespace std;

int main()
{

    


    sf::RenderWindow window(sf::VideoMode(900, 800), "SFML works!");

    textures::Player_setTextures();
    Player* player = new Player(textures::player_texture, sf::Vector2f(200, 300), 100);

    sf::Texture texture;

    if (!texture.loadFromFile("Texturs/Run_sheet.png")) 
    {
        // Если не получилось, выводим ошибку в консоль
        std::cerr << "Error: Could not load texture!" << std::endl;
        return 1;
    }

    sf::Texture texture_gun;
    texture_gun.loadFromFile("Texturs/Gun_animate.png");


    // Параметры анимации
    //const int frameWidth = 32;
    //const int frameHeight = 32;
    //const int numFrames = 9;
    //int currentFrame = 0;
    //float animationSpeed = 0.05f;
    //float elapsedTime = 0.f;

    // Параметры анимации оружия
   /* const int frameWidth_gun = 96;
    const int frameHeight_gun = 32;
    const int numFrames_gun = 5;
    int currentFrame_gun = 0;
    float animationSpeed_gun = 0.025f;
    float elapsedTime_gun = 0.f;*/

    // Настройка спрайта
    //sf::Sprite sprite(texture);
    //sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    //sprite.setPosition(300, 400);
    //sprite.setScale(4.f, 4.f); // Увеличим спрайт для лучшей видимости

   /* sf::Sprite gun(texture_gun);
    gun.setTextureRect(sf::IntRect(0, 0, frameWidth_gun, frameHeight_gun));
    gun.setScale(1.5, 1.5);
    gun.setPosition(400, 470);
    gun.setOrigin(texture.getSize().x / 2.f - 110, texture.getSize().y / 2.f - 10);*/
    // Параметры движения
    //float speed = 0.3f;
    //bool isMoving = false;
    //bool facingRight = true;

    sf::Clock clock;


    while (window.isOpen()) {
       /* float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 300;*/
        float time = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        player->Update(time);

        window.clear();

        window.draw(player->getSprite());

        window.display();
    }

    delete player;
    return 0;
}