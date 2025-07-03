#pragma once

// �O���b�h���̕\��
class Grid
{

public:
	// �萔��`

	// ���̒���
	static constexpr float LEN = 3000.0f;

	// ���̒����̔���
	static constexpr float HLEN = LEN / 2.0f;

	// ���̊Ԋu
	static constexpr float DISTANCE = 100.0f;

	// ���̐�
	static const int NUM = static_cast<int>(LEN / DISTANCE);

	// ���̐��̔���
	static const int HNUM = NUM / 2;

	// �R���X�g���N�^
	Grid(void);

	// �f�X�g���N�^
	~Grid(void);

	void Init(void);		// ������
	void Update(void);		// �X�V
	void Draw(void);		// �`��
	void Release(void);		// �X�V

};
