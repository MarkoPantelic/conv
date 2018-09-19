
# conv 
General purpose converter (numeral systems, weights and measures etc.)



## About:

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
	
	
	
## Author:

        Марко Пантелић (Marko Pantelić)
        marko_pantelic@mail.com

	
