#include "Stage.h"
#include "Block.h"

Block::Block(void)
{
}

Block::~Block(void)
{
}

void Block::Create(TYPE type, int baseModelId, int mapX, int mapZ)
{
	// �u���b�N�̎��
	type_ = type;

	// �I���W�i�����f���𕡐�����B
	modelId_ = MV1DuplicateModel(baseModelId);

	// �F�̒���(���Ȕ���)
	MV1SetMaterialEmiColor(modelId_, 0, EMI_COLOR);

	// 1�u���b�N������̔����̑傫��
	const float SIZE_HALF_BLOCK = (SIZE / 2.0f);

	// �傫���ݒ�
	scale_ = SCALE;
	MV1SetScale(modelId_, scale_);

	// �����Ŏw�肳�ꂽ�}�b�v���W������W���v�Z����
	// ����̂R�c���f���̒��S���W�́A�u���b�N�̒��S�Ɉʒu����
	float x = static_cast<float>(mapX);
	float z = static_cast<float>(mapZ);
	VECTOR pos = VGet(
		(SIZE * x) + SIZE_HALF_BLOCK,
		-SIZE_HALF_BLOCK,
		(SIZE * z) + SIZE_HALF_BLOCK
	);

	// ���W�ݒ�
	pos_ = pos;
	MV1SetPosition(modelId_, pos_);
}

void Block::Update(void)
{
}

void Block::Draw(void)
{
	// ���f���̕`��
	MV1DrawModel(modelId_);
}

void Block::Release(void)
{
	// ���f���̃��������
	MV1DeleteModel(modelId_);
}

int Block::GetModelId(void)
{
	return modelId_;
}
