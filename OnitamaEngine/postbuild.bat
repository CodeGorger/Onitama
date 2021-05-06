REM cd > "..\test.txt"
echo D|xcopy /Y /I "..\x64\Release\OnitamaEngine.dll" "..\PyTest\OnitamaEngine.pyd"

REM rename "..\PyTest\OnitamaEngine.dll" ".\PyTest\OnitamaEngine.pyd"