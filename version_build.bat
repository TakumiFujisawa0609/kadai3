@echo off
setlocal

cd /d %~dp0
set VERSION_FILE=version.txt

rem ファイルがなければ初期化
if not exist %VERSION_FILE% (
    echo 0.0.0 > %VERSION_FILE%
)

rem 現在バージョンを読み取り
set /p VERSION=<%VERSION_FILE%
for /f "tokens=1,2,3 delims=." %%a in ("%VERSION%") do (
    set MAJOR=%%a
    set MINOR=%%b
    set BUILD=%%c
)

rem ビルド番号 +1
set /a BUILD=%BUILD% + 1
set NEW_VERSION=%MAJOR%.%MINOR%.%BUILD%

rem ファイル更新
echo %NEW_VERSION% > %VERSION_FILE%
echo Version updated: %VERSION% → %NEW_VERSION%

rem Git タグ付けと push
git rev-parse --git-dir >nul 2>&1
if %errorlevel%==0 (
    echo Git repository detected.
    git tag -a v%NEW_VERSION% -m "Release v%NEW_VERSION%"
    git push origin v%NEW_VERSION%
    echo タグ "v%NEW_VERSION%" を作成しリモートにプッシュしました。
) else (
    echo Git repository ではありません。タグ付けをスキップします。
)

endlocal