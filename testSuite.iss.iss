; -- Languages.iss --
; Demonstrates a multilingual installation.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

[Setup]
AppName={cm:MyAppName}
AppId=62DA7343-2512-4713-8976-73C42F9D63EA
AppVerName={cm:MyAppVerName,1.0}
WizardStyle=modern
DefaultDirName={pf}\{cm:MyAppName}
DefaultGroupName={cm:MyAppName}
UninstallDisplayIcon={app}\MyProg.exe
VersionInfoDescription=testSuite
VersionInfoProductName=testSuite
OutputBaseFilename=testSuite
OutputDir=.\output
; Uncomment the following line to disable the "Select Setup Language"
; dialog and have it rely solely on auto-detection.
;ShowLanguageDialog=no

[Languages]
Name: en; MessagesFile: "compiler:Default.isl"

[CustomMessages]
en.MyDescription=TestSuite 1.0
en.MyAppName=TestSuite
en.MyAppVerName=TestSuite 1.0

[Dirs]
Name: "{app}\testTarget"; Flags: uninsalwaysuninstall;

[Files]
Source: ".\bin\testTarget\Readme.md"; DestDir: "{app}\testTarget\";

;Source: ".\release\testResult.json"; DestDir: "{app}"; Languages: en; Flags: isreadme 
Source: ".\bin\CppUnit.dll"; DestDir: "{app}"
Source: ".\bin\PocoFoundation.dll"; DestDir: "{app}"

Source: ".\bin\msvcp120.dll"; DestDir: "{app}";
Source: ".\bin\msvcp140.dll"; DestDir: "{app}";
Source: ".\bin\msvcr120.dll"; DestDir: "{app}";
Source: ".\bin\PocoJSON.dll"; DestDir: "{app}";
Source: ".\bin\RSFoundation.dll"; DestDir: "{app}";
Source: ".\bin\SoFProvider.dll"; DestDir: "{app}";

Source: ".\bin\TestSuite.exe"; DestDir: "{app}";

[Icons]
Name: "{group}\{cm:MyAppName}"; Filename: "{app}\TestSuite.exe"
Name: "{group}\{cm:UninstallProgram,{cm:MyAppName}}"; Filename: "{uninstallexe}"

[Tasks]
; The following task doesn't do anything and is only meant to show [CustomMessages] usage
Name: mytask; Description: "{cm:MyDescription}"

[UninstallDelete]
Type:filesandordirs; Name:"{app}\testTarget"
