#!/bin/bash
dirPath="./result/"$1
boundingProb=$2

if ls ${dirPath}"/prob_of_updateFreq_"* 1> /dev/null 2>&1; then
# if [[ -f ${dirPath}"/prob_of_updateFreq_"* ]]; then
    echo `rm ${dirPath}"/prob_of_updateFreq_"*".txt"`
fi
if [ -f $dirPath/updateFreq_to_dutyCycle_with_prob_$boundingProb.txt ]; then
    echo `rm ${dirPath}"/updateFreq_to_dutyCycle_with_prob_"${boundingProb}".txt"`
fi

# set variables
updateFreqency=(300000 600000 1800000 3600000 10800000 21600000 43200000 86400000 172800000)
# updateFreqency=(5 10 30 60 180 360 720 1440 2880)
dutyCycle=(0.01 0.02 0.05 0.1 0.2 0.5 1)

isReachBound=0

for i in ${updateFreqency[@]}
do
    isReachBound=0
    eval "echo $isReachBound"
    for j in ${dutyCycle[@]}
    do
        fileName=`echo $dirPath/updateFreqency_$i-dutyCycle_$j.raw`
        prob=`awk '/Average/{print $2}' $fileName`
        echo $j" "$prob >> $dirPath"/prob_of_updateFreq_"$i".txt"
        if [ $(echo " $prob < $boundingProb " | bc) -eq 0 ]; then
            if [ $isReachBound -eq 0 ]; then
                echo $i" "$j >> $dirPath"/updateFreq_to_dutyCycle_with_prob_"$boundingProb".txt"
                isReachBound=1
                eval "echo $isReachBound"
            fi
        fi
    done
    if [ $isReachBound -eq 0 ]; then
        echo $i" "~ >> $dirPath"/updateFreq_to_dutyCycle_with_prob_"$boundingProb".txt"
    fi
done
 