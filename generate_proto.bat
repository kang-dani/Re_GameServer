@echo off
echo [ProtoBuf Generator Starting...]

:: protoc 실행 경로
set PROTOC=Protoc\bin\protoc.exe

:: .proto 원본 파일이 들어있는 위치
set SOURCE_PROTO_DIR=Protoc\bin

:: Unity 클라이언트용 .cs 생성 경로
set CLIENT_OUTPUT_DIR=..\Frame_GameClient\GameClient\Assets\Scripts\ProtoBuf

:: 서버 프로젝트 내 .proto 파일 복사 위치
set SERVER_PROTO_DIR=GameServer

echo [Check] protoc = %PROTOC%
echo [Check] proto source dir = %SOURCE_PROTO_DIR%
echo [Check] client output dir = %CLIENT_OUTPUT_DIR%
echo [Check] server copy target = %SERVER_PROTO_DIR%

:: protoc 실행 여부 확인
if not exist %PROTOC% (
    echo [ERROR] protoc.exe not found at %PROTOC%
    pause
    exit /b
)

:: Unity 출력 디렉토리가 없으면 생성
if not exist %CLIENT_OUTPUT_DIR% (
    echo [Info] CLIENT_OUTPUT_DIR doesn't exist. Creating...
    mkdir %CLIENT_OUTPUT_DIR%
)

:: 서버용 .proto 복사 디렉토리도 없으면 생성
if not exist %SERVER_PROTO_DIR% (
    echo [Info] SERVER_PROTO_DIR doesn't exist. Creating...
    mkdir %SERVER_PROTO_DIR%
)

:: .proto → .cs 변환 및 복사
set FOUND_PROTO=false
for %%f in (%SOURCE_PROTO_DIR%\*.proto) do (
    echo [Compile] %%f → C#
    set FOUND_PROTO=true
    %PROTOC% --proto_path=%SOURCE_PROTO_DIR% --csharp_out=%CLIENT_OUTPUT_DIR% %%f

    echo [Copy] %%f → %SERVER_PROTO_DIR%
    copy /Y %%f %SERVER_PROTO_DIR% > nul
)

if "%FOUND_PROTO%" == "false" (
    echo [WARNING] No .proto files found in %SOURCE_PROTO_DIR%
)

echo [Done] .proto -> .cs Complete
pause
