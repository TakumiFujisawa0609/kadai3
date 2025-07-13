#pragma once
#include <DxLib.h>

class EnemyBase
{

public:

	// �R���X�g���N�^
	EnemyBase(void);

	// �f�X�g���N�^
	~EnemyBase(void);

	// ��������
	void Init(void);

	// �ǂݍ���
	void Load(void);

	// �ǂݍ��݌�
	void LoadEnd(void);

	// �X�V����
	void Update(void);

	// �`�揈��
	void Draw(void);

	// �������
	void Release(void);

private:
	// ���f���̃n���h��ID
	int modelId_;

	// ���W
	VECTOR pos_;
	// �p�x
	VECTOR angle_;
	// �傫��
	VECTOR scale_;

};


