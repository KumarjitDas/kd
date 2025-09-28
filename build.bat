@ECHO OFF
SETLOCAL ENABLEDELAYEDEXPANSION


@REM ========== Control switches ==========

SET "CLEAN_ALL=0"
SET "CLEAN_BUILDS=1"
SET "DEBUG_MODE=1"
SET "SHARED_LIBS=0"
SET "STATIC_LIBS=1"
SET "BUILD_TESTS=1"
SET "RUN_TESTS=1"
SET "BUILD_EXAMPLES=0"


@REM ========== Parse command-line args and set switches ==========

IF NOT "%~1"=="" (
	FOR %%A IN (%*) DO (
	    IF /I "%%A"=="clean" (
	        SET "CLEAN_BUILDS=1"
	    ) ELSE IF /I "%%A"=="clean-all" (
	        SET "CLEAN_ALL=1"
	    ) ELSE IF /I "%%A"=="release" (
	        SET "DEBUG_MODE=0"
	    ) ELSE IF /I "%%A"=="shared" (
	        SET "SHARED_LIBS=1"
	    ) ELSE IF /I "%%A"=="build-tests" (
	        SET "BUILD_TESTS=1"
	    ) ELSE IF /I "%%A"=="build-examples" (
	        SET "BUILD_EXAMPLES=1"
	    ) ELSE IF /I "%%A"=="build-all" (
	        SET "BUILD_TESTS=1"
	        SET "BUILD_EXAMPLES=1"
	    ) ELSE IF /I "%%A"=="run-tests" (
	        SET "RUN_TESTS=1"
	    )
	)
)


@REM ========== Set global flags ==========

SET "DEBUG_FLAGS=/Zi /Od"
IF "!DEBUG_MODE!"=="0" ( SET "DEBUG_FLAGS=" )

SET "C_FLAGS=/WX /W4 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928 /permissive- /Gy"
@REM "SET NO_C_RUNTIME=/nodefaultlib"
SET "NO_C_RUNTIME="

SET "INCLUDE_DIR=src"
SET "SRC_DIR=src"
SET "BUILD_DIR=build"
SET "TESTS_DIR=tests"
SET "EXAMPLES_DIR=examples"

SET "COMMON_PLATFORM_FLAGS=%DEBUG_FLAGS% %C_FLAGS% %NO_C_RUNTIME% /I %INCLUDE_DIR% /Fo:%BUILD_DIR%\"
SET "COMMON_FLAGS=%DEBUG_FLAGS% %C_FLAGS% /Za /TC %NO_C_RUNTIME% /I %INCLUDE_DIR% /Fo:%BUILD_DIR%\"


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

@REM Any source file that uses Windows headers
SET "PLATFORM_OBJECTS="
SET "PLATFORM_OBJECTS=!PLATFORM_OBJECTS! kd_mem"

SET "OBJECTS="

IF "!SHARED_LIBS!"=="1" (
	ECHO [INFO] SHARED LIBS is not implemented
) ELSE (
	IF "!STATIC_LIBS!"=="1" (
		FOR %%O IN (!PLATFORM_OBJECTS!) DO (
		    SET "OBJECT_NAME=%%O"
		    ECHO [BUILD] Compiling object file: !SRC_DIR!\!OBJECT_NAME!.c

		    CL !COMMON_PLATFORM_FLAGS! /Zc:strictStrings- /c "!SRC_DIR!\!OBJECT_NAME!.c"

		    IF ERRORLEVEL 1 (
		        ECHO [ERROR] Failed to compile: !OBJECT_NAME!
		        EXIT /B 1
		    )

		    ECHO [BUILD] Compilation output: !OBJECT_NAME!.obj
		)

		FOR %%O IN (!OBJECTS!) DO (
		    SET "OBJECT_NAME=%%O"
		    ECHO [BUILD] Compiling object file: !SRC_DIR!\!OBJECT_NAME!.c

		    CL !COMMON_FLAGS! /c "!SRC_DIR!\!OBJECT_NAME!.c"

		    IF ERRORLEVEL 1 (
		        ECHO [ERROR] Failed to compile: !OBJECT_NAME!
		        EXIT /B 1
		    )

		    ECHO [BUILD] Compilation output: !OBJECT_NAME!.obj
		)
	)
)


@REM ========== Tests ==========

IF "!BUILD_TESTS!"=="1" (
	SET "TESTS="
	SET "TESTS=!TESTS! platform_bool_macros"
	SET "TESTS=!TESTS! platform_cstr_macros"

	FOR %%T IN (!TESTS!) DO (
	    SET "TARGET_NAME=%%T"
	    ECHO [BUILD] Compiling test file: !TESTS_DIR!\!TARGET_NAME!.c

	    CL !COMMON_FLAGS! "!TESTS_DIR!\!TARGET_NAME!.c" /Fe:"!BUILD_DIR!\!TESTS_DIR!\!TARGET_NAME!.exe"

	    IF ERRORLEVEL 1 (
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

		ECHO [TEST] Running !TOTAL_TESTS! tests.

		SET /A PASSED=0
        SET /A CURRENT=0

		FOR %%T IN (!TESTS!) DO (
		    SET "TEST_NAME=%%T"
		    SET /A CURRENT+=1

		    ECHO [TEST] Running test !CURRENT!: !TEST_NAME!

		    "!BUILD_DIR!\!TESTS_DIR!\!TEST_NAME!.exe"

		    IF ERRORLEVEL 1 (
		        ECHO [TEST] Test failed: !TEST_NAME!
		        ECHO [TEST] Passed !PASSED!/!TOTAL_TESTS! tests.
		        EXIT /B 1
		    )

		    SET /A PASSED+=1
		)

		ECHO [TEST] Passed: !PASSED!/!TOTAL_TESTS! tests.
	)
)


@REM ========== Examples ==========

IF "!BUILD_EXAMPLES!"=="1" (
	SET "EXAMPLES="
	SET "EXAMPLES=!EXAMPLES! platform_bool_macros"
	SET "EXAMPLES=!EXAMPLES! platform_cstr_macros"

	FOR %%T IN (!EXAMPLES!) DO (
	    SET "TARGET_NAME=%%T"
	    ECHO [BUILD] Compiling example file: !EXAMPLES_DIR!\!TARGET_NAME!.c

	    CL !COMMON_FLAGS! "!EXAMPLES_DIR!\!TARGET_NAME!.c" /Fe:"!BUILD_DIR!\!EXAMPLES_DIR!\!TARGET_NAME!.exe"

	    IF ERRORLEVEL 1 (
	        ECHO [ERROR] Failed to compile: !TARGET_NAME!
	        EXIT /B 1
	    )

	    ECHO [BUILD] Compilation output: !TARGET_NAME!.exe
	)
)


ENDLOCAL
