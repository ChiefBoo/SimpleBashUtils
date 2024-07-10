#!/bin/bash

OK=0
FAIL=0
ITER=0
DIFF=""

# 1 flag test1
for flag in -b -n -e -s -t -v #-E -T --number-nonblank --number --squeeze-blank
do
  (( ITER++ ))
  echo --- TEST CAT $ITER ---
  ./s21_cat $flag test1.txt > s21_cat.txt
  cat $flag test1.txt > cat.txt
  DIFF="$(diff -s s21_cat.txt cat.txt)"
    if [ "$DIFF" == "Files s21_cat.txt and cat.txt are identical" ]
      then
        (( OK++ ))
    else
       (( FAIL++ ))
       echo "test1.txt flag $flag fail"
    fi
      rm s21_cat.txt cat.txt
done

#1 flag test2
for flag in -b -n -e -s -t -v #-E -T --number-nonblank --number --squeeze-blank
do
  (( ITER++ ))
  echo --- TEST CAT $ITER ---
  ./s21_cat $flag test2.txt > s21_cat.txt
  cat $flag test2.txt > cat.txt
  DIFF="$(diff -s s21_cat.txt cat.txt)"
  if [ "$DIFF" == "Files s21_cat.txt and cat.txt are identical" ]
    then
      (( OK++ ))
    else
      (( FAIL++ ))
      echo "test2.txt flag $flag fail"
    fi
      rm s21_cat.txt cat.txt
done

#2 flag test1
for flag1 in -b -n -e -s -t -v #-E -T --number-nonblank --number --squeeze-blank
do
  for flag2 in -b -n -e -s -t -v #-E -T --number-nonblank --number --squeeze-blank
  do
    if [ $flag1 != $flag2 ]
      then
        (( ITER++ ))
        echo --- TEST CAT $ITER ---
        ./s21_cat $flag1 $flag2 test1.txt > s21_cat.txt
        cat $flag1 $flag2 test1.txt > cat.txt
        DIFF="$(diff -s s21_cat.txt cat.txt)"
        if [ "$DIFF" == "Files s21_cat.txt and cat.txt are identical" ]
          then
            (( OK++ ))
          else
            (( FAIL++ ))
            echo "test1.txt flag $flag1 $flag2 fail"
        fi
          rm s21_cat.txt cat.txt
      fi
  done
done

#FEW flag test1
for flag in -bne -bes -bst -stb -bet -benst -neb -nes -ntv -veb
do
  (( ITER++ ))
  echo --- TEST CAT $ITER ---
  ./s21_cat $flag test1.txt > s21_cat.txt
  cat $flag test1.txt > cat.txt
  DIFF="$(diff -s s21_cat.txt cat.txt)"
  if [ "$DIFF" == "Files s21_cat.txt and cat.txt are identical" ]
    then
      (( OK++ ))
    else
       (( FAIL++ ))
       echo "test1.txt flag $flag fail"
    fi
      rm s21_cat.txt cat.txt
done

#FEW flag test1 test3
for flag in -bne -bes -bst -stb -bet -benst -neb -nes -ntv -veb
do
  (( ITER++ ))
  echo --- TEST CAT $ITER ---
  ./s21_cat $flag test1.txt test3.txt > s21_cat.txt
  cat $flag test1.txt test3.txt > cat.txt
  DIFF="$(diff -s s21_cat.txt cat.txt)"
  if [ "$DIFF" == "Files s21_cat.txt and cat.txt are identical" ]
    then
      (( OK++ ))
    else
       (( FAIL++ ))
       echo "test1 test3 flag $flag fail"
    fi
      rm s21_cat.txt cat.txt
done
    
echo "SUCCESS TESTS: $OK"
echo "FAIL TESTS: $FAIL"
