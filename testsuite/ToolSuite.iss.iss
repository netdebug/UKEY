; -- Languages.iss --
; Demonstrates a multilingual installation.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

[Setup]
AppName={cm:MyAppName}
AppId={{62DA7343-2512-4713-8976-73C42F9D63EA}
AppVerName={cm:MyAppVerName,1.1.36.0008}
WizardStyle=modern
DefaultDirName={pf}\{cm:MyAppName}
DefaultGroupName={cm:MyAppName}
UninstallDisplayIcon={app}\MyProg.exe
VersionInfoDescription=testSuite
VersionInfoProductName=testSuite
VersionInfoVersion=1.1.36.0008
OutputBaseFilename=testSuite
OutputDir=.\output
; Uncomment the following line to disable the "Select Setup Language"
; dialog and have it rely solely on auto-detection.
;ShowLanguageDialog=no

[Languages]
Name: en; MessagesFile: "compiler:Default.isl"

[CustomMessages]
en.MyDescription=testSuite
en.MyAppName=testSuite
en.MyAppVerName=testSuite

[Dirs]

Name: "{sys}\SKF_Library"; Flags: uninsalwaysuninstall;
Name: "{sys}\SKF_Library\001"; Flags: uninsalwaysuninstall;
Name: "{sys}\SKF_Library\002"; Flags: uninsalwaysuninstall;
Name: "{sys}\SKF_Library\003"; Flags: uninsalwaysuninstall;
Name: "{sys}\SKF_Library\004"; Flags: uninsalwaysuninstall;

Name: "{app}\testTarget"; Flags: uninsalwaysuninstall;

[Files]

;Source: ".\release\Drive\HSIC DriverSetup.exe"; DestDir: "{app}\Drive\";
;Source: ".\release\Drive\ePass3000SimpChinese-With-PrvDll_silent.exe"; DestDir: "{app}\Drive\";
;Source: ".\release\Drive\HTSetup_NMCA.exe"; DestDir: "{app}\Drive\";




    
Source: ".\release\msvcrt.dll"; DestDir: "{app}"
Source: ".\release\mfc120u.dll"; DestDir: "{app}"
Source: ".\release\msvcp100.dll"; DestDir: "{app}"
Source: ".\release\msvcp120.dll"; DestDir: "{app}";
;Source: ".\release\msvcp140.dll"; DestDir: "{app}";
Source: ".\release\msvcr90.dll"; DestDir: "{app}";
Source: ".\release\msvcr100.dll"; DestDir: "{app}";
Source: ".\release\msvcr120.dll"; DestDir: "{app}";


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

Source: "..\bin\testSuite.exe"; DestDir: "{app}";
Source: "..\bin\rsyncAgent.exe"; DestDir: "{app}";
Source: "..\bin\rsyncAgent.properties"; DestDir: "{app}";

Source: "..\bin\UKEYMonitor.exe"; DestDir: "{app}";
Source: "..\bin\UKEYMonitor.properties"; DestDir: "{app}";
Source: "..\bin\devicelist.json"; DestDir: "{app}";

Source: "..\bin\CppUnit.dll"; DestDir: "{app}"   
Source: "..\bin\PocoFoundation.dll"; DestDir: "{app}"     
Source: "..\bin\PocoJSON.dll"; DestDir: "{app}";
Source: "..\bin\PocoNet.dll"; DestDir: "{app}";
Source: "..\bin\PocoXML.dll"; DestDir: "{app}";
Source: "..\bin\PocoUtil.dll"; DestDir: "{app}";
Source: "..\bin\PocoData.dll"; DestDir: "{app}";
Source: "..\bin\PocoDataSQLite.dll"; DestDir: "{app}";

Source: "..\bin\SoFProvider.dll"; DestDir: "{app}"; 
Source: ".\release\config.ini"; DestDir: "{app}";

[Icons]
Name: "{group}\{cm:MyAppName}"; Filename: "{app}\testSuite.exe"
Name: "{group}\{cm:UninstallProgram,{cm:MyAppName}}"; Filename: "{uninstallexe}"

[Tasks]
; The following task doesn't do anything and is only meant to show [CustomMessages] usage
Name: mytask; Description: "{cm:MyDescription}"

[Run]
;Filename: "{app}\Drive\HSIC DriverSetup.exe";
;Filename: "{app}\Drive\ePass3000SimpChinese-With-PrvDll_silent.exe";
;Filename: "{app}\Drive\HTSetup_NMCA.exe";
Filename: "{app}\UKEYMonitor.exe"; Parameters: "/registerService" ; Flags: runascurrentuser
Filename: "{app}\rsyncAgent.exe"; Parameters: "/registerService" ; Flags: runascurrentuser
Filename: "{sys}\sc.exe";Parameters:"start UKEYMonitor";
Filename: "{sys}\sc.exe";Parameters:"start rsyncAgent";

[UninstallRun]
Filename: "{sys}\sc.exe";Parameters:"stop UKEYMonitor";
Filename: "{sys}\sc.exe";Parameters:"stop rsyncAgent";
Filename: "{app}\UKEYMonitor.exe"; Parameters: "/unregisterService" ; Flags: runascurrentuser
Filename: "{app}\rsyncAgent.exe"; Parameters: "/unregisterService" ; Flags: runascurrentuser

[UninstallDelete]
Type:filesandordirs; Name:"{app}\testTarget"

[Code]
function InitializeSetup(): boolean;  
var  
  ResultStr: String;  
  ResultCode: Integer;  
begin  
  if RegQueryStringValue(HKLM, 'SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\{62DA7343-2512-4713-8976-73C42F9D63EA}_is1', 'UninstallString', ResultStr) then  
    begin  
      ResultStr := RemoveQuotes(ResultStr);  
      Exec(ResultStr, '/silent', '', SW_HIDE, ewWaitUntilTerminated, ResultCode);  
    end;  
    result := true;  
end;
