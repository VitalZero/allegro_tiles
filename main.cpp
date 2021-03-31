#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "player.h"
#include "level.h"
#include <vector>
#include <algorithm>
#include <iostream>

int TileAt(int x, int y)
{
    return level[y * levelWidth + x];
}

bool CheckCollisionRect(const Rect& r1, const Rect& r2)
{
    return (r1.x + r1.w > r2.x && r1.x < r2.x + r2.w &&
            r1.y + r1.h > r2.y && r1.y < r2.y + r2.h);
}

int main()
{
    al_init();
    al_install_keyboard();

    ALLEGRO_DISPLAY* display = al_create_display(640, 480);
    if(!display)
    {
        return -1;
    }

    al_init_primitives_addon();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* eventQueue = al_create_event_queue();

    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));

    Player player(levelWidth, levelHeight, tileSize);
    player.pos = { 10, 10};
    player.size = {32, 32};

    ALLEGRO_EVENT event;
    bool redraw = true;
    al_start_timer(timer);

    while(1)    // just temporary
    {
        std::vector<Rect> rects;
        int tileIndex = -1;

        al_wait_for_event(eventQueue, &event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            // update
            player.Update();

            // check x first and resolve
            player.Move(player.vel.x, 0);

            // collision
            // get tiles on tiles on each corner of the player
            // and put them on a vector if the tile is solid
            int left = player.pos.x / tileSize;
            int top = player.pos.y / tileSize;
            int right = (player.pos.x + player.size.x) / tileSize;
            int bottom = (player.pos.y + player.size.y) / tileSize;

            for(int x = left; x <= right; ++x)
            {
                for(int y = top; y <= bottom; ++y)
                {
                    if(TileAt(x, y) == 1)
                    {
                        rects.push_back({x * tileSize, y * tileSize, tileSize, tileSize});
                    }
                }
            }

            for(const auto& r : rects)
            {
                if(CheckCollisionRect(player.GetRect(), r))
                {
                    float leftDist = std::abs((player.pos.x + player.size.x) - r.x);
                    float rightDist = std::abs(player.pos.x - (r.x + r.w));

                    if(leftDist < rightDist)
                    {
                        player.pos.x -= leftDist;
                    }
                    else
                    {
                        player.pos.x += rightDist;
                    }
                    break;
                }
            }

            // check y after
            player.Move(0, player.vel.y);

            rects.clear();

            left = player.pos.x / tileSize;
            top = player.pos.y / tileSize;
            right = (player.pos.x + player.size.x) / tileSize;
            bottom = (player.pos.y + player.size.y) / tileSize;

            for(int x = left; x <= right; ++x)
            {
                for(int y = top; y <= bottom; ++y)
                {
                    if(TileAt(x, y) == 1)
                    {
                        rects.push_back({x * tileSize, y * tileSize, tileSize, tileSize});
                    }
                }
            }

            for(const auto& r : rects)
            {
                if(CheckCollisionRect(player.GetRect(), r))
                {
                    float topDist = std::abs((player.pos.y + player.size.y) - r.y);
                    float bottomDist = std::abs(player.pos.y - (r.y + r.h));

                    if(topDist < bottomDist)
                    {
                        player.pos.y -= topDist;
                    }
                    else
                    {
                        player.pos.y += bottomDist;
                    }
                    break;
                }
            }

            // end collision

            // end update

            redraw = true;
        }

        if(redraw && al_event_queue_is_empty(eventQueue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            for(int y = 0; y < levelHeight; ++y)
            {
                for(int x = 0; x < levelWidth; ++x)
                {
                    int ti = y * levelWidth + x;
                    int tileType = level[ti];
                    if(tileType > 0)
                    {
                        if(tileIndex == ti)
                        {
                            al_draw_rectangle(x * tileSize + 1, y * tileSize + 1,
                                x * tileSize + tileSize, y * tileSize + tileSize, al_map_rgb(255, 255, 0), 1);
                        }
                        else
                        {
                            al_draw_rectangle(x * tileSize + 1, y * tileSize + 1,
                                x * tileSize + tileSize, y * tileSize + tileSize, al_map_rgb(255, 255, 255), 1);
                        }
                    }
                }
            }

            player.Draw();

            for(const auto& r : rects)
            {
                al_draw_filled_rectangle(r.x, r.y, r.x + r.w, r.y + r.h, al_map_rgba(255, 0, 0, 100));
            }

            al_flip_display();
            redraw = false;
        }
    }


    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(eventQueue);

    return 0;
}
