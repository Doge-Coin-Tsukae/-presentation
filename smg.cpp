//=====================================
//
//  ïêäÌ
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "sound.h"
#include "Vector.h"
#include "smoke.h"
#include "model.h"
#include "animationmodel.h"
#include "human.h"
#include "colider.h"
#include "weapon.h"
#include "smg.h"
#include "bullet.h"

#define MAX_AMMO 20
#define MAX_RELOADTIME 240
#define MAX_NEXT_SHOOT_TIME 10

void Csmg::Init()
{
	CWEAPON::Init();

	MaxAmmo = MAX_AMMO;
	Ammo = MaxAmmo;
	MaxReloadTime = MAX_RELOADTIME;
	MaxNextShootTime = MAX_NEXT_SHOOT_TIME;
}