proc emit_conf {} {

   # The array of environment variables
   global env

   # Identify the four events to be monitored
   simemit set "Header_Record" 1
   simemit set "Footer_Record" 1
   simemit set "Apu_Mem_Read" 1

   # Configure the event reader
   ereader expect 1
   ereader start $env(SYSTEMSIM_TOP)/Chapter4/emitter/eread [pid]
}

# Start emitters if emit specified
if { [catch {emit_conf} output] } {
   puts "Error!  emitter reader failed to start"
   puts $output
} else {
   puts "Emitter reader started!"
}


