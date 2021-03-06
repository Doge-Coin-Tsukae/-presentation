//=====================================
//
//  シーンの基底クラス
//  written by Y.Okubo
//
//=====================================
#pragma once
#include <list>
#include <vector>
#include <typeinfo>
#include "main.h"
#include "gameobject.h"

#define MAX_LAYER 5

class CScene
{
protected:
	std::list<CGameObject*> m_GameObject[MAX_LAYER];

public:
	CScene() {}
	virtual ~CScene() {}

	virtual void Init() = 0;
	virtual void Uninit()
	{
		for (int i = 0; i < MAX_LAYER; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();
		}
	}

	virtual void Update()
	{
		for (int i = 0; i < MAX_LAYER; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Update();
			}
			//remove_ifはリストから外す関数。最初にリスト、次に条件
			m_GameObject[i].remove_if([](CGameObject* object)
			{return object->Destroy(); });//(ポインタクラス引数,条件引数)
			//ラムダ式
		}
	}

	virtual void Draw()
	{


		for (int i = 0; i < MAX_LAYER; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}

	virtual void ShadowDraw()
	{
		for (CGameObject* object : m_GameObject[1])
		{
			object->Draw();
		}
	}

	//ゲームオブジェクトが継承されたオブジェクトをリストに追加する
	template <typename T>
	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
		gameObject->Init();

		return gameObject;
	}

	//既に宣言してあるゲームオブジェクトクラスをリストに加える
	CGameObject* AddArgumentGameObject(CGameObject* gameobject, int Layer)
	{
		CGameObject* GameObject = gameobject;
		m_GameObject[Layer].push_back(GameObject);
		//gameobject->Init();

		return gameobject;
	}

	//ゲームオブジェクトを捜索するテンプレート(単体のみ)
	template <typename T>
	T* GetGameObject(int Layer)
	{
		for (CGameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))
			{
				return (T*)object;
			}
		}

		return NULL;
	}

	//ゲームオブジェクトを捜索するテンプレート(複数)
	template<typename T>
	std::vector<T*> GetGameObjects(int Layer)
	{
		std::vector<T*>objects;//STLの配列
		for (CGameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))
			{
				objects.push_back((T*)object);
			}
		}
		return objects;
	}
};