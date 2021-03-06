/*
 *      Copyright (C) 2005-2013 Team XBMC
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

#include <stdint.h>

class BitstreamStats final
{
public:
  // in order not to cause a performance hit, we should only check the clock when
  // we reach m_nEstimatedBitrate bits.
  // if this value is 1, we will calculate bitrate on every sample.
  explicit BitstreamStats(unsigned int nEstimatedBitrate=(10240*8) /*10Kbit*/);

  void AddSampleBytes(unsigned int nBytes);
  void AddSampleBits(unsigned int nBits);

  inline double GetBitrate()    const { return m_dBitrate; }
  inline double GetMaxBitrate() const { return m_dMaxBitrate; }
  inline double GetMinBitrate() const { return m_dMinBitrate; }

  void Start();
  void CalculateBitrate();

private:
  double m_dBitrate;
  double m_dMaxBitrate;
  double m_dMinBitrate;
  unsigned int m_nBitCount;
  unsigned int m_nEstimatedBitrate; // when we reach this amount of bits we check current bitrate.
  int64_t m_tmStart;
  static int64_t m_tmFreq;
};

