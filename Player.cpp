#include "Player.h"
#include "Ball.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), myBall_(nullptr), direction_(0.0f), power_(0.1f)
     ,hModel_(-1)
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
    transform_.scale_.x *= 0.3f;
    transform_.scale_.y *= 0.3f;
    transform_.scale_.z *= 0.3f;
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("no0.fbx");
    assert(hModel_ >= 0);
}

//�X�V
void Player::Update()
{
    if (Input::IsKey(DIK_A)) {
        direction_ -= 0.03f;
    }
    if (Input::IsKey(DIK_D)) {
        direction_ += 0.03f;
    }
    if (Input::IsKeyDown(DIK_SPACE)) {
        //�ʂ𔭎˂���
        XMVECTOR base = XMVectorSet(0, 0, power_, 0);   //�ړ��ʂ̃X�J���[
        XMMATRIX yrot = XMMatrixRotationY(direction_);  //��]�s��
        XMVECTOR v = XMVector3Transform(base, yrot);    //�X�J���[�l�ɕ���������
        myBall_->AddForce(v);
    }
}

//�`��
void Player::Draw()
{
    if (hModel_ < 0)
        return;
    XMVECTOR base = XMVectorSet(0, 0, 1.2f, 0);     //�ړ��ʂ̃X�J���[
    XMMATRIX yrot = XMMatrixRotationY(direction_);  //��]�s��
    XMVECTOR v = XMVector3Transform(base, yrot);    //�X�J���[�l�ɕ���������
    transform_.position_ = myBall_->GetPosition() + v;

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Player::Release()
{
}