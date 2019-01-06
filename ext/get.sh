#!/bin/bash

fn_abort()
{
    ERRCODE=$?
    echo >&2 "Error $ERRCODE executing $BASH_COMMAND on line ${BASH_LINENO[0]}"
    exit $ERRCODE
}

trap fn_abort ERR
set -o errtrace -o pipefail

fn_get()
{
    cd "$1/src"
    rm -f tmp.zip
    echo "$2"
    curl -s "$2" --output tmp.zip
    unzip -q tmp.zip
    rm -f tmp.zip
    cd "$1"
}

PWD=`pwd`
mkdir -p src

fn_get "$PWD" https://codeload.github.com/campisano/GenericMakefile/zip/master
fn_get "$PWD" https://codeload.github.com/rbock/sqlpp11/zip/0.57
fn_get "$PWD" https://codeload.github.com/HowardHinnant/date/zip/v2.4.1
fn_get "$PWD" https://codeload.github.com/matthijs/sqlpp11-connector-postgresql/zip/5e834b311484a2f59a94e555723fb579fd0d95d9

cp -a src/GenericMakefile-master/Makefile.inc .
mv src/sqlpp11-connector-postgresql-5e834b311484a2f59a94e555723fb579fd0d95d9 src/sqlpp11-connector-postgresql_5e834b3
