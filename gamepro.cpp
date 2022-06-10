#include "gamepro.h"
AnimatedAssets::AnimatedAssets(){
    this->Tex=Tex;
}
void Gametext::SetText(Font *font, int size, sf::Color color, int x, int y){
    gametext.setCharacterSize(size);
    gametext.setFont(*font);
    gametext.setFillColor(color);
    gametext.setPosition(x,y);
}
void AnimatedAssets::moveopposite(const sf::Time &elapsed){
    shape.move(0,0);
    shape.move(200*elapsed.asSeconds(),-200*elapsed.asSeconds());
}

void moveInDirection(Sprite &player,const sf::Time &elapsed, const sf::Keyboard::Key key)
{
    double speed_x=600;
    double speed_y=600;
    double acc=50;

    if(player.getGlobalBounds().left>=0 &&key==Keyboard::A)
     {
        while(speed_x<=1200){
          speed_x+=acc*elapsed.asSeconds();
        }
      player.move(-speed_x*elapsed.asSeconds(), 0);}

    if(player.getGlobalBounds().left+player.getGlobalBounds().width<1850&&key==Keyboard::D)
      {
        while(speed_x<=1200){
          speed_x+=acc*elapsed.asSeconds();
        }
      player.move(speed_x*elapsed.asSeconds(),0);
      }
    if(player.getGlobalBounds().top>=0&&key==Keyboard::W)
      {
        while(speed_y<=1200){
          speed_y+=acc*elapsed.asSeconds();
        }
       player.move(0,-speed_y*elapsed.asSeconds());
      }
    if(player.getGlobalBounds().top+player.getGlobalBounds().height<1000&&key==Keyboard::S)
      {
        while(speed_y<=1200){
          speed_y+=acc*elapsed.asSeconds();
        }
       player.move(0,speed_y*elapsed.asSeconds());
      }

}
