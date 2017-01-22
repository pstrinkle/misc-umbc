# Initialize the primes array
proc init {} {
   global num
   for {set i 1} {$i <= $num+1} {incr i} {  
      lappend primes 0
   }
   sieve $primes
}

# Set composite numbers equal to 1
proc sieve {primes} {
   global num
   for {set i 2} {[expr $i * $i] <= $num} {incr i} {
      if {[lindex $primes $i] == 0} {
         for {set j [expr $i * $i]} \
            {$j <= $num} {incr j $i} {
               set primes [lset primes $j 1]
         }
      }
   }
   disp $primes
}

# Print all prime numbers between 2 and num
proc disp {primes} {
   global num
   for {set i 2} {$i <= $num} {incr i} {
      if {[lindex $primes $i] != 1} {
         puts $i
      }
   }
}

# Start the main processing
set num 250
init
