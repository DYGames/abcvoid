#pragma once

#include "cocos2d.h"
#include "CGHSprite.h"

USING_NS_CC;
using namespace std;

namespace GH
{
	class CGHAnimation
	{
	private:
		Layer*					m_pLayer;				//!< 이미지 뿌릴 경로
		string					m_strPlistPath;			//!< Plist 경로
		string					m_strImagePath;			//!< 이미지 이름
		string					m_strExtension;			//!< 확장자
		Point					m_cPos;
		Point					m_cScale;

		int						m_nLayer;				//!< 그려줄 레이어 번호
		int						m_nNowFrame;			//!< 현재 애니메이션 실행중인 프레임
		int						m_nMaxFrame;			//!< 최대 애니메이션 갯수
		int						m_nLoopCount;			//!< 몇번 재생하는 지
		int						m_nNowLoopCount;		//!< 현재 재생한 갯수

		bool					m_bType;				//!< 타입이 이펙트 인지 아닌지
		bool					m_bVisible;				//!< 애니메이션을 보이게 할지 안할지
		bool					m_bStop;				//!< 정지할 지 안할 지

		float					m_fTumTime;				//!< 다음 스프라이트로 넘어갈 시간
		float					m_fCurTime;				//!< 현재 진행중인 시간

		vector<GH::CGHSprite*>	m_pTable;				//!< vector 테이블 (Sprite 보관)

	public:
		CGHAnimation(Layer* pLayer) : m_pLayer(pLayer){}
		~CGHAnimation() { Destroy(); }

	public:
		/**
		@brief : 애니메이션 초기화 만약 image/hero/texture_hero.plist , png 파일이 있다면 Init("image/hero/texture_hero" , "hero_" , ".png" , 5 , 0); 해주면 됨
		@param : Plist의 경로 ( 확장자를 뺌 )
		@param : plist 내부의 사용할 이미지 이름
		@param : 확장자 이름
		@param : 최대 프레임 갯수
		@param : 0부터 시작할 것인지 1부터 시작할 것인지 설정
		@return : true 정상적인 초기화
		@return : false 초기화 실패
		*/
		bool Init(string plistPath , string imageGetpath , string extension , int maxFrame = 1, int intervalStart = 0);

		/**
		@brief : 애니메이션 업데이트 클래스
		@param : delay time
		*/
		void AnimationUpdate(float dt);

		void addChild();

		void setEffect(bool bChk);
		bool getEffect();

		void setLoopCount(int nLoop);
		int getLoopCount();

		void setAniTime(float time);
		float getAniTime();

		void setLayer(int nLayer);
		int getLayer();

		void setPosition(Point pos);
		Point getPosition();

		void setAnchorPositon(Point pos);
		Point getAnchorPosition();

		void setVisible(bool bChk);
		bool getVisible();

		void setScale(Point pos);
		float getScale();

		void setFrame(int nFrame);
		int getFrame();

		void setStop();
		void setResume();

		void Destroy();
	};
}