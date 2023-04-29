CALL ff
CD Build\_Cx
CALL Rebuild.bat

CALL ff
cx ***
IF ERRORLEVEL 1 START *[BUILD-ERROR]

CALL bat\oninstall.bat
