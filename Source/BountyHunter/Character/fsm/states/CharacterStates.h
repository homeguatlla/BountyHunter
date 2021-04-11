#pragma once
#include <string>
#include <map>

namespace TLN
{
	enum class CharacterState
	{
		STATE_IDLE = 0,
		STATE_WALKING = 1,
		STATE_RUNNING = 2,
		STATE_JUMPING = 3,
		STATE_ON_AIR = 4,		

		STATE_IDLE_ABILITY = 10,
		STATE_CASTING = 11,
		STATE_COOLDOWN = 12,

		STATE_IDLE_SHOT = 20,
		STATE_COOLDOWN_SHOT = 21,
		STATE_FIRE = 22,
		
		STATE_NORMAL = 100,
		STATE_DEBUG = 101,
		STATE_NEXT_NPC = 102,
		STATE_PREVIOUS_NPC = 103
	};

	static std::map<CharacterState, std::string> CharacterStateMap =
	{
		{ CharacterState::STATE_IDLE, std::string("Idle") },
		{ CharacterState::STATE_WALKING, std::string("Walking") },
		{ CharacterState::STATE_RUNNING, std::string("Running") },
		{ CharacterState::STATE_JUMPING, std::string("Jumping") },
		{ CharacterState::STATE_ON_AIR, std::string("OnAir") },

		{ CharacterState::STATE_IDLE_ABILITY, std::string("IdleAbility") },
		{ CharacterState::STATE_CASTING, std::string("Casting") },
		{ CharacterState::STATE_COOLDOWN, std::string("Cooldown") },

		{ CharacterState::STATE_IDLE_SHOT, std::string("IdleShot") },
		{ CharacterState::STATE_COOLDOWN_SHOT, std::string("CooldownShot") },
		{ CharacterState::STATE_FIRE, std::string("Fire") },
		
		{ CharacterState::STATE_NORMAL, std::string("Normal") },
		{ CharacterState::STATE_DEBUG, std::string("Debug") },
		{ CharacterState::STATE_NEXT_NPC, std::string("NextNPC") },
		{ CharacterState::STATE_PREVIOUS_NPC, std::string("PreviousNPC") }
	};
};
