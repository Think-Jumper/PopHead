
// NOTE: This code is automatically generated by meta/entitiesParser.exe 

#include "pch.hpp"
#include "entitiesDebugger.hpp"
#include "Renderer/renderer.hpp"

#include "ECS/Components/aiComponents.hpp"
#include "ECS/Components/animationComponents.hpp"
#include "ECS/Components/audioComponents.hpp"
#include "ECS/Components/charactersComponents.hpp"
#include "ECS/Components/debugComponents.hpp"
#include "ECS/Components/graphicsComponents.hpp"
#include "ECS/Components/itemComponents.hpp"
#include "ECS/Components/objectsComponents.hpp"
#include "ECS/Components/particleComponents.hpp"
#include "ECS/Components/physicsComponents.hpp"


extern bool debugWindowOpen;

namespace ph::system {

constexpr unsigned lookForSize = 255;
static char lookFor[lookForSize];
static bool highlightSelected = true;

static char* components[] = {
	"Health", "Damage", "Player", "Killable", "InPlayerGunAttackArea"
};
static bool selectedComponents[IM_ARRAYSIZE(components)];

static unsigned getCharCount(char* str, size_t size)
{
	for(unsigned charCount = 0; charCount < static_cast<unsigned>(size); ++charCount)
		if(str[charCount] == 0)
			return charCount;
	return static_cast<unsigned>(size);
}

void EntitiesDebugger::update(float dt)
{
	PH_PROFILE_FUNCTION();

	if(debugWindowOpen && ImGui::BeginTabItem("entities debugger"))
	{
		ImGui::BeginChild("entities", ImVec2(360, 0), true);
		ImGui::Checkbox("hightlight selected", &highlightSelected);

		/* TODO: Add support for components choosing
		if(ImGui::TreeNode("choose components"))
		{
			if(ImGui::ListBoxHeader("comListBox"))
			{	
				for(int i = 0; i < IM_ARRAYSIZE(components); ++i)			
				{
					ImGui::Selectable(components[i], selectedComponents + i);
				}
				ImGui::ListBoxFooter();
			}
			ImGui::TreePop();
		}
		*/

		ImGui::InputText("debug name", lookFor, lookForSize);

		unsigned lookForCharCount = getCharCount(lookFor, lookForSize);

		auto selectableEntity = [=](entt::entity entity)
		{
			bool displayThisEntity = true;
			char label[50];
			if(auto* debugName = mRegistry.try_get<component::DebugName>(entity))
			{
				char* name = debugName->name;
				unsigned nameCharCount = getCharCount(name, strlen(name));
				sprintf(label, "%u - %s", entity, name);
				if(lookForCharCount != 0 && lookFor[0] != ' ')
				{
					for(unsigned i = 0; i <= nameCharCount && i < lookForCharCount; ++i)
					{
						char nameChar = name[i];
						char lookForChar = lookFor[i]; 
						if(nameChar != lookForChar)
						{
							if(lookForChar > 96 && lookForChar < 123)
							{
								if(lookForChar - 32 != nameChar)
								{
									displayThisEntity = false;
									break;
								}
							}
							else
							{
								displayThisEntity = false;
								break;
							}
						}
					}
				}
			}
			else if(lookFor[0] == ' ')
			{
				sprintf(label, "%u", entity);
			}
			else
			{
				displayThisEntity = false;
			}

			if(displayThisEntity && ImGui::Selectable(label, mSelected == entity))
			{
				mSelected = entity;
			}
		};

		std::vector<entt::component> types;

		/* TODO: Add support for components choosing
		if(selectedComponents[0]) types.emplace_back(mRegistry.type<component::Health>());
		if(selectedComponents[1]) types.emplace_back(mRegistry.type<component::Damage>());
		if(selectedComponents[2]) types.emplace_back(mRegistry.type<component::Player>());
		if(selectedComponents[3]) types.emplace_back(mRegistry.type<component::Killable>());
		if(selectedComponents[4]) types.emplace_back(mRegistry.type<component::InPlayerGunAttackArea>());

		if(types.empty() || types.size() == IM_ARRAYSIZE(components))
		{
			mRegistry.each([=](auto entity)
			{
				selectableEntity(entity);
			});
		}
		else
		{
			mRegistry.runtime_view(types.cbegin(), types.cend()).each([=](auto entity)
			{
				selectableEntity(entity);
			});	
		}
		*/

		mRegistry.each([=](auto entity)
		{
			selectableEntity(entity);
		});

		ImGui::EndChild();
		ImGui::SameLine();

		ImGui::BeginChild("components view");
		ImGui::Text("Components view:");

		if(mRegistry.valid(mSelected))
		{
			bool bodyValid = false;
			component::BodyRect body;	

			// NOTE: Change value to 0 if this code doesn't compile
			//       because of bug in components parser!
			//       If that happens you can make a commit with #if value set to 0
			//       Make sure to inform Czapa about bug in parser. 
			#if 1

			// HEADER ENDS

if(auto* c = mRegistry.try_get<component::Zombie>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("Zombie");
ImGui::Text("pathMode: PathMode view is not supported!");
ImGui::Text("currentDirectionVector: %f, %f", c->currentDirectionVector.x, c->currentDirectionVector.y);
ImGui::Text("timeFromStartingThisMove: %f", c->timeFromStartingThisMove);
ImGui::Text("timeFromLastGrowl: %f", c->timeFromLastGrowl);
ImGui::Text("timeToMoveToAnotherTile: %f", c->timeToMoveToAnotherTile);
}
if(auto* c = mRegistry.try_get<component::SlowZombieBehavior>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("SlowZombieBehavior");
ImGui::Text("coolDownTimer: %f", c->coolDownTimer);
}
if(auto* c = mRegistry.try_get<component::Health>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("Health");
ImGui::Text("healthPoints: %i", c->healthPoints);
ImGui::Text("maxHealthPoints: %i", c->maxHealthPoints);
}
if(auto* c = mRegistry.try_get<component::Damage>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("Damage");
ImGui::Text("damageDealt: %i", c->damageDealt);
}
if(mRegistry.has<component::Player>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("Player");
}
if(mRegistry.has<component::Killable>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("Killable");
}
if(mRegistry.has<component::InPlayerGunAttackArea>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("InPlayerGunAttackArea");
}
if(auto* c = mRegistry.try_get<component::FaceDirection>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("FaceDirection: %f, %f", c->x, c->y);
}
if(auto* c = mRegistry.try_get<component::CollisionWithPlayer>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("CollisionWithPlayer");
ImGui::Text("pushForce: %f", c->pushForce);
if(c->isCollision) ImGui::Text("isCollision: true"); else ImGui::Text("isCollision: false");
}
if(auto* c = mRegistry.try_get<component::Lifetime>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("Lifetime");
ImGui::Text("lifetime: %f", c->lifetime);
}
if(auto* c = mRegistry.try_get<component::TeleportPoint>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("TeleportPoint");
ImGui::Text("name: %s", c->name.c_str());
}
if(auto* c = mRegistry.try_get<component::TextureRect>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("TextureRect: %i, %i, %i, %i", c->x, c->y, c->w, c->h);
}
if(auto* c = mRegistry.try_get<component::IndoorOutdoorBlendArea>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("IndoorOutdoorBlendArea");
switch(c->exit) {
case component::IndoorOutdoorBlendArea::Left: ImGui::Text("exit: Left"); break;
case component::IndoorOutdoorBlendArea::Right: ImGui::Text("exit: Right"); break;
case component::IndoorOutdoorBlendArea::Top: ImGui::Text("exit: Top"); break;
case component::IndoorOutdoorBlendArea::Down: ImGui::Text("exit: Down"); break;
default: ImGui::Text("IndoorOutdoorBlendArea: unknown enumeration!!!");
}
}
if(auto* c = mRegistry.try_get<component::IndoorOutdoorBlend>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("IndoorOutdoorBlend");
ImGui::Text("outdoor: %f", c->outdoor);
ImGui::Text("brightness: %f", c->brightness);
ImGui::Text("alpha: %f", c->alpha);
}
if(auto* c = mRegistry.try_get<component::OutdoorBlend>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("OutdoorBlend");
ImGui::Text("brightness: %f", c->brightness);
}
if(auto* c = mRegistry.try_get<component::IndoorBlend>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("IndoorBlend");
ImGui::Text("alpha: %f", c->alpha);
}
if(auto* c = mRegistry.try_get<component::RenderQuad>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("RenderQuad");
ImGui::Text("texture: %p", c->texture);
ImGui::Text("shader: %p", c->shader);
ImGui::Text("rotationOrigin: %f, %f", c->rotationOrigin.x, c->rotationOrigin.y);
ImGui::Text("color: %u, %u, %u, %u", c->color.r, c->color.g, c->color.b, c->color.a);
ImGui::Text("rotation: %f", c->rotation);
ImGui::Text("z: %u", c->z);
}
if(auto* c = mRegistry.try_get<component::GroundRenderChunk>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("GroundRenderChunk");
ImGui::Text("bounds: %f, %f, %f, %f", c->bounds.x,  c->bounds.y, c->bounds.w, c->bounds.h);
ImGui::Text("textureRect: %f, %f, %f, %f", c->textureRect.x,  c->textureRect.y, c->textureRect.w, c->textureRect.h);
ImGui::Text("z: %u", c->z);
if(c->outdoor) ImGui::Text("outdoor: true"); else ImGui::Text("outdoor: false");
}
if(auto* c = mRegistry.try_get<component::RenderChunk>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("RenderChunk");
ImGui::Text("quads: std::vector view is not supported!");
ImGui::Text("lightWalls: std::vector view is not supported!");
ImGui::Text("quadsBounds: %f, %f, %f, %f", c->quadsBounds.x,  c->quadsBounds.y, c->quadsBounds.w, c->quadsBounds.h);
ImGui::Text("lightWallsBounds: %f, %f, %f, %f", c->lightWallsBounds.x,  c->lightWallsBounds.y, c->lightWallsBounds.w, c->lightWallsBounds.h);
ImGui::Text("z: %u", c->z);
ImGui::Text("rendererID: %u", c->rendererID);
if(c->outdoor) ImGui::Text("outdoor: true"); else ImGui::Text("outdoor: false");
}
if(auto* c = mRegistry.try_get<component::LightWall>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("LightWall: %f, %f, %f, %f", c->x, c->y, c->w, c->h);
}
if(auto* c = mRegistry.try_get<component::LightSource>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("LightSource");
ImGui::Text("offset: %f, %f", c->offset.x, c->offset.y);
ImGui::Text("color: %u, %u, %u, %u", c->color.r, c->color.g, c->color.b, c->color.a);
ImGui::Text("attenuationAddition: %f", c->attenuationAddition);
ImGui::Text("attenuationFactor: %f", c->attenuationFactor);
ImGui::Text("attenuationSquareFactor: %f", c->attenuationSquareFactor);
ImGui::Text("startAngle: %f", c->startAngle);
ImGui::Text("endAngle: %f", c->endAngle);
}
if(auto* c = mRegistry.try_get<component::CameraRoom>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("CameraRoom");
ImGui::Text("timeFromPlayerEntrance: %f", c->timeFromPlayerEntrance);
}
if(auto* c = mRegistry.try_get<component::Camera>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("Camera");
ImGui::Text("center: %f, %f", c->center().x, c->center().y);
ImGui::Text("size: %f, %f", c->getSize().x, c->getSize().y);
ImGui::Text("name: %s", c->name.c_str());
}
if(mRegistry.has<component::HiddenForRenderer>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("HiddenForRenderer");
}
if(auto* c = mRegistry.try_get<component::Medkit>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("Medkit");
ImGui::Text("addHealthPoints: %i", c->addHealthPoints);
}
if(mRegistry.has<component::BulletBox>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("BulletBox");
}
if(auto* c = mRegistry.try_get<component::Bullets>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("Bullets");
ImGui::Text("numOfPistolBullets: %i", c->numOfPistolBullets);
ImGui::Text("numOfShotgunBullets: %i", c->numOfShotgunBullets);
}
if(auto* c = mRegistry.try_get<component::AreaVelocityChangingEffect>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("AreaVelocityChangingEffect");
ImGui::Text("areaSpeedMultiplier: %f", c->areaSpeedMultiplier);
}
if(auto* c = mRegistry.try_get<component::Hint>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("Hint");
ImGui::Text("hintName: %s", c->hintName.c_str());
ImGui::Text("keyboardContent: %s", c->keyboardContent.c_str());
ImGui::Text("joystickContent: %s", c->joystickContent.c_str());
if(c->isShown) ImGui::Text("isShown: true"); else ImGui::Text("isShown: false");
}
if(auto* c = mRegistry.try_get<component::PushingArea>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("PushingArea");
ImGui::Text("pushForce: %f, %f", c->pushForce.x, c->pushForce.y);
}
if(auto* c = mRegistry.try_get<component::Entrance>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("Entrance");
ImGui::Text("entranceDestination: %s", c->entranceDestination.c_str());
ImGui::Text("playerSpawnPosition: %f, %f", c->playerSpawnPosition.x, c->playerSpawnPosition.y);
}
if(auto* c = mRegistry.try_get<component::Lever>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("Lever");
ImGui::Text("id: %u", c->id);
if(c->isActivated) ImGui::Text("isActivated: true"); else ImGui::Text("isActivated: false");
if(c->turnOffAfterSwitch) ImGui::Text("turnOffAfterSwitch: true"); else ImGui::Text("turnOffAfterSwitch: false");
}
if(auto* c = mRegistry.try_get<component::LeverListener>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("LeverListener");
ImGui::Text("observedLeverId: %u", c->observedLeverId);
if(c->isActivated) ImGui::Text("isActivated: true"); else ImGui::Text("isActivated: false");
}
if(auto* c = mRegistry.try_get<component::PuzzleColor>(mSelected))
{
ImGui::Separator();
switch(*c)
{
case component::PuzzleColor::Red: ImGui::BulletText("PuzzleColor: Red"); break;
case component::PuzzleColor::Green: ImGui::BulletText("PuzzleColor: Green"); break;
case component::PuzzleColor::Blue: ImGui::BulletText("PuzzleColor: Blue"); break;
default: ImGui::BulletText("PuzzleColor: unknown enumeration!!!");
}
}
if(auto* c = mRegistry.try_get<component::PressurePlate>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("PressurePlate");
ImGui::Text("puzzleId: %u", c->puzzleId);
ImGui::Text("id: %u", c->id);
ImGui::Text("pressedByColor: PuzzleColor view is not supported!");
if(c->isPressed) ImGui::Text("isPressed: true"); else ImGui::Text("isPressed: false");
if(c->isPressIrreversible) ImGui::Text("isPressIrreversible: true"); else ImGui::Text("isPressIrreversible: false");
}
if(auto* c = mRegistry.try_get<component::PuzzleBoulder>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("PuzzleBoulder");
ImGui::Text("pushedLeftSince: %f", c->pushedLeftSince);
ImGui::Text("pushedRightSince: %f", c->pushedRightSince);
ImGui::Text("pushedUpSince: %f", c->pushedUpSince);
ImGui::Text("pushedDownSince: %f", c->pushedDownSince);
ImGui::Text("movingLeft: %f", c->movingLeft);
ImGui::Text("movingRight: %f", c->movingRight);
ImGui::Text("movingUp: %f", c->movingUp);
ImGui::Text("movingDown: %f", c->movingDown);
if(c->movedGridPosInThisMove) ImGui::Text("movedGridPosInThisMove: true"); else ImGui::Text("movedGridPosInThisMove: false");
}
if(auto* c = mRegistry.try_get<component::PuzzleGridPos>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("PuzzleGridPos: %i, %i", c->x, c->y);
}
if(auto* c = mRegistry.try_get<component::Gate>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("Gate");
ImGui::Text("id: %u", c->id);
if(c->previouslyOpen) ImGui::Text("previouslyOpen: true"); else ImGui::Text("previouslyOpen: false");
if(c->open) ImGui::Text("open: true"); else ImGui::Text("open: false");
}
if(auto* c = mRegistry.try_get<component::Spikes>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("Spikes");
ImGui::Text("puzzleId: %u", c->puzzleId);
ImGui::Text("id: %u", c->id);
ImGui::Text("timeToChange: %f", c->timeToChange);
ImGui::Text("changeFrequency: %f", c->changeFrequency);
if(c->changes) ImGui::Text("changes: true"); else ImGui::Text("changes: false");
if(c->active) ImGui::Text("active: true"); else ImGui::Text("active: false");
}
if(auto* c = mRegistry.try_get<component::SavePoint>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("SavePoint");
if(c->isIntersectingPlayer) ImGui::Text("isIntersectingPlayer: true"); else ImGui::Text("isIntersectingPlayer: false");
ImGui::Text("timeSincePlayerSteppedOnIt: %f", c->timeSincePlayerSteppedOnIt);
}
if(auto* c = mRegistry.try_get<component::ParticleEmitter>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("ParticleEmitter");
ImGui::Text("particles: std::vector view is not supported!");
ImGui::Text("parTexture: %p", c->parTexture);
ImGui::Text("spawnPositionOffset: %f, %f", c->spawnPositionOffset.x, c->spawnPositionOffset.y);
ImGui::Text("randomSpawnAreaSize: %f, %f", c->randomSpawnAreaSize.x, c->randomSpawnAreaSize.y);
ImGui::Text("parInitialVelocity: %f, %f", c->parInitialVelocity.x, c->parInitialVelocity.y);
ImGui::Text("parInitialVelocityRandom: %f, %f", c->parInitialVelocityRandom.x, c->parInitialVelocityRandom.y);
ImGui::Text("parAcceleration: %f, %f", c->parAcceleration.x, c->parAcceleration.y);
ImGui::Text("parSize: %f, %f", c->parSize.x, c->parSize.y);
ImGui::Text("parStartColor: %u, %u, %u, %u", c->parStartColor.r, c->parStartColor.g, c->parStartColor.b, c->parStartColor.a);
ImGui::Text("parEndColor: %u, %u, %u, %u", c->parEndColor.r, c->parEndColor.g, c->parEndColor.b, c->parEndColor.a);
ImGui::Text("amountOfParticles: %u", c->amountOfParticles);
ImGui::Text("amountOfAlreadySpawnParticles: %u", c->amountOfAlreadySpawnParticles);
ImGui::Text("parWholeLifetime: %f", c->parWholeLifetime);
ImGui::Text("parZ: %u", c->parZ);
if(c->oneShot) ImGui::Text("oneShot: true"); else ImGui::Text("oneShot: false");
if(c->isEmitting) ImGui::Text("isEmitting: true"); else ImGui::Text("isEmitting: false");
if(c->wasInitialized) ImGui::Text("wasInitialized: true"); else ImGui::Text("wasInitialized: false");
}
if(auto* c = mRegistry.try_get<component::MultiParticleEmitter>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("MultiParticleEmitter");
ImGui::Text("particleEmitters: std::vector view is not supported!");
}
if(auto* c = mRegistry.try_get<component::BodyRect>(mSelected)) 
{
ImGui::Separator();
body = *c;
bodyValid = true;
ImGui::BulletText("BodyRect: %f, %f, %f, %f", c->x, c->y, c->w, c->h);
}
if(auto* c = mRegistry.try_get<component::Kinematics>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("Kinematics");
ImGui::Text("vel: %f, %f", c->vel.x, c->vel.y);
ImGui::Text("acceleration: %f, %f", c->acceleration.x, c->acceleration.y);
ImGui::Text("friction: %f", c->friction);
ImGui::Text("defaultFriction: %f", c->defaultFriction);
ImGui::Text("frictionLerpSpeed: %f", c->frictionLerpSpeed);
}
if(auto* c = mRegistry.try_get<component::CharacterSpeed>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("CharacterSpeed");
ImGui::Text("speed: %f", c->speed);
}
if(mRegistry.has<component::StaticCollisionBody>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("StaticCollisionBody");
}
if(auto* c = mRegistry.try_get<component::MultiStaticCollisionBody>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("MultiStaticCollisionBody");
ImGui::Text("rects: std::vector view is not supported!");
ImGui::Text("sharedBounds: %f, %f, %f, %f", c->sharedBounds.x,  c->sharedBounds.y, c->sharedBounds.w, c->sharedBounds.h);
}
if(auto* c = mRegistry.try_get<component::KinematicCollisionBody>(mSelected)) 
{
ImGui::Separator();
ImGui::BulletText("KinematicCollisionBody");
ImGui::Text("mass: %f", c->mass);
if(c->staticallyMovedUp) ImGui::Text("staticallyMovedUp: true"); else ImGui::Text("staticallyMovedUp: false");
if(c->staticallyMovedDown) ImGui::Text("staticallyMovedDown: true"); else ImGui::Text("staticallyMovedDown: false");
if(c->staticallyMovedLeft) ImGui::Text("staticallyMovedLeft: true"); else ImGui::Text("staticallyMovedLeft: false");
if(c->staticallyMovedRight) ImGui::Text("staticallyMovedRight: true"); else ImGui::Text("staticallyMovedRight: false");
}


			// FOOTER STARTS

			#endif // !COMPONENTS_PARSER_MESSED_UP

			if(highlightSelected && bodyValid)
			{
				Renderer::submitQuad(nullptr, nullptr, &sf::Color(255, 0, 0, 150), nullptr, body.pos, body.size,
									 10, 0.f, {}, ProjectionType::gameWorld, false);
			}
		}

		ImGui::EndChild();
		ImGui::EndTabItem();
	}
}

}
