break main
display/i $pc
run 
while !$_exitcode
    stepi
end 
