#/bin/bash

# ==================================== #
# Script to test compiled conv program #
# ==================================== #


CONV="conv"
CONV_EXE=".././conv"
FAILED_COUNT=0


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

	local exe_stat res tname in_f out_f inval expected_val;
	tname=$1; in_f=$2; out_f=$3; inval=$4; expected_res=$5;

	echo -n "testing $tname: inval = $inval, expected result = $expected_res";

	res=`$CONV_EXE -i $in_f -o $out_f -n $inval 2>&1`

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

	local tname fin fout vals e_vals;
	tname=$1; fin=$2; fout=$3;
	vals=("${!4}"); e_vals=("${!5}");

	len=${#vals[@]};

	for (( i=0; i<len; i++ )); do

		test_single "$tname" $fin $fout ${vals[$i]} ${e_vals[$i]}

	done
}


function unit_test_dtb 
{
	local val=( 11 16 20 33 );
	local e_val=( "1011" "10000" "10100" "100001" );

	test_multiple "dec to bin" d b val[@] e_val[@]
}


function unit_test_dth 
{	
	local val=( 10 16 255 274 );
	local e_val=( "A" "10" "FF" "112" );

	test_multiple "dec to hex" d h val[@] e_val[@]
}


function unit_test_dto 
{
	local val=( 9 17 20 67);
	local e_val=( 11 21 24 103);

	test_multiple "dec to oct" d o val[@] e_val[@]
}


function unit_test_ctok
{
	local val=( 0 100 455 1000 123331);
	local e_val=( 273.15 373.15 728.15 1273.15 123604.20);

	test_multiple "celsius to kelvin" c k val[@] e_val[@]
}

function unit_test_ctof
{
	local val=( 0 20 34 599 15000);
	local e_val=( 32.00 68.00 93.20 1110.20 27032.00);

	test_multiple "celsius to fahrenheit" c f val[@] e_val[@]
}



echo 'starting `conv` test...';

# run all unit_test functions (functions who's name starts with 'unit_test')
for t_func in $(declare -f | grep -o "^unit_test[_a-zA-Z]*"); do
	${t_func}
done

echo ""
echo "number of failed tests = $FAILED_COUNT"




exit 0;


