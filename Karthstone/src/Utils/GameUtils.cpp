#include <MewtlePrecompiledHeaders.h>

#include "GameUtils.h"

#include "Mewtle.h"

BattleState* GameUtils::getBattleState(){
	return (BattleState*) Mewtle::Game::state;
}