#include <vector>
#include "Ready.h"
#include "Engine/Image.h"

namespace {
	float startX;     //移動開始のX座標
	float endX;       //移動終了のX座標
	float totalTime;  //移動時間
	float currentTime;//現在の時間

	int seqLine;		//今実行しているシークエンス
	float seqTime;		//シークエンスを実行している時間
	//シークエンスの中身
	enum ACT {
		A_SLIDEIN = 1,	//スライドイン
		A_WAIT,			//待機
		A_SLIDEOUT,		//スライドアウト
		A_END,			//終わり（消滅）
	};
	struct Sequence {
		float time;		//時間
		int action;		//やること
		float param;	//必要な値
	};
	std::vector<Sequence> tbl = {	//実行するシークエンスのテーブル
		{0.0f, A_SLIDEIN	,  5.0f},	//0秒目：スライドイン
		{3.0f, A_WAIT		,  0.0f},	//3秒目：1秒待ってから
		{4.0f, A_SLIDEOUT	, -5.0f},	//4秒目：スライドアウト
		{5.0f, A_END		,  0.0f},	//5秒目：そして、消滅
	};
	ACT currentAction;	//今実行しているアクション
	bool canMove;		//プレイヤーが移動できるか
};

float EaseInCubic(float x) {
	return x * x * x;
}

//コンストラクタ
Ready::Ready(GameObject* parent)
	:GameObject(parent, "Ready"), hPict_(-1)
{
	seqLine = -1;
	seqTime = 0.0f;
	canMove = false;
}

//デストラクタ
Ready::~Ready() {
}

//初期化
void Ready::Initialize() {
	//画像データのロード
	hPict_ = Image::Load("ReadyText.png");
	assert(hPict_ >= 0);
}

//更新
void Ready::Update() {
	seqTime += 1.0f / 60.0f;	//時間を進める
	//次のテーブルの開始時間を過ぎていたらシークエンスを一つ進める
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

	currentTime += 1.0f / 60.0f;	//1フレーム分の時間
	if (currentTime > totalTime)
		currentTime = totalTime;
	float t = currentTime / totalTime;
	float val = EaseInCubic(t);
	transform_.position_.x = (endX - startX) * val + startX;
}

//描画
void Ready::Draw() {
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void Ready::Release() {
}

bool Ready::Finished() {
	//return (currentTime < totalTime);
	return !canMove;
}
