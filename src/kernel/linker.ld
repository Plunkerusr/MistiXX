ENTRY(start)
 
SECTIONS
{
 . = 0x00100000;

 .multiboot ALIGN(4K): {
  *(.multiboot)
 }

 . += 0xC0000000;

 _kernel_start = .;
 _kernel_text_start = .;

 .text ALIGN(4K) : AT(ADDR(.text)-0xC0000000)
 {
  *(.text)
 }

 _kernel_text_end = .;
 _kernel_rodata_start = .;
 
 /* Read-only data. */
 .rodata ALIGN(4K) : AT(ADDR(.rodata)-0xC0000000)
 {
  *(.rodata)
 }

 _kernel_rodata_end = .;
 _kernel_data_start = .;
 
 /* Read-write data (initialized) */
 .data ALIGN(4K) : AT(ADDR(.data)-0xC0000000)
 {
  start_ctors = .;
  KEEP(*( .init_array ));
  KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.* )));
  end_ctors = .;

  data = .;
  *(.data)
 }

 _kernel_data_end = .;
 _kernel_bss_start = .;
 
 /* Read-write data (uninitialized) and stack */
 .bss ALIGN(4K) : AT(ADDR(.bss)-0xC0000000)
 {
  bss = .;
  *(COMMON)
  *(.bss)
  _kernel_stack_start = .;
  *(.bootstrap_stack)
  _kernel_stack_end = .;
 }

 _kernel_bss_end = .;
 . = ALIGN(4K);
 _kernel_end = .;

 end = .;

}