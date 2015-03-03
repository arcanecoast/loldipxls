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
 
 This application has 2 primary functions:
 1. Extract all .DIP files from Lands of Lore .PAKs and write them to .XLS.
 2. Update all .DIP files with modified strings from .XLS.
 
********************************************************************************************/

#include <cstring>
#include <iostream>
#include <sstream>

#include <lollibs/Package.h>
#include <lollibs/Translation.h>

#include <ExcelFormat.h>

#include "collation_utils.h"
#include "dip_list.h"

using namespace std;
using namespace lollibs;
using namespace ExcelFormat;

void ShowHelp()
{
    char *helpline =
"Lands of Lore XLS to/from DIP\n"
"----------------------------\n\n"
"Author:     metamaker\n"
"Build date: 23.02.2015\n"
"Version:    0.1\n"
"\n----------------------------\n\n"
"Usage: loldipxls <command>\n\n"
"Available commands:\n\n"
"- toxls <filename.xls> -- extract all .DIPs' strings to <filename.xls>\n"
"- fromxls <filename.xls> -- update all .DIPs with strings from <filename.xls>\n";

    cout << helpline << endl;
}

//! Write single translation file to .XLS worksheet. As side effect it writes hint about the error to cout
//! (in the case if any error occurred).
/*!
\param packageName relative path to package which contains needed file.
\param fileName name of translation file in the package.
\param worksheet .XLS file's worksheet to write translation strings to.
\param column column to write translation strings to.
\return true - if the operation was completed successfully; false - if an error occured.
\sa DIPtoXLS()
*/
bool WriteTranslationToXLS(const string& packageName, const string& fileName, BasicExcelWorksheet* worksheet, size_t column)
{
    // Load translation from .DIP file (named as `fileName') from the `packageName' package.

    Package package;
    package.LoadFromFile(packageName.c_str());

    Package::iterator fileInPackage = package.Find(fileName);
    if (fileInPackage == package.End()) {
        cout << "Error occurred while reading " << packageName << ":" << fileName << " file" << endl;

        return false;
    }

    Translation translatedFile;
    translatedFile.LoadFromMemory(fileInPackage->second.GetContent(), static_cast<unsigned short>(fileInPackage->second.GetSize()));

    // Write every record of .DIP file to .XLS

    for (int entryIndex = 0, entryEnd = translatedFile.Size(); entryIndex != entryEnd; ++entryIndex) {
        wstring utf8String = Codepage866ToUnicode(translatedFile[entryIndex]);

        worksheet->Cell(entryIndex, column)->Set(utf8String.c_str());
    }

    return true;
}

//! Write all Lands of Lore game's .DIP files to .XLS.
/*!
\param pathToXls path to new .XLS file where to write .DIP translation.
\return 0 - if the conversion was successfull; 1 - if an error occured
*/
int DIPtoXLS(const char* pathToXls)
{
    // Iterate through paths and write content of every original and translated .DIP file to .XLS

    BasicExcel xlsFile;

    for (int pathIndex = 0, pathEnd = DIP_FILES_COUNT; pathIndex != pathEnd; ++pathIndex) {
        BasicExcelWorksheet* sheet = xlsFile.AddWorksheet(DIP_PATHS[pathIndex].SheetName);

        // Write translated .DIP file to .XLS

        if (!WriteTranslationToXLS(DIP_PATHS[pathIndex].TranslatedPackageName, DIP_PATHS[pathIndex].FileName, sheet, 0)) {
            return 1;
        }

        // Write original .DIP file to .XLS

        if (!WriteTranslationToXLS(DIP_PATHS[pathIndex].NotTranslatedPackageName, DIP_PATHS[pathIndex].FileName, sheet, 1)) {
            return 1;
        }
    }

    // Save .XLS file

    xlsFile.SaveAs(pathToXls);

    return 0;
}

//! Write single .XLS worksheet to translation file. As side effect it writes hint about the error to cout
//! (in the case if any error occurred).
/*!
\param packageName relative path to package which contains needed file.
\param fileName name of translation file in the package.
\param worksheet .XLS file's worksheet to write translation strings from.
\return true - if the operation was completed successfully; false - if an error occured.
\sa DIPtoXLS()
*/
bool WriteXLSSheetToTranslation(const string& packageName, const string& fileName, BasicExcelWorksheet* worksheet)
{
    // Load translation from .DIP file (named as `fileName') from the `packageName' package.

    Package package;
    package.LoadFromFile(packageName.c_str());

    Package::iterator fileInPackage = package.Find(fileName);
    if (fileInPackage == package.End()) {
        cout << "Error occurred while reading " << packageName << ":" << fileName << " file" << endl;

        return false;
    }

    Translation translatedFile;
    translatedFile.LoadFromMemory(fileInPackage->second.GetContent(), static_cast<unsigned short>(fileInPackage->second.GetSize()));

    // Update entries of translation file

    for (int entryIndex = 0, entryEnd = translatedFile.Size(); entryIndex != entryEnd; ++entryIndex) {
        const wchar_t* unicodeString = worksheet->Cell(entryIndex, 0)->GetWString();

        if (unicodeString != nullptr) {
            string cp866String = UnicodeToCodepage866(unicodeString);

            translatedFile[entryIndex] = cp866String;
        }
    }

    // Generate translation file binary content (to write on disk or to memory or elsewhere)

    stringstream outStreamTranslation(ios_base::out | ios_base::in | ios_base::binary);
    translatedFile.SaveToStream(outStreamTranslation);

    // Get generated translation file content size

    outStreamTranslation.seekg(0, ios_base::end);
    unsigned long translationFileSize = static_cast<unsigned long>(outStreamTranslation.tellg());
    outStreamTranslation.seekg(0);

    // Write the file's new content to package

    char *translationFileContent = new char[translationFileSize];
    outStreamTranslation.read(translationFileContent, translationFileSize);
    fileInPackage->second.SetContent(translationFileContent, translationFileSize);

    // Save package

    package.SaveToFile(packageName.c_str());

    return true;
}

//! Update all Lands of Lore game's .DIP files from .XLS.
/*!
\param pathToXls path to .XLS file with .DIP translation modifications.
\return 0 - if the conversion was successfull; 1 - if an error occured
\sa WriteXLSSheetToTranslation()
*/
int XLStoDIP(const char* pathToXls)
{
    // Iterate through .XLS sheets and write all modifications to .DIP files

    BasicExcel xlsFile;
    xlsFile.Load(pathToXls);

    for (int pathIndex = 0, pathEnd = DIP_FILES_COUNT; pathIndex != pathEnd; ++pathIndex) {
        BasicExcelWorksheet* sheet = xlsFile.GetWorksheet(DIP_PATHS[pathIndex].SheetName);

        if (sheet == nullptr) {
            cout << "Error: unable to load " << DIP_PATHS[pathIndex].SheetName << " worksheet" << endl;

            return 1;
        }

        if (!WriteXLSSheetToTranslation(DIP_PATHS[pathIndex].TranslatedPackageName, DIP_PATHS[pathIndex].FileName, sheet)) {
            return 1;
        }
    }

    // Synchronize .FDT file with packages updates

    // NB! No need to do this as for now DATA\GER\STARTUP.PAK is not included to .FDT index

    return 0;
}

int main(int argc, char **argv)
{
    if (argc >= 2) {
        if (argc == 3 && strcmp(argv[1], "fromxls") == 0) {
            return XLStoDIP(argv[2]);
        } else if (argc == 3 && strcmp(argv[1], "toxls") == 0) {
            return DIPtoXLS(argv[2]);
        }
    }

    ShowHelp();

    return 1;
}
