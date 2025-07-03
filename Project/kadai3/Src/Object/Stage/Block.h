#pragma once
#include <DxLib.h>

class Block
{
public:

	// �u���b�N���f���̎��Ȕ����F
	static constexpr COLOR_F EMI_COLOR = { 0.5f, 0.5f, 0.5f, 1.0f };

	// �u���b�N���f���̑傫��
	//static constexpr VECTOR SCALES = { 0.5f, 0.5f, 0.5f };
	static constexpr VECTOR SCALE = { 0.51f, 0.51f, 0.51f };

	// 1�u���b�N������̃T�C�Y
	static constexpr float SIZE = 100.0f;

	// �u���b�N���
	enum class TYPE
	{
		NONE = -1,
		GRASS,
		METAL,
		ICE,

		MAX
	};

	// �R���X�g���N�^
	Block(void);

	// �f�X�g���N�^
	~Block(void);

	// �u���b�N�𐶐�����
	void Create(TYPE type, int baseModelId, int mapX, int mapZ);
	void Update(void);
	void Draw(void);
	void Release(void);

	// ���f���̃n���h��ID���擾����
	int GetModelId(void);

private:

	// �u���b�N���
	TYPE type_;

	// ���f���̃n���h��ID
	int modelId_;

	// ���W
	VECTOR pos_;

	// �傫��
	VECTOR scale_;

};
