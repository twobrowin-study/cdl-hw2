#!/bin/bash
gcc -o ./main main.c errors/errors_helper.c errors/errors_helper.h token_scan/token_scan.c token_scan/token_scan.h token_scan/token_scan_helpers.c token_scan/token_scan_helpers.h syntax_analyzer/syntax_analyzer.c syntax_analyzer/syntax_analyzer.h syntax_analyzer/syntax_analyzer_helpers.c syntax_analyzer/syntax_analyzer_helpers.h
if [ "$(uname)" == "Linux" ]; then
  ./main "$1"
elif [ "$(uname)" == "CYGWIN_NT-10.0" ]; then
  ./main.exe "$1"
fi
