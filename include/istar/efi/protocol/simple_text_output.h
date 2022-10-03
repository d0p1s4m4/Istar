#ifndef ISTAR_EFI_PROTOCOL_SIMPLE_TEXT_OUTPUT_H
# define ISTAR_EFI_PROTOCOL_SIMPLE_TEXT_OUTPUT_H 1

# include <istar/efi/types.h>

typedef struct efi_simple_text_output_protocol {
	EfiStatus	(*reset)(struct efi_simple_text_output_protocol *, boolean_t);
	EfiStatus	(*wprint)(struct efi_simple_text_output_protocol *, wchar_t *);
} EfiSimpleTextOutputProtocol;

#endif /* !ISTAR_EFI_PROTOCOL_SIMPLE_TEXT_OUTPUT_H */
