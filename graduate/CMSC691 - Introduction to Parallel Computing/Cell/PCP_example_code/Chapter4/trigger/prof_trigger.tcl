proc print_prof { arg_list } {

   # Create array from the input list
   array set arg_array $arg_list

   # Check for end of statistic collection
   if {$arg_array(rt) == 31} {
   
      # Read the SPU statistics
      array set stat_array [ mysim spu $arg_array(spu) stats export ]

      puts "Pipe dependent stall cycles: \
         $stat_array(pipe_dep_stall_cycles)"

      puts "Branch instruction count: \
         $stat_array(BR_inst_count)"   
   }
}
