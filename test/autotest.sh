#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
RESET='\033[0m' # No Color

testCommand="pytest autotest.py"

echo -e "${GREEN} Running test suite... ${RESET}"

$testCommand
