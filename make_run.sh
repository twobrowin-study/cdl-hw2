#!/bin/bash
if [ "$(uname)" == "Linux" ]; then
  gcc -o ./main main.c errors/errors_helper.c errors/errors_helper.h token_scan/token_scan.c token_scan/token_scan.h token_scan/token_scan_helpers.c token_scan/token_scan_helpers.h syntax_analyzer/syntax_analyzer.c syntax_analyzer/syntax_analyzer.h syntax_analyzer/syntax_analyzer_helpers.c syntax_analyzer/syntax_analyzer_helpers.h
  ./main "$1"
elif [ "$(uname)" == "MINGW32_NT-10.0" ] || [ "$(uname)" == "MSYS_NT-10.0" ]; then
  mingw32-gcc -o ./main.exe main.c errors/errors_helper.c errors/errors_helper.h token_scan/token_scan.c token_scan/token_scan.h token_scan/token_scan_helpers.c token_scan/token_scan_helpers.h syntax_analyzer/syntax_analyzer.c syntax_analyzer/syntax_analyzer.h syntax_analyzer/syntax_analyzer_helpers.c syntax_analyzer/syntax_analyzer_helpers.h
  ./main.exe "$1"
fi
