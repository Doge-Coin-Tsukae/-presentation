#pragma once

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

	virtual void Init() {};		//�������z�֐�
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() {};

	//�Q�b�^�[
	D3DXVECTOR3 GetPosition() { return m_Position; }
	D3DXVECTOR3 GetRotation() { return m_Rotation; }
	D3DXVECTOR3 GetScale()	  { return m_Scale; }

	//�Z�b�^�[
	virtual void SetPosition(D3DXVECTOR3 Pos) { m_Position = Pos; }
	void SetRotation(D3DXVECTOR3 Rot) { m_Rotation = Rot; }
	void SetScale(D3DXVECTOR3 Scl) { m_Scale = Scl; }

	void SetDestroy() { m_Destroy = true; }

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
};