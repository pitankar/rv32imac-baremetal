target extended-remote localhost:3333
monitor reset halt
monitor resume
p $a0
q

