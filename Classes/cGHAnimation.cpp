#include "cGHAnimation.h"

namespace GH
{

	bool CGHAnimation::Init(string plistPath, string imageGetpath, string extension, int maxFrame, int intervalStart)
	{
		//!< 초기화 구문
		m_strPlistPath	= plistPath;
		m_strImagePath	= imageGetpath;
		m_strExtension	= extension;
		m_cPos			= ccp(0,0);
		m_nLayer		= 0;
		m_nMaxFrame		= maxFrame;
		m_fTumTime		= 0.1f;
		m_nNowFrame		= 0;
		m_bType			= false;
		m_bStop			= false;
		m_bVisible		= true;
		m_fCurTime		= 0.0f;
		m_nLoopCount	= 1;
		m_nNowLoopCount = 0;

		//!< Plist에 등록된 이미지 로드
		String* plistStringName = String::createWithFormat("%s.plist" , plistPath.c_str());
		if(plistStringName == NULL) return false;
		//!< Plist에 등록된 이미지 캐싱
		SpriteFrameCache* cache = SpriteFrameCache::sharedSpriteFrameCache();
		//!< 캐시에 넣음
		cache->addSpriteFramesWithFile(plistStringName->getCString());

		//!< 갯수만큼 interval 돌아서 애니메이션 구축
		for(int i = intervalStart ; i < m_nMaxFrame + intervalStart ; i++)
		{
			//!< plist 의 key 값들 가져옴
			String * fileName = CCString::createWithFormat("%s%d%s" , imageGetpath.c_str() , i , extension.c_str());

			//!< 프레임 등록
			SpriteFrame* frame = cache->spriteFrameByName(fileName->getCString());

			//!< 한장마다 등록
			auto pSprite = new GH::CGHSprite;
			pSprite->initWithSpriteFrame(frame);
			pSprite->setPosition(m_cPos);
			pSprite->setVisible(false);

			//!< vector에 등록하여 자원관리
			m_pTable.push_back(pSprite);
		}

		//!< 첫 프레임은 보이도록 설정
		m_pTable[0]->setVisible(true);

		return true;
	}

	void CGHAnimation::AnimationUpdate(float dt)
	{
		if(m_bStop) return;

		switch(m_bType)
		{
		case true:
			//!< 이펙트 일때
			if(m_nNowLoopCount >= m_nLoopCount) return;
			//!< 시간 타이머 누적
			m_fCurTime += dt;

			//!< 만약 다음 프레임으로 넘어갈 시간일 경우
			if(m_fCurTime >= m_fTumTime)
			{
				m_pTable[m_nNowFrame]->setVisible(false);			//!< 이전 프레임은 안보이도록 설정
				m_nNowFrame++;										//!< 현재 프레임을 증가
				m_fCurTime = 0;										//!< 재는 시간은 초기화
			}

			//!< 반복되면 안되므로 마지막 프레임으로 고정
			//!< 최대 반복횟수 설정 한 것 만큼 돌음
			if(m_nNowFrame >= m_nMaxFrame)
			{
				m_nNowLoopCount++;
				m_nNowFrame = 0;
			}

			if(m_nNowLoopCount >= m_nLoopCount) m_nNowFrame = m_nMaxFrame - 1;

			break;
		case false:
			//!< 이펙트 아닐때

			//!< 시간 타이머 누적
			m_fCurTime += dt;

			//!< 만약 다음 프레임으로 넘어갈 시간일 경우
			if(m_fCurTime >= m_fTumTime)
			{
				m_pTable[m_nNowFrame]->setVisible(false);			//!< 이전 프레임은 안보이도록 설정
				m_nNowFrame++;										//!< 현재 프레임을 증가
				m_fCurTime = 0;										//!< 재는 시간은 초기화
			}

			//!< 반복되야 하므로 현재 프레임이 최대 프레임 넘어갈 시 초기 프레임으로 재 설정
			if(m_nNowFrame >= m_nMaxFrame)
				m_nNowFrame = 0;

			break;
		}

		if(m_bVisible)
		{
			if(!m_pTable[m_nNowFrame]->isVisible())
				m_pTable[m_nNowFrame]->setVisible(true);
		}
		else
		{
			if(m_pTable[m_nNowFrame]->isVisible())
				m_pTable[m_nNowFrame]->setVisible(false);
		}
	}

	void CGHAnimation::addChild()
	{
		for (int i = 0; i < m_nMaxFrame; i++)
			m_pLayer->addChild(m_pTable[i], m_nLayer);
	}

	void CGHAnimation::setAniTime(float time)
	{
		m_fTumTime = time;
	}

	float CGHAnimation::getAniTime()
	{
		return m_fTumTime;
	}

	void CGHAnimation::setEffect(bool bChk)
	{
		m_bType = bChk;
	}

	bool CGHAnimation::getEffect()
	{
		return m_bType;
	}

	void CGHAnimation::setLoopCount(int nLoop)
	{
		m_nLoopCount = nLoop;
	}

	int CGHAnimation::getLoopCount()
	{
		return m_nLoopCount;
	}

	void CGHAnimation::setLayer(int nLayer)
	{
		m_nLayer = nLayer;
	}

	int CGHAnimation::getLayer()
	{
		return m_nLayer;
	}

	void CGHAnimation::setPosition(Point pos)
	{
		m_cPos = pos;
		for (int i = 0; i < m_nMaxFrame; i++)
			m_pTable[i]->setPosition(m_cPos);
	}

	Point CGHAnimation::getPosition()
	{
		return m_cPos;
	}

	void CGHAnimation::setAnchorPositon(Point pos)
	{
		m_pTable[m_nNowFrame]->setAnchorPoint(pos);
	}

	Point CGHAnimation::getAnchorPosition()
	{
		return m_pTable[m_nNowFrame]->getAnchorPoint();
	}

	void CGHAnimation::setVisible(bool bChk)
	{
		m_bVisible = bChk;
	}

	bool CGHAnimation::getVisible()
	{
		return m_bVisible;
	}

	void CGHAnimation::setScale(Point pos)
	{
		m_cScale = pos;
		m_pTable[m_nNowFrame]->setScaleX(m_cScale.x);
		m_pTable[m_nNowFrame]->setScaleY(m_cScale.y);
	}

	float CGHAnimation::getScale()
	{
		return m_pTable[m_nNowFrame]->getScale();
	}

	void CGHAnimation::setFrame(int nFrame)
	{
		m_pTable[m_nNowFrame]->setVisible(false);
		m_nNowFrame = nFrame;
		m_fCurTime = 0.0f;
		m_pTable[m_nNowFrame]->setVisible(true);
	}

	int CGHAnimation::getFrame()
	{
		return m_nNowFrame;
	}

	void CGHAnimation::setStop()
	{
		m_bStop = true;
	}

	void CGHAnimation::setResume()
	{
		m_bStop = false;
	}

	void CGHAnimation::Destroy()
	{
		for(int i = 0 ; i < m_pTable.size() ; i++)
			CC_SAFE_DELETE(m_pTable[i]);

		m_pTable.clear();
	}
}