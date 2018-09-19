
# conv 
General purpose converter (numeral systems, weights and measures etc.)



### About:

Conv converts input value to desired output value

Usage: conv [OPTION]... -i input_type -o desired_output_type [VALUE]

options:
```
-h	 --help
-l	 --printlist
-p	 --precision
-v	 --verbose
```



## Supported conversions:


	Number systems:
	---------------

	* Binary
	* Decimal
	* Octal
	* Hexadecimal 


	Systems of units of measurement:
	--------------------------------

	* Imperial system
	* SI system

	
	Temperature:
	------------

	* Celsius
	* Kelvin
	* Fahrenheit
	


## Install:

##### Necessary prerequisites:
* gcc compiler
* make

##### To install from source run:
```
make
make install
```
To change location of executable after installation (currently set to conv's source dir) set INSTALL_DIR variable in Makefile to desired install path.

##### To uninstall run:
```
make uninstall
```


## Examples:
Get list of all conversions
```
[user@machine]$ ./conv --printlist
 system          quantity                                  unit symbol
==============================================================================
 US customary    volume                                hogshead (hogshead)
 US customary    volume                              oil barrel (oil bbl)
 US customary    volume                                  barrel (bbl)
 US customary    volume                                  gallon (gal)
 US customary    volume                                   quart (qt)
...
```

Convert 30 degrees Celsius to Kelvin
```
[user@machine]$ ./conv -i C -o K -n 30
303.15
```
Convert decimal number 1234 to binary
```
[user@machine]$ ./conv -i dec -o bin -n 1234
10011010010
```



### Author:

Марко Пантелић (Marko Pantelić)
marko_pantelic@mail.com

	
