#ifndef POPHEAD_WORLD_ENTITY_OBJECTS_SHAPEWITHCOLLISION_H_
#define POPHEAD_WORLD_ENTITY_OBJECTS_SHAPEWITHCOLLISION_H_

#include "World/Entity/object.hpp"
#include "Physics/collisionBody.hpp"

///This class is for test purposes
///It should be probably deleted when map collisions and the whole Physics module are made

namespace PopHead {
namespace World {
namespace Entity {


class ShapeWithCollision : public Object
{
public:
	ShapeWithCollision(PopHead::Base::GameData*);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setPosition(sf::Vector2f, bool recursive = true) override;

private:
	sf::RectangleShape mShape;
	Physics::CollisionBody mCollisionBody;
};


}}}

#endif // !POPHEAD_WORLD_ENTITY_OBJECTS_STATICOBJECTTOCAMERA_H_
