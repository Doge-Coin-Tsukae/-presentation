#pragma once

#include "cereal/cereal.hpp"

//�V���A���C�Y(D3DXVECTOR3���V���A���C�Y����Ƃ�)
template<class Archive>
void serialize(Archive& archive, D3DXVECTOR3& vector)
{
	archive(cereal::make_nvp("x", vector.x), cereal::make_nvp("y", vector.y), cereal::make_nvp("z", vector.z));
}


class CGameObject
{
protected:	//�A�N�Z�X�w��q
	bool			m_Destroy = false;
	D3DXVECTOR3		m_Position;
	D3DXVECTOR3		m_Rotation;
	D3DXVECTOR3		m_Scale;

public:		//�A�N�Z�X�w��q
	CGameObject() {}	//�R���X�g���N�^
	virtual ~CGameObject() {}	//�f�X�g���N�^(virtual�͕K������)

	virtual void Init() {};
	virtual void Uninit() = 0;		//�������z�֐�
	virtual void Update() = 0;
	virtual void Draw() {};

	//�Q�b�^�[
	D3DXVECTOR3 GetPosition() { return m_Position; }
	D3DXVECTOR3 GetRotation() { return m_Rotation; }
	D3DXVECTOR3 GetScale()	  { return m_Scale; }

	//�Z�b�^�[
	void SetPosition(D3DXVECTOR3 Pos) { m_Position = Pos; }
	void SetRotation(D3DXVECTOR3 Rot) { m_Rotation = Rot; }
	void SetScale(D3DXVECTOR3 Scl) { m_Scale = Scl; }

	void SetDestroy() { m_Destroy = true; }

	//�I�u�W�F�N�g�̔j�󏈗�
	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}

	//ImGuin�ɕ\�������鍀��
	virtual void SetImGui()
	{
		ImGui::Text("SetMode");
		ImGui::SliderFloat("rotation",&m_Rotation.y,0,10);
		ImGui::Checkbox("delete",&m_Destroy);
	}

	virtual void SetGizmo()
	{

	}
	virtual void Load(){}	//�f�[�^�̃��[�h
	virtual void Save(){}	//�f�[�^�̃Z�[�u
};