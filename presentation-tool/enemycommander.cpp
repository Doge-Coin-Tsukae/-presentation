#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "human.h"

#include "model.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "enemy.h"
#include "base.h"
#include "enemycommander.h"

#define MAX_RESPORNTIME 240;

void CENEMY_COMMANDER::Init()
{
	resporn_timer = MAX_RESPORNTIME;
}
void CENEMY_COMMANDER::Uninit()
{

}
void CENEMY_COMMANDER::Update()
{
	if (resporn_timer <= 0)
	{
		CScene* scene = CManager::GetScene();
		std::vector<CBASE*> baseList = scene->GetGameObjects<CBASE>(1);

		for (CBASE* base : baseList)
		{
			if (base->GetTerritory() == ENEMY_ZONE)
			{
				D3DXVECTOR3 posbase = base->GetPosition();
				posbase.x += rand() % 10 + -rand() % 10;
				posbase.y += 1.0f;
				posbase.z += rand() % 10 + -rand() % 10;

				scene->AddGameObject<CEnemy>(1)->SetPosition(posbase);
			}
		}
		resporn_timer = MAX_RESPORNTIME;
	}

	resporn_timer--;
}