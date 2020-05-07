#include "pch.hpp"
#include "velocityChangingAreas.hpp"
#include "ECS/Components/objectsComponents.hpp"
#include "ECS/Components/physicsComponents.hpp"

namespace ph::system {

	void VelocityChangingAreas::update(float dt)
	{
		PH_PROFILE_FUNCTION();

		if(sPause)
			return;

		auto velocityChaningAreasView = mRegistry.view<component::BodyRect, component::AreaVelocityChangingEffect>();
		auto kinematicObjectsView = mRegistry.view<component::KinematicCollisionBody, component::BodyRect, component::Kinematics>();

		for(auto velocityChangingArea : velocityChaningAreasView)
		{
			const auto& [areaBody, velocityChangeEffect] = velocityChaningAreasView.get<component::BodyRect, component::AreaVelocityChangingEffect>(velocityChangingArea);
			
			for(auto kinematicObject : kinematicObjectsView)
			{
				auto& objectKinematics = kinematicObjectsView.get<component::Kinematics>(kinematicObject);
				const auto& objectBody = kinematicObjectsView.get<component::BodyRect>(kinematicObject);

				if(areaBody.contains(objectBody.center()))
				{
					objectKinematics.vel *= velocityChangeEffect.areaSpeedMultiplier;
				}
			}
		}
	}
}
