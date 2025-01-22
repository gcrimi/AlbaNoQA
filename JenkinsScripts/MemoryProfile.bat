REM -----------------------------------------------------------------------------
REM AQTime memory profiler driver script
REM -----------------------------------------------------------------------------
echo  ** memory profile started **
echo.

REM BEWARE! These directory names are  referenced in MemoryProfile.vbs script so the not change them
set ProfilingResultsDirectory=.\build\bin\Debug\MemoryAllocation\
set XMLResultsDirectory=%ProfilingResultsDirectory%\XML\
set HTMLResultsDirectory=%ProfilingResultsDirectory%\HTML\

REM delete the directory storing previous results
REM rmdir /s /q %ProfilingResultsDirectory%

REM create the directory again the directories for storing XML and HTML memory profiling results
REM mkdir %XMLResultsDirectory%
REM mkdir %HTMLResultsDirectory%
echo  creating profiling results... 

REM run the memory profile Visual Basic script
.\source\JenkinsScripts\MemoryProfile.vbs

ren .\build\bin\Debug\MemoryAllocation\XML\MemoryAllocationLog.txt %1%
echo.
echo   profiling results created successfully!
echo.
echo **  memory profile ended successfully **