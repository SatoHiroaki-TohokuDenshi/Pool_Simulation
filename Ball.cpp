#include "Ball.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Ball::Ball(GameObject* parent)
    :GameObject(parent, "Ball"), hModel_(-1), number_(-1)
{
    velocity_ = XMVectorSet(0, 0, 0, 0);
}

//�f�X�g���N�^
Ball::~Ball() {
}

//������
void Ball::Initialize()
{
    if (hModel_ >= 0) {
        Model::Release(hModel_);
    }
}

//�X�V
void Ball::Update()
{
    //velocity_�̒��������߂�
    float len = Length(velocity_);
    //�Z������i�����j
    len -= 0.001f;
    //�P�ʃx�N�g���ɒ����̏���������
    velocity_ = XMVector3Normalize(velocity_) * len;

    //�ړ�
    transform_.position_ += velocity_;
}

//�`��
void Ball::Draw()
{
    if (hModel_ < 0)
        return;

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Ball::Release()
{
}

//�{�[���̔ԍ����w�肷��
void Ball::SetNumber(int no)
{
    number_ = no;
    //���f���f�[�^�̃��[�h
    std::string fileName = "no" + std::to_string(number_) + ".fbx";
    hModel_ = Model::Load(fileName);
    assert(hModel_ >= 0);
}

//�{�[���ɗ͂�������
void Ball::AddForce(XMVECTOR f)
{
    velocity_ += f;
}