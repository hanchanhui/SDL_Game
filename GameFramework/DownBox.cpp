#include "DownBox.h"
#include "Game.h"
#include <iostream>
#include "PlayState.h"

DownBox::DownBox(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void DownBox::draw()
{
	SDLGameObject::draw();
	SDLGameObject::flip = SDL_FLIP_NONE;
}

void DownBox::update()
{
  m_acceleration.setY(0.01);
  DownBoxCollision();
  arr();

  SDLGameObject::update();
}

void DownBox::DownBoxCollision()
{
    std::vector<GameObject*> collWall = PlayState::Instance()->getWall();
    std::vector<GameObject*> collDownBox = PlayState::Instance()->getDownBox();

    int boxLeft = m_position.getX();
    int boxRight = boxLeft + m_width;
    int boxTop = m_position.getY();
    int boxBottom = boxTop + m_height;
    // wall and block crash
    for (int i = 0; i < collWall.size(); i++)
    {
        int wallLeft = dynamic_cast<SDLGameObject*>(collWall[i])->GetPos().getX();
        int wallRight = wallLeft + dynamic_cast<SDLGameObject*>(collWall[i])->GetWidth();
        int wallTop = dynamic_cast<SDLGameObject*>(collWall[i])->GetPos().getY();
        int wallBottom = wallTop + dynamic_cast<SDLGameObject*>(collWall[i])->GetHeight();

        if (boxLeft <= wallRight && boxRight >= wallLeft && boxTop <= wallBottom && boxBottom >= wallTop)
        {
            if (m_velocity.getY() > 0 && boxBottom >= wallTop && boxBottom < wallBottom && boxLeft != wallRight && boxRight != wallLeft)
            {
                m_position.setY(wallTop - m_height);
                boxTop = m_position.getY();
                boxBottom = boxTop + m_height;

                m_velocity.setY(0);
            }
            else if (m_velocity.getY() < 0 && boxTop <= wallBottom && boxTop > wallTop && boxLeft != wallRight && boxRight != wallLeft)
            {
                m_position.setY(wallBottom);
                boxTop = m_position.getY();
                boxBottom = boxTop + m_height;

                m_velocity.setY(0);
            }

            if (m_velocity.getX() < 0 && boxLeft <= wallRight && boxLeft > wallLeft && boxTop != wallBottom && boxBottom != wallTop)
            {
                m_position.setX(wallRight);
                m_velocity.setX(0);
                
            }
            else if (m_velocity.getX() > 0 && boxRight >= wallLeft && boxRight < wallRight && boxTop != wallBottom && boxBottom != wallTop)
            {
                m_position.setX(wallLeft - m_width);
                m_velocity.setX(0);
                
            }
        }

    }
    // Blocks and block crash
    for (int i = 0; i < collDownBox.size(); i++)
    {
        int DownLeft = dynamic_cast<SDLGameObject*>(collDownBox[i])->GetPos().getX();
        int DownRight = DownLeft + dynamic_cast<SDLGameObject*>(collDownBox[i])->GetWidth();
        int DownTop = dynamic_cast<SDLGameObject*>(collDownBox[i])->GetPos().getY();
        int DownBottom = DownTop + dynamic_cast<SDLGameObject*>(collDownBox[i])->GetHeight();


        if (boxLeft <= DownLeft && boxRight >= DownLeft && boxTop <= DownBottom && boxBottom >= DownTop)
        {
            if (m_velocity.getY() > 0 && boxBottom >= DownTop && boxBottom < DownBottom && boxLeft != DownRight && boxRight != DownLeft)
            {
                m_position.setY(DownTop - m_height);
                boxTop = m_position.getY();
                boxBottom = boxTop + m_height;

                m_velocity.setY(0);
            }
            else if (m_velocity.getY() < 0 && boxTop <= DownBottom && boxTop > DownTop && boxLeft != DownRight && boxRight != DownLeft)
            {
                m_position.setY(DownBottom);
                boxTop = m_position.getY();
                boxBottom = boxTop + m_height;

                m_velocity.setY(0);
            }

        }
        
    }
}

// two-dimensional array block check
void DownBox::arr()
{
    for (int i = 0; i < 17; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (PlayState::Instance()->getMap(i, j) == 0)
            {
                if ((m_position.getX() == (360 + (j * 48))) && (m_position.getY() == (94 + (i * 48))))
                {
                    PlayState::Instance()->setMap(i, j, 1);
                }
            }

        }
    }
}


void DownBox::clean()
{

}