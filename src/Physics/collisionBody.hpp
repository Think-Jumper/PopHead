#ifndef POPHEAD_PHYSICS_COLLISIONSBODY_H_
#define POPHEAD_PHYSICS_COLLISIONSBODY_H_

#include <SFML/Graphics.hpp>
#include "Base/gameData.hpp"
#include "World/Entity/object.hpp"
#include "CollisionDebug/collisionDebugRect.hpp"

namespace PopHead{
namespace Physics{

enum class BodyType;

class CollisionBody
{
public:
    CollisionBody(sf::FloatRect rect, float mass, BodyType, PopHead::World::Entity::Object* const owner, PopHead::Base::GameData*);
	~CollisionBody();

    void move(sf::Vector2f velocity);
    void setPosition(sf::Vector2f position);

    void setForceVector(sf::Vector2f forceVector);
    void updatePush(sf::Time delta);
    float getMass();
    sf::Vector2f getPosition();
    bool getStunStatus();

    auto getBodyType() const -> const BodyType& { return mBodyType; }

private:
    void updateOwnerPosition();
    void setPreviousPositionToCurrentPosition();
    sf::FloatRect getPreviousRect();

private:
    sf::FloatRect mRect;
    sf::Vector2f mPreviousPosition;
    sf::Vector2f forceVector;
    float mMass;
    const BodyType mBodyType;
    CollisionDebugRect mCollisionDebugRect;
    World::Entity::Object* const mOwner;
	Base::GameData* mGameData;

    friend PhysicsEngine;
    friend StaticCollisionHandler;
};


}}

#endif // POPHEAD_PHYSICS_COLLISIONSBODY_H_
