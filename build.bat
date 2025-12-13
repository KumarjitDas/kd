@ECHO OFF
SETLOCAL ENABLEDELAYEDEXPANSION
CLS


@REM ========== Control switches ==========

SET "CLEAN_ALL=0"
SET "CLEAN_BUILDS=0"
SET "DEBUG_MODE=0"
SET "SHARED_LIBS=0"
SET "STATIC_LIBS=1"
SET "BUILD_TESTS=0"
SET "RUN_TESTS=0"
SET "BUILD_EXAMPLES=0"


@REM ========== Parse command-line args and set switches ==========

IF NOT "%~1"=="" (
	FOR %%A IN (%*) DO (
	    IF /I "%%A"=="clean" (
	        SET "CLEAN_BUILDS=1"
	    ) ELSE IF /I "%%A"=="clean-all" (
	        SET "CLEAN_ALL=1"
	    ) ELSE IF /I "%%A"=="debug" (
	        SET "DEBUG_MODE=0"
	    ) ELSE IF /I "%%A"=="shared" (
	        SET "SHARED_LIBS=1"
	    ) ELSE IF /I "%%A"=="tests" (
	        SET "BUILD_TESTS=1"
	    ) ELSE IF /I "%%A"=="examples" (
	        SET "BUILD_EXAMPLES=1"
	    ) ELSE IF /I "%%A"=="all" (
	        SET "BUILD_TESTS=1"
	        SET "BUILD_EXAMPLES=1"
	    ) ELSE IF /I "%%A"=="run" (
	        SET "RUN_TESTS=1"
	    )
	)
)

IF "!SHARED_LIBS!"=="1" (
	SET "STATIC_LIBS=0"
)


@REM ========== Set global flags ==========

SET LIB_NAME=kd
SET "DEBUG_FLAGS=/Zi /Od"
IF "!DEBUG_MODE!"=="0" ( SET "DEBUG_FLAGS=" )

SET "C_FLAGS=/nologo /WX /W4 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928 /permissive- /Gy"
@REM "SET NO_C_RUNTIME=/nodefaultlib"
SET "NO_C_RUNTIME="

SET "INCLUDE_DIR=include"
SET "SRC_DIR=src"
SET "BUILD_DIR=build"
SET "TESTS_DIR=tests"
SET "EXAMPLES_DIR=examples"

SET "COMMON_PLATFORM_FLAGS=%DEBUG_FLAGS% %C_FLAGS% %NO_C_RUNTIME% /I %INCLUDE_DIR%"
SET "COMMON_EXE_FLAGS=%DEBUG_FLAGS% %C_FLAGS% /Za %NO_C_RUNTIME% /I %INCLUDE_DIR%"
SET "COMMON_FLAGS=%DEBUG_FLAGS% %C_FLAGS% /Za /TC %NO_C_RUNTIME% /I %INCLUDE_DIR%"


@REM ========== Clean up ==========

IF "!CLEAN_ALL!"=="1" (
	ECHO [CLEAN] Cleaning up everything.

	IF EXIST "%BUILD_DIR%" (
		RMDIR /S /Q %BUILD_DIR%
	)
) ELSE (
	IF "!CLEAN_BUILDS!"=="1" (
		ECHO [CLEAN] Cleaning up build files.

		IF EXIST "%BUILD_DIR%" (
			DEL /Q "%BUILD_DIR%\*"
			ECHO [CLEAN] Cleaned %BUILD_DIR%.
		)

		IF EXIST "%BUILD_DIR%\%TESTS_DIR%" (
			DEL /Q "%BUILD_DIR%\%TESTS_DIR%\*"
			ECHO [CLEAN] Cleaned %BUILD_DIR%\%TESTS_DIR%.
		)

		IF EXIST "%BUILD_DIR%\%EXAMPLES_DIR%" (
			DEL /Q "%BUILD_DIR%\%EXAMPLES_DIR%\*"
			ECHO [CLEAN] Cleaned %BUILD_DIR%\%EXAMPLES_DIR%.
		)
	)
)

