REM cd > "..\test.txt"
echo D|xcopy /Y /I "..\x64\Release\OnitamaMessages.dll" "..\PyTest\OnitamaMessages.pyd"

REM rename "..\PyTest\OnitamaMessages.dll" ".\PyTest\OnitamaMessages.pyd"