#include <istar/types.h>
#include <istar/efi.h>

static EfiSystemTable *efi_system_table = NULL;
static EfiHandle *efi_handle = NULL;
static EfiBootServices *efi_boot_services = NULL;

void
efi_initialize(EfiHandle handle, EfiSystemTable *table)
{
	efi_handle = handle;
	efi_system_table = table;
}

EfiHandle *
efi_get_handle(void)
{
	return (efi_handle);
}

EfiSystemTable *
efi_get_system_table(void)
{
	return (efi_system_table);
}

EfiBootServices *
efi_get_boot_services(void)
{
	if (efi_boot_services != NULL)
	{
		return (efi_boot_services);
	}

	if (efi_system_table != NULL)
	{
		efi_boot_services = efi_system_table->boot_services;
	}

	return (efi_boot_services);
}
