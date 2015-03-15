break main
display/i $pc
run
while !$_exitcode
    stepi
    set $len = $instn_length($pc)
    p $len
end 
