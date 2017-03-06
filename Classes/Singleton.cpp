#include "stdafx.h"

Singleton* Singleton::m_uInstance = NULL;
Singleton* Singleton::getInstance()
{
	if (!m_uInstance)
		m_uInstance = new Singleton();

	return m_uInstance;
}