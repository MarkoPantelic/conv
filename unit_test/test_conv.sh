#!/bin/bash

# ==================================== #
# Script to test compiled conv program #
# ==================================== #


CONV="conv"
CONV_EXE="../build/conv"
FAILED_COUNT=0
F_CALL_NUM=0

function assert 
{

	eval "${1}"
	
	if [[ $? -ne 0 ]]; then
		echo "${FUNCNAME[1]}: FAILED"
		FAILED_COUNT=$(($FAILED_COUNT+1))
	else
		echo "${FUNCNAME[1]}: valid"
	fi
}


function test_single
{
	#test single call to 'conv' executable

	local exe_stat res tname in_f out_f prec inval expected_val;
	tname=$1; in_f=$2; out_f=$3; prec=$4 inval=$5; expected_res=$6;

	echo -n "$tname: inval = $inval, expected result = $expected_res";

	res=`$CONV_EXE -i $in_f -o $out_f -p $prec -n $inval 2>&1`

	#catch possible executable error
	exe_stat=$?

	if [[ $exe_stat -ne 0 ]]; then
		echo ", error occured => $CONV returned errno $exe_stat, errstr => $res; ERROR !!!"
		exit 1;			
	fi


	echo -n ", result = $res; ";

	assert "[[ ${res} == $expected_res ]]"
}


function test_multiple 
{

	local i tname fin fout prec vals e_vals;
	tname=$1; fin=$2; fout=$3; prec=$4
	vals=("${!5}"); e_vals=("${!6}");

	len=${#vals[@]};

	for (( i=0; i<len; i++ )); do

		F_CALL_NUM=$((F_CALL_NUM+1))
		echo -n "test no. $F_CALL_NUM - "

		test_single "$tname" $fin $fout $prec ${vals[$i]} ${e_vals[$i]}

	done
}



# import test functions from files
. nsconv_test
. imperial_test
. tempconv_test



echo 'starting `conv` test...';

# run all unit_test functions (functions who's name starts with 'unit_test')
for t_func in $(declare -f | grep -o "^unit_test[_a-zA-Z]*"); do
	${t_func}
done

echo ""
echo "number of failed tests = $FAILED_COUNT"




exit 0;


