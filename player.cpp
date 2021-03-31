#include "player.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

void Player::Input()
{
    ALLEGRO_KEYBOARD_STATE kbdState;
    al_get_keyboard_state(&kbdState);

    if(al_key_down(&kbdState, ALLEGRO_KEY_RIGHT))
    {
        vel.x = speed;
    }
    if(al_key_down(&kbdState, ALLEGRO_KEY_LEFT))
    {
        vel.x = -speed;
    }
    if(al_key_down(&kbdState, ALLEGRO_KEY_DOWN))
    {
        vel.y = speed;
    }
    if(al_key_down(&kbdState, ALLEGRO_KEY_UP))
    {
        vel.y = -speed;
    }
}

void Player::Update()
{
    vel = {0, 0};
    Input();

//    oldPos = pos;
//    pos.x += vel.x;
//    pos.y += vel.y;
}

void Player::Move(float x, float y)
{
    oldPos = pos;
    pos.x += x;
    pos.y += y;
}

void Player::Draw()
{
    // draw tiles checked
    for(int y = Top(); y <= Bottom(); ++y)
    {
        for(int x = Left(); x <= Right(); ++x)
        {
//            al_draw_filled_rectangle(x * tileSize, y * tileSize,
//                x * tileSize + tileSize, y * tileSize + tileSize, al_map_rgba(0, 255, 0, 150));
        }
    }

    // draw player
    al_draw_filled_rectangle(pos.x, pos.y,
        pos.x + size.x, pos.y + size.y, al_map_rgb(0, 128, 0));

    //draw sensors (corner points)
    al_draw_circle(pos.x, pos.y, 2, al_map_rgb(255, 255, 255), 1);
    al_draw_circle(pos.x + size.x, pos.y, 2, al_map_rgb(255, 255, 255), 1);
    al_draw_circle(pos.x, pos.y + size.y, 2, al_map_rgb(255, 255, 255), 1);
    al_draw_circle(pos.x + size.x, pos.y + size.x, 2, al_map_rgb(255, 255, 255), 1);


}
