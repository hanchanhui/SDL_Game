#include "Player.h"
#include "PlayState.h"
#include "GameOverState.h"
#include "Camera.h"


Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) , isGrounded(0) , ground(0), attack(true), HP(3)
{
    _timer.setInterval(3000);
    
}


void Player::draw()
{
  if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
  {
    SDLGameObject::drawFrame();
    PlayState::Instance()->SetAniCount(1);
  }else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
  {
    SDLGameObject::drawFrame();
    PlayState::Instance()->SetAniCount(1);
  }else{
    SDLGameObject::drawFrame();
    PlayState::Instance()->SetAniCount(0);
  }
}


void Player::update()
{
  m_currentFrame = ((SDL_GetTicks() / 100) % 11);
  handleInput();
  checkCollision();
  CameraMove();
  

  if (TheTextureManager::Instance()->getPlayerColCheck())
  {
      Transparency();
  }
  else if(_timer.getstart() != 0)
  {
      _timer.resume();
  }

  GameOver();
  
  SDLGameObject::update();
}


void Player::handleInput()
{

  if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) 
  {
    flip = SDL_FLIP_NONE;
    m_velocity.setX(2);
    ground += 1;
    
  }
  else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) 
  {
    flip = SDL_FLIP_HORIZONTAL;
    m_velocity.setX(-2);
    ground -= 1;
    
  }
  else
  {
    m_velocity.setX(0);
  }
  
  if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) &&m_velocity.getY() >= 0)
  {
      // 더블 점프 구현
    if(isGrounded < 2)
    {
        if (isGrounded == 0) {
            m_velocity.setY(-10);
            Gravity(2.5);
            isGrounded++;
        }
        else
        {
            m_velocity.setY(-9);
            Gravity(2.5);
            isGrounded++;
        }
    }
  }

}

