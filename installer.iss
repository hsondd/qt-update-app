#define MyAppName "TestGithubUpdate"
#define MyAppVersion "19.6"
#define MyAppPublisher "Emotiv"
#define MyAppExeName "appTestGithubUpdate.exe"
#define MyAppSourceDir "C:\\Emotiv\\qt-update-app\\build\\Desktop_Qt_6_8_3_MSVC2022_64bit-Release"

[Setup]
AppId={{F9F5C4B7-3B4E-4A77-8E9D-7B2A8C9F4B18}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
DefaultDirName={autopf}\{#MyAppName}
DisableProgramGroupPage=yes
OutputDir=C:\Emotiv\qt-update-app\release
OutputBaseFilename=appTestGithubUpdate-{#MyAppVersion}
Compression=lzma2
SolidCompression=yes
ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible
WizardStyle=modern

[Files]
Source: "{#MyAppSourceDir}\*"; DestDir: "{app}"; Flags: recursesubdirs ignoreversion

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "Launch {#MyAppName}"; Flags: nowait postinstall skipifsilent
