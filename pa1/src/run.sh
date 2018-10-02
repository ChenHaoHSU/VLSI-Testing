#!/bin/bash
if [ $2 == g ]
then
    time ../bin/golden_atpg -fsim ../reports/golden_c$1.report ../sample_circuits/c$1.ckt
    echo "[golden_atpg]: c$1.ckt"
else
    time ./atpg -fsim ../reports/golden_c$1.report ../sample_circuits/c$1.ckt
    echo "[atpg]: c$1.ckt"
fi