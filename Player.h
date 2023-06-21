#pragma once
#include "Engine/GameObject.h"

class Ball;

//Player���Ǘ�����N���X
class Player : public GameObject
{
    Ball* myBall_;      //���ʂ�\���|�C���^
    float direction_;   //�ʂ�ł����iY��]�̃��W�A���p�j
    float power_;       //�͂̋���
    int hModel_;        //���f���ԍ�

    bool isPull_;
    XMFLOAT3 pullBegin_;
    XMFLOAT3 pullEnd_;

    bool isCharge_;
    bool isCountUp;
public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�v���C���[�����삷��ʂ̐ݒ�
    void SetMyBall(Ball* ball) { myBall_ = ball; };
};