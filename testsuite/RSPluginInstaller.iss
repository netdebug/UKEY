; -- Languages.iss --
; Demonstrates a multilingual installation.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

[Setup]
AppName={cm:MyAppName}
AppId={{D773AD72-9454-4684-96A7-89E478625FB6}
AppVerName={cm:MyAppVerName,1.0.39}
WizardStyle=modern
DefaultDirName={pf}\{cm:MyAppName}
DefaultGroupName={cm:MyAppName}
UninstallDisplayIcon={app}\MyProg.exe
VersionInfoDescription=统一安全认证客户端
VersionInfoProductName=统一安全认证客户端
OutputBaseFilename=SafeCertSetup
VersionInfoVersion=1.0.0.5
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
Name: "{app}\Drive"; Flags: uninsalwaysuninstall;
Name: "{sys}\SKF_Library"; Flags: uninsalwaysuninstall;
Name: "{sys}\SKF_Library\001"; Flags: uninsalwaysuninstall;
Name: "{sys}\SKF_Library\002"; Flags: uninsalwaysuninstall;
Name: "{sys}\SKF_Library\003"; Flags: uninsalwaysuninstall;
Name: "{sys}\SKF_Library\004"; Flags: uninsalwaysuninstall;

[Files]
;复制驱动程序
Source: ".\release\Drive\HSIC DriverSetup.exe"; DestDir: "{app}\Drive\";
;Source: ".\release\Drive\ePass3000SimpChinese-With-PrvDll_silent.exe"; DestDir: "{app}\Drive\";
;Source: ".\release\Drive\HTSetup_NMCA.exe"; DestDir: "{app}\Drive\";

Source: ".\release\ocx\ActiveXConfig.ini"; DestDir: "{app}";
Source: ".\release\ocx\RS_CertSafe.ocx"; DestDir: "{app}"; Flags: restartreplace regserver

Source: ".\release\ocx\libcrypto-1_1.dll"; DestDir: "{app}"
Source: ".\release\ocx\lib_json.dll"; DestDir: "{app}"
Source: ".\release\ocx\libssl-1_1.dll"; DestDir: "{app}"

Source: ".\release\CppUnit.dll"; DestDir: "{app}"       
Source: ".\release\msvcrt.dll"; DestDir: "{app}"
Source: ".\release\mfc120u.dll"; DestDir: "{app}"
Source: ".\release\msvcp100.dll"; DestDir: "{app}"
Source: ".\release\msvcp120.dll"; DestDir: "{app}";
;Source: ".\release\msvcp140.dll"; DestDir: "{app}";
Source: ".\release\msvcr90.dll"; DestDir: "{app}";
Source: ".\release\msvcr100.dll"; DestDir: "{app}";
Source: ".\release\msvcr120.dll"; DestDir: "{app}";

;Source: ".\release\bcrypt.dll"; DestDir: "{app}"; 
;Source: ".\release\IEShims.dll"; DestDir: "{app}"; 
;Source: ".\release\wer.dll"; DestDir: "{app}"; 

Source: ".\release\PocoFoundation.dll"; DestDir: "{app}"
Source: ".\release\PocoJSON.dll"; DestDir: "{app}";
Source: ".\release\RSFoundation.dll"; DestDir: "{app}";
Source: ".\release\SoFProvider.dll"; DestDir: "{app}"; 
Source: ".\release\config.ini"; DestDir: "{app}";

; 001 CFCA 翔晟
Source: ".\release\SKF_Library\001\SKF_APP_XS.dll"; DestDir: "{sys}\SKF_Library\001\";
; 002 内蒙CA-海泰
Source: ".\release\SKF_Library\002\SKFAPI20549.dll"; DestDir: "{sys}\SKF_Library\002\";
; 003 BJCA-林果
Source: ".\release\SKF_Library\003\lgu3073_p1514_gm.dll"; DestDir: "{sys}\SKF_Library\003\";
Source: ".\release\SKF_Library\003\lgu3073_p1514_gm_x64.dll"; DestDir: "{sys}\SKF_Library\003\";
;004
Source: ".\release\SKF_Library\004\gm3k_for_bjca.dll"; DestDir: "{sys}\SKF_Library\004\";
Source: ".\release\SKF_Library\004\gm3k_for_bjca_x64.dll"; DestDir: "{sys}\SKF_Library\004\";

[Code]
function InitializeSetup(): boolean;  
var  
  ResultStr: String;  
  ResultCode: Integer;  
begin  
  if RegQueryStringValue(HKLM, 'SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\{D773AD72-9454-4684-96A7-89E478625FB6}_is1', 'UninstallString', ResultStr) then  
    begin  
      ResultStr := RemoveQuotes(ResultStr);  
      Exec(ResultStr, '/silent', '', SW_HIDE, ewWaitUntilTerminated, ResultCode);  
    end;  
    result := true;  
end;

[Icons]
;Name: "{group}\{cm:MyAppName}"; Filename: "{app}\TestSuited.exe"
Name: "{group}\{cm:UninstallProgram,{cm:MyAppName}}"; Filename: "{uninstallexe}"

[Tasks]
; The following task doesn't do anything and is only meant to show [CustomMessages] usage
Name: mytask; Description: "{cm:MyDescription}"

[Run]
Filename: "{sys}\regsvr32.exe";Parameters:" /s ""{app}\RSyncControl.ocx"" ";
Filename: "{app}\Drive\HSIC DriverSetup.exe";
;Filename: "{app}\Drive\ePass3000SimpChinese-With-PrvDll_silent.exe";
;Filename: "{app}\Drive\HTSetup_NMCA.exe";
[UninstallRun]
Filename: "{sys}\regsvr32.exe";Parameters:"/u /s ""{app}\RSyncControl.ocx"" "

[UninstallDelete]
; Type: files; Name:"{app}\RS_CertSafe.ocx"
