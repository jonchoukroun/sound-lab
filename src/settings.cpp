#include "settings.h"

int Settings::sampleRate() const { return m_sampleRate; }
void Settings::sampleRate(int s) { m_sampleRate = s; }

int Settings::sampleCount() const { return m_sampleCount; }
void Settings::sampleCount(int s) { m_sampleCount = s; }

int Settings::bitDepth() const { return m_bitDepth; }
void Settings::bitDepth(int b) { m_bitDepth = b; }

int Settings::channelCount() const { return m_channelCount; }
void Settings::channelCount(int c) { m_channelCount = c; }

int Settings::screenWidth() const { return m_screenWidth; }
void Settings::screenWidth(int s) { m_screenWidth = s; }

int Settings::screenHeight() const { return m_screenHeight; }
void Settings::screenHeight(int s) { m_screenHeight = s; }
