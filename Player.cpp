#include "Player.h"
#include "Ball.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), myBall_(nullptr), direction_(0.0f), power_(0.1f)
     ,hModel_(-1), isPull_(false), pullBegin_(0.0f, 0.0f, 0.0f), pullEnd_(0.0f, 0.0f, 0.0)
     ,state_(S_ROTATE), chargeMax_(1.0f), chargeLv_(0.0f), pGauge(nullptr), isCharge_(false), isCountUp(true)
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

    pGauge = Instantiate<Gauge>(this);
    pGauge->SetValue(chargeMax_, chargeLv_);
}

//�X�V
void Player::Update()
{
    //�ʏ�̓���
    //if (!isCharge_) {
    //    if (Input::IsKey(DIK_A)) {
    //        direction_ -= 0.03f;
    //    }
    //    if (Input::IsKey(DIK_D)) {
    //        direction_ += 0.03f;
    //    }
    //}
    //if (Input::IsKeyDown(DIK_SPACE)) {
    //    //�ʂ𔭎˂���
    //    XMVECTOR base = XMVectorSet(0, 0, power_, 0);   //�ړ��ʂ̃X�J���[
    //    XMMATRIX yrot = XMMatrixRotationY(direction_);  //��]�s��
    //    XMVECTOR v = XMVector3Transform(base, yrot);    //�X�J���[�l�ɕ���������
    //    myBall_->AddForce(v);
    //}

    //�C�ӂ̑�����@
    //�����X�g��
    //�}�E�X�̃N���b�N�œ��͊J�n
    //���������ė����Ɣ��Ό����ɔ���
    {
        if (!isPull_) {
            if (Input::IsMouseButtonDown(0)) {
                isPull_ = true;
                pullBegin_.x = Input::GetMousePosition().x;
                pullBegin_.z = Input::GetMousePosition().y;
            }
        }
        else {
            if (Input::IsMouseButtonUp(0)) {
                isPull_ = false;
                pullEnd_.x = Input::GetMousePosition().x;
                pullEnd_.z = Input::GetMousePosition().y;
                direction_ = (float)atan2((double)(pullBegin_.x - pullEnd_.x),
                    (double)(pullEnd_.z - pullBegin_.z));
                XMVECTOR pullvec = pullBegin_ - pullEnd_;
                //pullvec = XMVector3Normalize(pullvec);
                power_ = Length(pullvec) / 300.0f;

                XMVECTOR base = XMVectorSet(0, 0, power_, 0);   //�ړ��ʂ̃X�J���[
                XMMATRIX yrot = XMMatrixRotationY(direction_);  //��]�s��
                XMVECTOR v = XMVector3Transform(base, yrot);    //�X�J���[�l�ɕ���������
                myBall_->AddForce(v);
                power_ = 0.1f;
            }
            else {
                pullEnd_.x = Input::GetMousePosition().x;
                pullEnd_.z = Input::GetMousePosition().y;
                direction_ = (float)atan2((double)(pullBegin_.x - pullEnd_.x),
                    (double)(pullEnd_.z - pullBegin_.z));
            }
        }
    }

    //�S���t��
    //A/D�ŕ���������
    //Enter�Ńp���[�𗭂߂�
    //0�����^����0�Ƃ������ɐ��ڂ���
    //�s�b�^�����^���̏ꍇ�̓X�[�p�[�V���b�g
    switch (state_) {
    case S_ROTATE:
        if (Input::IsKey(DIK_A)) direction_ -= 0.03f;
        if (Input::IsKey(DIK_D)) direction_ += 0.03f;
        if (Input::IsKeyDown(DIK_RETURN)) state_ = S_POWER;
        break;
    case S_POWER:
        //�p�x����ɖ߂�
        if (Input::IsKeyDown(DIK_ESCAPE)) state_ = S_ROTATE;
        if (chargeLv_ < -0.1f) isCountUp = true;
        else if (chargeLv_ >= chargeMax_) isCountUp = false;

        if (isCountUp) {
            chargeLv_ += 0.01f;
            pGauge->SetValue(chargeMax_, chargeLv_);
        }
        else {
            chargeLv_ -= 0.01f;
            pGauge->SetValue(chargeMax_, chargeLv_);
        }

        //�ł��o��
        if (Input::IsKeyDown(DIK_RETURN)) {
            if (abs(chargeMax_ - chargeLv_) == 0.1) chargeLv_ = 2.0f;   //�X�[�p�[�V���b�g
            XMVECTOR base = XMVectorSet(0, 0, power_ + chargeLv_, 0);   //�ړ��ʂ̃X�J���[
            XMMATRIX yrot = XMMatrixRotationY(direction_);  //��]�s��
            XMVECTOR v = XMVector3Transform(base, yrot);    //�X�J���[�l�ɕ���������
            myBall_->AddForce(v);
            chargeLv_ = 0.0f;
            state_ = S_MOVE;
        }
        break;
    case S_MOVE:
        std::list<Ball*> all = GetParent()->FindGameObjects<Ball>();
        bool flag = true;
        for (auto itr : all) {
            if ((*itr).IsMoving()) {
                flag = false;
                break;
            }
        }
        if (flag) state_ = S_ROTATE;
        break;
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