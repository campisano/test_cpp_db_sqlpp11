# CUSTOM output executable and lib files
DEFAULT_TARGET =		debug
TARGET_EXEC =			test_db
TARGET_LIB =
HEADER_EXT =			.hpp
SOURCE_EXT =			.cpp

# CUSTOM paths
INC_DIRS =			inc
INC_EXT_DIRS =			ext/sqlpp11/include ext/date/include /usr/include/postgresql
FORMAT_INC_DIRS =		inc
SRC_DIRS =			src/tdb
TEST_SRC_DIRS =			src/test
FORMAT_SRC_DIRS =		src
MAIN_SRC =			src/main.cpp
LIB_DIRS =			ext/sqlpp11/lib
ROOT_BUILD_DIR =		bin

# CUSTOM libs for different targets
RELEASE_LIBS =			sqlpp11-connector-postgresql pq
STATIC_LIBS =			$(RELEASE_LIBS)
LIBRARY_LIBS =			$(RELEASE_LIBS)
DEBUG_LIBS =			$(RELEASE_LIBS)
PROFILE_LIBS =			$(RELEASE_LIBS)
TEST_LIBS =			$(RELEASE_LIBS)

# finally, include the generic makefile
include ext/Makefile.inc
