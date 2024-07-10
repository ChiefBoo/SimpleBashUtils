#!/bin/bash

OK=0
FAIL=0
ITER=0
DIFF=""

# 1 flag test3 not flags
(( ITER++ ))
echo --- TEST GREP $ITER ---
./s21_grep limit test3.txt > s21_grep.txt
grep limit test3.txt > grep.txt
DIFF="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF" == "Files s21_grep.txt and grep.txt are identical" ]
  then
    (( OK++ ))
  else
    (( FAIL++ ))
    echo "test3.txt flag $flag fail"
  fi
    rm s21_grep.txt grep.txt

# 1 flag test3 1 pattern
for flag in -i -v -c -l -n -h -s -o
do
  (( ITER++ ))
  echo --- TEST GREP $ITER ---
  ./s21_grep $flag -e new test3.txt > s21_grep.txt
  grep $flag -e new test3.txt > grep.txt
  DIFF="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        (( OK++ ))
    else
      (( FAIL++ ))
      echo "test3.txt flag $flag fail"
    fi
      rm s21_grep.txt grep.txt
done

# 1 flag test3 2 pattern
for flag in -i -v -c -l -n -h -s -o
do
  (( ITER++ ))
  echo --- TEST GREP $ITER ---
  ./s21_grep $flag -e new -e much test3.txt > s21_grep.txt
  grep $flag -e new -e much test3.txt > grep.txt
  DIFF="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        (( OK++ ))
    else
      (( FAIL++ ))
      echo "test3.txt flag $flag fail"
    fi
      rm s21_grep.txt grep.txt
done

#2 flag test3 2 pattern
for flag1 in -i -v -c -l -n -h -s -o
do
  for flag2 in -i -v -c -l -n -h -s -o
  do
    if [ $flag1 != $flag2 ]
      then
        (( ITER++ ))
        echo --- TEST GREP $ITER ---
        ./s21_grep $flag -e new -e much test3.txt > s21_grep.txt
        grep $flag -e new -e much test3.txt > grep.txt
        DIFF="$(diff -s s21_grep.txt grep.txt)"
        if [ "$DIFF" == "Files s21_grep.txt and grep.txt are identical" ]
          then
            (( OK++ ))
          else
            (( FAIL++ ))
            echo "test3.txt flag $flag1 $flag2 fail"
        fi
          rm s21_grep.txt grep.txt
      fi
  done
done

#FEW flag test3 2 pattern
for flag in -ivc -inh -osi -nc -lo -lh -lc -ovc -ivclnhso -voi
do
  (( ITER++ ))
  echo --- TEST GREP $ITER ---
  ./s21_grep $flag -e new -e much test3.txt > s21_grep.txt
  grep $flag -e new -e much test3.txt > grep.txt
  DIFF="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF" == "Files s21_grep.txt and grep.txt are identical" ]
    then
      (( OK++ ))
    else
       (( FAIL++ ))
       echo "test3.txt flag $flag fail"
    fi
      rm s21_grep.txt grep.txt
done

#FEW flag test3 2 pattern 1 file
for flag in -ivc -inh -osi -nc -lo -lh -lc -ovc -ivclnhso -voi
do
  (( ITER++ ))
  echo --- TEST GREP $ITER ---
  ./s21_grep $flag -e new -e much -f pattern1.txt test3.txt > s21_grep.txt
  grep $flag -e new -e much -f pattern1.txt test3.txt > grep.txt
  DIFF="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF" == "Files s21_grep.txt and grep.txt are identical" ]
    then
      (( OK++ ))
    else
       (( FAIL++ ))
       echo "test3.txt flag $flag fail"
    fi
      rm s21_grep.txt grep.txt
done

#FEW flag test3 2 pattern 2 file
for flag in -ivc -inh -osi -nc -lo -lh -lc -ovc -ivclnhso -voi
do
  (( ITER++ ))
  echo --- TEST GREP $ITER ---
  ./s21_grep $flag -e new -e much -f pattern1.txt -f pattern2.txt test3.txt > s21_grep.txt
  grep $flag -e new -e much -f pattern1.txt -f pattern2.txt test3.txt > grep.txt
  DIFF="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF" == "Files s21_grep.txt and grep.txt are identical" ]
    then
      (( OK++ ))
    else
       (( FAIL++ ))
       echo "test3.txt flag $flag fail"
    fi
      rm s21_grep.txt grep.txt
done
    
echo "SUCCESS TESTS: $OK"
echo "FAIL TESTS: $FAIL"