void Player::checkCollision()
{
  
  std::vector<GameObject*> collWall = PlayState::Instance()->getWall();
  std::vector<GameObject*> collDownBox = PlayState::Instance()->getDownBox();

  int plyLeft = m_position.getX() + 10;
  int plyRight = plyLeft + m_width - 20;
  int plyTop = m_position.getY();
  int plyBottom = plyTop + m_height;

  // 바닥과 충돌
  for(int i = 0; i < collWall.size(); i++)
  {
    int wallLeft = dynamic_cast<SDLGameObject*>(collWall[i])->GetPos().getX();
    int wallRight = wallLeft + dynamic_cast<SDLGameObject*>(collWall[i])->GetWidth();
    int wallTop = dynamic_cast<SDLGameObject*>(collWall[i])->GetPos().getY();
    int wallBottom = wallTop + dynamic_cast<SDLGameObject*>(collWall[i])->GetHeight();

    if(plyLeft <= wallRight && plyRight >= wallLeft && plyTop <= wallBottom && plyBottom >= wallTop)
    {
      if(m_velocity.getY() > 0 && plyBottom >= wallTop && plyBottom < wallBottom && plyLeft != wallRight && plyRight != wallLeft)
      {
        m_position.setY(wallTop - m_height);
        plyTop = m_position.getY();
        plyBottom = plyTop + m_height;

        m_velocity.setY(0);
        Gravity(0.0);
        isGrounded = 0; // 바닥 인식
      }
      else if(m_velocity.getY() < 0 && plyTop <= wallBottom && plyTop > wallTop && plyLeft != wallRight && plyRight != wallLeft)
      {
        m_position.setY(wallBottom);
        plyTop = m_position.getY();
        plyBottom = plyTop + m_height;

        m_velocity.setY(0);
      }

      if(m_velocity.getX() < 0 && plyLeft <= wallRight && plyLeft > wallLeft && plyTop != wallBottom && plyBottom != wallTop)
      {
          
          m_position.setX(wallRight);
          m_velocity.setX(0);
      }
      else if(m_velocity.getX() > 0 && plyRight >= wallLeft && plyRight < wallRight && plyTop != wallBottom && plyBottom != wallTop)
      {
        m_position.setX(wallLeft - m_width);
        m_velocity.setX(0);
      }
    } 
   }
  // 떨어지는 박스와 충돌
  for (int i = 0; i < collDownBox.size(); i++)
  {
      int boxLeft = dynamic_cast<SDLGameObject*>(collDownBox[i])->GetPos().getX();
      int boxRight = boxLeft + dynamic_cast<SDLGameObject*>(collDownBox[i])->GetWidth();
      int boxTop = dynamic_cast<SDLGameObject*>(collDownBox[i])->GetPos().getY();
      int boxBottom = boxTop + dynamic_cast<SDLGameObject*>(collDownBox[i])->GetHeight();
      int boxVal = dynamic_cast<SDLGameObject*>(collDownBox[i])->GetVel().getY();

      if (plyLeft <= boxRight && plyRight >= boxLeft && plyTop <= boxBottom && plyBottom >= boxTop)
      {
          if (m_velocity.getY() > 0 && plyBottom >= boxTop && plyBottom < boxBottom && plyLeft != boxRight && plyRight != boxLeft )
          {
              if (boxVal == 0) {
                  m_position.setY(boxTop - m_height);
                  plyTop = m_position.getY();
                  plyBottom = plyTop + m_height;

                  isGrounded = 0; // 바닥 인식

                  m_velocity.setY(0);
                  Gravity(0.0);
              }
          }
          if (m_velocity.getY() <= 0 && plyTop <= boxBottom && plyTop > boxTop && plyLeft != boxRight && plyRight != boxLeft && TheTextureManager::Instance()->getPlayerColCheck() == false)
          {
             
              TheTextureManager::Instance()->setPlayerColCheck(true);
              
              if (attack) {
                  HP -= 1;
                  attack = false;
                  std::cout << "hp :" << HP << std::endl;
                  std::cout << "at :" << attack << std::endl;
                  _timer.start();
              }
          }
          
          if (m_velocity.getX() < 0 && plyLeft <= boxRight && plyLeft > boxLeft && plyTop != boxBottom && plyBottom != boxTop)
          {
              if (boxVal == 0) {
                  m_position.setX(boxRight - 10);
                  m_velocity.setX(0);
              }
          }
          else if (m_velocity.getX() > 0 && plyRight >= boxLeft && plyRight < boxRight && plyTop != boxBottom && plyBottom != boxTop)
          {
              if (boxVal == 0) {
                  m_position.setX(boxLeft - m_width + 10);
                  m_velocity.setX(0);
              }
          }
      }
  }
    
    // 핸드폰 밖으로 나가지 못하게 설정
    
    if ((m_position.getX() < 350 && TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
        || (m_position.getX() > 788 && TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)))
    {
        if (m_position.getY() > 100) {
            m_velocity.setX(0);
        }
    }
    else if (m_position.getY() < 80 && m_position.getX() < 852)
    {
        m_velocity.setY(0);
    }
}

void Player::Gravity(float gravity)
{
  m_acceleration.setY(gravity);
}


void Player::CameraMove()
{
  TheCamera::Instance()->getCameraRectX(m_position.getX() + (m_width / 2) - 387);
  TheCamera::Instance()->getCameraRectY(m_position.getY() + (m_height / 2) - 700);

  if(TheCamera::Instance()->getCameraRect().x < 190)
  {
      TheCamera::Instance()->getCameraRectX(190);
  }
  else if(TheCamera::Instance()->getCameraRect().x > 220)
  {
      TheCamera::Instance()->getCameraRectX(220);
  }

  if(TheCamera::Instance()->getCameraRect().y < 0)
  {
      TheCamera::Instance()->getCameraRectY(0);
  }
}



// 무적 시간
void Player::Transparency()
{
    
    if (_timer.done())
    {
        TheTextureManager::Instance()->setPlayerColCheck(false);
        _timer.pause();
        attack = true;
        std::cout << "at :" << attack << std::endl;
        
    }
}


void Player::clean()
{
  
}

// 게임 오버
void Player::GameOver()
{
    if (HP <= 0)
    {
        PlayState::Instance()->SetHeartAni(0, 1);
        TheGame::Instance()->getStateMachine()->changeState(GameOverState::Instance());
    }
    else if (HP == 1)
    {
        PlayState::Instance()->SetHeartAni(1, 3);
    }
    else if (HP == 2)
    {
        PlayState::Instance()->SetHeartAni(2, 5);
    }
    else if (m_position.getY() > 4000)
    {
        TheGame::Instance()->getStateMachine()->changeState(GameOverState::Instance());
    }
}