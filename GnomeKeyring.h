/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Gnome Keyring password manager storage.
 *
 * The Initial Developer of the Original Code is
 * Sylvain Pasche <sylvain.pasche@gmail.com>
 * Portions created by the Initial Developer are Copyright (C) 2007
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include "nsILoginManagerStorage.h"
extern "C" {
#include "gnome-keyring.h"
}

#define GNOMEKEYRING_CID \
{ 0xda355706, 0x2b26, 0x4682, { 0xbe, 0x76, 0xd6, 0x87, 0x13, 0x12, 0xd3, 0xa1}}

static const char kGnomeKeyringContractID[] = "@mozilla.org/gnome-keyring;1";

#ifdef PR_LOGGING
// (NSPR_LOG_MODULES=GnomeKeyringLog:5)
extern PRLogModuleInfo *gGnomeKeyringLog;
#endif
#define GK_LOG(args) PR_LOG(gGnomeKeyringLog, PR_LOG_DEBUG, args)
#define GK_LOG_ENABLED() PR_LOG_TEST(gGnomeKeyringLog, PR_LOG_DEBUG)

class GnomeKeyring : public nsILoginManagerStorage
{
  private:
  GnomeKeyringAttributeList *buildAttributeList(nsILoginInfo *aLogin);
  void appendAttributesFromBag(nsIPropertyBag *matchData,
                                    GnomeKeyringAttributeList * &attributes);
  nsresult deleteFoundItems(GList* foundList,
                                 PRBool);
  
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSILOGINMANAGERSTORAGE
};
