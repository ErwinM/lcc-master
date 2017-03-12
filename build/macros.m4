divert(-1)
define(`push',
`
stw   0(sp), $1
subi  sp, 1, sp
')

divert


