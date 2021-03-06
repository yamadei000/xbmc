/*
 *      Copyright (C) 2012-2013 Team XBMC
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include <functional>

#include "Event.h"
#include "Thread.h"

class ITimerCallback
{
public:
  virtual ~ITimerCallback() = default;

  virtual void OnTimeout() = 0;
};

class CTimer : protected CThread
{
public:
  explicit CTimer(ITimerCallback *callback);
  explicit CTimer(std::function<void()> const& callback);
  ~CTimer() override;

  bool Start(uint32_t timeout, bool interval = false);
  bool Stop(bool wait = false);
  bool Restart();
  void RestartAsync(uint32_t timeout);

  bool IsRunning() const { return CThread::IsRunning(); }

  float GetElapsedSeconds() const;
  float GetElapsedMilliseconds() const;

protected:
  void Process() override;

private:
  std::function<void()> m_callback;
  uint32_t m_timeout;
  bool m_interval;
  uint32_t m_endTime;
  CEvent m_eventTimeout;
};
