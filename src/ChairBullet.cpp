/*Copyright 2017 MIT*/

#include "ChairBullet.h"
#include "SDLGameObject.h"
#include "Vector2D.h"
#include "LoaderParams.h"
#include "Timer.h"
#include "Player.h"
#include "Game.h"
#include "InputHandler.h"
#include "Log.h"
#include "Enemy.h"
#include "Physics.h"
#include "GameOverState.h"
#include "AudioManager.h"
#include <iostream>

ChairBullet::~ChairBullet() {
    INFO("REMOVE CHAIR BULLET");
}

ChairBullet::ChairBullet(Player *target) : SDLGameObject() {
    setPlayer(target);
    timeToLive = 5000;
    m_active = true;
}

void ChairBullet::load(const engine::LoaderParams* pParams) {
    m_velocity = engine::Vector2D(0, 0);

    SDLGameObject::load(pParams);
}

double ChairBullet::rotateTowards(engine::Vector2D pPosition) {
    engine::Vector2D target =
        engine::InputHandler::Instance().getMousePosition() - pPosition;
    target = target.norm();

    engine::Vector2D horizontal(0, 1);

    return engine::Vector2D::angle(target, engine::Vector2D(0, 1));
}
void ChairBullet::load(engine::Vector2D pVelocity, engine::Vector2D pPosition) {
    double angle = rotateTowards(pPosition);

    m_moveSpeed = 7;
    engine::LoaderParams* pParams = new engine::LoaderParams(pPosition.getX(),
                                                             pPosition.getY(),
                                                             60, 96,
                                                             "chairBullet", 0,
                                                             0, 0, angle, 55,
                                                             80);
    SDLGameObject::load(pParams);

    m_currentFrame = 0;
    bornTime = engine::Timer::Instance().step();
    m_velocity = pVelocity.norm() * m_moveSpeed;
    // m_velocity = engine::Vector2D(0.5, 0.5);
}

void ChairBullet::draw() {
    SDLGameObject::draw();
}

void ChairBullet::update() {
    m_position += m_velocity;

    if (engine::Timer::Instance().step() >= bornTime + timeToLive) {
        m_active = false;
       engine::Game::Instance().getStateMachine()->currentState()->
                         removeGameObject(this);
    }

    checkCollision();
}

void ChairBullet::checkCollision() {
    if (m_active) {
        engine::Vector2D pos = m_player->getPosition();
        engine::Vector2D thisPos = getPosition();

        if (engine::Physics::Instance().
            checkCollision(dynamic_cast<SDLGameObject*>(m_player),
                           dynamic_cast<SDLGameObject*>(this))) {
            m_active = false;
           engine::Game::Instance().getStateMachine()->currentState()->
                             removeGameObject(this);
            INFO("Bullet collided");
            INFO("PLAYER LOST THEengine::Game");
            if (!m_player->getShieldActive()) {
                engine::AudioManager::Instance().
                    playChunk("assets/sounds/chair.wav");
                m_player->setLife((m_player->getLife()) - 1);
                m_player->setPlayerMoves(false);
                m_player->setStunTime(engine::Timer::Instance().step());
            } else if (m_player->getShieldActive()) {
                m_player->setShieldHits();
            }

            /*engine::Game::Instance().getStateMachine()->
            changeState(newengine::GameOverState()); */
        }
    }
}

void ChairBullet::clean() {
    SDLGameObject::clean();
}

