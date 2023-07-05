#pragma once
#include "Gauge.h"
#include "Engine/GameObject.h"

class Ball;

//�S���t���Ɏg����ԑJ��
enum SHOT_STATE{
    S_ROTATE = 0,
    S_POWER,
    S_MOVE,
    S_MAX,
};

//Player���Ǘ�����N���X
class Player : public GameObject
{
    Ball* myBall_;      //���ʂ�\���|�C���^
    float direction_;   //�ʂ�ł����iY��]�̃��W�A���p�j
    float power_;       //�͂̋���
    int hModel_;        //���f���ԍ�

    //�����X�g��
    bool isPull_;       //�����Ă��邩�ǂ���
    XMFLOAT3 pullBegin_;//�J�n�n�_
    XMFLOAT3 pullEnd_;  //�I���n�_

    //�S���t��
    Gauge* pGauge;      //�`���[�W�o�[
    float chargeMax_;   //�ő�l
    float chargeLv_;    //���ݒl
    int state_;
    bool isCharge_;     //�`���[�W���Ă��邩
    bool isCountUp;     //�`���[�W�����債�Ă��邩
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