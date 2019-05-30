; -- Languages.iss --
; Demonstrates a multilingual installation.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

[Setup]
AppName={cm:MyAppName}
AppId=62DA7343-2512-4713-8976-73C42F9D63EA
AppVerName={cm:MyAppVerName,1.0.30}
WizardStyle=modern
DefaultDirName={pf}\{cm:MyAppName}
DefaultGroupName={cm:MyAppName}
UninstallDisplayIcon={app}\MyProg.exe
VersionInfoDescription=testSuite
VersionInfoProductName=testSuite
VersionInfoVersion=1.0.30
OutputBaseFilename=testSuite
OutputDir=.\output
; Uncomment the following line to disable the "Select Setup Language"
; dialog and have it rely solely on auto-detection.
;ShowLanguageDialog=no

[Languages]
Name: en; MessagesFile: "compiler:Default.isl"

[CustomMessages]
en.MyDescription=TestSuite
en.MyAppName=TestSuite
en.MyAppVerName=TestSuite

[Dirs]
Name: "{app}\SKF_Library"; Flags: uninsalwaysuninstall;
Name: "{app}\SKF_Library\001"; Flags: uninsalwaysuninstall;
Name: "{app}\SKF_Library\002"; Flags: uninsalwaysuninstall;
Name: "{app}\SKF_Library\003"; Flags: uninsalwaysuninstall;

Name: "{app}\testTarget"; Flags: uninsalwaysuninstall;

[Files]
Source: ".\bin\testTarget\Readme.md"; DestDir: "{app}\testTarget\";

;Source: ".\release\testResult.json"; DestDir: "{app}"; Languages: en; Flags: isreadme 

Source: ".\bin\msvcrt.dll"; DestDir: "{app}";

Source: ".\bin\msvcr90.dll"; DestDir: "{app}";
Source: ".\bin\msvcp90.dll"; DestDir: "{app}";

Source: ".\bin\msvcp120.dll"; DestDir: "{app}";
Source: ".\bin\msvcr120.dll"; DestDir: "{app}";

Source: ".\bin\msvcp140.dll"; DestDir: "{app}";
;Source: ".\bin\vcruntime140.dll"; DestDir: "{app}";

Source: ".\bin\PocoJSON.dll"; DestDir: "{app}";
Source: ".\bin\RSFoundation.dll"; DestDir: "{app}";
Source: ".\bin\SoFProvider.dll"; DestDir: "{app}";
Source: ".\bin\CppUnit.dll"; DestDir: "{app}"
Source: ".\bin\PocoFoundation.dll"; DestDir: "{app}"

; 001 CFCA 翔晟
Source: ".\bin\SKF_Library\001\SKF_APP_XS.dll"; DestDir: "{app}\SKF_Library\001\"
;Source: ".\bin\SKF_Library\001\XSCipherService.dll"; DestDir: "{app}\SKF_Library\001\"
;Source: ".\bin\SKF_Library\001\XSSealProviderLib.dll"; DestDir: "{app}\SKF_Library\001\"
; 002 内蒙CA-海泰
Source: ".\bin\SKF_Library\002\SKFAPI20549.dll"; DestDir: "{app}\SKF_Library\002\"
; 003 BJCA-林果
Source: ".\bin\SKF_Library\003\lgu3073_p1514_gm.dll"; DestDir: "{app}\SKF_Library\003\"
Source: ".\bin\SKF_Library\003\lgu3073_p1514_gm_x64.dll"; DestDir: "{app}\SKF_Library\003\"

Source: ".\bin\TestSuite.exe"; DestDir: "{app}";

[Icons]
Name: "{group}\{cm:MyAppName}"; Filename: "{app}\TestSuite.exe"
Name: "{group}\{cm:UninstallProgram,{cm:MyAppName}}"; Filename: "{uninstallexe}"

[Tasks]
; The following task doesn't do anything and is only meant to show [CustomMessages] usage
Name: mytask; Description: "{cm:MyDescription}"

[UninstallDelete]
Type:filesandordirs; Name:"{app}\testTarget"
