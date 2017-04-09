ENTRY(_start)
phys = 0x0010000;
SECTIONS
{
  .text phys : AT(phys)
  {
    code = .;
    *(.text)
    *(.rodata)
    *(.rodata.str1.1)
    . = ALIGN(4096);
  }
  .data : AT(phys + (data - code))
  {
    data = .;
    *(.data)
    . = ALIGN(4096);
  }
  .bss : AT(phys + (bss - code))
  {
    bss = .;
    *(.bss)
    . = ALIGN(4096);
  }
  _end = .;
}
