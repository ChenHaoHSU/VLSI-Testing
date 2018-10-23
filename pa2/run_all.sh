CASES="17 432 499 880 1355 1908 2670 3540 5315 6288 7552"

for case in $CASES
do
  echo "##### c$case BEGIN #####"
  ../run.sh $case
  echo "##### c$case END #######"
  echo ""
  echo "---------------------------------------------------------"
  echo ""
done
