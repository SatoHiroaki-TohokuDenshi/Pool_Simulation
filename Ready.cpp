#include <vector>
#include "Ready.h"
#include "Engine/Image.h"

namespace {
	float startX;     //�ړ��J�n��X���W
	float endX;       //�ړ��I����X���W
	float totalTime;  //�ړ�����
	float currentTime;//���݂̎���

	int seqLine;		//�����s���Ă���V�[�N�G���X
	float seqTime;		//�V�[�N�G���X�����s���Ă��鎞��
	//�V�[�N�G���X�̒��g
	enum ACT {
		A_SLIDEIN = 1,	//�X���C�h�C��
		A_WAIT,			//�ҋ@
		A_SLIDEOUT,		//�X���C�h�A�E�g
		A_END,			//�I���i���Łj
	};
	struct Sequence {
		float time;		//����
		int action;		//��邱��
		float param;	//�K�v�Ȓl
	};
	std::vector<Sequence> tbl = {	//���s����V�[�N�G���X�̃e�[�u��
		{0.0f, A_SLIDEIN	,  5.0f},	//0�b�ځF�X���C�h�C��
		{3.0f, A_WAIT		,  0.0f},	//3�b�ځF1�b�҂��Ă���
		{4.0f, A_SLIDEOUT	, -5.0f},	//4�b�ځF�X���C�h�A�E�g
		{5.0f, A_END		,  0.0f},	//5�b�ځF�����āA����
	};
	ACT currentAction;	//�����s���Ă���A�N�V����
	bool canMove;		//�v���C���[���ړ��ł��邩
};

float EaseInCubic(float x) {
	return x * x * x;
}

//�R���X�g���N�^
Ready::Ready(GameObject* parent)
	:GameObject(parent, "Ready"), hPict_(-1)
{
	seqLine = -1;
	seqTime = 0.0f;
	canMove = false;
}

//�f�X�g���N�^
Ready::~Ready() {
}

//������
void Ready::Initialize() {
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("ReadyText.png");
	assert(hPict_ >= 0);
}

//�X�V
void Ready::Update() {
	seqTime += 1.0f / 60.0f;	//���Ԃ�i�߂�
	//���̃e�[�u���̊J�n���Ԃ��߂��Ă�����V�[�N�G���X����i�߂�
	if (seqTime >= tbl.at(seqLine + 1).time) {
		seqLine++;
		switch (tbl.at(seqLine).action) {
		case A_END:
			KillMe();
			break;
		case A_SLIDEIN:
			startX = tbl.at(seqLine).param;
			endX = 0.0f;
			totalTime = tbl.at(seqLine + 1).time - seqTime;;
			currentTime = 0.0f;
			break;
		case A_WAIT:
			startX = transform_.position_.x;
			endX = transform_.position_.x;
			totalTime = tbl.at(seqLine + 1).time - seqTime;;
			currentTime = 0.0f;
			break;
		case A_SLIDEOUT:
			canMove = true;
			startX = transform_.position_.x;
			endX = tbl.at(seqLine).param;
			totalTime = tbl.at(seqLine + 1).time - seqTime;;
			currentTime = 0.0f;
			break;
		}
	}

	currentTime += 1.0f / 60.0f;	//1�t���[�����̎���
	if (currentTime > totalTime)
		currentTime = totalTime;
	float t = currentTime / totalTime;
	float val = EaseInCubic(t);
	transform_.position_.x = (endX - startX) * val + startX;
}

//�`��
void Ready::Draw() {
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void Ready::Release() {
}

bool Ready::Finished() {
	//return (currentTime < totalTime);
	return !canMove;
}