SET "CLEAN_OTHER_FILES=0"
IF "!CLEAN_ALL!"=="1" SET "CLEAN_OTHER_FILES=1"
IF "!CLEAN_BUILDS!"=="1" SET "CLEAN_OTHER_FILES=1"

IF "!CLEAN_OTHER_FILES!"=="1" (
	DEL /Q "*.pdb"
)


@REM ========== Create necessary dirs ==========

SET "CREATE_BUILD_DIR=0"
IF "!BUILD_TESTS!"=="1" SET "CREATE_BUILD_DIR=1"
IF "!BUILD_EXAMPLES!"=="1" SET "CREATE_BUILD_DIR=1"

IF "!CREATE_BUILD_DIR!"=="1" (
	IF NOT EXIST "%BUILD_DIR%" (
		MKDIR "%BUILD_DIR%"
		ECHO Created directory: %BUILD_DIR%
	)
)

IF "!BUILD_TESTS!"=="1" (
	IF NOT EXIST "%BUILD_DIR%\%TESTS_DIR%" (
		MKDIR "%BUILD_DIR%\%TESTS_DIR%"
		ECHO Created directory: %BUILD_DIR%\%TESTS_DIR%
	)
)

IF "!BUILD_EXAMPLES!"=="1" (
	IF NOT EXIST "%BUILD_DIR%\%EXAMPLES_DIR%" (
		MKDIR "%BUILD_DIR%\%EXAMPLES_DIR%"
		ECHO Created directory: %BUILD_DIR%\%EXAMPLES_DIR%
	)
)


@REM ========== Objects ==========

SET "INTERNAL_OBJECTS="
SET "INTERNAL_OBJECTS=!INTERNAL_OBJECTS! gen_mem_ops"

@REM Any source file that uses Windows headers
SET "PLATFORM_OBJECTS="
SET "PLATFORM_OBJECTS=!PLATFORM_OBJECTS! mem"

SET "OBJECTS="
SET "OBJECTS=!OBJECTS! mem"
SET "OBJECTS=!OBJECTS! gen_mem_ops"
@REM SET "OBJECTS=!OBJECTS! mem_ops"

SET "OUTPUT_OBJECTS="

FOR %%O IN (%INTERNAL_OBJECTS%) DO (
    SET "OUTPUT_OBJECTS=!OUTPUT_OBJECTS! %BUILD_DIR%\kdi_%%O.obj"
)

FOR %%P IN (%PLATFORM_OBJECTS%) DO (
    SET "OUTPUT_OBJECTS=!OUTPUT_OBJECTS! %BUILD_DIR%\kdi_windows_%%P.obj"
)

FOR %%O IN (%OBJECTS%) DO (
    SET "OUTPUT_OBJECTS=!OUTPUT_OBJECTS! %BUILD_DIR%\kd_%%O.obj"
)

