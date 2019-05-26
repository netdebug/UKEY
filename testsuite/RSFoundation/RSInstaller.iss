; -- Languages.iss --
; Demonstrates a multilingual installation.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

[Setup]
AppName={cm:MyAppName}
AppId=D773AD72-9454-4684-96A7-89E478625FB6
AppVerName={cm:MyAppVerName,1.1}
WizardStyle=modern
DefaultDirName={autopf}\{cm:MyAppName}
DefaultGroupName={cm:MyAppName}
UninstallDisplayIcon={app}\MyProg.exe
VersionInfoDescription=统一安全认证平台
VersionInfoProductName=统一安全认证服务平台
OutputDir=userdocs:Inno Setup Examples Output
; Uncomment the following line to disable the "Select Setup Language"
; dialog and have it rely solely on auto-detection.
;ShowLanguageDialog=no

[Languages]
Name: chs; MessagesFile: "compiler:Languages\ChineseSimplified.isl"

[Messages]
chs.BeveledLabel=简体中文


[CustomMessages]
chs.MyDescription=统一安全认证服务平台
chs.MyAppName=RSFoundation.ocx
chs.MyAppVerName=RSFoundation %1

[Dirs]
Name: "{app}\SKFLibrary"; Flags: uninsalwaysuninstall;
Name: "{app}\SKFLibrary\ShareSun"; Flags: uninsalwaysuninstall;

[Files]
Source: "..\bin\TestSuited.exe"; DestDir: "{app}"
Source: "..\bin\testResult.json"; DestDir: "{app}"; Languages: en; Flags: isreadme 
Source: "..\bin\CppUnitd.dll"; DestDir: "{app}"
Source: "..\bin\PocoFoundation.dll"; DestDir: "{app}"
Source: "..\bin\SoFProvider.dll"; DestDir: "{app}"; Flags: restartreplace regserver
Source: "..\bin\SKFLibrary\ShareSun\SKF_APP_XS.dll"; DestDir: "{app}\SKFLibrary\ShareSun\"
Source: "..\bin\SKFLibrary\ShareSun\XSCipherService.dll"; DestDir: "{app}\SKFLibrary\ShareSun\"
Source: "..\bin\SKFLibrary\ShareSun\XSSealProviderLib.dll"; DestDir: "{app}\SKFLibrary\ShareSun\"

[Icons]
Name: "{group}\{cm:MyAppName}"; Filename: "{app}\TestSuited.exe"
Name: "{group}\{cm:UninstallProgram,{cm:MyAppName}}"; Filename: "{uninstallexe}"

[Tasks]
; The following task doesn't do anything and is only meant to show [CustomMessages] usage
Name: mytask; Description: "{cm:MyDescription}"

[Run]

[UninstallRun]
Filename: "regsvr32"; Parameters:"/u {app}\SoFProvider.dll"

[UninstallDelete]
Type: files; Name:"{app}\SoFProvider.dll"
