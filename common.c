#include "main.h"

OperationType check_operation_type(char *argv[])
{
	if(strcmp(argv[1],"-e") == 0)
	{
		return e_encode;
	}
	else if(strcmp(argv[1],"-d") == 0)
	{
		return e_decode;
	}
	return e_unsupported;
}


Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
	char *t;
	int i;
	int flag = 0;
	if(check_operation_type(argv) == e_encode)
	{
		flag = 0;
		for(i = 2; i < 4; i++)
		{
			t = argv[i];

			if(strcmp(argv[2],encInfo -> src_image_fname)==0)
			{
				while(*t++)
				{
//					printf(".bmp\n");
					if(*t == '.' && *(t+1) == 'b' && *(t+2) == 'm' && *(t+3) == 'p')
					{
						flag = 1;		
					}
				}
			}
			if(flag ==1 && strcmp(argv[3], encInfo -> secret_fname) == 0)
			{
					while(*t++)
					{
//						printf(".txt\n");
						if(*t == '.' && *(t+1) == 't' && *(t+2) == 'x' && *(t+3) == 't')
						{
							return e_success;
						}
					}
			}
		}
	}
	else if(check_operation_type(argv) == e_decode)
	{
		t = argv[2];
		if(strcmp(argv[2],encInfo -> stego_image_fname) == 0)
		{
			while(*t++)
			{
					if(*t == '.' && *(t+1) == 'b' && *(t+2) == 'm' && *(t+3) == 'p')
					{
						return e_success;
					}
			}
			return e_failure;
		}
	}
}
