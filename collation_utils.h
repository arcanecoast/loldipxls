/****************************************************************************************//**

 Author of this file is
     __________ _______   __   _____ __ __________ _____ __ __ _____ ______   __ ____   
    / _   _   // ___  /__/ /_ / ___ / // _   _   // ___ / // //____// ____ \ / //___ \  
   / / / / / // /__/_//_  __// /  /  // / / / / // /  /  //   /    / /___/_//   /__/_/  
  / / / / / // /_____  / /_ / /__/  // / / / / // /__/  // /\ \__ / /_____ / /\ \__     
 /_/ /_/ /_/ \______/  \__/ \____/_//_/ /_/ /_/ \____/_//_/  \___/\______//_/  \___/    
                                                                                         
 webpage: http://www.goblinov.net
 email: guru@goblinov.net   

 This file is provided under certain circumstances. For more details see LICENSE file in
 the project's root folder.
  
 \author metamaker
 \brief 
 
 This unit provides functions to convert text from one collation to another. 

********************************************************************************************/

#include <string>

using std::string;
using std::wstring;

//! Convert string from Unicode to CP866 collation.
/*!
\param toConvert Unicode string to convert.
\return String in CP866 collation.
\sa Codepage866ToUnicode()
*/
string UnicodeToCodepage866(const wstring& toConvert);

//! Convert string from CP866 to Unicode collation.
/*!
\param toConvert CP866 string to convert.
\return String in Unicode collation.
\sa UnicodeToCodepage866()
*/
wstring Codepage866ToUnicode(const string& toConvert);
