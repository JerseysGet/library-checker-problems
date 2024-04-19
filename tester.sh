#!/bin/bash

WHITE_BOLD='\033[1;37m'
RED_BOLD='\033[1;31m'
GREEN_BOLD='\033[1;32m'
YELLOW_BOLD='\033[1;33m'
NC='\033[0m' # No Color
SEP="――――――――――――――――――――――――――――――――――――――――――――――――――――――"

CXX="g++"
CXX_FLAGS=()
CXX_FLAGS+=( "-Wall" )
CXX_FLAGS+=( "-Wextra" )
CXX_FLAGS+=( "-Wconversion" )
CXX_FLAGS+=( "-static" )
CXX_FLAGS+=( "-DONLINE_JUDGE" )
CXX_FLAGS+=( "-O2" )
CXX_FLAGS+=( "-std=c++20" )

ulimit -s unlimited

# Source: https://stackoverflow.com/a/246128
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

GENERATE_PY="$SCRIPT_DIR/generate.py"
SUBSTITUTE_PY="$SCRIPT_DIR/substitute.py"

PROBLEMS=()
PROBLEMS+=( "datastructure/unionfind" )
PROBLEMS+=( "datastructure/staticrmq" )
PROBLEMS+=( "datastructure/point_add_range_sum" )
PROBLEMS+=( "datastructure/range_affine_range_sum" )
PROBLEMS+=( "datastructure/line_add_get_min" )

for problem in ${PROBLEMS[@]}; do
    passed=1
    printf "${WHITE_BOLD}${SEP}[ ${problem} ]${SEP}${NC}\n"
    my_dir="$SCRIPT_DIR/mine/$problem"
    dir="$SCRIPT_DIR/$problem"
    mkdir -p "$my_dir/test"
    checker="$dir/checker"
    info_toml="$dir/info.toml"
    $GENERATE_PY "$info_toml"
    $SUBSTITUTE_PY -i "$my_dir/driver.cpp" -o "$my_dir/__tester.cpp" 2> /dev/null
    $CXX "${CXX_FLAGS[@]}" "$my_dir/__tester.cpp" -o "$my_dir/__tester.out"
    for test_case in $dir/in/*; do
        base="$(basename $test_case .in)"
        printf "%s: " "$base"
        # Source: https://stackoverflow.com/a/22051517
        if ! ( $my_dir/__tester.out < "$dir/in/$base.in" > "$my_dir/test/$base.test" || false ) >/dev/null 2>&1; then
            passed=0
            printf "${YELLOW}RTE${NC}\n"        
            continue
        fi
        $checker "$dir/in/$base.in" "$my_dir/test/$base.test" "$dir/out/$base.out" 
        if [ $? -ne 0 ]; then
            passed=0
        fi
    done
    printf "${WHITE_BOLD}${problem} ${NC}"
    if [ $passed -eq 1 ]; then
        printf "${GREEN_BOLD}PASSED${NC}\n"
    else
        printf "${RED_BOLD}FAILED${NC}\n"
    fi
    printf "\n"
    rm "$my_dir/__tester.cpp"
    rm "$my_dir/__tester.out"
done