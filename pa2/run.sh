#!/bin/bash
./atpg ../sample_circuits/c$1.ckt > ../reports/c$1.report
../bin/golden_atpg ../sample_circuits/c$1.ckt > ../reports/golden2_c$1.report

diff ../reports/c$1.report ../reports/golden2_c$1.report


