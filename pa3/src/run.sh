#!/bin/bash
EXE=./atpg
GOLDEN_EXE=../bin/golden_tdfsim
CIRPATH=../sample_circuits/
PATPATH=../tdf_patterns/
RPTPATH=../reports/

ALLCASES="17 432 499 880 1355 1908 2670 3540 5315 6288 7552"

CKT_FILE=c$1.ckt
PAT_FILE=c$1.pat

if [ $2 = 'g' ]
then
    $GOLDEN_EXE -ndet 1 -tdfsim $PATPATH$PAT_FILE $CIRPATH$CKT_FILE
else
    $EXE -tdfsim $PATPATH$PAT_FILE $CIRPATH$CKT_FILE
fi

# # Command-line
# if [ $# -eq 0 ]
# then
#     CASES=$ALLCASES
# else
#     CASES=$1
# fi

# # Run cases
# for case in $CASES
# do
#   CKT_FILE=c$case.ckt
#   RPT=c$case.report
#   GOLDEN_RPT=golden2_c$case.report
#   echo "##### $CKT_FILE BEGIN #####"
#   $EXE $CIRPATH$CKT_FILE > $RPTPATH$RPT
#   $GOLDEN_EXE $CIRPATH$CKT_FILE > $RPTPATH$GOLDEN_RPT
#   diff $RPTPATH$RPT $RPTPATH$GOLDEN_RPT
#   echo "##### $CKT_FILE END #######"
#   echo ""
#   echo "---------------------------------------------------------"
#   echo ""
# done