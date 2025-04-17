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
    const int frameWidth = 32;
    const int frameHeight = 32;
    const int numFrames = 9;
    int currentFrame = 0;
    float animationSpeed = 0.05f;
    float elapsedTime = 0.f;

    // Параметры анимации оружия
   /* const int frameWidth_gun = 96;
    const int frameHeight_gun = 32;
    const int numFrames_gun = 5;
    int currentFrame_gun = 0;
    float animationSpeed_gun = 0.025f;
    float elapsedTime_gun = 0.f;*/

    // Настройка спрайта
    sf::Sprite sprite(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    sprite.setPosition(300, 400);
    sprite.setScale(4.f, 4.f); // Увеличим спрайт для лучшей видимости

   /* sf::Sprite gun(texture_gun);
    gun.setTextureRect(sf::IntRect(0, 0, frameWidth_gun, frameHeight_gun));
    gun.setScale(1.5, 1.5);
    gun.setPosition(400, 470);
    gun.setOrigin(texture.getSize().x / 2.f - 110, texture.getSize().y / 2.f - 10);*/
    // Параметры движения
    float speed = 0.3f;
    bool isMoving = false;
    bool facingRight = true;

    sf::Clock clock;


    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        elapsedTime += deltaTime;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        //sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        //sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

        //sf::Vector2f direction = worldPos - gun.getPosition();
        //float angle = atan2(direction.y, direction.x);
        //float angel_grad = angle * 180 / 3.14159265f;
        //if (gun.getScale().x < 0) {
        //    angel_grad += 180.f;
        //    
        //}
        //    gun.setRotation(angel_grad);
        //    bool shouldFaceRight = (angel_grad > -90.f && angel_grad < 90.f);
        //    if (facingRight != shouldFaceRight)
        //    {
        //        gun.setScale(-1.5, 1.5);
        //        facingRight = shouldFaceRight;
        //        // Обновляем текущий кадр с учетом нового направления
        //        sprite.setTextureRect(sf::IntRect(
        //            currentFrame * frameWidth,
        //            0,
        //            facingRight ? frameWidth : -frameWidth-1,
        //            frameHeight
        //        ));
        //    }
           
        

        // Обработка управления
        isMoving = false;
        sf::Vector2f movement(0.f, 0.f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            movement.x -= speed;
            isMoving = true;
            facingRight = false;
            sprite.move(-speed, 0);


           
         //   gun.setScale(-1.5, 1.5);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            movement.x += speed;
            isMoving = true;
            facingRight = true;
            sprite.move(speed, 0);

            
         //   gun.setScale(1.5, 1.5);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            movement.y -= speed;
            isMoving = true;
            sprite.move(0, -speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            movement.y += speed;
            isMoving = true;
            sprite.move(0, speed);
        }
       // gun.setPosition(sprite.getPosition().x + 40, sprite.getPosition().y + 70);
        // Применяем движение
       // sprite.move(movement * deltaTime);

        // Анимация только при движении вправо/влево
        if ((movement.x != 0) && elapsedTime >= animationSpeed)
        {
            currentFrame = (currentFrame + 1) % numFrames;
            sprite.setTextureRect(sf::IntRect(
                currentFrame * frameWidth,
                0,
                facingRight ? frameWidth : -frameWidth, // Отражение спрайта
                frameHeight));

            elapsedTime = 0.f;
        }




        //if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        //{
        //    elapsedTime_gun += deltaTime; // Не забываем увеличивать таймер

        //    if (elapsedTime_gun >= animationSpeed_gun)
        //    {
        //        // Обновляем кадр анимации
        //        currentFrame_gun = (currentFrame_gun + 1) % numFrames_gun;

        //        gun.setTextureRect(sf::IntRect(
        //            currentFrame_gun * frameWidth_gun, // X-позиция кадра
        //            0,                                // Y-позиция (если есть несколько строк анимации)
        //            frameWidth_gun,
        //            frameHeight_gun
        //        ));

        //        elapsedTime_gun = 0.f; // Сбрасываем таймер

        //        // Если анимация завершила цикл
        //        if (currentFrame_gun == numFrames_gun - 1) {
        //            // Дополнительные действия по завершению анимации
        //        }
        //    }
        //}
        //else
        //{
        //    // Сброс анимации, когда кнопка не нажата
        //    currentFrame_gun = 0;
        //    gun.setTextureRect(sf::IntRect(0, 1, frameWidth_gun, frameHeight_gun));
        //    elapsedTime_gun = 0.f;
        //}

        // Ограничение границ
        sf::Vector2f pos = sprite.getPosition();
        sf::FloatRect bounds = sprite.getGlobalBounds();

        if (pos.x < 0) sprite.setPosition(0, pos.y);
        if (pos.y < 0) sprite.setPosition(pos.x, 0);
        if (pos.x > window.getSize().x - bounds.width)
            sprite.setPosition(window.getSize().x - bounds.width, pos.y);
        if (pos.y > window.getSize().y - bounds.height)
            sprite.setPosition(pos.x, window.getSize().y - bounds.height);



        window.clear();
        window.draw(sprite);
        //window.draw(gun);
        window.display();
    }

    return 0;
}