#pragma once
#include "Engine/GameObject.h"

//Ball���Ǘ�����N���X
class Ball : public GameObject
{
    int hModel_;    //���f���ԍ�
    int number_;    //�{�[���̔ԍ�(1�`9)���ʂ�0
    XMVECTOR velocity_;     //�ړ����x
public:
    //�R���X�g���N�^
    Ball(GameObject* parent);

    //�f�X�g���N�^
    ~Ball();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�{�[���̔ԍ����w�肷��
    void SetNumber(int no);

    //�ړ����x�̌v�Z
    void CalcVeloCity();

    //�ǂ̔��˂��v�Z����
    void CalcReflectWall();

    //���˂���x�N�g�����v�Z����
    //�����@�F�@���x�N�g��
    //�߂�l�F���˂����x�N�g��
    XMVECTOR CalcReflection(XMVECTOR Nomal);

    //�{�[���ɗ͂�������
    void AddForce(XMVECTOR f);

    //���̃t���[���ɂ�����W��Ԃ�
    XMFLOAT3 GetNextPosition() { return GetPosition() + velocity_; };

    //�ړ��ʂ̃Q�b�^�[�֐�
    XMVECTOR GetVelocity() { return velocity_; };

    bool IsMoving() { return (Length(velocity_) == 0.0f); };
};