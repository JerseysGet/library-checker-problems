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
CLEAN=0
PROBLEMS=()
if [[ $# -eq 0 || ($# -eq 1 && ("$1" = "-c" || "$1" = "--clean")) ]]; then
    PROBLEMS+=( "datastructure/unionfind" )
    PROBLEMS+=( "datastructure/staticrmq" )
    PROBLEMS+=( "datastructure/point_add_range_sum" )
    PROBLEMS+=( "datastructure/range_affine_range_sum" )
    PROBLEMS+=( "datastructure/line_add_get_min" )
    PROBLEMS+=( "datastructure/range_kth_smallest" )
    PROBLEMS+=( "math/primality_test" )
    PROBLEMS+=( "graph/scc" )
    PROBLEMS+=( "string/enumerate_palindromes" )
    PROBLEMS+=( "math/convolution_mod" )
    PROBLEMS+=( "graph/lca" )
    PROBLEMS+=( "graph/jump_on_tree" )
    PROBLEMS+=( "math/two_sat" )
    PROBLEMS+=( "geo/static_convex_hull" )
    if [[ $# -eq 1 && ("$1" = "-c" || "$1" = "--clean") ]]; then
        CLEAN=1
    fi
else
    # Source: https://www.baeldung.com/linux/bash-parse-command-line-arguments
    VALID_ARGS=$(getopt -o c --long clean -- "$@")
    if [[ $? -ne 0 ]]; then
        exit 1;
    fi
    eval set -- "$VALID_ARGS"
    while [ : ]; do
        case "$1" in
            -c | --clean)
                CLEAN=1
                shift;
                ;;
            --)
                shift;
                PROBLEMS=( "$@" ) 
                break
                ;;
        esac
    done
fi

FAILED_LIST=()
for problem in ${PROBLEMS[@]}; do
    passed=1
    printf "${WHITE_BOLD}${SEP}[ ${problem} ]${SEP}${NC}\n"
    my_dir="$SCRIPT_DIR/mine/$problem"
    dir="$SCRIPT_DIR/$problem"
    mkdir -p "$my_dir/test"
    checker="$dir/checker"
    info_toml="$dir/info.toml"
    if [ $CLEAN -eq 1 ]; then
        $GENERATE_PY --clean "$info_toml"
        printf "\n\n"
        continue
    fi
    $GENERATE_PY "$info_toml"
    $SUBSTITUTE_PY -i "$my_dir/driver.cpp" -o "$my_dir/__tester.cpp" 2> /dev/null
    $CXX "${CXX_FLAGS[@]}" "$my_dir/__tester.cpp" -o "$my_dir/__tester.out"
    run_time=0
    for test_case in $dir/in/*; do
        base="$(basename $test_case .in)"
        printf "%s: " "$base"
        # Source: https://stackoverflow.com/a/22051517
        ts=$(date +%s%N)
        if ! ( $my_dir/__tester.out < "$dir/in/$base.in" > "$my_dir/test/$base.test" || false ) >/dev/null 2>&1; then
            passed=0
            printf "${YELLOW_BOLD}RTE${NC}\n"        
            continue
        fi
        tt=$((($(date +%s%N) - $ts)/1000000))
        if [ $tt -gt $run_time ]; then
            run_time=$tt
        fi
        printf "${WHITE_BOLD}${tt}ms, ${NC}"
        $checker "$dir/in/$base.in" "$my_dir/test/$base.test" "$dir/out/$base.out" 
        if [ $? -ne 0 ]; then
            passed=0
        fi
    done
    printf "${WHITE_BOLD}${problem} ${NC}"
    if [ $passed -eq 1 ]; then
        printf "${GREEN_BOLD}PASSED${NC} "
    else
        printf "${RED_BOLD}FAILED${NC} "
        FAILED_LIST+=( "$problem" )
    fi
    printf "in ${WHITE_BOLD}${run_time}ms${NC}"
    printf "\n\n"
    rm "$my_dir/__tester.cpp"
    rm "$my_dir/__tester.out"
done

if [ $CLEAN -eq 1 ]; then
    exit
fi

if [ ${#FAILED_LIST[@]} -eq 0 ]; then
    printf "${GREEN_BOLD}All Passed${NC}\n"
else
    printf "${WHITE_BOLD}${#FAILED_LIST[@]} failed.${NC}\n"
    for problem in ${FAILED_LIST[@]}; do
        printf "${WHITE_BOLD}${problem}${NC} ${RED_BOLD}failed${NC}\n"
    done
fi