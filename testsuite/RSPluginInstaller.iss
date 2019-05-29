; -- Languages.iss --
; Demonstrates a multilingual installation.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

[Setup]
AppName={cm:MyAppName}
AppId=D773AD72-9454-4684-96A7-89E478625FB6
AppVerName={cm:MyAppVerName,1.0}
WizardStyle=modern
DefaultDirName={pf}\{cm:MyAppName}
DefaultGroupName={cm:MyAppName}
UninstallDisplayIcon={app}\MyProg.exe
VersionInfoDescription=统一安全认证客户端
VersionInfoProductName=统一安全认证客户端
OutputBaseFilename=SafeCertSetup
OutputDir=.\output
; Uncomment the following line to disable the "Select Setup Language"
; dialog and have it rely solely on auto-detection.
;ShowLanguageDialog=no

[Languages]
Name: chs; MessagesFile: "compiler:Languages\ChineseSimplified.isl"

[Messages]
;chs.BeveledLabel=中文简体 

[CustomMessages]
chs.MyDescription=统一安全认证客户端 1.0
chs.MyAppName=统一安全认证客户端
chs.MyAppVerName=统一安全认证客户端 1.0

[Dirs]
Name: "{app}\SKF_Library"; Flags: uninsalwaysuninstall;
Name: "{app}\SKF_Library\001"; Flags: uninsalwaysuninstall;
Name: "{app}\SKF_Library\002"; Flags: uninsalwaysuninstall;
Name: "{app}\SKF_Library\003"; Flags: uninsalwaysuninstall;

[Files]
Source: ".\release\ocx\RS_CertSafe.ocx"; DestDir: "{app}"; Flags: restartreplace regserver
Source: ".\release\ocx\DEMO.htm"; DestDir: "{app}"
Source: ".\release\ocx\paho-mqtt3a.dll"; DestDir: "{app}"
Source: ".\release\ocx\paho-mqtt3as.dll"; DestDir: "{app}"
Source: ".\release\ocx\paho-mqtt3c.dll"; DestDir: "{app}"
Source: ".\release\ocx\paho-mqtt3cs.dll"; DestDir: "{app}"
Source: ".\release\ocx\libcrypto-1_1.dll"; DestDir: "{app}"

;Source: ".\release\testResult.json"; DestDir: "{app}"; Languages: en; Flags: isreadme 
Source: ".\release\CppUnit.dll"; DestDir: "{app}"
Source: ".\release\PocoFoundation.dll"; DestDir: "{app}"
Source: ".\release\SoFProvider.dll"; DestDir: "{app}";

Source: ".\release\msvcp120.dll"; DestDir: "{app}";
Source: ".\release\msvcp140.dll"; DestDir: "{app}";
Source: ".\release\msvcr120.dll"; DestDir: "{app}";
Source: ".\release\PocoJSON.dll"; DestDir: "{app}";
Source: ".\release\RSFoundation.dll"; DestDir: "{app}";
; 001 CFCA 翔晟
Source: ".\release\SKFLibrary\ShareSun\SKF_APP_XS.dll"; DestDir: "{app}\SKF_Library\001\"
Source: ".\release\SKFLibrary\ShareSun\XSCipherService.dll"; DestDir: "{app}\SKF_Library\001\"
Source: ".\release\SKFLibrary\ShareSun\XSSealProviderLib.dll"; DestDir: "{app}\SKF_Library\001\"
; 002 内蒙CA-海泰
Source: ".\release\SKFLibrary\NMGCA\SKFAPI20549.dll"; DestDir: "{app}\SKF_Library\002\"
; 003 BJCA-林果
Source: ".\release\SKFLibrary\LG_BJCA\lgu3073_p1514_gm.dll"; DestDir: "{app}\SKF_Library\003\"
Source: ".\release\SKFLibrary\LG_BJCA\lgu3073_p1514_gm_x64.dll"; DestDir: "{app}\SKF_Library\003\"


[Icons]
Name: "{group}\{cm:MyAppName}"; Filename: "{app}\TestSuited.exe"
Name: "{group}\{cm:UninstallProgram,{cm:MyAppName}}"; Filename: "{uninstallexe}"

[Tasks]
; The following task doesn't do anything and is only meant to show [CustomMessages] usage
Name: mytask; Description: "{cm:MyDescription}"

[Run]
Filename: "{sys}\regsvr32.exe";Parameters:" /s ""{app}\RS_CertSafe.ocx"" "
[UninstallRun]
Filename: "{sys}\regsvr32.exe";Parameters:"/u /s ""{app}\RS_CertSafe.ocx"" "

[UninstallDelete]
; Type: files; Name:"{app}\RS_CertSafe.ocx"
