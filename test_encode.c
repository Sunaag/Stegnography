#include "main.h"

int main(int argc,char *argv[])
{
	if(check_operation_type(argv) == e_encode)
	{
		EncodeInfo encInfo;
		uint img_size;

		// Fill with sample filenames
		encInfo.src_image_fname = argv[2];
		encInfo.secret_fname = argv[3];
		encInfo.stego_image_fname = argv[4];
		
		if(read_and_validate_encode_args(argv,&encInfo) == e_failure)
		{
			printf("ERROR: read and validate function called and files have not matched\n");
			return 1;
		}
		// Test open_files
		if (open_files(&encInfo) == e_failure)
		{
			printf("ERROR: %s function failed\n", "open_files" );
			return 1;
		}
		else
		{
			printf("SUCCESS: %s function completed\n", "open_files" );
		}

		// Test get_image_size_for_bmp
		img_size = get_image_size_for_bmp(encInfo.fptr_src_image);
		printf("INFO: Image size = %u\n", img_size);

		rewind(encInfo.fptr_src_image);

		if(copy_bmp_header(encInfo.fptr_src_image,encInfo.fptr_stego_image) == e_success)
		{
			printf("DONE\n");
		}


		if(encode_magic_string(MAGIC_STRING,&encInfo)==e_success)
		{
			printf("Magic String: ENCRYPTION AND COPYING DONE\n");
		}

		if(encode_secret_file_extn_size(encInfo.secret_fname,&encInfo) == e_success)
		{
			printf("FILE EXTENSION SIZE ENCRYPTED\n");
		}


		const char *file_extn = encInfo.secret_fname;
		while(*file_extn != '.')
		{
			file_extn++;
		}
		if(encode_secret_file_extn(file_extn, &encInfo) == e_success)
		{
			printf("FILE EXTENSION ENCRYPTED\n");
		}

		printf ("SECRET FILE SIZE: %d\n", get_file_size(encInfo.fptr_secret));
		encInfo.size_secret_file = get_file_size(encInfo.fptr_secret);

		if (encode_secret_file_size(encInfo.size_secret_file, &encInfo) == e_success)
		{
			printf ("SECRET FILE SIZE ENCRYPTED\n");
		}

		if(encode_secret_file_data(&encInfo) == e_success)
		{
			printf("SECRET FILE CONTENT ENCRYPTED\n");
		}
		if(copy_remaining_img_data(encInfo.fptr_src_image,encInfo.fptr_stego_image) == e_success)
		{
			printf("REMAINING BYTES COPIED\n");
		}
	}

	else if(check_operation_type(argv) == e_decode)
	{
		EncodeInfo decInfo;

		decInfo.stego_image_fname = argv[2];
		decInfo.decode_info_fname = "decoded_file.txt";
		decInfo.src_image_fname = "beautiful.bmp";
		decInfo.secret_fname = "secret.txt";

		if(read_and_validate_encode_args(argv,&decInfo) == e_failure)
		{
			printf("ERROR: read and validate function called and files have not matched\n");
			return 1;
		}
		// Test open_files
		if(open_decode_file(&decInfo) == e_success)
		{
			printf("STEGO IMAGE IS OPENED\n");
		}
		if(decode_magic_string(MAGIC_STRING,&decInfo)==e_success)
		{
			printf("MAGIC STRING ACQUIRED\n");
		}
		if(decode_secret_file_extn_size(decInfo.secret_fname,&decInfo)==e_success)
		{
			printf("FILE EXTENSION SIZE ACQUIRED\n");
		}
		if(decode_secret_file_extn(decInfo.secret_fname,&decInfo)==e_success)
		{
			printf("FILE EXTENSION ACQUIRED\n");
		}

		if(decode_secret_file_data(decode_secret_file_size(&decInfo),&decInfo) == e_success)
		{
			printf("SECRET FILE DATA ACQUIRED\n");
		}
	}
	return 0;
}
