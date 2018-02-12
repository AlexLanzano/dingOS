void main()
{
	char *frame_buffer = (char *)0xc00b8000;

	*frame_buffer = 'X';
	while (1){}
}
