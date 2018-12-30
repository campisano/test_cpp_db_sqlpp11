#!/bin/bash

fn_abort()
{
    ERRCODE=$?
    echo >&2 "Error $ERRCODE executing $BASH_COMMAND on line ${BASH_LINENO[0]}"
    exit $ERRCODE
}

trap fn_abort ERR
set -o errtrace -o pipefail

fn_build()
{
    BASE_DIR=$1
    NAME=$2
    DIR=$3
    CMAKEARGS=$4
    echo -e " * \\033[1;33m${NAME}\\033[0;39m"
    mkdir "${BASE_DIR}/${DIR}/build"
    cd "${BASE_DIR}/${DIR}/build"
    cmake ${CMAKEARGS} | grep -v -- '-- Detecting C' | grep -v -- '-- Check for working C' | grep -v -- '-- Looking for '
    make
    make install
    cd "${BASE_DIR}"
    echo
}

rm -rf date sqlpp11
rm -rf src/date-2.4.1/build/ src/sqlpp11-0.57/build/ src/sqlpp11-connector-postgresql_custom/build/

PWD=`pwd`

fn_build "$PWD" "HinnantDate" "src/date-2.4.1" "-DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=11 -DCMAKE_INSTALL_MESSAGE=NEVER -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=../../../date .."

fn_build "$PWD" "sqlpp11" "src/sqlpp11-0.57" "-DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=11 -DCMAKE_INSTALL_MESSAGE=NEVER -DHinnantDate_ROOT_DIR=../../../date -DENABLE_TESTS=OFF -DCMAKE_INSTALL_PREFIX=../../../sqlpp11 .."

fn_build "$PWD" "sqlpp11-connector-postgresql" "src/sqlpp11-connector-postgresql_custom" "-DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=11 -DCMAKE_INSTALL_MESSAGE=NEVER -DHinnantDate_ROOT_DIR=../../../date -DPostgreSQL_TYPE_INCLUDE_DIR=/usr/include/postgresql -DENABLE_TESTS=OFF -DCMAKE_INSTALL_PREFIX=../../../sqlpp11 .."
