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
 
 DIPPath structure is defined in this file. This structure describes two distinct paths for
 a translation file: one for the original file and another one for translated.

 All paths to .DIP files are stored in DIP_PATHS constant.
 
********************************************************************************************/

#define DIP_FILES_COUNT 2

struct DIPPath {
    const char *TranslatedPackageName; //! Path to the package with translated .DIP file
    const char *NotTranslatedPackageName; //! Path to the package with original .DIP file
    const char *FileName;  //! Filename of translation file in the package
    const char *SheetName; //! File's sheet name in .XLS file
};

extern const DIPPath DIP_PATHS[DIP_FILES_COUNT];
