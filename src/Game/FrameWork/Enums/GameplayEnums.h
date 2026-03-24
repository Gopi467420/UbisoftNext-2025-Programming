#pragma once
#include <initializer_list>
#include <cstdint>



enum class EInputAction 
{
	IA_None = 0,
	IA_Fire,
	IA_MoveBase,
	IA_NextWeapon,
	IA_Restart
	
};

enum class EGameState
{
	EGS_None,
	EGS_StartScreen,
	EGS_Playing,
	EGS_Paused,
	EGS_End
};

//This defines the character state of the entity,only for player and enemies
enum class ECharacterState
{
	ECS_Dead,
	ECS_Idle,
	ECS_Moving,
	ECS_Attack

};


//Collision Preset for Entities in the game
enum class ECollisionResponse
{
	ECR_None,
	ECR_Ignore,
	ECR_Trigger,
	ECR_Block
};


enum class GemType : uint8_t
{
	Small,   // low value
	Medium,  // mid value
	Large,   // high value
	Count
};

enum class ProjectileType
{

	Rocket,     // single target burst / elite killer
	Sweep,      // crowd control (arc / whip)
	Homing,     // passive defense / auto targeting
	Zone,       // area denial
	count,

};

enum class EEnemyType
{
	ET_Bomber,
	ET_Airborne,
	ET_WallBreaker,
	ET_Swarm,
	count
};

enum class ECollisionLayer :uint32_t
{   
	Player = 1 << 0, 
	Projectile = 1 << 1, 
	Enemy = 1 << 2,
	World = 1 << 3,
	Camera = 1 << 4,
	Base =1 <<5,
	Gem  =1<<6,

};

enum class MovementType : uint8_t
{
	Straight,
	SweepOrbit,
	Precision
};

constexpr uint32_t DefineCollisionMask(std::initializer_list<ECollisionLayer> layers)
{
	uint32_t mask = 0;
	for (ECollisionLayer layer : layers)
		mask |= static_cast<uint32_t>(layer);
	return mask;
}

enum class ShapeColor
{
	White, Black, Red, Green, Blue, Yellow, Cyan, Magenta, Orange, Purple, Gray
};