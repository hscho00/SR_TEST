#pragma once

namespace OBJ
{
	enum class ID : unsigned int
	{
		TERRAIN,
		NPC,
		PLAYER,
		EFFECT,
		UI,
		END
	};

	enum class EVENT : unsigned int
	{
		NO_EVENT,
		DEAD,
		END
	};

	enum class RENDER_GROUP : unsigned int
	{
		BACKGROUND,
		GAMEOBJECT,
		EFFECT,
		UI,
		SCREEN_EFFECT,
		END
	};

	enum class DIR
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		END
	};

	enum class BGOBJ
	{
		FLOWER,
		WATER,
		END
	};
}

namespace SCENE
{
	enum class ID : unsigned int
	{
		TITLE,
		STAGE_1,	// PALLET_TOWN
		END
	};
}

namespace POKeMON
{
	enum class TYPE : unsigned int
	{
		NORMAL,
		FIRE,
		WATER,
		GRASS,
		ELECTRIC,
		ICE,
		FIGHTING,
		POISON,
		GROUND,
		FLYING,
		PSYCHIC,
		BUG,
		ROCK,
		GHOST,
		DRAGON
	};
}

namespace BATTLE
{
	enum class RESULT : unsigned int
	{
		NO_EVENT,
		WIN,
		LOSE,
		RUN
	};

	enum class TYPE_EFFECT : unsigned int
	{
		GOOD,	// 효과가 굉장했다! (2배)
		NORMAL, // 보통 (1배)
		BAD,	// 효과가 별로인 것 같다... (0.5배)
		NO_EFFECT // 효과가 없는 것 같다... (0배)
	};
}

namespace ITEM
{
	enum class CLASS
	{
		ITEM,
		KEYITEM,
		POKeBALL
	};
}
