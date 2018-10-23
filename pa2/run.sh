#!/bin/bash
EXE=./atpg
GOLDEN_EXE=../bin/golden_atpg
CIRPATH=../sample_circuits/
RPTPATH=../reports/

ALLCASES="17 432 499 880 1355 1908 2670 3540 5315 6288 7552"

if [ $# -eq 0 ]
then
    CASES=$ALLCASES
else
    CASES=$1
fi

for case in $CASES
do
  CKT_FILE=c$case.ckt
  RPT=c$case.report
  GOLDEN_RPT=golden2_c$case.report
  echo "##### $CKT_FILE BEGIN #####"
  $EXE $CIRPATH$CKT_FILE > $RPTPATH$RPT
  $GOLDEN_EXE $CIRPATH$CKT_FILE > $RPTPATH$GOLDEN_RPT
  diff $RPTPATH$RPT $RPTPATH$GOLDEN_RPT
  echo "##### $CKT_FILE END #######"
  echo ""
  echo "---------------------------------------------------------"
  echo ""
done