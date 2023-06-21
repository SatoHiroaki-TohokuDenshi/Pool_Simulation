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
    if (hModel_ >= 0) {
        Model::Release(hModel_);
    }
}

//������
void Ball::Initialize()
{
}

//�X�V
void Ball::Update()
{
    //�ړ����x���v�Z����
    CalcVeloCity();

    //�{�[�����m�̔���
    std::list<Ball*> all = GetParent()->FindGameObjects<Ball>();
    for (std::list<Ball*>::iterator itr = all.begin(); itr != all.end(); itr++) {
        if (*itr == this) continue;
        XMFLOAT3 next = transform_.position_ + velocity_;   //���̃t���[���̎���
        XMFLOAT3 other = (*itr)->GetNextPosition();         //���̃t���[���̑���
        //2�̋ʂ̋������ʂ̒��a���Z��
        if (Length(next - other) < 1.0f * 2.0f) {
            //����ɗ͂�������
            XMVECTOR n = other - next;
            n = XMVector3Normalize(n);      //n�̒�����1�ɂ���
            XMVECTOR powDot = XMVector3Dot(velocity_, n);
            float pow = XMVectorGetX(powDot);   //�����͂̑傫��
            XMVECTOR push = n * pow;
            velocity_ -= push;
            (*itr)->AddForce(push);

            //���肩��͂��󂯎��
            n = next - other;
            n = XMVector3Normalize(n);      //n�̒�����1�ɂ���
            powDot = XMVector3Dot(velocity_, n);
            pow = XMVectorGetX(powDot);     //�����͂̑傫��
            push = n * pow;
            (*itr)->AddForce(-push);        //���肩�����
            this->AddForce(push);           //�����ɉ�����


        }
    }
    
    //�ǂƂ̔��˂��v�Z����
    CalcReflectWall();



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

//�ړ����x�̌v�Z
void Ball::CalcVeloCity() {
    //velocity_�̒��������߂�
    float len = Length(velocity_);
    //�Z������i�����j
    len -= 0.001f;
    if (len < 0.0f) len = 0.0f;
    //�P�ʃx�N�g���ɒ����̏���������
    velocity_ = XMVector3Normalize(velocity_) * len;
}

//�ǂ̔��˂��v�Z����
void Ball::CalcReflectWall() {
    XMVECTOR n = XMVectorSet(-1, 0, 0, 0);     //�ǂ̖@���x�N�g��
    XMFLOAT3 nextPos = transform_.position_ + velocity_;
    if (nextPos.x >= 30.0f) {
        n = XMVectorSet(-1,0,0,0);
        n *= -1;
        velocity_ = CalcReflection(n);
    }
    if (nextPos.x <= -30.0f) {
        n = XMVectorSet( 1, 0, 0, 0);
        n *= -1;
        velocity_ = CalcReflection(n);
    }
    if (nextPos.z >= 20.0f) {
        n = XMVectorSet( 0, 0, -1, 0);
        n *= -1;
        velocity_ = CalcReflection(n);
    }
    if (nextPos.z <= -20.0f) {
        n = XMVectorSet( 0, 0,  1, 0);
        n *= -1;
        velocity_ = CalcReflection(n);
    }
}

//���˂���x�N�g�����v�Z����
//�����@�F�@���x�N�g��
//�߂�l�F���˂����x�N�g��
XMVECTOR Ball::CalcReflection(XMVECTOR Nomal) {
    XMVECTOR ipvec = XMVector3Dot(velocity_, Nomal);
    float ip = XMVectorGetX(ipvec);         //�ǂ������͂̑傫��
    XMVECTOR push = Nomal * ip;             //�ǂ������x�N�g��
    XMVECTOR through = velocity_ - push;    //�ǂɉ������x�N�g��
    push *= -1;                             //�����Ԃ����x�N�g��
    return (push + through);                //���˂���x�N�g��
}