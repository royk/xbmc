/*
 *      Copyright (C) 2005-2011 Team XBMC
 *      http://xbmc.org
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
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include "PeripheralNyxboard.h"
#include "PeripheralHID.h"
#include "guilib/Key.h"
#include "utils/log.h"
#include "interfaces/Builtins.h"

using namespace PERIPHERALS;
using namespace std;

CPeripheralNyxboard::CPeripheralNyxboard(const PeripheralType type, const PeripheralBusType busType, const CStdString &strLocation, const CStdString &strDeviceName, int iVendorId, int iProductId) :
  CPeripheralHID(type, busType, strLocation, strDeviceName, iVendorId, iProductId)
{
  m_features.push_back(FEATURE_NYXBOARD);
}

bool CPeripheralNyxboard::LookupSymAndUnicode(XBMC_keysym &keysym, uint8_t *key, char *unicode)
{
  CStdString strCommand;
  if (keysym.sym == XBMCK_F7 && keysym.mod == XBMCKMOD_NONE && GetSettingBool("enable_flip_commands"))
  {
    /* switched to keyboard side */
    CLog::Log(LOGDEBUG, "%s - switched to keyboard side", __FUNCTION__);
    strCommand = GetSettingString("flip_keyboard");
  }
  else if (keysym.sym == XBMCK_F7 && keysym.mod == XBMCKMOD_LCTRL && GetSettingBool("enable_flip_commands"))
  {
    /* switched to remote side */
    CLog::Log(LOGDEBUG, "%s - switched to remote side", __FUNCTION__);
    strCommand = GetSettingString("flip_remote");
  }
  else if (keysym.sym == XBMCK_F4 && keysym.mod == XBMCKMOD_NONE)
  {
    /* 'user' key pressed */
    CLog::Log(LOGDEBUG, "%s - 'user' key pressed", __FUNCTION__);
    strCommand = GetSettingString("key_user");
  }

  if (!strCommand.IsEmpty())
  {
    CLog::Log(LOGDEBUG, "%s - executing command '%s'", __FUNCTION__, strCommand.c_str());
    CBuiltins::Execute(strCommand);

    *key = 0;
    *unicode = (char) 0;
    return true;
  }

  return false;
}
