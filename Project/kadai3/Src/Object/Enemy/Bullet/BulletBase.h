#pragma once
#include <DxLib.h>

class BulletBase
{

public:

	// �e�̎��
	enum class TYPE
	{
		STRAIGHT,
		ROCK
	};
	
	BulletBase(void);			// �R���X�g���N�^
	virtual ~BulletBase(void);	// �f�X�g���N�^

	void Load(void);			// �ǂݍ���
	void LoadEnd(void);			// �ǂݍ��݌�
	virtual void Update(void);	// �X�V
	void Draw(void);			// �`��
	void Release(void);			// ���

	// �e�̐���(�\���J�n���W�A�e�̐i�s����)
	virtual void CreateBullet(VECTOR pos, VECTOR dir);

	// ��������
	bool GetIsAlive(void);

	// �e�̍��W
	VECTOR GetPos(void);

	// �e�̏Փ˔���p���a
	float GetCollisionRadius(void);

	// �e�̎��
	TYPE GetType(void);

protected:

	// �e�̎��
	TYPE type_;

	// ���ƂȂ�e�̃��f��ID
	int baseModelId_;

	// �e�̃��f��ID
	int modelId_;

	// ����
	VECTOR dir_;

	// �e�̑傫��
	VECTOR scale_;

	// �e�̍��W
	VECTOR pos_;

	// �e�̈ړ����x
	float speed_;

	// �e�̐�������
	bool isAlive_;

	// �e�̐�������
	int cntAlive_;

	// �e�̏Փ˔���p���a
	float collisionRadius_;

	// �p�����[�^�ݒ�
	virtual void SetParam(void) = 0;

	// �e�̐������Ԃ̌���
	void ReduceCntAlive(void);

};
