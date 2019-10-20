#pragma once

namespace ph::component {
	
	struct Health
	{
		unsigned healthPoints;
	};

	struct Player
	{
	};

	struct MeleeAttacker
	{
		float minSecondsInterval;
		bool isTryingToAttack;
	};

	struct GunAttacker
	{
		float minSecondsInterval;
		unsigned bullets;
		bool isTryingToAttack;
	};
}
