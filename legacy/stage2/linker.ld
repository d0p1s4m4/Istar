
OUTPUT_FORMAT(binary)
ENTRY(_start)

SECTIONS
{
    . = 0x8000;

    .text : ALIGN(0x1000) {
        _TEXT_START_ = .;
        *(.text)
        _TEXT_END_ = .;
    }
    
    .data : ALIGN(0x1000) {
        _DATA_START_ = .;
        *(.data)
        _DATA_END_ = .;
    }
    
    .bss : ALIGN(0x1000) {
        _BSS_START_ = .;
        *(.bss)
        _BSS_END_ = .;
    }
}