IF "!SHARED_LIBS!"=="1" (
	ECHO [INFO] SHARED LIBS is not implemented
) ELSE (
	IF "!STATIC_LIBS!"=="1" (
		FOR %%O IN (!INTERNAL_OBJECTS!) DO (
		    SET "OBJECT_NAME=%%O"
		    ECHO [BUILD] Compiling internal object file: !SRC_DIR!\internal\!OBJECT_NAME!.c

		    CL !COMMON_FLAGS! /c "!SRC_DIR!\internal\!OBJECT_NAME!.c" /Fo:!BUILD_DIR!\kdi_!OBJECT_NAME!.obj

		    IF !ERRORLEVEl! NEQ 0 (
		        ECHO [ERROR] Failed to compile: !OBJECT_NAME!
		        EXIT /B 1
		    )

		    ECHO [BUILD] Compilation output: !OBJECT_NAME!.obj
		)

		FOR %%O IN (!PLATFORM_OBJECTS!) DO (
		    SET "OBJECT_NAME=%%O"
		    ECHO [BUILD] Compiling platform object file: !SRC_DIR!\os\windows\!OBJECT_NAME!.c

		    CL !COMMON_PLATFORM_FLAGS! /Zc:strictStrings- /c "!SRC_DIR!\os\windows\!OBJECT_NAME!.c" /Fo:!BUILD_DIR!\kdi_windows_!OBJECT_NAME!.obj

		    IF !ERRORLEVEl! NEQ 0 (
		        ECHO [ERROR] Failed to compile: !OBJECT_NAME!
		        EXIT /B 1
		    )

		    ECHO [BUILD] Compilation output: !OBJECT_NAME!.obj
		)

		FOR %%O IN (!OBJECTS!) DO (
		    SET "OBJECT_NAME=%%O"
		    ECHO [BUILD] Compiling object file: !SRC_DIR!\!OBJECT_NAME!.c

		    CL !COMMON_FLAGS! /c "!SRC_DIR!\!OBJECT_NAME!.c" /Fo:!BUILD_DIR!\kd_!OBJECT_NAME!.obj

		    IF !ERRORLEVEl! NEQ 0 (
		        ECHO [ERROR] Failed to compile: !OBJECT_NAME!
		        EXIT /B 1
		    )

		    ECHO [BUILD] Compilation output: !OBJECT_NAME!.obj
		)

		LIB /OUT:%BUILD_DIR%\%LIB_NAME%.lib !OUTPUT_OBJECTS!

	    IF %ERRORLEVEl% NEQ 0 (
	        ECHO [ERROR] Failed to build library: %LIB_NAME%
	        EXIT /B 1
	    )

	    ECHO [BUILD] Compilation output: %LIB_NAME%.lib
	)
)


@REM ========== Tests ==========

IF "!BUILD_TESTS!"=="1" (
	SET "TESTS="
	SET "TESTS=!TESTS! platform_bool_macros"
	SET "TESTS=!TESTS! platform_cstr_macros"

	SET "TESTS=!TESTS! mem\kdMemAlloc"
	SET "TESTS=!TESTS! mem\kdMemFree"
	SET "TESTS=!TESTS! mem\kdMemRealloc"

	SET "TESTS=!TESTS! gen_mem_ops\kdGenMemOpsCopy"
	SET "TESTS=!TESTS! gen_mem_ops\kdGenMemOpsCopyRegion"
	SET "TESTS=!TESTS! gen_mem_ops\kdGenMemOpsCopyRange"
	SET "TESTS=!TESTS! gen_mem_ops\kdGenMemOpsMove"
	SET "TESTS=!TESTS! gen_mem_ops\kdGenMemOpsMoveRegion"
	SET "TESTS=!TESTS! gen_mem_ops\kdGenMemOpsMoveRange"
	SET "TESTS=!TESTS! gen_mem_ops\kdGenMemOpsConcat"
	SET "TESTS=!TESTS! gen_mem_ops\kdGenMemOpsConcatRange"
	SET "TESTS=!TESTS! gen_mem_ops\kdGenMemOpsSetBytes"
	SET "TESTS=!TESTS! gen_mem_ops\kdGenMemOpsSetBytesRange"
	SET "TESTS=!TESTS! gen_mem_ops\kdGenMemOpsSetBlocks"
	SET "TESTS=!TESTS! gen_mem_ops\kdGenMemOpsSetBlocksRange"

	FOR %%T IN (!TESTS!) DO (
	    SET "TARGET_NAME=%%T"
	    ECHO [BUILD] Compiling test file: !TESTS_DIR!\!TARGET_NAME!.c

		ECHO "!TARGET_NAME!" | FIND "\" >NUL
		IF ERRORLEVEL 1 (
	    	CL !COMMON_FLAGS! /c "!TESTS_DIR!\!TARGET_NAME!.c" /Fo:!BUILD_DIR!\
			CL !COMMON_EXE_FLAGS! "!BUILD_DIR!\!TARGET_NAME!.obj" "!BUILD_DIR!\!LIB_NAME!.lib" /Fe:"!BUILD_DIR!\!TESTS_DIR!\!TARGET_NAME!.exe"
		) ELSE (
			FOR /F "tokens=1,2 delims=\\" %%A IN ("!TARGET_NAME!") DO (
				SET "TEST_SUBDIR_NAME=%%A"
				SET "TEST_TARGET_NAME=%%B"

				IF NOT EXIST "!BUILD_DIR!\!TESTS_DIR!\!TEST_SUBDIR_NAME!" (
					MKDIR "!BUILD_DIR!\!TESTS_DIR!\!TEST_SUBDIR_NAME!"
					ECHO [BUILD] Created directory: !BUILD_DIR!\!TESTS_DIR!\!TEST_SUBDIR_NAME!
				)

				CL !COMMON_FLAGS! /c "!TESTS_DIR!\!TEST_SUBDIR_NAME!\!TEST_TARGET_NAME!.c" /Fo:!BUILD_DIR!\
				CL !COMMON_EXE_FLAGS! "!BUILD_DIR!\!TEST_TARGET_NAME!.obj" "!BUILD_DIR!\!LIB_NAME!.lib" /Fe:"!BUILD_DIR!\!TESTS_DIR!\!TEST_SUBDIR_NAME!\!TEST_TARGET_NAME!.exe"
			)
		)

	    IF !ERRORLEVEl! NEQ 0 (
	        ECHO [ERROR] Failed to compile: !TARGET_NAME!
	        EXIT /B 1
	    )

	    ECHO [BUILD] Compilation output: !TARGET_NAME!.exe
	)
)


