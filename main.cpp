#include <iostream>
#include<SFML/Graphics.hpp>
#include<time.h>
#include<vector>
#include<algorithm>
#include"gamepro.h"
using namespace sf;
using namespace std;
int main()
{
   Clock clock;
   RenderWindow window(VideoMode(1600,1080),"DOG ROAD KILLER");
   window.setFramerateLimit(60);
   //UI Init
   int level=0;
   int life=3;
   Font font,gamefont;
   font.loadFromFile("IMMORTAL.ttf");
   gamefont.loadFromFile("BebasNeue-Regular.ttf");
   Gametext scores,gameover,lifes,easy,hard;
   scores.SetText(&font,40,Color::White,30,30);
   gameover.SetText(&gamefont,300,Color::Red,400,300);
   gameover.gametext.setString("GAME OVER!");
   lifes.SetText(&font,40,Color::White,30,70);
   easy.SetText(&gamefont,300,Color::Red,500,200);
   easy.gametext.setString("E A S Y");
   hard.SetText(&gamefont,300,Color::Red,500,600);
   hard.gametext.setString("H A R D");
   //Init Background
   int score=100;
   Sprite background;
   Texture backTex;
   backTex.loadFromFile("road.png");
   background.setScale(float(window.getSize().x)/float(backTex.getSize().x),
                   float(window.getSize().y)/float(backTex.getSize().y));
   background.setTexture(backTex);
   //Init explosion
   Texture exploTex;
   exploTex.loadFromFile("explosion.png");

   Explosion explosion(&exploTex);
   //Init bullet
   Texture bullTex;
   bullTex.loadFromFile("bullet.png");
   vector<Bullet> bullets;
   //Init Player
   Texture starTex;
   int speedmoveback=800;
   starTex.loadFromFile("stardog.png");
   Player player(&starTex);
   //Init Wall
   Texture wallTex;
   wallTex.loadFromFile("wall.png");
   vector<Wall> walls;
   for(int j=0;j<5;j++){
      walls.push_back(Wall(&wallTex));
    }
   //Init BlueEnemy
   int enemySpawnTimer=0;
   int colorSpawnTimer=0;
   Texture bluetex;
   bluetex.loadFromFile("blue.png");
   vector<BlueEnemy> bluenemies;
   bluenemies.push_back(BlueEnemy(&bluetex));
   //Init ColorEnemy
   Texture colortex;
   colortex.loadFromFile("color.png");
   vector<ColorEnemy> colorenemies;
   colorenemies.push_back(ColorEnemy(&colortex));
 while (window.isOpen()){
     srand(time(NULL));
     sf::Time elapsed=clock.restart();
     Event event;
     while(window.pollEvent((event)))
    {
     if(event.type==Event::Closed)
        window.close();
     if(event.KeyPressed && event.key.code==Keyboard::Escape)
        window.close();
   //Set Levels
     if(event.type==Event::MouseButtonPressed){
         if(Mouse::isButtonPressed(Mouse::Left)) {

             if(Mouse::getPosition().y<=600){
                 level=1;
             }
             else{
                 level=2;
            }

         }
     }
     //Player Move
     if(event.type==sf::Event::KeyPressed && life!=0)
        {
         const sf::Keyboard::Key key =event.key.code;
         moveInDirection(player.shape,elapsed,key);
         for(size_t i=0;i<walls.size();i++)
          {
             while(player.shape.getGlobalBounds().intersects(walls[i].shape.getGlobalBounds()) && level==2)
             {

              if(key==Keyboard::A)
                     player.shape.move(speedmoveback*elapsed.asSeconds(),0);
                  else if(key==Keyboard::D)
                     player.shape.move(-speedmoveback*elapsed.asSeconds(),0);
                  else if(key==Keyboard::W)
                     player.shape.move(0,speedmoveback*elapsed.asSeconds());
                  else if(key==Keyboard::S)
                     player.shape.move(0,-speedmoveback*elapsed.asSeconds());
              }
           }
         }
     }

   if(life>0)
 { //EnemiesMove
     if(enemySpawnTimer<80)
         enemySpawnTimer++;
     if(enemySpawnTimer>=80)
      {
         bluenemies.push_back(BlueEnemy(&bluetex));
         bullets.push_back(Bullet(&bullTex));
         enemySpawnTimer=0;
      }
    for(size_t i=0;i<bluenemies.size();i++)//wall and bluenemy collision detect
    {
     bluenemies[i].shape.move(-200*elapsed.asSeconds(),0);
     for(size_t j=0;j<walls.size();j++)
     {
         while(bluenemies[i].shape.getGlobalBounds().intersects(walls[j].shape.getGlobalBounds()) && level==2)
             bluenemies[i].moveopposite(elapsed);
     }
        //player and bluenemy collision detect
     if(bluenemies[i].shape.getPosition().x<= 0-bluenemies[i].shape.getGlobalBounds().width)
         bluenemies.erase(bluenemies.begin()+i);
     if(bluenemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
       {  score=score-10;
         bluenemies.erase(bluenemies.begin()+i);}
    }
  //BulletMove
    for(size_t i=0;i<bullets.size();i++)
    {
        bullets[i].shape.move(0,400*elapsed.asSeconds());
        if(bullets[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
         {
            bullets.erase(bullets.begin()+i);
            life--;
        }
    }
  //ColorEnemies
    if(colorSpawnTimer<200)
        colorSpawnTimer++;
    if( colorSpawnTimer>=200)
     {
        colorenemies.push_back(ColorEnemy(&colortex));
        colorSpawnTimer=0;
     }
  //Collision Detect
    //wall and bluenemy collision detect
    for(size_t i=0;i<colorenemies.size();i++)//wall and bluenemy collision detect
    {
     colorenemies[i].shape.move(-200*elapsed.asSeconds(),0);
     for(size_t j=0;j<walls.size();j++)
     {
         while(colorenemies[i].shape.getGlobalBounds().intersects(walls[j].shape.getGlobalBounds()) && level==2)
             colorenemies[i].moveopposite(elapsed);
     }
    }
     //player and colorenemy collision detect
   for(size_t i=0;i<colorenemies.size();i++)//player and colorenemy collision detect
   {
    colorenemies[i].shape.move(-2,0);
    if(colorenemies[i].shape.getPosition().x<= 0-colorenemies[i].shape.getGlobalBounds().width)
        colorenemies.erase(colorenemies.begin()+i);
    if(colorenemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
    {
        colorenemies.erase(colorenemies.begin()+i);
        score+=40;
        explosion.shape.setPosition(player.shape.getPosition().x,player.shape.getPosition().y);
        break;
    }

   }

}

  //UI Update
   scores.gametext.setString("SCORE: "+to_string(score));
   lifes.gametext.setString("Lifes: "+to_string(life));
  //Draw
   window.clear();
   window.draw(background);
if(level==0){
   window.draw(easy.gametext);
   window.draw(hard.gametext);}
if(level==2){
    for(size_t i=0;i<walls.size();i++)
    {
        window.draw(walls[i].shape);
    }
}
if(level==1 || level==2){
   for(size_t i=0;i<bluenemies.size();i++)
   {
    window.draw(bluenemies[i].shape);

    }
   for(size_t i=0;i<colorenemies.size();i++)
   {
    window.draw(colorenemies[i].shape);

    }

   for(size_t i=0;i<bullets.size();i++)
   {
       window.draw(bullets[i].shape);
   }
   window.draw(explosion.shape);
   window.draw(player.shape);
   window.draw(scores.gametext);
   window.draw(lifes.gametext);
   if(life==0){
       window.draw(gameover.gametext);
   }
}
   window.display();
   }
    return 0;
}

