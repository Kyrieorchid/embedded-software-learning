/*
Commands + Symbols(funtions, global or static local var...)

*/


/**/


/*describe the memory layout of the output obj file*/
SECTIONS
{
    /*location counter, has the value 0 at the start of SECTIONS */
    . = 0x10000;
    /*".text" is a output section, list corresponding input sections as follow*/
    .text : { *(.text) }
    . = 0x8000000;
    .data : { *(.data) }
    .bss : { *(.bss) }

}