@REM ========== Run tests ==========

IF "!BUILD_TESTS!"=="1" (
	IF "!RUN_TESTS!"=="1" (
		SET /A TOTAL_TESTS=0
        FOR %%T IN (!TESTS!) DO (
            SET /A TOTAL_TESTS+=1
        )

		ECHO [TEST] Running !TOTAL_TESTS! test(s^).

		SET /A PASSED=0
        SET /A CURRENT=0

		FOR %%T IN (!TESTS!) DO (
		    SET "TEST_NAME=%%T"
		    SET /A CURRENT+=1

		    ECHO [TEST] Running test !CURRENT!: !TEST_NAME!

		    "!BUILD_DIR!\!TESTS_DIR!\!TEST_NAME!.exe"

		    IF !ERRORLEVEl! NEQ 0 (
				SET /A UNREACHED=TOTAL_TESTS-PASSED-1
				ECHO
		        ECHO [TEST] Test failed: !TEST_NAME!
		        ECHO [TEST] Total tests: !TOTAL_TESTS!
		        ECHO [TEST] Passed tests !PASSED!
		        ECHO [TEST] Unreached tests: !UNREACHED!
		        EXIT /B 1
		    )

		    SET /A PASSED+=1
		)

		ECHO [TEST] Passed: !PASSED!/!TOTAL_TESTS! test(s^).
	)
)


@REM ========== Examples ==========

IF "!BUILD_EXAMPLES!"=="1" (
	SET "EXAMPLES="
	SET "EXAMPLES=!EXAMPLES! platform_bool_macros"
	SET "EXAMPLES=!EXAMPLES! platform_cstr_macros"
	SET "EXAMPLES=!EXAMPLES! fixed_widths"
	SET "EXAMPLES=!EXAMPLES! floating_points"

	FOR %%T IN (!EXAMPLES!) DO (
	    SET "TARGET_NAME=%%T"
	    ECHO [BUILD] Compiling example file: !EXAMPLES_DIR!\!TARGET_NAME!.c

	    CL !COMMON_EXE_FLAGS! /c "!EXAMPLES_DIR!\!TARGET_NAME!.c" /Fo:!BUILD_DIR!\
	    CL !COMMON_EXE_FLAGS! "!BUILD_DIR!\!TARGET_NAME!.obj" "!BUILD_DIR!\!LIB_NAME!.lib" /Fe:"!BUILD_DIR!\!EXAMPLES_DIR!\!TARGET_NAME!.exe"

	    IF !ERRORLEVEl! NEQ 0 (
	        ECHO [ERROR] Failed to compile: !TARGET_NAME!
	        EXIT /B 1
	    )

	    ECHO [BUILD] Compilation output: !TARGET_NAME!.exe
	)
)


ENDLOCAL
