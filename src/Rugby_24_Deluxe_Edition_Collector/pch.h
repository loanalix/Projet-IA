#pragma once

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DEBUG_NEW
#endif

#define _USE_MATH_DEFINES
#define NOMINMAX
#define INVINCIBLE_TIME 1.0f
#define SPEED_TIME 1.0f

#include <chrono>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <string> 
#include <map>

#include "JsonManager.h"
#include "TextureManager.hpp"
#include "Lane.h"
#include "Time.h"
#include "Utils.hpp"
#include "Behaviour.hpp"
#include "Context.hpp"
#include "Entity.hpp"
#include "Animator.hpp"
#include "Ball.hpp"
#include "Player.hpp"
#include "DebugClass.h"
#include "GameManager.hpp"
#include "Action.hpp"
#include "Behaviour.hpp"
#include "Transition.hpp"

#include "ActionPlayerRunner.h"
#include "ActionPlayerDefender.h"
#include "ActionPlayerAttack.h"
#include "ActionPlayerDefend.h"
#include "ActionPlayerHaveBall.h"
#include "ActionPlayerSeekBall.h"
#include "ConditionPlayerAttack.h"
#include "ConditionPlayerRunner.h"
#include "ConditionPlayerDefender.h"
#include "ConditionPlayerDefend.h"
#include "ConditionPlayerHaveBall.h"
#include "ConditionPlayerSeekBall.h"