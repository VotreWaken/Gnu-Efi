#include <efi.h>
#include <efilib.h>

EFI_FILE* LoadFile(EFI_FILE* Directory, CHAR16* Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable){
	EFI_FILE* LoadedFile;

	EFI_LOADED_IMAGE_PROTOCOL* LoadedImage;
	SystemTable->BootServices->HandleProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, (void**)&LoadedImage);

	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FileSystem = NULL;
	SystemTable->BootServices->HandleProtocol(LoadedImage->DeviceHandle, &gEfiLoadedImageProtocolGuid, (void**)&LoadedImage);

	if(Directory == NULL){
		FileSystem->OpenVolume(FileSystem, &Directory);
	}

	EFI_STATUS s =Directory->Open(Directory, &LoadedFile, Path, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
	if(s != EFI_SUCCESS){
		return NULL;
	}
	return LoadedFile;
}

EFI_STATUS efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {


	InitializeLib(ImageHandle, SystemTable);

	Print(L"WAKEN HELLO WORLD \n\r");

	if(LoadFile(NULL, L"kernel.elf", ImageHandle, SystemTable)){
		Print(L"Could not load kernel \n\r");
	}
	else {
		Print(L"Kernel Loaded Successfully \n\r");
	}

	return EFI_SUCCESS; 
}
