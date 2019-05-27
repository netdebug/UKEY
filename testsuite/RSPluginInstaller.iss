; -- Languages.iss --
; Demonstrates a multilingual installation.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

[Setup]
AppName={cm:MyAppName}
AppId=D773AD72-9454-4684-96A7-89E478625FB6
AppVerName={cm:MyAppVerName,1.0}
WizardStyle=modern
DefaultDirName={autopf}\{cm:MyAppName}
DefaultGroupName={cm:MyAppName}
UninstallDisplayIcon={app}\MyProg.exe
VersionInfoDescription=ͳһ��ȫ�ͻ���
VersionInfoProductName=ͳһ��ȫ�ͻ���
OutputBaseFilename=SafeCertSetup
OutputDir=.\output
; Uncomment the following line to disable the "Select Setup Language"
; dialog and have it rely solely on auto-detection.
;ShowLanguageDialog=no

[Languages]
Name: chs; MessagesFile: "compiler:Languages\ChineseSimplified.isl"

[Messages]
chs.BeveledLabel=��������


[CustomMessages]
chs.MyDescription=��֤ͨ��������
chs.MyAppName=ͳһ��ȫ�ͻ���
chs.MyAppVerName=ͳһ��ȫ�ͻ��� %1

[Dirs]
Name: "{app}\SKFLibrary"; Flags: uninsalwaysuninstall;
Name: "{app}\SKFLibrary\ShareSun"; Flags: uninsalwaysuninstall;

[Files]
Source: ".\release\ocx\RS_CertSafe.ocx"; DestDir: "{app}"; Flags: restartreplace regserver
Source: ".\release\ocx\DEMO.htm"; DestDir: "{app}"
Source: ".\release\ocx\paho-mqtt3a.dll"; DestDir: "{app}"
Source: ".\release\ocx\paho-mqtt3as.dll"; DestDir: "{app}"
Source: ".\release\ocx\paho-mqtt3c.dll"; DestDir: "{app}"
Source: ".\release\ocx\paho-mqtt3cs.dll"; DestDir: "{app}"
Source: ".\release\ocx\libcrypto-1_1.dll"; DestDir: "{app}"

;Source: ".\release\testResult.json"; DestDir: "{app}"; Languages: en; Flags: isreadme 
Source: ".\release\CppUnitd.dll"; DestDir: "{app}"
Source: ".\release\PocoFoundationd.dll"; DestDir: "{app}"
Source: ".\release\SoFProvider.dll"; DestDir: "{app}"; 
; 001 CFCA ����
Source: ".\release\SKFLibrary\ShareSun\SKF_APP_XS.dll"; DestDir: "{app}\SKFLibrary\001\"
Source: ".\release\SKFLibrary\ShareSun\XSCipherService.dll"; DestDir: "{app}\SKFLibrary\001\"
Source: ".\release\SKFLibrary\ShareSun\XSSealProviderLib.dll"; DestDir: "{app}\SKFLibrary\001\"
; 002 ����CA-��̩
; 003 BJCA-�ֹ�

[Icons]
Name: "{group}\{cm:MyAppName}"; Filename: "{app}\TestSuited.exe"
Name: "{group}\{cm:UninstallProgram,{cm:MyAppName}}"; Filename: "{uninstallexe}"

[Tasks]
; The following task doesn't do anything and is only meant to show [CustomMessages] usage
Name: mytask; Description: "{cm:MyDescription}"

[Run]

[UninstallRun]
Filename: "regsvr32"; Parameters:"/u {app}\RS_CertSafe.ocx"

[UninstallDelete]
Type: files; Name:"{app}\RS_CertSafe.ocx"
