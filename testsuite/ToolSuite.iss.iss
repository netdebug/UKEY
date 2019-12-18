; -- Languages.iss --
; Demonstrates a multilingual installation.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

[Setup]
AppName={cm:MyAppName}
AppId={{D773AD72-9454-4684-96A7-89E478625FB6}
AppVerName={cm:MyAppVerName,2.0.3.009}
AppCopyright=福建瑞术信息科技有限公司
WizardStyle=modern
DefaultDirName={pf}\{cm:MyAppName}
DefaultGroupName={cm:MyAppName}
UninstallDisplayIcon={app}\MyProg.exe
VersionInfoDescription=统一安全认证客户端
VersionInfoProductName=统一安全认证客户端
VersionInfoVersion=2.0.3.009
OutputBaseFilename=SafeCertSetupV2.0.3.009_jg
OutputDir=.\output
; Uncomment the following line to disable the "Select Setup Language"
; dialog and have it rely solely on auto-detection.
;ShowLanguageDialog=no

[Languages]
Name: en; MessagesFile: "compiler:Default.isl"

[CustomMessages]
en.MyDescription=统一安全认证客户端 2.0
en.MyAppName=统一安全认证客户端 2.0
en.MyAppVerName=统一安全认证客户端 2.0

[Dirs]

;Name: "{sys}\SKF_Library"; Flags: uninsalwaysuninstall;
;Name: "{sys}\SKF_Library\001"; Flags: uninsalwaysuninstall;
;Name: "{sys}\SKF_Library\002"; Flags: uninsalwaysuninstall;
;Name: "{sys}\SKF_Library\003"; Flags: uninsalwaysuninstall;
;Name: "{sys}\SKF_Library\004"; Flags: uninsalwaysuninstall;

Name: "{app}\testTarget"; Flags: uninsalwaysuninstall;

[Files]
;SoFProvider folder
Source: "..\bin\SKF_Library\*"; DestDir: "{app}\SKF_Library\";  Flags: createallsubdirs recursesubdirs;
;BJCAClient
Source: "..\bin\extern\BJCAClient\*"; DestDir: "{pf}\BJCAClient\"; Flags: recursesubdirs;
;Driver
Source: "..\bin\extern\Driver\*"; DestDir: "{app}\Driver\"; Flags: recursesubdirs;
Source: "..\bin\extern\CertTools\*"; DestDir: "{app}\CertTools\"; Flags: recursesubdirs;
Source: "..\bin\extern\redist\*"; DestDir: "{app}\redist\"; Flags: recursesubdirs;
Source: "..\bin\extern\SKF_APP_XS.dll"; DestDir: "{sys}";                                     
Source: "..\bin\extern\SKF_IFD_XS.dll"; DestDir: "{sys}";
Source: "..\bin\extern\XSCipherService.dll"; DestDir: "{sys}";
Source: "..\bin\extern\XSSealProviderLib.dll"; DestDir: "{sys}";
Source: "..\bin\extern\msvcrt.dll"; DestDir: "{app}"
Source: "..\bin\extern\mfc90u.dll"; DestDir: "{app}"
Source: "..\bin\extern\mfc120u.dll"; DestDir: "{app}"
Source: "..\bin\extern\mfc140u.dll"; DestDir: "{app}"
Source: "..\bin\extern\msvcp100.dll"; DestDir: "{app}"
Source: "..\bin\extern\msvcp120.dll"; DestDir: "{app}";
Source: "..\bin\extern\msvcr90.dll"; DestDir: "{app}";
Source: "..\bin\extern\msvcr100.dll"; DestDir: "{app}";
Source: "..\bin\extern\msvcr120.dll"; DestDir: "{app}";
Source: "..\bin\extern\vcruntime140.dll"; DestDir: "{app}";
Source: "..\bin\extern\clearlnk.bat"; DestDir: "{app}";

;updater
Source: "..\bin\updater.exe"; DestDir: "{app}";
Source: "..\bin\settings.ini"; DestDir: "{app}";
Source: "..\bin\lng\*"; DestDir: "{app}\lng"; Flags: recursesubdirs;

;Architecture 2.0
Source: "..\bin\rsyncAgent.exe"; DestDir: "{app}";
Source: "..\bin\rsyncAgent.properties"; DestDir: "{app}";
Source: "..\bin\RS_CertSafe.ocx"; DestDir: "{app}"; Flags: restartreplace regserver
;Source: "..\bin\rsyncDaemon.exe"; DestDir: "{app}"
;Source: "..\bin\rsyncDaemon.properties"; DestDir: "{app}";
Source: "..\bin\Language.ini"; DestDir: "{app}";
;rsyncAgent
Source: "..\bin\rsyncData.dll"; DestDir: "{app}";
Source: "..\bin\rsyncFJCA.dll"; DestDir: "{app}";
Source: "..\bin\rsyncSOF.dll"; DestDir: "{app}";
Source: "..\bin\SoFProvider.dll"; DestDir: "{app}";
Source: "..\bin\config.ini"; DestDir: "{app}";
;config
Source: "..\bin\config\*"; DestDir: "{app}\config\"; Flags: recursesubdirs;

;rsyncClient
Source: "..\bin\rsyncClient.exe"; DestDir: "{app}"
Source: "..\bin\rsyncClient.properties"; DestDir: "{app}";
Source: "..\bin\QZSyncWorker.json"; DestDir: "{app}";
Source: "..\bin\TCardCert.dll"; DestDir: "{app}";
Source: "..\bin\StampManageSystem.dll"; DestDir: "{app}";
Source: "..\bin\StampManageSystem.dll"; DestDir: "{app}";
Source: "..\bin\GEA_FJCA.dll"; DestDir: "{app}";

Source: "..\bin\UKEYMonitor.exe"; DestDir: "{app}";
Source: "..\bin\UKEYMonitor.properties"; DestDir: "{app}";
Source: "..\bin\devicelist.json"; DestDir: "{app}";
;all
Source: "..\bin\CppUnit.dll"; DestDir: "{app}"
Source: "..\bin\PocoCrypto.dll"; DestDir: "{app}";
Source: "..\bin\PocoData.dll"; DestDir: "{app}";
Source: "..\bin\PocoDataSQLite.dll"; DestDir: "{app}";
Source: "..\bin\PocoFoundation.dll"; DestDir: "{app}"
Source: "..\bin\PocoJSON.dll"; DestDir: "{app}";
Source: "..\bin\PocoNetXP.dll"; DestDir: "{app}"; DestName:"PocoNet.dll";
Source: "..\bin\PocoUtil.dll"; DestDir: "{app}";
Source: "..\bin\PocoXML.dll"; DestDir: "{app}";
Source: "..\bin\PocoEncodings.dll"; DestDir: "{app}";

;PocoCrypto GMSSL
Source: "..\bin\openssl.exe"; DestDir: "{app}";
Source: "..\bin\libcrypto-1_1.dll"; DestDir: "{app}";
Source: "..\bin\libssl-1_1.dll"; DestDir: "{app}";

;MQTT
Source: "..\bin\paho-mqtt3a.dll"; DestDir: "{app}";
Source: "..\bin\paho-mqtt3as.dll"; DestDir: "{app}";

;lua engine
Source: "..\bin\lua53.dll"; DestDir: "{app}";

[Icons]
Name: "{group}\{cm:UninstallProgram,{cm:MyAppName}}"; Filename: "{uninstallexe}"
Name: "{group}\{cm:MyAppName,{cm:MyAppName}}"; Filename: "{app}\CertTools\index.html"
Name: "{commondesktop}\{cm:MyAppName}"; Filename: "{app}\CertTools\index.html";

[Tasks]
; The following task doesn't do anything and is only meant to show [CustomMessages] usage
Name: mytask; Description: "{cm:MyDescription}"

[Run]
Filename: "{app}\Driver\HSIC DriverSetup.exe";
Filename: "{app}\Driver\20549_User_Driver_SDKey_Silent_x86_x64_5.0.2019.9041.exe";
Filename: "{app}\Driver\UKey20079_User_Silent_x64 _5.1.2019.9111_NoTool.exe";
Filename: "{app}\Driver\NETCA_Crypto.exe"; Parameters:" /sp- /VERYSILENT /norestart ";
Filename: "{app}\Driver\NETCA_Devices(ES).exe"; Parameters:" /sp- /VERYSILENT /norestart ";
Filename: "{app}\Driver\USK218CSP(BJCA).exe"; Parameters:" /verysilent /suppressmsgboxes /norestart /DETACHEDMSG ";
;
Filename: "{app}\clearlnk.bat";

Filename: "{app}\UKEYMonitor.exe"; Parameters: "/registerService /startup=automatic" ; Flags: runascurrentuser
Filename: "{sys}\sc.exe";Parameters:"start UKEYMonitor";

Filename: "{app}\rsyncAgent.exe"; Parameters: "/registerService /startup=automatic" ; Flags: runascurrentuser
Filename: "{sys}\sc.exe";Parameters:"start rsyncAgent";

;Filename: "{app}\rsyncClient.exe"; Parameters: "/registerService /startup=automatic" ; Flags: runascurrentuser
;Filename: "{sys}\sc.exe";Parameters:"start rsyncClient";

Filename: "{sys}\regsvr32.exe";Parameters:" /s ""{app}\RS_CertSafe.ocx"" ";
Filename: "{sys}\regsvr32.exe";Parameters:" /s ""{pf}\BJCAClient\CertAppEnvV2.14.4\Program\XTXAppCOM.dll"" ";
[UninstallRun]
Filename: "{sys}\sc.exe";Parameters:"stop UKEYMonitor";
Filename: "{app}\UKEYMonitor.exe"; Parameters: "/unregisterService " ; Flags: runascurrentuser

Filename: "{sys}\sc.exe";Parameters:"stop rsyncAgent";
Filename: "{app}\rsyncAgent.exe"; Parameters: "/unregisterService " ; Flags: runascurrentuser

Filename: "{sys}\sc.exe";Parameters:"stop rsyncClient";
Filename: "{app}\rsyncClient.exe"; Parameters: "/unregisterService " ; Flags: runascurrentuser

Filename: "{sys}\regsvr32.exe";Parameters:"/u /s ""{app}\RS_CertSafe.ocx"" "
Filename: "{sys}\regsvr32.exe";Parameters:"/u /s ""{pf}\BJCAClient\CertAppEnvV2.14.4\Program\XTXAppCOM.dll"" ";
[UninstallDelete]
Type:filesandordirs; Name:"{app}\testTarget"

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
