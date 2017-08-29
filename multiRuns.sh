#/bin/sh

slotDuration=$1
runTime=$2

for ((i=0;i<$runTime;i=i+1))
do
    echo `./run.sh $slotDuration $i`
done
