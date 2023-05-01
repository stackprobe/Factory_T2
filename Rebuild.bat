CALL ff
CD Build\_Cx
CALL BuildCx.bat

CALL ff
cx ***
IF ERRORLEVEL 1 C:\app\MsgBox\MsgBox.exe E "BUILD ERROR"

CALL ff
CALL Clean
CALL mkt
