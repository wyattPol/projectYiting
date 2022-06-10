#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class Gametext{
public:
    Text gametext;
    void SetText(Font *font,int size, sf::Color color,int x,int y);
};
class AnimatedAssets{
public:
    AnimatedAssets();
    Texture *Tex;
    Sprite shape;
    void moveopposite(const sf::Time &elapsed);

};
class Explosion:public AnimatedAssets{
public:
    Explosion(Texture *Tex):AnimatedAssets(){
    this->Tex=Tex;
    this->shape.setTexture(*Tex);
    this->shape.setScale(0.5,0.5);
    this->shape.setPosition(-300,-300);
    }

};
class Bullet:public AnimatedAssets{
public:
    Bullet(Texture *Tex):AnimatedAssets(){
        this->Tex=Tex;
        this->shape.setTexture(*Tex);
        this->shape.setScale(0.1,0.1);
        this->shape.setPosition(rand()%1550+50,0);
    }
};
class ColorEnemy:public AnimatedAssets{
public:
    ColorEnemy(Texture *Tex):AnimatedAssets(){
        this->Tex=Tex;
        this->shape.setTexture(*Tex);
        this->shape.setScale(0.13,0.13);
        this->shape.setPosition(1600,rand()%870+60);
    }
};

class Player:public AnimatedAssets{
public:
    Player(Texture *Tex){
        this->Tex=Tex;
        this->shape.setTexture(*Tex);
        this->shape.setScale(0.12,0.12);
        this->shape.setPosition(25,900);

    }
};
class BlueEnemy:public AnimatedAssets{
public:
    BlueEnemy(Texture *Tex):AnimatedAssets(){
        this->Tex=Tex;
        this->shape.setTexture(*Tex);
        this->shape.setScale(0.11,0.11);
        this->shape.setPosition(1600,rand()%870+60);
    }
};

class Wall:public AnimatedAssets{
public:

    Wall(Texture *Tex){
        this->Tex=Tex;
        this->Tex->setRepeated(true);
        this->shape.setTexture(*Tex);
        this->shape.setScale(0.5,0.5);
        this->shape.setTextureRect(sf::IntRect(150, 100, 150, rand()%21+300));
        this->shape.rotate(90);
        this->shape.setPosition(rand()%1300+300,rand()%900+100);
    }
};
void moveInDirection(Sprite &player,const sf::Time &elapsed, const sf::Keyboard::Key key);
